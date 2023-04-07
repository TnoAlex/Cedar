//
// Created by NicoAlex on 2023/4/6.
//
#pragma once

#ifndef CEDAR_IMAGE_TYPE_H
#define CEDAR_IMAGE_TYPE_H

#include <map>
#include <string>

enum ImageType : unsigned int
{
    GREY = 1,
    GREY_WITH_ALPHA = 2,
    RGB = 3,
    RGB_WITH_ALPHA = 4
};

#endif //CEDAR_IMAGE_TYPE_H
