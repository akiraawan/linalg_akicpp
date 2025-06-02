#include <iostream>
#include <cassert>
#include "algorithms.h"
#include "matrix.h"
#include "vector.h"
#include "slice.h"

using namespace la::matrix;
using namespace la::vector;
using namespace la::algorithms;
using namespace la;

void test_GS_classical() {
    Matrix A = Matrix({
        {12, -51, 4},
        {6, 167, -68},
        {-4, 24, -41},
        {-1, 1, 0}
    });

    Matrix R = GS_classical(A);
    
    // Check the shape of R
    assert(R.rows == A.cols && R.cols == A.cols);
    
    // Check orthogonality of columns in A
    for (size_t i = 0; i < A.cols; ++i) {
        for (size_t j = i + 1; j < A.cols; ++j) {
            assert(std::abs(dot(A(Slice(), i), A(Slice(), j)) < 1e-10));
        }
    }
    
    std::cout << "GS Classical Test Passed!" << std::endl;
}

void test_GS_modified() {
    Matrix A = Matrix({
        {12, -51, 4},
        {6, 167, -68},
        {-4, 24, -41},
        {-1, 1, 0}
    });

    Matrix R = GS_modified(A);
    
    // Check the shape of R
    assert(R.rows == A.cols && R.cols == A.cols);
    
    // Check orthogonality of columns in A
    for (size_t i = 0; i < A.cols; ++i) {
        for (size_t j = i + 1; j < A.cols; ++j) {
            assert(std::abs(dot(A(Slice(), i), A(Slice(), j)) < 1e-10));
        }
    }
    
    std::cout << "GS Modified Test Passed!" << std::endl;
}

void test_householder_qr() {
    Matrix A = Matrix({
        {12, -51, 4},
        {6, 167, -68},
        {-4, 24, -41},
        {-1, 1, 0}
    });

    auto [Q, R] = householder_qr(A);
    
    // Check orthogonality of Q
    // Check orthogonality of Q: Q^T * Q should be close to identity
    Matrix QtQ = Q.transpose() * Q;
    Matrix I = Matrix::identity(Q.rows);
    for (size_t i = 0; i < Q.rows; ++i) {
        for (size_t j = 0; j < Q.rows; ++j) {
            assert(std::abs(QtQ(i, j) - I(i, j)) < 1e-10);
        }
    }
    
    // Check that A = QR
    Matrix QR = Q * R;
    for (size_t i = 0; i < A.rows; ++i) {
        for (size_t j = 0; j < A.cols; ++j) {
            assert(std::abs(A(i, j) - QR(i, j)) < 1e-10);
        }
    }
    
    std::cout << "Householder QR Test Passed!" << std::endl;
}

int main() {
    test_GS_classical();
    test_GS_modified();
    test_householder_qr();
    
    std::cout << "All algorithm tests passed!" << std::endl;
    return 0;
}