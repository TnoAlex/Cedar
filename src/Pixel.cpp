//
// Created by NicoAlex on 2023/4/6.
//

#include "Pixel.h"

bool Pixel::operator!=(const Pixel &p) const
{
    return p.value!=this->value || p.position != this->position;
}

bool Pixel::operator==(const Pixel &p) const
{
    return p.value == this->value && p.position == this->position;
}
