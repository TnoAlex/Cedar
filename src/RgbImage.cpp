//
// Created by NicoAlex on 2023/4/6.
//

#include "RgbImage.h"


void RgbImage::to_gray_image(GrayImage &image)
{
    auto matrix = std::make_shared<ublas::matrix<uchar>>(this->height, this->width);
    ublas::matrix<uchar> b = (*get_chunk(1));
    ublas::matrix<uchar> g = (*get_chunk(2));
    ublas::matrix<uchar> r = (*get_chunk(3));
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            (*matrix.get())(i, j) = ceil(r(i,j)*0.3+g(i,j)*0.59+b(i,j)*0.11);
        }
    }
    auto new_channel = std::make_shared<Channel>(matrix, GREY, this->height, this->width);
    image.channel = std::move(new_channel);
    image.height = this->height;
    image.width = this->width;
    image.type = GREY;
}
