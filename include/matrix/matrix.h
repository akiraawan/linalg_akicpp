#ifndef LA_MATRIX_H
#define LA_MATRIX_H

#include <iostream>
#include <vector>

namespace la {

namespace matrix{

class Matrix {
public:
    size_t rows;
    size_t cols;
    std::vector<std::vector<double>> data;

    Matrix(size_t rows, size_t cols); // Constructor to create a matrix with specified dimensions
    Matrix(size_t rows, size_t cols, double value); // Constructor to create a matrix with specified dimensions and initial value
    Matrix(size_t size); // Constructor to create a square matrix

    Matrix(const std::vector<std::vector<double>>& data); // Constructor to create a matrix from a 2D vector
    Matrix(const Matrix& other); // Copy constructor
    Matrix(Matrix&& other) noexcept; // Move constructor
    ~Matrix() = default; // Default destructor

    void set(size_t row, size_t col, double value);
    double get(size_t row, size_t col) const;

    Matrix& operator=(const Matrix& other); // Copy assignment operator
    Matrix& operator=(Matrix&& other) noexcept; // Move assignment operator

    Matrix operator+(const Matrix& other) const; // Matrix addition
    Matrix operator-(const Matrix& other) const; // Matrix subtraction
    Matrix operator*(const Matrix& other) const; // Matrix multiplication
    Matrix operator*(double scalar) const; // Scalar multiplication
    Matrix transpose() const; // Transpose of the matrix

    bool operator==(const Matrix& other) const; // Equality comparison
    bool operator!=(const Matrix& other) const; // Inequality comparison

    static Matrix zeros(size_t rows, size_t cols);
    static Matrix ones(size_t rows, size_t cols);
    static Matrix identity(size_t size);

    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix); // Overloaded output operator for printing
};

} // namespace matrix

} // namespace la

#endif // LA_MATRIX_H