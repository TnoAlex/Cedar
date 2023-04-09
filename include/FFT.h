//
// Created by NicoAlex on 2023/4/8.
//

#ifndef CEDAR_FFT_H
#define CEDAR_FFT_H

#include "type_assign.h"
#include "Complex.h"
#include <memory>
#include <boost/container/stable_vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

namespace container = boost::container;
namespace ublas = boost::numeric::ublas;

class FFT
{
public:
    static std::shared_ptr<uchar[]> scale(const std::shared_ptr<double[]> &data, uint row, uint col);

    static void fft(container::stable_vector<Complex> &c, int lim, int opt);

    static void fft2d(ublas::matrix<Complex> &src, ublas::matrix<Complex> &des, int opt);

    static void byte_2_complex(ublas::matrix<Complex> &des, const std::shared_ptr<uchar[]> &data);

    static void complex_2_byte(ublas::matrix<Complex> &data, const std::shared_ptr<uchar[]> &des);

    static void complex_2_double(ublas::matrix<Complex> &data, const std::shared_ptr<double[]> &des);

    template<class T>
    static void array_2_matrix(ublas::matrix<T> &matrix,const std::shared_ptr<T[]> &array,uint row,uint col);

private:
    static int reverse_bin(int a, int n);
};


#endif //CEDAR_FFT_H