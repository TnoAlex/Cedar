//
// Created by NicoAlex on 2023/4/9.
//

#ifndef GAUSSIANFILTER_H
#define GAUSSIANFILTER_H
#include "Complex.h"
#include "util.h"
#include <boost/numeric/ublas/matrix.hpp>
#include "FFT.h"

namespace ublas = boost::numeric::ublas;

void gaussian_filter(ublas::matrix<Complex> &matrix_fft, double sigma, int type);

template<class T>
void center_matrix(ublas::matrix<T> &matrix_fft){
    int rows = matrix_fft.size1();
    int cols = matrix_fft.size2();
    int center_row = rows / 2;
    int center_col = cols / 2;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if ((i + j) % 2 == 1) {
                matrix_fft(i, j) = -matrix_fft(i,j);
            }
        }
    }

    ublas::matrix<T> tmp(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            tmp(i, j) = matrix_fft((i + center_row) % rows, (j + center_col) % cols);
        }
    }

    matrix_fft.swap(tmp);
}


#endif //GAUSSIANFILTER_H
