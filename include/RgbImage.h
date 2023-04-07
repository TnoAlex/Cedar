//
// Created by NicoAlex on 2023/4/6.
//

#ifndef CEDAR_RGB_IMAGE_H
#define CEDAR_RGB_IMAGE_H

#include "Image.h"
#include "GrayImage.h"
#include <memory>
#include <string>

class RgbImage : public Image
{
public:
    void to_gray_image(GrayImage &image);
    using Image::Image;
};


#endif //CEDAR_RGB_IMAGE_H
