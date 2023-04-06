//
// Created by NicoAlex on 2023/4/6.
//

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
std::map<unsigned int,std::string> ImageTypeString = {
        {1,"GREY"},
        {2,"GREY_WITH_ALPHA"},
        {3,"RGB"},
        {4,"RGB_WITH_ALPHA"}
};
#endif //CEDAR_IMAGE_TYPE_H
