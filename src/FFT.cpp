//
// Created by NicoAlex on 2023/4/8.
//

#include "FFT.h"

const auto PI = acos(-1);

std::shared_ptr<unsigned char[]> FFT::centralization(const std::shared_ptr<uchar[]> &data, uint row, uint col)
{
    uint size = row * col;
    auto out_data = std::make_shared<uchar[]>(size);
    for (uint i = 0; i < size; i++) {
        uint j = i + row * col / 2 + row / 2;
        if (j > size) j = j - size;   //低频移至中间
        out_data[i] = data[j];
    }
    return out_data;
}

void FFT::fft(container::stable_vector<Complex> &c, int lim, int opt)
{
    container::stable_vector<Complex> tC0(lim);
    for (int i = 0; i < lim; i++) {
        int index = reverse_bin(i, (int) log2(lim));
        tC0[i] = c[index];
    }
    container::stable_vector<Complex> WN(lim / 2);
    for (int i = 0; i < lim / 2; i++) {
        WN[i] = Complex(cos(2 * PI * i / lim), opt * (-sin(2 * PI * i / lim)));
    }
    for (int i = 2; i <= lim; i *= 2) {
        for (int j = 0; j < lim / i; j++) {
            for (int k = 0; k < i / 2; k++) {
                int index0 = i * j + k;
                int index1 = i * j + k + i / 2;
                Complex tC = tC0[index1] * WN[lim / i * k];
                tC0[index1] = tC0[index0] - tC;
                tC0[index0] = tC0[index0] + tC;
            }
        }
    }

    for (int i = 0; i < lim; i++) {
        if (opt == -1) {
            c[i] = tC0[i] / lim;
        } else {
            c[i] = tC0[i];
        }
    }
}

int FFT::reverse_bin(int a, int n)
{
    int ret = 0;
    for (int i = 0; i < n; i++) {
        if (a & (1 << i)) {
            ret |= (1 << (n - 1 - i));
        }
    }
    return ret;
}

void FFT::fft2d(ublas::matrix<Complex> &src, ublas::matrix<Complex> &des, int opt)
{
    for (int i = 0; i < src.size1(); i++) {
        auto row = ublas::row(src, i);
        auto row_vec = container::stable_vector<Complex>(row.begin(), row.end());
        fft(row_vec, (int) src.size2(), opt);
        for (int j = 0; j < src.size2(); j++) {
            des(i, j) = row_vec[j];
        }
    }
    for (int i = 0; i < src.size2(); i++) {
        auto col = ublas::column(src, i);
        auto col_vec = container::stable_vector<Complex>(col.begin(), col.end());
        fft(col_vec, (int) src.size1(), opt);
        for (int j = 0; j < src.size1(); j++) {
            des(j, i) = col_vec[j];
        }
    }
}

void FFT::byte_2_complex(ublas::matrix<Complex> &des, const std::shared_ptr<uchar[]> &data, uint row, uint col)
{
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            des(i, j) = Complex((data)[i * (int) col + j], 0);
        }
    }
}

void FFT::complex_2_byte(ublas::matrix<Complex> &data, const std::shared_ptr<unsigned char[]> &des)
{
    int pos = 0;
    for (auto row = data.begin1(); row != data.end1(); row++) {
        for (auto col = row.begin(); col != row.end(); col++) {
            des[pos] = (uchar) sqrt((*col).r * (*col).r);
            pos++;
        }
    }
}

void FFT::complex_2_double(ublas::matrix<Complex> &data, const std::shared_ptr<double[]> &des)
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

template<class T>
void FFT::array_2_matrix(ublas::matrix<T> &matrix, const std::shared_ptr<T[]> &array,uint row,uint col)
{
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            matrix(i,j) = array[i * (int) col + j];
        }
    }
}

