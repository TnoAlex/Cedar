//
// Created by NicoAlex on 2023/4/6.
//

#ifndef CEDAR_PIXEL_H
#define CEDAR_PIXEL_H
#include "Point.h"

class Pixel
{
public:
    Point position;
    int value;

    bool operator ==(const Pixel &p)const;
    bool operator !=(const Pixel &p)const;
};


#endif //CEDAR_PIXEL_H
