//
// Created by NicoAlex on 2023/4/10.
//
#include "util.h"


void complex_2_byte(ublas::matrix<Complex> &data, const std::shared_ptr<unsigned char[]> &des)
{
    int pos = 0;
    for (auto row = data.begin1(); row != data.end1(); row++) {
        for (auto col = row.begin(); col != row.end(); col++) {
            des[pos] = (uchar) sqrt((*col).r * (*col).r);
            pos++;
        }
    }
}

void complex_2_double(ublas::matrix<Complex> &data, const std::shared_ptr<double[]> &des)
{
    int pos = 0;
    for (auto row = data.begin1(); row != data.end1(); row++) {
        for (auto col = row.begin(); col != row.end(); col++) {
            double g = sqrt((*col).r * (*col).r + (*col).i * (*col).i);
            des[pos] = log(g + 1);
            pos++;
        }
    }
}

ublas::matrix<Complex> padding_image(const ublas::matrix<Complex> &img, int type)
{
    ublas::matrix<Complex> res;
    if (type == 0) {
        res = ublas::matrix<Complex>(img.size1() + 1, img.size2());
        res.clear();
        for (int i = 1; i < img.size1() + 1; i++) {
            for (int j = 0; j < img.size2(); j++) {
                res(i, j) = img(i - 1, j);
            }
        }
        return res;
    } else if (type == 1) {
        res = ublas::matrix<Complex>(img.size1(), img.size2() + 1);
        res.clear();
        for (int i = 0; i < img.size1(); i++) {
            for (int j = 0; j < img.size2() + 1; j++) {
                res(i, j) = img(i, j - 1);
            }
        }
        return res;
    } else {
        res = ublas::matrix<Complex>(img.size1() + 1, img.size2() + 1);
        res.clear();
        for (int i = 1; i < img.size1() + 1; i++) {
            for (int j = 1; j < img.size2() + 1; j++) {
                res(i, j) = img(i - 1, j - 1);
            }
        }
        return res;
    }
}