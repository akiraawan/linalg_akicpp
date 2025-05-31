#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"
#include "slice.h"
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

    Matrix& operator=(const Matrix& other); // Copy assignment operator
    Matrix& operator=(Matrix&& other) noexcept; // Move assignment operator

    double& operator()(size_t row, size_t col);
    const double& operator()(size_t row, size_t col) const;

    void replace(const Slice& row_slice, const Slice& col_slice, const Matrix& submat); // Replace a submatrix with another matrix
    Matrix operator()(const Slice& row_slice, const Slice& col_slice) const;

    void replace(const Slice& slice, size_t col, const vector::Vector& subvec); // Replace a column with a vector
    vector::Vector operator()(const Slice& slice, size_t col) const; // Extract a column as a vector

    void replace(size_t row, const Slice& slice, const vector::Vector& subvec); // Replace a row with a vector
    vector::Vector operator()(size_t row, const Slice& slice) const; // Extract a row as a vector

    Matrix operator+(const Matrix& other) const; // Matrix addition
    Matrix operator-(const Matrix& other) const; // Matrix subtraction
    Matrix operator*(const Matrix& other) const; // Matrix multiplication
    Matrix operator*(double scalar) const; // Scalar multiplication

    Matrix transpose() const; // Transpose of the matrix
    Matrix inverse() const; // Inverse of the matrix (if applicable)
    Matrix adjugate() const; // Adjugate of the matrix (if applicable)
    Matrix cofactor() const; // Cofactor matrix (if applicable)
    Matrix minor(size_t row, size_t col) const; // Minor of the matrix at specified row and column
    double determinant() const; // Determinant of the matrix (if applicable)
    double trace() const; // Trace of the matrix (if applicable)
    // size_t rank() const; // Rank of the matrix

    bool operator==(const Matrix& other) const; // Equality comparison
    bool operator!=(const Matrix& other) const; // Inequality comparison

    friend Matrix operator*(const double scalar, const Matrix& matrix); // Scalar multiplication with scalar on the left
    static Matrix zeros(size_t rows, size_t cols);
    static Matrix ones(size_t rows, size_t cols);
    static Matrix identity(size_t size);

    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix); // Overloaded output operator for printing
};

} // namespace matrix

} // namespace la

#endif // LA_MATRIX_H