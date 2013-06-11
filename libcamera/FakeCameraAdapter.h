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

#include "CameraAdapter.h"
class FakeCameraAdapter:public CameraAdapter
{
    public:
        FakeCameraAdapter(int cameraid):CameraAdapter(cameraid) {
        }
        virtual void get_camera_parameters(CameraParameters * m_CameraParameters) {
            set_default_parameters();
            m_CameraParameters->set("jpeg-quality", "65");
        }
        void blit(void * dst, void * src, int w, int h);
        void putnumber_yuv420p(void * img,int n, int xpos, int ypos );
        void print_number(void * img, int n);

        virtual int preview_fill_frame(void * img);
        virtual bool get_frame_from_camera(void * x);
        virtual bool getNextFrameAsYuv420_2_jpg(void * x);

        virtual ~FakeCameraAdapter() {
        }
};

