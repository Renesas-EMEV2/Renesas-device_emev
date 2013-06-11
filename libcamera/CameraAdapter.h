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

#ifndef __CAMERA_ADAPTER_H__
#define __CAMERA_ADAPTER_H__
#include "hardware/camera.h"
#include "camera/CameraParameters.h"
//#include "CameraHardwareInterface.h"

#define FNC_ENTRY ALOGI("<<<<<<<<<<%d:Entered function %s\n", __LINE__, __FUNCTION__)
#define CAMERA_PRINT ALOGI
#define GETFRAMESTEP_DQBUFFER 0
#define GETFRAMESTEP_TRANSBUFFER 1
#define GETFRAMESTEP_QBUFFER 2
class CameraAdapter:public camera_device
{
    //The default camera parameter table
#define  PREVIEW_PIX_FORMAT "yuv420p";
#define  PREVIEW_SIZE_WIDTH 640;
#define  PREVIEW_SIZE_HEIGHT 480;
#define  PREVIEW_SIZE_VALUES "640x480";
#define  PREVIEW_FRAMERATE 30;
#define  PICTURE_SIZE_VALUES "640x480";
#define  PICTURE_SIZE_WIDTH 640;
#define  PICTURE_SIZE_HEIGHT 480;
#define  PICTURE_FORMAT "jpeg";
#define  JPEG_QUALITY "85";
#define  FOCUS_MODE "auto";
#define THREAD_DELAY_TIME 5
#define THREAD_START_WAIT_TIME 15
    enum{
        ISTATUSCONTROL_NOWIS_PREVIEW        = 0x00,
        ISTATUSCONTROL_NOWIS_TAKEPICTURE    = 0x01,
        ISTATUSCONTROL_NOWIS_RECORDING      = 0x02,
        ISTATUSCONTROL_UNKNOW               = 0xFF,
    };
    public:
    /** msgType in notifyCallback and dataCallback functions */
    enum {
        CAMERA_MSG_ERROR = 0x0001,              // notifyCallback
        CAMERA_MSG_SHUTTER = 0x0002,            // notifyCallback
        CAMERA_MSG_FOCUS = 0x0004,              // notifyCallback
        CAMERA_MSG_ZOOM = 0x0008,               // notifyCallback
        CAMERA_MSG_PREVIEW_FRAME = 0x0010,      // dataCallback
        CAMERA_MSG_VIDEO_FRAME = 0x0020,        // data_timestamp_callback
        CAMERA_MSG_POSTVIEW_FRAME = 0x0040,     // dataCallback
        CAMERA_MSG_RAW_IMAGE = 0x0080,          // dataCallback
        CAMERA_MSG_COMPRESSED_IMAGE = 0x0100,   // dataCallback
        CAMERA_MSG_RAW_IMAGE_NOTIFY = 0x0200,   // dataCallback
        // Preview frame metadata. This can be combined with
        // CAMERA_MSG_PREVIEW_FRAME in dataCallback. For example, the apps can
        // request FRAME and METADATA. Or the apps can request only FRAME or only
        // METADATA.
        CAMERA_MSG_PREVIEW_METADATA = 0x0400,   // dataCallback
        CAMERA_MSG_ALL_MSGS = 0xFFFF
    };
    CameraParameters m_CameraParameters;
    camera_notify_callback m_notify_cb;
    camera_data_callback m_data_cb;
    void *mCallbackCookie;
    camera_request_memory           mGetMemoryCB;
    camera_data_timestamp_callback m_data_cb_timestamp;
    int m_msg_type;
    bool m_mdata;
    pthread_t mThread1;
    pthread_t mThread2;
    pthread_t mThread3;
    public: //Interface that sub class must implament
    bool m_preview_started;
    struct preview_stream_ops * mPreviewWindow;
    mutable Mutex mLockm_preview_started1;
    mutable Mutex mLockm_preview_started2;
    mutable Mutex mlGetFrameAndShowFrame;
    int mStartNotUseDisplay1;
    int mStartNotUseDisplay2;

    bool mVideoRecEnabled;
    virtual int preview_fill_frame(void * img)=0;
    virtual bool get_frame_from_camera(void *x)=0;
    virtual bool getNextFrameAsYuv420_2_jpg(void *x)=0;
    virtual ~CameraAdapter(){}
    public: //CameraHAL interfaces
    CameraAdapter(int cameraid);
    //virtual void open(char * name)=0;
    virtual void get_camera_parameters(CameraParameters * CameraParameters) {
        set_default_parameters();
    }
    int camera_set_preview_window(struct camera_device * device,
            struct preview_stream_ops *window);
    void camera_set_callbacks(struct camera_device * device,
            camera_notify_callback notify_cb,
            camera_data_callback data_cb,
            camera_data_timestamp_callback data_cb_timestamp,
            camera_request_memory get_memory,
            void *user);
    void camera_enable_msg_type(struct camera_device * device, int32_t msg_type);
    void camera_disable_msg_type(struct camera_device * device, int32_t msg_type);
    int camera_msg_type_enabled(struct camera_device * device, int32_t msg_type);
    virtual int camera_start_preview(struct camera_device * device);
    virtual void camera_stop_preview(struct camera_device * device);
    int camera_preview_enabled(struct camera_device * device);
    int camera_store_meta_data_in_buffers(struct camera_device * device, int enable);
    int camera_start_recording(struct camera_device * device);
    void camera_stop_recording(struct camera_device * device);
    int camera_recording_enabled(struct camera_device * device);
    void camera_release_recording_frame(struct camera_device * device, const void *opaque);
    int camera_auto_focus(struct camera_device * device);
    int camera_cancel_auto_focus(struct camera_device * device);
    int camera_take_picture(struct camera_device * device);
    int camera_cancel_picture(struct camera_device * device);
    int camera_set_parameters(struct camera_device * device, const char *params);
    char* camera_get_parameters(struct camera_device * device);
    void camera_put_parameters(struct camera_device *device, char *parms);
    int camera_send_command(struct camera_device * device, int32_t cmd, int32_t arg1, int32_t arg2);
    void camera_release(struct camera_device * device);
    int camera_dump(struct camera_device * device, int fd);

    public: //Internal functions

    void * yuvframe;
    nsecs_t mCurFrameTimestamp;
    bool fill_previewWindow(void);
    static void * pictureThreadEntry (void* cookie);
    void * pictureThreadExe(void);
    static void * poll_thread_entry(void* cookie);
    void * poll_thread(void);
    static void * display_thread_entry(void * cookie);
    void * display_thread(void);
    virtual void set_default_parameters(void);
    void WaitUntilDisplayAndPollThreadIsRunning();
    void WaitUntilDisplayAndPollThreadIsStopped();
    int iStatusControl;
    bool poll_thread_running;
    bool display_thread_running;
};
#endif /* __CAMERA_ADAPTER_H__ */
