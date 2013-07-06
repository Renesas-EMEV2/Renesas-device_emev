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

#ifndef __VGA_CAMERA_ADAPTER_H__
#define __VGA_CAMERA_ADAPTER_H__

#include "CameraAdapter.h"
#include "YuvToJpegEncoder.h"
#define NB_BUFFER 4
#define CAMDEVICE "/dev/video1"

class VGACameraAdapter:public CameraAdapter
{
    struct sFrameIndex{
        int iIndex;
        unsigned char *p;
    }mFrameIndex[4];
    void *mem[NB_BUFFER];
    int imemlength;
    int m_fd;
    bool m_fdIsOpen;
    int iCurrentIndex;

    int OffsetAddr;
    public:
    VGACameraAdapter(int cameraid);
    virtual ~VGACameraAdapter();
    virtual void get_camera_parameters(CameraParameters * m_CameraParameters)
    {
        set_default_parameters();
        m_CameraParameters->set("jpeg-quality", "65");
    }

    virtual void camera_stop_preview(struct camera_device * device);
    virtual int camera_start_preview(struct camera_device * device);

    void OpenDevice(void);
    void CloseDevice(void);

    void OpenStepByStep(void);
    void CloseStepByStep(void);

    int SetFormat(void);
    int GetFormat(void);

    int StartStreaming(void);
    int StopStreaming(void);

    int MapBuf(void);
    int UnmapBuf(void);

    int RequestBuf(void);
    int UnRequestBuf(void);

    int StartPreviewThreads(void);
    int StopPreviewThreads(void);

    virtual int preview_fill_frame(void * img);
    virtual bool getNextFrameAsYuv420_2_jpg(void *x);
    virtual bool get_frame_from_camera(void *x);

    void blit(void * dst, void * src, int w, int h);
    void putnumber_yuv420p(void * img,int n, int xpos, int ypos );
    void print_number(void * img, int n);
    void savepicturetodisk(void);

    char * currentYUV420FRame;

};
#endif /*__VGA_CAMERA_ADAPTER_H__*/

