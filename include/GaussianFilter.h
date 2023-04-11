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
void center_matrix(ublas::matrix<Complex> &matrix_fft);


#endif //GAUSSIANFILTER_H
