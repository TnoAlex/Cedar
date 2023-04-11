//
// Created by NicoAlex on 2023/4/8.
//

#ifndef CEDAR_COMPLEX_H
#define CEDAR_COMPLEX_H


class Complex
{
public:
    double r, i;

    Complex() : r(0), i(0) {}

    Complex(double _r, double _i) : r(_r), i(_i) {}

    Complex operator+(Complex c) const;

    Complex operator-(Complex c) const;

    Complex operator-() const;

    Complex operator*(Complex c) const;

    Complex operator*(double c) const;

    Complex operator/(int b) const;

    bool operator==(Complex c) const;

    bool operator!=(Complex c) const;
};


#endif //CEDAR_COMPLEX_H
