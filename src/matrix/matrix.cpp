#include "matrix/matrix.h"
#include <iostream>
#include <vector>

namespace la {

namespace matrix {

Matrix::Matrix(size_t rows, size_t cols)
    : rows(rows), cols(cols), data(rows, std::vector<double>(cols)) {}

Matrix::Matrix(size_t rows, size_t cols, double value)
    : rows(rows), cols(cols), data(rows, std::vector<double>(cols, value)) {}

Matrix::Matrix(size_t size)
    : Matrix(size, size) {}
    
Matrix::Matrix(const std::vector<std::vector<double>>& data)
    : rows(data.size()), cols(data.empty() ? 0 : data[0].size()), data(data) {
    if (rows > 0 && cols > 0) {
        for (const auto& row : data) {
            if (row.size() != cols) {
                throw std::invalid_argument("All rows must have the same number of columns.");
            }
        }
    } else {
        throw std::invalid_argument("Matrix dimensions must be greater than zero. Please use la/vector.");
    }
}

Matrix::Matrix(const Matrix& other)
    : rows(other.rows), cols(other.cols), data(other.data) {}

Matrix::Matrix(Matrix&& other) noexcept
    : rows(other.rows), cols(other.cols), data(std::move(other.data)) {
    other.rows = 0;
    other.cols = 0;
}

void Matrix::set(size_t row, size_t col, double value) {
    if (row >=  rows || col >= cols) {
        throw std::out_of_range("Index out of range.");
    }
    data[row][col] = value;
}

double Matrix::get(size_t row, size_t col) const {
    if (row >= rows || col >= cols) {
        throw std::out_of_range("Index out of range.");
    }
    return data[row][col];
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        rows = other.rows;
        cols = other.cols;
        data = other.data;
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrices must have the same dimensions for addition.");
    }
    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrices must have the same dimensions for subtraction.");
    }
    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows) {
        throw std::invalid_argument("Matrix multiplication requires the number of columns in the first matrix to match the number of rows in the second matrix.");
    }
    Matrix result(rows, other.cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < other.cols; ++j) {
            for (size_t k = 0; k < cols; ++k) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

Matrix Matrix::operator*(double scalar) const {
    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] * scalar;
        }
    }
    return result;
}

Matrix Matrix::transpose() const {
    Matrix result(cols, rows);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result.data[j][i] = data[i][j];
        }
    }
    return result;
}

bool Matrix::operator==(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        return false;
    }
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (data[i][j] != other.data[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    os << "[";
    for (size_t i = 0; i < matrix.rows; ++i) {
        os << "[";
        for (size_t j = 0; j < matrix.cols; ++j) {
            os << matrix.data[i][j];
            if (j + 1 < matrix.cols) os << ", ";
        }
        os << "]";
        if (i + 1 < matrix.rows) os << ",\n ";
    }
    os << "]";
    return os;
}

Matrix Matrix::zeros(size_t rows, size_t cols) {
    return Matrix(rows, cols, 0.0);
}

Matrix Matrix::ones(size_t rows, size_t cols) {
    return Matrix(rows, cols, 1.0);
}

Matrix Matrix::identity(size_t size) {
    Matrix identity(size, size, 0.0);
    for (size_t i = 0; i < size; ++i) {
        identity.data[i][i] = 1.0;
    }
    return identity;
}

} // namespace matrix

} // namespace la