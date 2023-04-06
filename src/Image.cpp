//
// Created by NicoAlex on 2023/4/6.
//

#include "Image.h"

Image::Image(unsigned char *raw, int w, int h, int type)
{

}

Image::~Image()
{

}

std::shared_ptr<ublas::matrix<Pixel>> Image::get_page(int d)
{
    return std::shared_ptr<ublas::matrix<Pixel>>();
}
