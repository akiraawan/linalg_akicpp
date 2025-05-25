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
        Matrix(size_t rows, size_t cols); // Constructor to create a matrix with specified dimensions
        Matrix(const std::vector<std::vector<double>>& data); // Constructor to create a matrix from a 2D vector
        Matrix(const Matrix& other); // Copy constructor
        void set(size_t row, size_t col, double value);
        double get(size_t row, size_t col) const;
        friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix); // Overloaded output operator for printing
        ~Matrix() = default; // Default destructor
};

}