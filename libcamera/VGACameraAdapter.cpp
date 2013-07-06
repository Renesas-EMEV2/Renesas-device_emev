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
#include <sys/mman.h>
#include <ui/GraphicBufferMapper.h>
#include "hwcomposer.h"

using namespace android;

#include "camera/CameraParameters.h"
#include "VGACameraAdapter.h"

/*--------------------- Function Declare: -----------------*/
void cvt_420p_to_rgb565(int width, int height, const unsigned char *src, unsigned short *dst);
// overload PREVIEW operation::<<
int VGACameraAdapter::camera_start_preview(struct camera_device * device)
{
    iCurrentIndex=-1;
    SetFormat();
    RequestBuf();
    MapBuf();
    StartPreviewThreads();
    StartStreaming();
    return 0;
}

void VGACameraAdapter::camera_stop_preview(struct camera_device * device)
{
    StopStreaming();
    StopPreviewThreads();
    UnmapBuf();
    UnRequestBuf();
}

// overload PREVIEW operation::>>
//Open Close flow::<<
void VGACameraAdapter::OpenStepByStep(void)
{
    OpenDevice();
};

void VGACameraAdapter::CloseStepByStep(void)
{
    CloseDevice();
};

//Open Close flow::>>

//RequestBuf operation::<<
int VGACameraAdapter::RequestBuf(void)
{
    const char *device=CAMDEVICE;
    int ret = 0;
    struct v4l2_requestbuffers rb;
    rb.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    rb.memory = V4L2_MEMORY_MMAP;
    rb.count = NB_BUFFER;
    if(true == m_fdIsOpen) {
        ret = ioctl(m_fd, VIDIOC_REQBUFS, &rb);
        if (ret < 0) {
            ALOGE("Init: VIDIOC_REQBUFS failed: %s", strerror(errno));
            return ret;
        }
    }
    else {
        ALOGD("File is Closed,ret = -1;%s",__FUNCTION__);
        return -1;
    }
    return 0;
}

int VGACameraAdapter::UnRequestBuf(void)
{
    return 0;
}

//RequestBuf operation::>>
int VGACameraAdapter::SetFormat(void)
{
    int ret=0;
    struct v4l2_format mFmt;
    mFmt.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;
    mFmt.fmt.pix.width = 640;
    mFmt.fmt.pix.height= 480;
    mFmt.fmt.pix.pixelformat=V4L2_PIX_FMT_YUV420;
    ret = ioctl(m_fd, VIDIOC_S_FMT, &mFmt);
    return  ret;
}

int VGACameraAdapter::GetFormat()
{
    return 0;
}

//Mappping Buffer from kernel operation::<<
int VGACameraAdapter::MapBuf(void)
{
    const char *device=CAMDEVICE;
    int ret;
    struct v4l2_buffer buf;
    fd_set fds;
    iCurrentIndex=0;
    for (int i = 0; i < NB_BUFFER; i++) {
        memset (&buf, 0, sizeof (struct v4l2_buffer));
        buf.index = i;
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        if(true == m_fdIsOpen) {
            ret = ioctl (m_fd, VIDIOC_QUERYBUF, &buf);
            if (ret < 0) {
                ALOGE("MapBuf: Unable to query buffer-index=%d (%s)", i,strerror(errno));
                return ret;
            }
            imemlength=buf.length;
            mem[i] = mmap (0, buf.length,PROT_READ|PROT_WRITE,MAP_SHARED,m_fd,buf.m.offset);
            if (mem[i] == MAP_FAILED) {
                ALOGE("MapBuf: Unable to map buffer");
                return -1;
            }
            mFrameIndex[i].iIndex = i;
            mFrameIndex[i].p = (unsigned char *)mem[i];
            ret = ioctl(m_fd, VIDIOC_QBUF, &buf);
            if (ret < 0) {
                ALOGE("Init: VIDIOC_QBUF Failed(%s)",strerror(errno));
                return -1;
            }
        }
        else {
            ALOGD("File is Closed,ret = -1;%s",__FUNCTION__);
            return -1;
        }

    }
    return 0;
};

int VGACameraAdapter::UnmapBuf(void)
{
    int ret = 0;
    for (int i = 0; i < 4; i++) {
        ret = munmap(mem[i], imemlength);
        if (ret < 0) {
            ALOGE("v4l2CloseBuf Unmap failed");
            return ret;
        }
    }
    ALOGD("UnmapBuf success;");
    return 0;
}

//Mappping Buffer from kernel operation::>>
int VGACameraAdapter::StartPreviewThreads()
{
    CameraAdapter::camera_start_preview(NULL);// Start Preview threads.
    ALOGI("WaitUntilDisplayAndPollThreadIsRunning...");
    WaitUntilDisplayAndPollThreadIsRunning();
    ALOGI("Threads is Running.");
    return 0;
}

int VGACameraAdapter::StopPreviewThreads()
{
    ALOGI("WaitUntilDisplayAndPollThreadIsStopped...");
    CameraAdapter::camera_stop_preview(NULL);//Stop threads.
    WaitUntilDisplayAndPollThreadIsStopped();
    ALOGI("Threads is Stopped.");
    return 0;
}

//Streaming ctrl operation::<<
int VGACameraAdapter::StopStreaming (void)
{
    int ret = 0;
    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if(true == m_fdIsOpen) {
        ret = ioctl (m_fd, VIDIOC_STREAMOFF, &type);
        if (ret < 0) {
            ALOGE("StopStreaming: Unable to stop capture: %s", strerror(errno));
            return ret;
        }
        ALOGV("V4L2Camera::v4l2StopStreaming OK");
    }
    else {
        ALOGD("File is Closed,ret = -1;%s",__FUNCTION__);
        return -1;
    }
    return 0;
}

int VGACameraAdapter::StartStreaming ()
{
    enum v4l2_buf_type type;
    int ret=0;
    ALOGI("V4L2Camera::StartStreaming");
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ALOGI("%d,%d",m_fd,V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY);
    if(true == m_fdIsOpen) {
        enum v4l2_buf_type *tmp;
        tmp = new(enum v4l2_buf_type);
        *tmp = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        ret = ioctl (m_fd, VIDIOC_STREAMON, tmp);
        memcpy(&type,tmp,sizeof(enum v4l2_buf_type));
        delete(tmp);
        if(ret<0) {
            return -1;
        }
        if (ret < 0) {
            ALOGE("StartStreaming: Unable to start capture: %s", strerror(errno));
            return ret;
        }
        else {
            ALOGI("StartStreaming: SUCCESS", strerror(errno));}
    }
    else {
        ALOGD("File is Closed,ret = -1;%s",__FUNCTION__);
        return -1;
    }
    return 0;
}

//Streaming ctrl operation::>>
bool VGACameraAdapter::getNextFrameAsYuv420_2_jpg(void *x)
{
    x = (void *)currentYUV420FRame;
    return true;
}

//Open Close Camera operation:: <<
void VGACameraAdapter::OpenDevice(){
    //TODO: add mult camera:
    const char *device = CAMDEVICE;
    m_fdIsOpen=false;
    if ((m_fd = open(device, O_RDWR)) == -1) {
        ALOGE("ERROR opening V4L interface: %s", strerror(errno));
        while(1);
    }
    else {
        ALOGD("opening V4L interface OK : %s", strerror(errno));
        m_fdIsOpen=true;
    }
};

void VGACameraAdapter::CloseDevice(){
    close (m_fd);
    m_fdIsOpen=false;
};

//Open Close Camera operation:: >>
//Camera Picture operation:<<
bool VGACameraAdapter::get_frame_from_camera(void * x)
{
    struct v4l2_buffer buf;
    static int i=0,previousIndex;
    static nsecs_t mOldFrameTimestamp;
    static long int iii=0,jjj=0;
    if(true == m_fdIsOpen) {
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        if (ioctl(m_fd, VIDIOC_DQBUF, &buf) < 0) {
            ALOGE("Poll: VIDIOC_DQBUF Failed err=%s,mfd=%d", strerror(errno),m_fd);
            return false;
        }
        OffsetAddr=buf.m.offset;
        previousIndex = iCurrentIndex;
        {
            iCurrentIndex = buf.index;
            Mutex::Autolock lock3(mlGetFrameAndShowFrame);
        }

        usleep(30000);
        static int i=10;
        mCurFrameTimestamp=systemTime();
        if (camera_msg_type_enabled(NULL,CAMERA_MSG_VIDEO_FRAME) && mVideoRecEnabled==true) {
            if(i!=0) {
                i--;
                //ALOGD("i = %d",i);
            }
            else {
                camera_memory_t* cam_buff = mGetMemoryCB(-1, 640*480*3/2, 1, NULL);
                if (NULL != cam_buff && NULL != cam_buff->data) {
                    memcpy(cam_buff->data, mem[iCurrentIndex], 640*480*3/2);
                    m_data_cb_timestamp(mCurFrameTimestamp, CAMERA_MSG_VIDEO_FRAME,cam_buff, 0, mCallbackCookie);
                    ALOGD("(%lld)(%llx)[%p][%d]",mCurFrameTimestamp,mOldFrameTimestamp,cam_buff->data,cam_buff->size);
                    cam_buff->release(cam_buff); // star add
                }
                else {
                    ALOGE("%s: Memory failure in CAMERA_MSG_VIDEO_FRAME", __FUNCTION__);
                }
            }
        }
        mOldFrameTimestamp = mCurFrameTimestamp;
        if(previousIndex!=-1) {
            buf.index=previousIndex;
            if (ioctl(m_fd, VIDIOC_QBUF, &buf)< 0) {
                ALOGE("Poll: VIDIOC_QBUF Failed(%s)",strerror(errno));
                return false;
            }
        }
    }
    else {
        ALOGD("File is Closed,ret = -1;%s",__FUNCTION__);
        return -1;
    }
    return true;
}

int VGACameraAdapter::preview_fill_frame(void * img)
{
    static int i=0;
    Mutex::Autolock lock3(mlGetFrameAndShowFrame);
    if(i!=iCurrentIndex) {
        if((mem[iCurrentIndex]==NULL)||(img==NULL)) {
            return -1;
        }
        else {
            cvt_420p_to_rgb565(640,480,(unsigned char *)mem[iCurrentIndex],(unsigned short *)img);
            yuvframe = mem[iCurrentIndex];
        }
    }
    else {
        return -1;// cancel buffer
    }
    i=iCurrentIndex;
    return 0;
}

//Camera Picture operation:>>
// <<
VGACameraAdapter::VGACameraAdapter(int cameraid):CameraAdapter(cameraid)
{
    OpenStepByStep();
}

VGACameraAdapter::~VGACameraAdapter(void)
{
    CloseStepByStep();
}

//>>
///**********************************************************
void cvt_420p_to_rgb565(int width, int height, const unsigned char *src, unsigned short *dst)
{
    int line, col, linewidth;
    int y, u, v, yy, vr, ug, vg, ub;
    int r, g, b;
    const unsigned char *py, *pu, *pv;
    if(src==NULL) return;
    if(dst==NULL) return;
    linewidth = width >> 1;
    py = src;
    pu = py + (width * height);
    pv = pu + (width * height) / 4;
    y = *py++;
    yy = y << 8;
    u = *pu - 128;
    ug = 88 * u;
    ub = 454 * u;
    v = *pv - 128;
    vg = 183 * v;
    vr = 359 * v;
    for (line = 0; line < height; line++) {
        for (col = 0; col < width; col++) {
            r = (yy + vr) >> 8;
            g = (yy - ug - vg) >> 8;
            b = (yy + ub ) >> 8;
            if (r < 0) r = 0;
            if (r > 255) r = 255;
            if (g < 0) g = 0;
            if (g > 255) g = 255;
            if (b < 0) b = 0;
            if (b > 255) b = 255;
            *dst++ = (((unsigned short)r>>3)<<11) | (((unsigned short)g>>2)<<5) | (((unsigned short)b>>3)<<0);
            y = *py++;
            yy = y << 8;
            if (col & 1) {
                pu++;
                pv++;
                u = *pu - 128;
                ug = 88 * u;
                ub = 454 * u;
                v = *pv - 128;
                vg = 183 * v;
                vr = 359 * v;
            }
        }
        if ((line & 1) == 0) {
            pu -= linewidth;
            pv -= linewidth;
        }
    }
}

