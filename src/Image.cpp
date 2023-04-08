//
// Created by NicoAlex on 2023/4/6.
//

#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_WINDOWS_UTF8
#define STBI_FAILURE_USERMSG
#include "stb/stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb/stb_image_resize.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#include <boost/log/trivial.hpp>

std::map<unsigned int, std::string> ImageTypeString = {
        {1,"GREY"},
        {2,"GREY_WITH_ALPHA"},
        {3,"RGB"},
        {4,"RGB_WITH_ALPHA"}
};

Image::Image(uchar *raw, int w, int h, int type)
{
            BOOST_LOG_TRIVIAL(info) << "Load Image" << "\n";
    this->width = w;
    this->height = h;
    this->type = (ImageType) type;
    this->channel = std::make_shared<Channel>(this->type, h, w, raw);
    BOOST_LOG_TRIVIAL(info) << "width : " << w << "px" << "\n" << "height: "
                      << h << "\n" << "type: " << ImageTypeString[type] << "\n";
}

Image::Image(const std::string &fileName)
{
    BOOST_LOG_TRIVIAL(info) << "Load Image";
    int n =0;
    uchar * data =  stbi_load(fileName.c_str(), &this->width, &this->height, &n, 0);
    this->type = (ImageType)n;
    this->channel = std::make_shared<Channel>(this->type, height, width, data);
    BOOST_LOG_TRIVIAL(info) <<"\n"<< "width : " << width << "px" << "\n" << "height: "
                      << height << "\n" << "type: " << ImageTypeString[type] ;
}


std::shared_ptr<ublas::matrix<uchar>> Image::get_chunk(int d) const
{
    assert(d <= (uint) this->type && d >= 1);
    return this->channel->chunks->at(d);
}

void Image::show() const
{
//    uchar *raw = channel->to_raw();
//    stbi_write_png("test.png",width,height,1,raw,0);
    HWND hwnd = GetForegroundWindow();
    HDC hdc = GetDC(hwnd);
    RECT rect = {};
    GetWindowRect(hwnd, &rect);
    int i_h = ceil((rect.bottom - rect.top) * 0.75);
    int i_w = ceil((rect.right - rect.left) * 0.75);
    uchar *raw = channel->to_raw().get();
    uchar *resize_raw = raw;
    if (width > i_w || height > i_h) {
        int alpha = -1;
        if (type == GREY_WITH_ALPHA || type == RGB_WITH_ALPHA) {
            alpha = width * height * (int) (type - 1);
        }
        stbir_resize(raw, width, height, 0,
                     resize_raw, i_w, i_h, 0, STBIR_TYPE_UINT32,
                     (int) type, alpha, 0, STBIR_EDGE_CLAMP,
                     STBIR_EDGE_CLAMP,
                     STBIR_FILTER_BOX, STBIR_FILTER_BOX,
                     STBIR_COLORSPACE_SRGB, nullptr);
    }
    for (int i = 0; i < height; i++) {
        for (int l = 0; l < width; l++) {
            if (type == GREY || type == GREY_WITH_ALPHA) {
                uint pixel = (*get_chunk(1))(i,l);
                SetPixel(hdc, this->width-l, this->height - i, RGB(pixel, pixel, pixel));
            } else {
                uint r=0, g=0, b=0;
                r = (*get_chunk(1))(i,this->width-l-1);
                g = (*get_chunk(2))(i,this->width-l-1);
                b = (*get_chunk(3))(i,this->width-l-1);
                SetPixel(hdc, l,  i, RGB(r, g, b));
            }
        }
    }
    ReleaseDC(hwnd,hdc);
}

