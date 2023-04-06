//
// Created by NicoAlex on 2023/4/6.
//

#ifndef CEDAR_RGB_IMAGE_H
#define CEDAR_RGB_IMAGE_H

#include "Image.h"
#include "GrayImage.h"
#include <memory>

class RgbImage : public Image
{
public:
    GrayImage to_gray_image();
};


#endif //CEDAR_RGB_IMAGE_H
