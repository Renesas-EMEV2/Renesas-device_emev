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

#ifndef YuvToJpegEncoder_DEFINED
#define YuvToJpegEncoder_DEFINED

#include "SkTypes.h"
#include "SkStream.h"
extern "C" {
#include "jpeglib.h"
#include "jerror.h"
}
//typedef uint8_t unsigned char
class YuvToJpegEncoder {
    public:
        /** Create an encoder based on the YUV format.
         *
         *  @param pixelFormat The yuv pixel format as defined in ui/PixelFormat.h.
         *  @param strides The number of row bytes in each image plane.
         *  @return an encoder based on the pixelFormat.
         */
        static YuvToJpegEncoder* create(int pixelFormat, int* strides);

        YuvToJpegEncoder(int* strides);

        /** Encode YUV data to jpeg,  which is output to a stream.
         *
         *  @param stream The jpeg output stream.
         *  @param inYuv The input yuv data.
         *  @param width Width of the the Yuv data in terms of pixels.
         *  @param height Height of the Yuv data in terms of pixels.
         *  @param offsets The offsets in each image plane with respect to inYuv.
         *  @param jpegQuality Picture quality in [0, 100].
         *  @return true if successfully compressed the stream.
         */
        bool encode(SkWStream* stream,  void* inYuv, int width,
                int height, int* offsets, int jpegQuality);

        virtual ~YuvToJpegEncoder() {}

    protected:
        int fNumPlanes;
        int* fStrides;
        void setJpegCompressStruct(jpeg_compress_struct* cinfo, int width,
                int height, int quality);
        virtual void configSamplingFactors(jpeg_compress_struct* cinfo) = 0;
        virtual void compress(jpeg_compress_struct* cinfo,
                uint8_t* yuv, int* offsets) = 0;
};

class Yuv420SpToJpegEncoder : public YuvToJpegEncoder {
    public:
        Yuv420SpToJpegEncoder(int* strides);
        virtual ~Yuv420SpToJpegEncoder() {}

    private:
        void configSamplingFactors(jpeg_compress_struct* cinfo);
        void deinterleaveYuv(uint8_t* yuv, int width, int height,
                uint8_t*& yPlanar, uint8_t*& uPlanar, uint8_t*& vPlanar);
        void deinterleave(uint8_t* vuPlanar, uint8_t* uRows, uint8_t* vRows,
                int rowIndex, int width);
        void compress(jpeg_compress_struct* cinfo, uint8_t* yuv, int* offsets);
};

class Yuv422IToJpegEncoder : public YuvToJpegEncoder {
    public:
        Yuv422IToJpegEncoder(int* strides);
        virtual ~Yuv422IToJpegEncoder() {}

    private:
        void configSamplingFactors(jpeg_compress_struct* cinfo);
        void compress(jpeg_compress_struct* cinfo, uint8_t* yuv, int* offsets);
        void deinterleave(uint8_t* yuv, uint8_t* yRows, uint8_t* uRows,
                uint8_t* vRows, int rowIndex, int width, int height);
};

#endif
