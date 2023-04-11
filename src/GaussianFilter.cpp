#include "GaussianFilter.h"

void center_matrix(ublas::matrix<Complex> &matrix_fft)
{
    int rows = matrix_fft.size1();
    int cols = matrix_fft.size2();
    int center_row = rows / 2;
    int center_col = cols / 2;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if ((i + j) % 2 == 1) {
                matrix_fft(i, j) = {-matrix_fft(i, j).r, -matrix_fft(i, j).i};
            }
        }
    }

    ublas::matrix<Complex> tmp(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            tmp(i, j) = matrix_fft((i + center_row) % rows, (j + center_col) % cols);
        }
    }

    matrix_fft.swap(tmp);
}

void crop_matrix(ublas::matrix<Complex> &matrix_fft, int rows, int cols)
{
    int new_rows = matrix_fft.size1();
    int new_cols = matrix_fft.size2();
    int start_row = (new_rows - rows) / 2;
    int start_col = (new_cols - cols) / 2;

    ublas::matrix<Complex> tmp(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            tmp(i, j) = matrix_fft(i + start_row, j + start_col);
        }
    }

    matrix_fft.swap(tmp);
}

// 计算高斯函数
double gaussian_function(int x, int y, double sigma)
{
    return exp(-(x * x + y * y) / (2 * sigma * sigma));
}

void padding_matrix(ublas::matrix<Complex> &matrix_fft, int new_rows, int new_cols)
{
    int rows = matrix_fft.size1();
    int cols = matrix_fft.size2();
    int start_row = (new_rows - rows) / 2;
    int start_col = (new_cols - cols) / 2;

    ublas::matrix<Complex> tmp(new_rows, new_cols);
    for (int i = 0; i < new_rows; i++) {
        for (int j = 0; j < new_cols; j++) {
            if (i >= start_row && i < start_row + rows && j >= start_col && j < start_col + cols) {
                tmp(i, j) = matrix_fft(i - start_row, j - start_col);
            }
        }
    }

    matrix_fft.swap(tmp);
}

void gaussian_filter(ublas::matrix<Complex> &matrix_fft, double sigma, int type)
{
    int rows = matrix_fft.size1();
    int cols = matrix_fft.size2();
    int new_rows = pow(2, ceil(log2(rows)));
    int new_cols = pow(2, ceil(log2(cols)));
    padding_matrix(matrix_fft, new_rows, new_cols);


    ublas::matrix<double> filter(new_rows, new_cols);
    int center_row = new_rows / 2;
    int center_col = new_cols / 2;
    for (int i = 0; i < new_rows; i++) {
        for (int j = 0; j < new_cols; j++) {
            int x = i - center_row;
            int y = j - center_col;
            filter(i, j) = type == 0 ? gaussian_function(x, y, sigma) : (1 - gaussian_function(x, y, sigma));
        }
    }

    for (int i = 0; i < center_row; i++) {
        for (int j = 0; j < center_col; j++) {
            std::swap(filter(i, j), filter(i + center_row, j + center_col));
            std::swap(filter(i + center_row, j), filter(i, j + center_col));
        }
    }

    for (int i = 0; i < new_rows; i++) {
        for (int j = 0; j < new_cols; j++) {
            matrix_fft(i, j) = matrix_fft(i, j) * filter(i, j);
        }
    }

    crop_matrix(matrix_fft, rows, cols);
}