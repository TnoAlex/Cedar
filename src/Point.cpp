//
// Created by NicoAlex on 2023/4/6.
//

#include "Point.h"

bool Point::operator==(const Point &p) const
{
    return p.x == this->x && p.y == this->y;
}

bool Point::operator!=(const Point &p) const
{
    return p.x!=this->x || p.y!= this->y;
}

