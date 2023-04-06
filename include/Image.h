//
// Created by NicoAlex on 2023/4/6.
//

#ifndef CEDAR_IMAGE_H
#define CEDAR_IMAGE_H

#include "Channel.h"
#include "image_type.h"
#include <memory>

class Image
{
    int width,height;
    std::shared_ptr<Channel> channel;
    ImageType type;

    Image(unsigned char * raw,int w,int h,int type);
    ~Image();
    std::shared_ptr<ublas::matrix<Pixel>> get_page(int d);
};


#endif //CEDAR_IMAGE_H
