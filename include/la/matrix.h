#pragma once

#include <iostream>
#include <vector>

namespace la {


class Matrix {
    private:
        size_t rows;
        size_t cols;
        std::vector<std::vector<double>> data;
    public:
        Matrix(size_t rows, size_t cols);
        Matrix(const std::vector<std::vector<double>>& data);
        Matrix(const Matrix& other);
        void set(size_t row, size_t col, double value);
        double get(size_t row, size_t col) const;
        void print() const;

};

}