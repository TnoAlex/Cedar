//
// Created by NicoAlex on 2023/4/10.
//

#ifndef UTIL_H
#define UTIL_H

#ifdef STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION

#endif
#include "stb/stb_image_resize.h"
#include "type_assign.h"
#include <memory>
#include "Complex.h"
#include <boost/numeric/ublas/matrix.hpp>
namespace ublas = boost::numeric::ublas;

enum class DATE_TYPE{
    UINT8,
    UINT16,
    UINT32,
    FLOAT
};

enum class EDGE_TYPE{
    CLAMP   = 1,
    REFLECT = 2,
    WRAP    = 3,
    ZERO    = 4,
};

template<class T>
void array_2_complex(const std::shared_ptr<T []> &data,ublas::matrix<Complex> &des){
    uint row = des.size1();
    uint col = des.size2();
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            des(i, j) = Complex((data)[i * (int) col + j], 0);
        }
    }
}
void complex_2_byte(ublas::matrix<Complex> &data, const std::shared_ptr<unsigned char[]> &des);
void complex_2_double(ublas::matrix<Complex> &data, const std::shared_ptr<double[]> &des);

template<class T>
std::shared_ptr<ublas::matrix<T>>
resize_matrix(const ublas::matrix<T> &src, DATE_TYPE type, EDGE_TYPE edge_type, int new_row,
              int new_col){
    auto src_raw = from_matrix(src);
    return resize_matrix(src_raw.get(), src.size1(), src.size2(), type, new_row, new_col, edge_type);
}

template<class T>
std::shared_ptr<ublas::matrix<T>>
resize_matrix(const T *src, int row, int col, DATE_TYPE type, int new_row, int new_col, EDGE_TYPE edge_type){
    auto stbi_type = STBIR_TYPE_UINT8;
    switch (type) {
        case DATE_TYPE::UINT32:
            stbi_type = STBIR_TYPE_UINT32;
            break;
        case DATE_TYPE::UINT8:
            break;
        case DATE_TYPE::UINT16:
            stbi_type = STBIR_TYPE_UINT16;
            break;
        case DATE_TYPE::FLOAT:
            stbi_type = STBIR_TYPE_FLOAT;
            break;
    }
    auto res = new T[new_col * new_row];
    stbir_resize(src, col, row, 0, res, new_col, new_row,
                 0, stbi_type, 1, STBIR_ALPHA_CHANNEL_NONE,
                 0, edge_type, edge_type,
                 STBIR_FILTER_BOX, STBIR_FILTER_BOX,
                 STBIR_COLORSPACE_LINEAR, nullptr);
    auto des = std::make_signed<ublas::matrix<T>>(new_row, new_col);
    to_matrix(res, *des);
    delete[]res;
    return des;
}

template<class T>
std::shared_ptr<T []> from_matrix(const ublas::matrix<T> &m){
    int pos = 0;
    auto res = std::make_shared<T[]>(m.size1() * m.size2());
    for (int i = 0; i < m.size1(); ++i) {
        for (int j = 0; j < m.size2(); ++j) {
            res[pos] = m(i, j);
            pos++;
        }
    }
    return res;
}

template<class T>
void to_matrix(const T *arr,ublas::matrix<T> &matrix){
    int pos = 0;
    for (int i = 0; i < matrix.size1(); i++) {
        for (int j = 0; j < matrix.size2(); j++) {
            matrix(i, j) = arr[pos];
            pos++;
        }
    }
}

ublas::matrix<Complex> padding_image(const ublas::matrix<Complex> &img, int type);
#endif //UTIL_H
