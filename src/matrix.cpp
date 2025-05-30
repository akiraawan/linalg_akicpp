#include "matrix.h"
#include <vector>
#include <iostream>

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
    }
}

Matrix::Matrix(const Matrix& other)
    : rows(other.rows), cols(other.cols), data(other.data) {}

Matrix::Matrix(Matrix&& other) noexcept
    : rows(other.rows), cols(other.cols), data(std::move(other.data)) {
    other.rows = 0;
    other.cols = 0;
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        rows = other.rows;
        cols = other.cols;
        data = other.data;
    }
    return *this;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept {
    if (this != &other) {
        rows = other.rows;
        cols = other.cols;
        data = std::move(other.data);
        other.rows = 0;
        other.cols = 0;
    }
    return *this;
}

double& Matrix::operator()(size_t row, size_t col) {
    if (row >= rows || col >= cols) {
        throw std::out_of_range("Index out of range.");
    }
    return data[row][col];
}

const double& Matrix::operator()(size_t row, size_t col) const {
    if (row >= rows || col >= cols) {
        throw std::out_of_range("Index out of range.");
    }
    return data[row][col];
}

void Matrix::replace(const Slice& row_slice, const Slice& col_slice, const Matrix& submat) {
    size_t start_row = row_slice.start.value_or(0);
    size_t end_row = row_slice.end.value_or(rows);
    size_t start_col = col_slice.start.value_or(0);
    size_t end_col = col_slice.end.value_or(cols);

    if (start_row >= rows || end_row > rows || start_col >= cols || end_col > cols || start_row > end_row || start_col > end_col) {
        throw std::out_of_range("Slice indices are out of range.");
    }

    if (submat.rows != (end_row - start_row) || submat.cols != (end_col - start_col)) {
        throw std::invalid_argument("Submatrix dimensions do not match the specified slice.");
    }

    for (size_t i = start_row; i < end_row; ++i) {
        for (size_t j = start_col; j < end_col; ++j) {
            data[i][j] = submat.data[i - start_row][j - start_col];
        }
    }
}

Matrix Matrix::operator()(const Slice& row_slice, const Slice& col_slice) const {
    size_t start_row = row_slice.start.value_or(0);
    size_t end_row = row_slice.end.value_or(rows);
    size_t start_col = col_slice.start.value_or(0);
    size_t end_col = col_slice.end.value_or(cols);

    if (start_row >= rows || end_row > rows || start_col >= cols || end_col > cols || start_row > end_row || start_col > end_col) {
        throw std::out_of_range("Slice indices are out of range.");
    }

    Matrix result(end_row - start_row, end_col - start_col);
    for (size_t i = start_row; i < end_row; ++i) {
        for (size_t j = start_col; j < end_col; ++j) {
            result.data[i - start_row][j - start_col] = data[i][j];
        }
    }
    return result;
}

void Matrix::replace(const Slice& slice, size_t col, const vector::Vector& subvec) {
    if (col >= cols) {
        throw std::out_of_range("Column index out of range.");
    }
    size_t start = slice.start.value_or(0);
    size_t end = slice.end.value_or(rows);

    if (start >= rows || end > rows || start > end) {
        throw std::out_of_range("Slice indices are out of range.");
    }

    if (subvec.size != (end - start)) {
        throw std::invalid_argument("Replacement vector must match slice size.");
    }

    for (size_t i = start; i < end; ++i) {
        data[i][col] = subvec.data[i - start];
    }
}

vector::Vector Matrix::operator()(const Slice& slice, size_t col) const {
    if (col >= cols) {
        throw std::out_of_range("Column index out of range.");
    }
    size_t start = slice.start.value_or(0);
    size_t end = slice.end.value_or(rows);

    if (start >= rows || end > rows || start > end) {
        throw std::out_of_range("Slice indices are out of range.");
    }

    vector::Vector result(end - start);
    for (size_t i = start; i < end; ++i) {
        result.data[i - start] = data[i][col];
    }
    return result;
}

void Matrix::replace(size_t row, const Slice& slice, const vector::Vector& subvec) {
    if (row >= rows) {
        throw std::out_of_range("Row index out of range.");
    }
    size_t start = slice.start.value_or(0);
    size_t end = slice.end.value_or(cols);

    if (start >= cols || end > cols || start > end) {
        throw std::out_of_range("Slice indices are out of range.");
    }

    if (subvec.size != (end - start)) {
        throw std::invalid_argument("Replacement vector must match slice size.");
    }

    for (size_t j = start; j < end; ++j) {
        data[row][j] = subvec.data[j - start];
    }
}

vector::Vector Matrix::operator()(size_t row, const Slice& slice) const {
    if (row >= rows) {
        throw std::out_of_range("Row index out of range.");
    }
    size_t start = slice.start.value_or(0);
    size_t end = slice.end.value_or(cols);

    if (start >= cols || end > cols || start > end) {
        throw std::out_of_range("Slice indices are out of range.");
    }

    vector::Vector result(end - start);
    for (size_t j = start; j < end; ++j) {
        result.data[j - start] = data[row][j];
    }
    return result;
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

Matrix Matrix::inverse() const {
    if (rows != cols) {
        throw std::invalid_argument("Inverse can only be calculated for square matrices.");
    }
    double det = determinant();
    if (det == 0.0) {
        throw std::runtime_error("Matrix is singular and cannot be inverted.");
    }
    return adjugate() * (1.0 / det);
}

Matrix Matrix::adjugate() const {
    if (rows != cols) {
        throw std::invalid_argument("Adjugate can only be calculated for square matrices.");
    }
    return cofactor().transpose();
}

Matrix Matrix::cofactor() const {
    Matrix result(rows, cols);
    if (rows != cols) {
        throw std::invalid_argument("Adjugate can only be calculated for square matrices.");
    }
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result.data[i][j] = minor(i, j).determinant() * ((i + j) % 2 == 0 ? 1 : -1);
        }
    }
    return result;
}

Matrix Matrix::minor(size_t row, size_t col) const {
    if (row >= rows || col >= cols) {
        throw std::out_of_range("Index out of range for minor.");
    }
    Matrix result(rows - 1, cols - 1);
    for (size_t i = 0, r = 0; i < rows; ++i) {
        if (i == row) continue;
        for (size_t j = 0, c = 0; j < cols; ++j) {
            if (j == col) continue;
            result.data[r][c++] = data[i][j];
        }
        ++r;
    }
    return result;
}

double Matrix::determinant() const {
    if (rows != cols) {
        throw std::invalid_argument("Determinant can only be calculated for square matrices.");
    }
    if (rows == 1) {
        return data[0][0];
    }
    if (rows == 2) {
        return data[0][0] * data[1][1] - data[0][1] * data[1][0];
    }
    double det = 0.0;
    for (size_t j = 0; j < cols; ++j) {
        det += data[0][j] * minor(0, j).determinant() * ((j % 2 == 0) ? 1 : -1);
    }
    return det;
}

double Matrix::trace() const {
    if (rows != cols) {
        throw std::invalid_argument("Trace can only be calculated for square matrices.");
    }
    double sum = 0.0;
    for (size_t i = 0; i < rows; ++i) {
        sum += data[i][i];
    }
    return sum;
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