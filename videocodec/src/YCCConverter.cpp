//
// Created by ptriller on 23.06.16.
//

#include "YCCConverter.h"
// http://www.equasys.de/colorconversion.html


namespace {
    inline std::tuple<float,float,float> calc_med(const VideoFrame &frame, std::uint32_t x, std::uint32_t y,
                          std::uint32_t scaleX, std::uint32_t scaleY) {
        float col_r = 0.0f;
        float col_g = 0.0f;
        float col_b = 0.0f;
        for(std::uint32_t py = y; py < y+scaleY;++py)
            for(std::uint32_t px = x; px < x+scaleX;++px) {
                const std::uint8_t *pixel = frame.get(x,y);
                col_r += (float)pixel[0];
                col_g += (float)pixel[1];
                col_b += (float)pixel[2];
            }
        std::uint32_t scale = scaleX * scaleY;
        return std::make_tuple(col_r / scale, col_g / scale, col_b / scale);
    }
}

std::unique_ptr<ComponentImage> frame_to_ycc(const VideoFrame &frame) {
    std::unique_ptr<ComponentImage> result(new ComponentImage("ycc"));
    // Y
    ComponentBitmap &ybitmap = (*result)[0];
    ybitmap.type = "Y";
    ybitmap.initialize(frame.width(), frame.height(), 1, 1);
    for(std::uint32_t y = 0; y < frame.height();++y)
        for(std::uint32_t x = 0; x < frame.width();++x) {
            const std::uint8_t *pixel = frame.get(x,y);
            float col_r = (float)pixel[0];
            float col_g = (float)pixel[1];
            float col_b = (float)pixel[2];
            float col_y =  0.183f * col_r + 0.614f * col_g + 0.062f * col_b;
            ybitmap.data[x+y*ybitmap.width] = (std::uint8_t)16 + (std::uint8_t)col_y;
        }
    // Cb
    ComponentBitmap &cbbitmap = (*result)[1];
    cbbitmap.type ="Cb";
    cbbitmap.initialize(frame.width()/2, frame.height()/2, 2, 2);
    for(std::uint32_t y = 0; y < cbbitmap.height;++y)
        for(std::uint32_t x = 0; x < cbbitmap.width;++x) {
            float col_r,col_g,col_b;
            std::tie(col_r, col_g, col_b) = calc_med(frame, x,y,2,2);
            float col_cb = -0.101f * col_r + -0.339f * col_g + 0.439f *col_b + 128.f;
            cbbitmap.data[x+y*ybitmap.width] = (std::uint8_t)col_cb;
        }
    // Cr
    ComponentBitmap &crbitmap = (*result)[1];
    crbitmap.initialize(frame.width()/2, frame.height()/2, 2, 2);
    crbitmap.type = "Cr";
    for(std::uint32_t y = 0; y < crbitmap.height;++y)
        for(std::uint32_t x = 0; x < crbitmap.width;++x) {
            float col_r,col_g,col_b;
            std::tie(col_r, col_g, col_b) = calc_med(frame, x,y,2,2);
            float col_cr = 0.439f * col_r + -0.399f * col_g + -0.040f *col_b + 128.f;
            crbitmap.data[x+y*ybitmap.width] = (std::uint8_t)col_cr;
        }
    return result;
}
