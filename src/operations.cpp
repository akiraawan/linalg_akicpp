#include "operations.h"
#include "vector.h"
#include "matrix.h"

namespace la {

double dot(const vector::Vector& a, const vector::Vector& b) {
    if (a.size != b.size) {
        throw std::invalid_argument("Vectors must have the same size for dot product.");
    }
    double result = 0.0;
    for (size_t i = 0; i < a.size; ++i) {
        result += a.data[i] * b.data[i];
    }
    return result;
}

vector::Vector dot(const matrix::Matrix& A, const vector::Vector& x) {
    if (A.cols != x.size) {
        throw std::invalid_argument("Matrix columns must match vector size for multiplication.");
    }
    vector::Vector result(A.rows);
    for (size_t i = 0; i < A.rows; ++i) {
        result.data[i] = 0.0;
        for (size_t j = 0; j < A.cols; ++j) {
            result.data[i] += A.data[i][j] * x.data[j];
        }
    }
    return result;
}

vector::Vector dot(const vector::Vector& x, const matrix::Matrix& A) {
    if (x.size != A.rows) {
        throw std::invalid_argument("Vector size must match matrix rows for multiplication.");
    }
    vector::Vector result(A.cols);
    for (size_t j = 0; j < A.cols; ++j) {
        result.data[j] = 0.0;
        for (size_t i = 0; i < A.rows; ++i) {
            result.data[j] += x.data[i] * A.data[i][j];
        }
    }
    return result;
}

matrix::Matrix outer(const vector::Vector& a, const vector::Vector& b) {
    matrix::Matrix result(a.size, b.size);
    for (size_t i = 0; i < a.size; ++i) {
        for (size_t j = 0; j < b.size; ++j) {
            result.data[i][j] = a.data[i] * b.data[j];
        }
    }
    return result;
}

vector::Vector solve_Q(const matrix::Matrix& Q, const vector::Vector& b) {
    if (Q.rows != Q.cols) {
        throw std::invalid_argument("Matrix Q must be square.");
    }
    if (Q.rows != b.size) {
        throw std::invalid_argument("Matrix Q rows must match vector b size.");
    }
    vector::Vector x = la::dot(Q.transpose(), b);

    return x;
}

} // namespace la