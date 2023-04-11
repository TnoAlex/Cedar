//
// Created by NicoAlex on 2023/4/8.
//

#include "Complex.h"

Complex Complex::operator+(const Complex c) const
{
    return {c.r + r, c.i + i};
}

Complex Complex::operator-(const Complex c) const
{
    return {r - c.r, i - c.i};
}

Complex Complex::operator*(const Complex c) const
{
    return {c.r * r - c.i * i, c.r * i + c.i * r};
}

Complex Complex::operator/(int b) const
{
    return {r * 1.0 / b, i * 1.0 / b};
}

bool Complex::operator==(const Complex c) const
{

    return c.r == r && c.i == i;
}

bool Complex::operator!=(const Complex c) const
{

    return c.r != r || c.i != i;
}

Complex Complex::operator*(double c) const
{
    return {r * c, i * c};
}

Complex Complex::operator-() const
{
    return {-r, -i};
}


