//
// Created by NicoAlex on 2023/4/8.
//

#include "FFT.h"

const auto PI = acos(-1);

std::shared_ptr<uchar[]> FFT::scale(const std::shared_ptr<double[]> &data, uint row, uint col)
{
    uint size = row * col;
    auto out_data = std::make_shared<uchar[]>(size);
    double max = data[0];
    double min = data[1];

    for (int i = 0; i < size; i++) {
        max = max > data[i] ? max : data[i];
        min = min < data[i] ? min : data[i];
    }

    double sc = 255.0 / (max - min);
    for (uint i = 0; i < size; i++) {
        out_data[i] = (uchar) ((data[i] - min) * sc);
    }
    return out_data;
}

int FFT::reverse_bin(int a, int n)
{
    int ret = 0;
    for (int i = 0; i < n; i++) {
        if (a & (1 << i)) {
            ret |= ((0x01 << (n - 1)) >> i);
        }
    }
    return ret;
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
        WN[i] = Complex(cos(2 * PI / lim * i), -opt * (sin(2 * PI / lim * i)));
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
        auto col = ublas::column(des, i);
        auto col_vec = container::stable_vector<Complex>(col.begin(), col.end());
        fft(col_vec, (int) src.size1(), opt);
        for (int j = 0; j < src.size1(); j++) {
            des(j, i) = col_vec[j];
        }
    }
}


void FFT::do_fft(ublas::matrix<Complex> &src, ublas::matrix<Complex> &des,int type){
    int row = src.size1();
    int col = src.size2();
    ublas::matrix<Complex> padding_img;
    if (row % 2 != 0 && col % 2 == 0) {
        padding_img = padding_image(src, 0);
        row++;
    } else if (col % 2 != 0 && row % 2 == 0) {
        padding_img = padding_image(src, 1);
        col++;
    } else if (col % 2 != 0 && row % 2 != 0) {
        padding_img = padding_image(src, 2);
        col++;
        row++;
    } else {
        padding_img = src;
    }
    ublas::matrix<Complex> padding_des(padding_img.size1(),padding_img.size2());
    fft2d(padding_img,padding_des,type);

    int r_s = row - src.size1();
    int c_s = col - src.size2();
    for (uint i = 0; i < src.size1(); i++) {
        for (uint j = 0; j < src.size2(); j++) {
            des(i, j) = padding_des(i + r_s, j + c_s);
        }
    }
}

void FFT::DFT(ublas::matrix<Complex> &src, ublas::matrix<Complex> &des)
{
    do_fft(src,des,1);
}

void FFT::IDFT(ublas::matrix<Complex> &src, ublas::matrix<Complex> &des)
{
    do_fft(src,des,-1);
}

