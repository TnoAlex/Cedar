//
// Created by NicoAlex on 2023/4/8.
//

#ifndef CEDAR_FFT_H
#define CEDAR_FFT_H

#include "util.h"
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

    static void DFT(ublas::matrix<Complex> &src, ublas::matrix<Complex> &des);

    static void IDFT(ublas::matrix<Complex> &src, ublas::matrix<Complex> &des);

private:
    static int reverse_bin(int a, int n);

    static void fft(container::stable_vector<Complex> &c, int lim, int opt);

    static void fft2d(ublas::matrix<Complex> &src, ublas::matrix<Complex> &des, int opt);
    static void do_fft(ublas::matrix<Complex> &src, ublas::matrix<Complex> &des,int type);
};


#endif //CEDAR_FFT_H