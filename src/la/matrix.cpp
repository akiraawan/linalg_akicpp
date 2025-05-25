#include "la/matrix.h"

namespace la {

Matrix::Matrix(size_t rows, size_t cols)
    : rows(rows), cols(cols), data(rows, std::vector<double>(cols, 0.0)) {}
    
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

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (const auto& row : matrix.data) {
        for (const auto& value : row) {
            os << value << " ";
        }
        os << std::endl;
    }
    return os;
}

}