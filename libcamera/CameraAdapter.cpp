/*
 * Copyright (C) Renesas Electronics 
 *   http://www.renesas.com/
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <utils/Log.h>
#include <linux/videodev2.h>
#include <utils/threads.h>
#include <pthread.h>
#include "hwcomposer.h"
#include <sys/mman.h>

using namespace android;

#include "camera/CameraParameters.h"
#include <hardware/camera.h>
#include <ui/Rect.h>
#include <ui/GraphicBufferMapper.h>
#include "CameraAdapter.h"
#include "JpegCompressor.h"
#define LOGN ALOGI("FUNC %s,Line%d,%s\n", __FUNCTION__,__LINE__,__TIME__);

CameraAdapter::CameraAdapter(int cameraid)
{
    int rv = 0;
    FNC_ENTRY;
    CAMERA_PRINT("camera_device open");
    m_msg_type=0;
    m_preview_started=m_mdata=false;
    iStatusControl=ISTATUSCONTROL_UNKNOW;
    poll_thread_running=display_thread_running=false;
    mVideoRecEnabled=false;
    //Init default camera pametrators
    set_default_parameters();
}

int CameraAdapter::camera_set_preview_window(struct camera_device * device, struct preview_stream_ops *window)
{
    FNC_ENTRY;
    if(window!=NULL) {
        mPreviewWindow=window;
        mPreviewWindow->set_buffers_geometry(window,640,480,4);
    }
    else {
        mPreviewWindow=0;
        return -1;
    }
    return 0;
}

void CameraAdapter::camera_set_callbacks(struct camera_device * device,
        camera_notify_callback notify_cb,
        camera_data_callback data_cb,
        camera_data_timestamp_callback data_cb_timestamp,
        camera_request_memory get_memory,
        void *user)
{
    FNC_ENTRY;
    CAMERA_PRINT("notify_cb=%p, data_cb=%p, data_cb_timestamp=%p", notify_cb, data_cb, data_cb_timestamp);
    m_notify_cb = notify_cb;
    m_data_cb = data_cb;
    m_data_cb_timestamp = data_cb_timestamp;
    mGetMemoryCB =get_memory;
    mCallbackCookie = user;
}

void CameraAdapter::camera_enable_msg_type(struct camera_device * device, int32_t msg_type)
{
    FNC_ENTRY;
    CAMERA_PRINT("msg_type=0x%08x", msg_type);
    m_msg_type |= msg_type;
}

void CameraAdapter::camera_disable_msg_type(struct camera_device * device, int32_t msg_type)
{
    FNC_ENTRY;
    CAMERA_PRINT("msg_type=0x%08x", msg_type);
    m_msg_type &= ~msg_type;
}

int CameraAdapter::camera_msg_type_enabled(struct camera_device * device, int32_t msg_type)
{
    //FNC_ENTRY;
    return (m_msg_type & msg_type);
}

int CameraAdapter::camera_take_picture(struct camera_device * device)
{
    FNC_ENTRY;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&mThread3, &attr, pictureThreadEntry,this);
    iStatusControl=ISTATUSCONTROL_NOWIS_TAKEPICTURE;
    return 0;
}

int CameraAdapter::camera_start_preview(struct camera_device * device)
{
    FNC_ENTRY;
    mStartNotUseDisplay1=THREAD_START_WAIT_TIME;
    mStartNotUseDisplay2=THREAD_START_WAIT_TIME;
    m_preview_started=true;
    pthread_attr_t attr1; //Create Thread 1
    pthread_attr_init(&attr1);
    pthread_attr_setdetachstate(&attr1, PTHREAD_CREATE_JOINABLE);
    pthread_create(&mThread1, &attr1, display_thread_entry,this);
    pthread_attr_t attr2; //Create Thread 2
    pthread_attr_init(&attr2);
    pthread_attr_setdetachstate(&attr2, PTHREAD_CREATE_JOINABLE);
    pthread_create(&mThread2, &attr2, poll_thread_entry,this);
    iStatusControl=ISTATUSCONTROL_NOWIS_PREVIEW;
    return 0;
}

void CameraAdapter::camera_stop_preview(struct camera_device * device)
{
    FNC_ENTRY;
    m_preview_started=false;
    Mutex::Autolock lock1(mLockm_preview_started1);
    Mutex::Autolock lock2(mLockm_preview_started2);
    sleep(1);
}

int CameraAdapter::camera_preview_enabled(struct camera_device * device)
{
    FNC_ENTRY;
    return m_preview_started;
}

int CameraAdapter::camera_store_meta_data_in_buffers(struct camera_device * device, int enable)
{
    FNC_ENTRY;
    m_mdata=(enable==0);
    return 0;
}

int CameraAdapter::camera_start_recording(struct camera_device * device)
{
    FNC_ENTRY;
    m_preview_started = false;
    camera_stop_preview(device);

    m_preview_started = true;
    camera_start_preview(device);
    mVideoRecEnabled=true;

    return 0;
}

void CameraAdapter::camera_stop_recording(struct camera_device * device)
{
    FNC_ENTRY;
    mVideoRecEnabled=false;
}

int CameraAdapter::camera_recording_enabled(struct camera_device * device)
{
    FNC_ENTRY;
    return mVideoRecEnabled;
}

void CameraAdapter::camera_release_recording_frame(struct camera_device * device,
        const void *opaque)
{
    FNC_ENTRY;
}

int CameraAdapter::camera_auto_focus(struct camera_device * device)
{
    FNC_ENTRY;
    return 0;
}

int CameraAdapter::camera_cancel_auto_focus(struct camera_device * device)
{
    FNC_ENTRY;
    return 0;
}

int CameraAdapter::camera_cancel_picture(struct camera_device * device)
{
    FNC_ENTRY;
    return 0;
}

int CameraAdapter::camera_set_parameters(struct camera_device * device, const char *params)
{
    FNC_ENTRY;
    return 0;
}

char* CameraAdapter::camera_get_parameters(struct camera_device * device)
{
    String8 params_str8;
    char* params_string;
    mStartNotUseDisplay1=THREAD_START_WAIT_TIME;
    mStartNotUseDisplay2=THREAD_START_WAIT_TIME;
    CameraParameters mParams = m_CameraParameters;
    FNC_ENTRY;
    params_str8 = mParams.flatten();
    params_string = (char*) malloc(sizeof(char) * (params_str8.length()+1));
    strcpy(params_string, params_str8.string());
    CAMERA_PRINT("parameter: %s", params_string);
    return params_string;
}

void CameraAdapter::camera_put_parameters(struct camera_device *device, char *parms)
{
    FNC_ENTRY;
    mStartNotUseDisplay1=THREAD_START_WAIT_TIME;
    mStartNotUseDisplay2=THREAD_START_WAIT_TIME;
    CAMERA_PRINT("parms: %s", parms);
}

int CameraAdapter::camera_send_command(struct camera_device * device,
        int32_t cmd, int32_t arg1, int32_t arg2)
{
    FNC_ENTRY;
    return 0;
}

void CameraAdapter::camera_release(struct camera_device * device)
{
    FNC_ENTRY;
}

int CameraAdapter::camera_dump(struct camera_device * device, int fd)
{
    FNC_ENTRY;
    return 0;
}

bool CameraAdapter::fill_previewWindow(void)
{
    int res=0;
    if(mPreviewWindow == NULL){
        return true;
    };

    //res = mPreviewWindow->set_buffer_count(mPreviewWindow, 3);
    if(res != NO_ERROR) {
        ALOGD("%d: Failed %d", __LINE__, res);
        return false;
    }
    buffer_handle_t* buffer = NULL;
    int stride = 0;
    res = mPreviewWindow->dequeue_buffer(mPreviewWindow, &buffer, &stride);
    if (res != NO_ERROR || buffer == NULL) {
        ALOGE("%s: Unable to dequeue preview window buffer: %d -> %s",__FUNCTION__, -res, strerror(-res));
        return false;
    }
    res = mPreviewWindow->lock_buffer(mPreviewWindow, buffer);
    if (res != NO_ERROR) {
        ALOGE("%s: Unable to lock preview window buffer: %d -> %s",__FUNCTION__, -res, strerror(-res));
        mPreviewWindow->cancel_buffer(mPreviewWindow, buffer);
        return false;
    }

    void* img = NULL;
    const Rect rect(640, 480);
    GraphicBufferMapper& grbuffer_mapper(GraphicBufferMapper::get());
    res = grbuffer_mapper.lock(*buffer, GRALLOC_USAGE_SW_WRITE_OFTEN, rect, &img);
    if (res != NO_ERROR) {
        ALOGE("%s: grbuffer_mapper.lock failure: %d -> %s",__FUNCTION__, res, strerror(res));
        mPreviewWindow->cancel_buffer(mPreviewWindow, buffer);
        return false;
    }
    res=preview_fill_frame(img);

    if(img!=NULL) {
        if (res == NO_ERROR) {
            // Show it.usleep(THREAD_DELAY_TIME);
            mPreviewWindow->enqueue_buffer(mPreviewWindow, buffer);
        } else {
            mPreviewWindow->cancel_buffer(mPreviewWindow, buffer);
        }
    }
    grbuffer_mapper.unlock(*buffer);
    return true;
}
void convert_yuv420p_to_yuv420sp(unsigned char *InBuff,
        unsigned char *OutBuff,
        int width, int height)
{
    unsigned char *pBuffer=NULL;
    unsigned char *pTmp=NULL;
    unsigned int *pCbCr=NULL;
    int i,idx,pixels;
    pixels = width * height;
    pBuffer = (unsigned char *)malloc(pixels);
    memcpy(pBuffer, InBuff, (size_t)pixels);
    memcpy(OutBuff, pBuffer, (size_t)pixels);
    memcpy(pBuffer, InBuff + pixels, (size_t)pixels/4);//Y
    pTmp = pBuffer;
    for (idx = 0; idx <  (pixels/2); idx+=2) {
        memcpy(OutBuff+pixels+1+idx, pTmp++, (size_t)1);//Cb
    }
    memcpy(pBuffer, InBuff + pixels*5/4, (size_t)pixels/4);
    pTmp = pBuffer;
    for (idx = 0;idx <(pixels/2); idx+=2) {
        memcpy(OutBuff + pixels+idx, pTmp++, (size_t)1);//Cr
    }
    free(pBuffer);
    return;
}

void CameraAdapter::WaitUntilDisplayAndPollThreadIsRunning(void)
{
    while((display_thread_running==false)||(poll_thread_running==false)) {
        m_preview_started=true;
        usleep(THREAD_DELAY_TIME);
    }
}

void CameraAdapter::WaitUntilDisplayAndPollThreadIsStopped()
{
    while((display_thread_running==true)||(poll_thread_running==true)) {
        m_preview_started=false;
        usleep(THREAD_DELAY_TIME);
    }
}

//3 Lock Setting>>
//3 Thread Entry Functions:<<
void * CameraAdapter::pictureThreadEntry(void* cookie)
{
    CameraAdapter * camera = reinterpret_cast<CameraAdapter*>(cookie);
    return camera->pictureThreadExe();
}

void * CameraAdapter::poll_thread_entry(void* cookie)
{
    CameraAdapter * camera = reinterpret_cast<CameraAdapter*>(cookie);
    return camera->poll_thread();
}

void * CameraAdapter::display_thread_entry(void * cookie) 
{
    CameraAdapter * camera = reinterpret_cast<CameraAdapter*>(cookie);
    return camera->display_thread();
}

//3 >>
//3 Thread Functions:<<
void * CameraAdapter::poll_thread(void)
{
    void *img=NULL;
    while(true) {
        Mutex::Autolock lock2(mLockm_preview_started2);
        poll_thread_running = true;
        if(!m_preview_started) {
            poll_thread_running = false;
            ALOGD("poll_thread_running = false;");
            return NULL;
        }
        if(mStartNotUseDisplay2!=0) {
            mStartNotUseDisplay2--;
        }
        else {
            get_frame_from_camera(img);
        }
        usleep(THREAD_DELAY_TIME);
    }
    poll_thread_running = false;
    return NULL;
}
void * CameraAdapter::display_thread(void)
{
    void *img=NULL;
    while(true) {
        Mutex::Autolock lock1(mLockm_preview_started1);
        display_thread_running = true;
        if(!m_preview_started) {
            display_thread_running = false;
            ALOGD("display_thread_running = false;%d",m_preview_started);
            return NULL;
        }
        if(mStartNotUseDisplay1!=0) {
            mStartNotUseDisplay1--;
        }
        else {
            fill_previewWindow();
        }
        usleep(THREAD_DELAY_TIME);
    }
    display_thread_running = false;
    return NULL;
}
void * CameraAdapter::pictureThreadExe()
{
    ALOGD("%s, taking photo begin", __FUNCTION__);
    if (camera_msg_type_enabled(NULL,CAMERA_MSG_COMPRESSED_IMAGE)) {
        void *yuv420sp;
        NV21JpegCompressor compressor;
        getNextFrameAsYuv420_2_jpg(yuvframe);
        yuv420sp=malloc(640*480*3/2);
        memcpy(yuv420sp,yuvframe,640*480*3/2);
        convert_yuv420p_to_yuv420sp((unsigned char*)yuvframe,
                (unsigned char*)yuv420sp,640,480);
        status_t res=compressor.compressRawImage(yuv420sp, 640,480,75);
        if (res == 0) {
            camera_memory_t* jpeg_buff =
                mGetMemoryCB(-1, compressor.getCompressedSize(), 1, NULL);
            if (NULL != jpeg_buff && NULL != jpeg_buff->data) {
                compressor.getCompressedImage(jpeg_buff->data);
                m_data_cb(CAMERA_MSG_COMPRESSED_IMAGE, jpeg_buff, 0, NULL, mCallbackCookie);
                jpeg_buff->release(jpeg_buff);
            } else {ALOGE("%s: Memory failure in CAMERA_MSG_COMPRESSED_IMAGE", __FUNCTION__);}
        } else {ALOGE("%s: Compression failure in CAMERA_MSG_COMPRESSED_IMAGE", __FUNCTION__);}
    }
    return NULL;
}

//3 Thread Functions>>
void CameraAdapter::set_default_parameters(void)
{
    m_CameraParameters.setPreviewFormat("yuv420sp");
    m_CameraParameters.set("preview-size-values", "640x480");
    m_CameraParameters.setPreviewSize(640, 480);
    m_CameraParameters.setPreviewFrameRate(30);
    m_CameraParameters.set("picture-size-values", "640x480");
    m_CameraParameters.set("video-frame-format", CameraParameters::PIXEL_FORMAT_YUV420P);
    m_CameraParameters.set(CameraParameters::KEY_SUPPORTED_PREVIEW_FRAME_RATES, "30");
    m_CameraParameters.set(CameraParameters::KEY_PREVIEW_FPS_RANGE, "5000,60000");  // add temp for CTS
    m_CameraParameters.set(CameraParameters::KEY_SUPPORTED_PREVIEW_FPS_RANGE, "(5000,60000)");// add temp for CTS
    m_CameraParameters.setPictureSize(640, 480);
    m_CameraParameters.setPictureFormat("jpeg");
    m_CameraParameters.set("jpeg-quality", "85");
    m_CameraParameters.set("focus-mode", "infinity");
}
