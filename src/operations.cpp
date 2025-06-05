#include "operations.h"
#include "vector.h"
#include "matrix.h"
#include <iostream>
#include <cmath>

using namespace la::matrix;
using namespace la::vector;

namespace la {

double dot(const Vector& a, const Vector& b) {
    if (a.size != b.size) {
        throw std::invalid_argument("Vectors must have the same size for dot product.");
    }
    double result = 0.0;
    for (size_t i = 0; i < a.size; ++i) {
        result += a.data[i] * b.data[i];
    }
    return result;
}

Vector dot(const Matrix& A, const Vector& x) {
    if (A.cols != x.size) {
        throw std::invalid_argument("Matrix columns must match vector size for multiplication.");
    }
    Vector result(A.rows);
    for (size_t i = 0; i < A.rows; ++i) {
        result.data[i] = 0.0;
        for (size_t j = 0; j < A.cols; ++j) {
            result.data[i] += A.data[i][j] * x.data[j];
        }
    }
    return result;
}

Vector dot(const Vector& x, const Matrix& A) {
    if (x.size != A.rows) {
        throw std::invalid_argument("Vector size must match matrix rows for multiplication.");
    }
    Vector result(A.cols);
    for (size_t j = 0; j < A.cols; ++j) {
        result.data[j] = 0.0;
        for (size_t i = 0; i < A.rows; ++i) {
            result.data[j] += x.data[i] * A.data[i][j];
        }
    }
    return result;
}

Matrix outer(const Vector& a, const Vector& b) {
    Matrix result(a.size, b.size);
    for (size_t i = 0; i < a.size; ++i) {
        for (size_t j = 0; j < b.size; ++j) {
            result.data[i][j] = a.data[i] * b.data[j];
        }
    }
    return result;
}

double norm(const Vector& vec) {
    double res = 0;

    for (size_t i = 0; i < vec.size; ++i) {
        res += pow(vec.data[i], 2);
    }
    res = pow(res, 0.5);
    return res;
}

int sign(double value) {
    if (value >= 0) {
        return 1;
    } else {
        return -1;
    }
}

Matrix hstack(const Matrix& A, const Matrix& B) {
    if (A.rows != B.rows) {
        throw std::invalid_argument("Matrices must have the same number of rows for horizontal stacking.");
    }
    Matrix result(A.rows, A.cols + B.cols);
    for (size_t i = 0; i < A.rows; ++i) {
        for (size_t j = 0; j < A.cols; ++j) {
            result.data[i][j] = A.data[i][j];
        }
        for (size_t j = 0; j < B.cols; ++j) {
            result.data[i][A.cols + j] = B.data[i][j];
        }
    }
    return result;
}

Matrix hstack(const Matrix& A, const Vector& b) {
    if (A.rows != b.size) {
        throw std::invalid_argument("Matrix A rows must match vector b size for horizontal stacking.");
    }
    Matrix result(A.rows, A.cols + 1);
    for (size_t i = 0; i < A.rows; ++i) {
        for (size_t j = 0; j < A.cols; ++j) {
            result.data[i][j] = A.data[i][j];
        }
        result.data[i][A.cols] = b.data[i];
    }
    return result;
}

Matrix vstack(const Matrix& A, const Matrix& B) {
    if (A.cols != B.cols) {
        throw std::invalid_argument("Matrices must have the same number of columns for vertical stacking.");
    }
    Matrix result(A.rows + B.rows, A.cols);
    for (size_t i = 0; i < A.rows; ++i) {
        for (size_t j = 0; j < A.cols; ++j) {
            result.data[i][j] = A.data[i][j];
        }
    }
    for (size_t i = 0; i < B.rows; ++i) {
        for (size_t j = 0; j < B.cols; ++j) {
            result.data[A.rows + i][j] = B.data[i][j];
        }
    }
    return result;
}

Matrix vstack(const Matrix& A, const Vector& b) {
    if (A.cols != 1) {
        throw std::invalid_argument("Matrix A must have exactly one column for vertical stacking with a vector.");
    }
    if (A.rows + 1 != b.size) {
        throw std::invalid_argument("Matrix A rows plus one must match vector b size for vertical stacking.");
    }
    Matrix result(A.rows + 1, 1);
    for (size_t i = 0; i < A.rows; ++i) {
        result.data[i][0] = A.data[i][0];
    }
    result.data[A.rows][0] = b.data[0];
    return result;
}

} // namespace la