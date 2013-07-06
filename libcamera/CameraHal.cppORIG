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
#include "ui/Rect.h"
#include "ui/GraphicBufferMapper.h"
#include "hardware/camera.h"
#include "camera/CameraParameters.h"
using namespace android;

#include "CameraAdapter.h"
//=========Customize area====================
#include "FakeCameraAdapter.h"
#include "VGACameraAdapter.h"
//=========End of Customeize area============

//#include <sys/stat.h>
//#include <sys/mman.h>
//#include <utils/threads.h>
//#include <utils/threads.h>
//#include "binder/MemoryBase.h"
//#include "binder/MemoryHeapBase.h"

using namespace android;

#define FNC_ENTRY ALOGI("<<<<<<<<<<%d:Entered function %s\n", __LINE__, __FUNCTION__)

int get_number_of_cameras(void)
{
    FNC_ENTRY;
    //=========Customize area====================
    return 1;
    //=========End of Customeize area============
}

int getCameraInfo(int camera_id, struct camera_info* info)
{
    FNC_ENTRY;
    //=========Customize area====================
    switch(camera_id)
    {
        case 0:
            info->facing = CAMERA_FACING_FRONT;
            info->orientation = 0;
        case 1:
            info->facing = CAMERA_FACING_FRONT;
            info->orientation = 0;
    }
    //=========End of Customeize area============
    return 0;
}

int camera_set_preview_window(struct camera_device * device,
        struct preview_stream_ops *window)
{
    FNC_ENTRY;
    CameraAdapter * hardware = reinterpret_cast<CameraAdapter*>(device->priv);
    if (hardware == NULL) {
        ALOGE("%s: Unexpected NULL camera device", __FUNCTION__);
        return -EINVAL;
    }
    return hardware->camera_set_preview_window(device, window);
}

void camera_set_callbacks(struct camera_device * device,
        camera_notify_callback notify_cb,
        camera_data_callback data_cb,
        camera_data_timestamp_callback data_cb_timestamp,
        camera_request_memory get_memory,
        void *user)
{
    FNC_ENTRY;
    CameraAdapter * hardware = reinterpret_cast<CameraAdapter*>(device->priv);
    if (hardware == NULL) {
        ALOGE("%s: Unexpected NULL camera device", __FUNCTION__);
        return;
    }
    hardware-> camera_set_callbacks(device, notify_cb,
            data_cb, data_cb_timestamp, get_memory, user);
}

void camera_enable_msg_type(struct camera_device * device, int32_t msg_type)
{
    FNC_ENTRY;
    CameraAdapter * hardware = reinterpret_cast<CameraAdapter*>(device->priv);
    if (hardware == NULL) {
        ALOGE("%s: Unexpected NULL camera device", __FUNCTION__);
        return;
    }
    hardware-> camera_enable_msg_type(device,msg_type);
}

void camera_disable_msg_type(struct camera_device * device, int32_t msg_type)

{
    FNC_ENTRY;
    CameraAdapter * hardware = reinterpret_cast<CameraAdapter*>(device->priv);
    if (hardware == NULL) {
        ALOGE("%s: Unexpected NULL camera device", __FUNCTION__);
        return;
    }
    hardware-> camera_disable_msg_type(device,msg_type);
}

int camera_msg_type_enabled(struct camera_device * device, int32_t msg_type)
{
    FNC_ENTRY;
    CameraAdapter * hardware = reinterpret_cast<CameraAdapter*>(device->priv);
    if (hardware == NULL) {
        ALOGE("%s: Unexpected NULL camera device", __FUNCTION__);
        return -EINVAL;
    }
    return hardware->camera_msg_type_enabled(device, msg_type);
}

int camera_start_preview(struct camera_device * device)
{
    FNC_ENTRY;
    CameraAdapter * hardware = reinterpret_cast<CameraAdapter*>(device->priv);
    if (hardware == NULL) {
        ALOGE("%s: Unexpected NULL camera device", __FUNCTION__);
        return -EINVAL;
    }
    return hardware->camera_start_preview(device);
}

void camera_stop_preview(struct camera_device * device)
{
    FNC_ENTRY;
    CameraAdapter * hardware = reinterpret_cast<CameraAdapter*>(device->priv);
    if (hardware == NULL) {
        ALOGE("%s: Unexpected NULL camera device", __FUNCTION__);
        return;
    }
    hardware->camera_stop_preview(device);
}

int camera_preview_enabled(struct camera_device * device)
{
    FNC_ENTRY;
    CameraAdapter * hardware = reinterpret_cast<CameraAdapter*>(device->priv);
    if (hardware == NULL) {
        ALOGE("%s: Unexpected NULL camera device", __FUNCTION__);
        return -EINVAL;
    }
    return hardware->camera_preview_enabled(device);
}

int camera_store_meta_data_in_buffers(struct camera_device * device, int enable)
{
    FNC_ENTRY;
    CameraAdapter * hardware = reinterpret_cast<CameraAdapter*>(device->priv);
    if (hardware == NULL) {
        ALOGE("%s: Unexpected NULL camera device", __FUNCTION__);
        return -EINVAL;
    }
    return 0;//camera_store_meta_data_in_buffers(device,enable);
}

int camera_start_recording(struct camera_device * device)
{
    FNC_ENTRY;
    CameraAdapter * hardware = reinterpret_cast<CameraAdapter*>(device->priv);
    if (hardware == NULL) {
        ALOGE("%s: Unexpected NULL camera device", __FUNCTION__);
        return -EINVAL;
    }
    return hardware->camera_start_recording(device);
}

void camera_stop_recording(struct camera_device * device)
{
    FNC_ENTRY;
    CameraAdapter * hardware = reinterpret_cast<CameraAdapter*>(device->priv);
    if (hardware == NULL) {
        ALOGE("%s: Unexpected NULL camera device", __FUNCTION__);
        return;
    }
    hardware->camera_stop_recording(device);
}

int camera_recording_enabled(struct camera_device * device)
{
    FNC_ENTRY;
    CameraAdapter * hardware = reinterpret_cast<CameraAdapter*>(device->priv);
    if (hardware == NULL) {
        ALOGE("%s: Unexpected NULL camera device", __FUNCTION__);
        return -EINVAL;
    }
    return hardware->camera_recording_enabled(device);
}

void camera_release_recording_frame(struct camera_device * device,
        const void *opaque)
{
    //FNC_ENTRY;
    CameraAdapter * hardware = reinterpret_cast<CameraAdapter*>(device->priv);
    if (hardware == NULL) {
        ALOGE("%s: Unexpected NULL camera device", __FUNCTION__);
        return;
    }
    hardware->camera_release_recording_frame(device, opaque);
}

int camera_auto_focus(struct camera_device * device)
{
    FNC_ENTRY;
    CameraAdapter * hardware = reinterpret_cast<CameraAdapter*>(device->priv);
    if (hardware == NULL) {
        ALOGE("%s: Unexpected NULL camera device", __FUNCTION__);
        return -EINVAL;
    }
    return hardware->camera_auto_focus(device);
}

int camera_cancel_auto_focus(struct camera_device * device)
{
    FNC_ENTRY;
    CameraAdapter * hardware = reinterpret_cast<CameraAdapter*>(device->priv);
    if (hardware == NULL) {
        ALOGE("%s: Unexpected NULL camera device", __FUNCTION__);
        return -EINVAL;
    }
    return hardware->camera_cancel_auto_focus(device);
}

int camera_take_picture(struct camera_device * device)
{
    FNC_ENTRY;
    CameraAdapter * hardware = reinterpret_cast<CameraAdapter*>(device->priv);
    if (hardware == NULL) {
        ALOGE("%s: Unexpected NULL camera device", __FUNCTION__);
        return -EINVAL;
    }
    return hardware->camera_take_picture(device);
}

int camera_cancel_picture(struct camera_device * device)
{
    FNC_ENTRY;
    CameraAdapter * hardware = reinterpret_cast<CameraAdapter*>(device->priv);
    if (hardware == NULL) {
        ALOGE("%s: Unexpected NULL camera device", __FUNCTION__);
        return -EINVAL;
    }
    return hardware->camera_cancel_picture(device);
}

int camera_set_parameters(struct camera_device * device, const char *params)
{
    FNC_ENTRY;
    CameraAdapter * hardware = reinterpret_cast<CameraAdapter*>(device->priv);
    if (hardware == NULL) {
        ALOGE("%s: Unexpected NULL camera device", __FUNCTION__);
        return -EINVAL;
    }
    return hardware->camera_set_parameters(device, params);
}

char* camera_get_parameters(struct camera_device * device)
{
    FNC_ENTRY;
    CameraAdapter * hardware = reinterpret_cast<CameraAdapter*>(device->priv);
    if (hardware == NULL) {
        ALOGE("%s: Unexpected NULL camera device", __FUNCTION__);
        return NULL;
    }
    return hardware->camera_get_parameters(device);
}

static void camera_put_parameters(struct camera_device *device, char *parms)
{
    FNC_ENTRY;
    CameraAdapter * hardware = reinterpret_cast<CameraAdapter*>(device->priv);
    if (hardware == NULL) {
        ALOGE("%s: Unexpected NULL camera device", __FUNCTION__);
        return;
    }
    hardware->camera_put_parameters(device, parms);
}

int camera_send_command(struct camera_device * device,
        int32_t cmd, int32_t arg1, int32_t arg2)
{
    FNC_ENTRY;
    CameraAdapter * hardware = reinterpret_cast<CameraAdapter*>(device->priv);
    if (hardware == NULL) {
        ALOGE("%s: Unexpected NULL camera device", __FUNCTION__);
        return -EINVAL;
    }
    return hardware->camera_send_command(device, cmd, arg1, arg2);
}

void camera_release(struct camera_device * device)
{
    FNC_ENTRY;
    CameraAdapter * hardware = reinterpret_cast<CameraAdapter*>(device->priv);
    if (hardware == NULL) {
        ALOGE("%s: Unexpected NULL camera device", __FUNCTION__);
        return;
    }
    delete(hardware);
    //hardware->camera_release(device);
}

int camera_dump(struct camera_device * device, int fd)
{
    FNC_ENTRY;
    CameraAdapter * hardware = reinterpret_cast<CameraAdapter*>(device->priv);
    if (hardware == NULL) {
        ALOGE("%s: Unexpected NULL camera device", __FUNCTION__);
        return -EINVAL;
    }
    return hardware->camera_dump(device,fd);
}

int camera_device_close(hw_device_t* device)
{
    FNC_ENTRY;
    return 0;
}

static camera_device_ops_t camera_ops = {
set_preview_window : camera_set_preview_window,
                     set_callbacks : camera_set_callbacks,
                     enable_msg_type : camera_enable_msg_type,
                     disable_msg_type : camera_disable_msg_type,
                     msg_type_enabled : camera_msg_type_enabled,
                     start_preview : camera_start_preview,
                     stop_preview : camera_stop_preview,
                     preview_enabled : camera_preview_enabled,
                     store_meta_data_in_buffers : camera_store_meta_data_in_buffers,
                     start_recording : camera_start_recording,
                     stop_recording : camera_stop_recording,
                     recording_enabled : camera_recording_enabled,
                     release_recording_frame : camera_release_recording_frame,
                     auto_focus : camera_auto_focus,
                     cancel_auto_focus : camera_cancel_auto_focus,
                     take_picture : camera_take_picture,
                     cancel_picture : camera_cancel_picture,
                     set_parameters : camera_set_parameters,
                     get_parameters : camera_get_parameters,
                     put_parameters : camera_put_parameters,
                     send_command : camera_send_command,
                     release : camera_release,
                     dump : camera_dump,
};

int camera_device_open(const hw_module_t* module, const char* name,
        hw_device_t** device)
{
    int cameraid=0;
    CameraAdapter * camera =  NULL;

    FNC_ENTRY;
    ALOGI("camera_device open");

    if (name != NULL) {
        cameraid = atoi(name);
        switch( cameraid )
        {
            //=========Customize area====================
            case 0:
                //camera = new FakeCameraAdapter(cameraid);
                camera = new VGACameraAdapter(cameraid);
                break;
#if 0
            case 1:
                camera = new FackCameraAdapter(cameraid);
                break;
#endif
                //=========End of Customeize area============
            default:
                break;
        }
        if(camera == NULL)
        {
            *device = NULL;
            return -ENOMEM;
        }
        camera_device_t *base = (camera_device_t*) malloc( sizeof (camera_device_t));
        if(base==NULL)
        {
            *device = NULL;
            delete camera;
            return -ENOMEM;
        }
        base->common.tag = HARDWARE_DEVICE_TAG;
        base->common.version = 0;
        base->common.module=(hw_module_t*)module;
        base->common.close = camera_device_close;
        base->ops = &camera_ops;
        camera_ops.take_picture = camera_take_picture;

        *device = &(base->common);
        base->priv=(void*)camera;
    }
    return 0;
}

struct hw_module_methods_t mCameraModuleMethods = {
open: camera_device_open,
};

camera_module_t HAL_MODULE_INFO_SYM = {
common: {
tag:           HARDWARE_MODULE_TAG,
               version_major: 1,
               version_minor: 0,
               id:            CAMERA_HARDWARE_MODULE_ID,
               name:          "Camera Module",
               author:        "Liu Xu",
               methods:       &mCameraModuleMethods,
               dso:           NULL,
               reserved:      {0},
        },
get_number_of_cameras:  get_number_of_cameras,
                        get_camera_info:        getCameraInfo,
};

