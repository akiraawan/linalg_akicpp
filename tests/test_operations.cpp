#include <iostream>
#include <cassert>
#include "operations.h"
#include "matrix.h"
#include "vector.h"

using namespace la::matrix;
using namespace la::vector;
using namespace la;

void test_dot_vecvec() {
    Vector a = Vector({1, 2, 3});
    Vector b = Vector({4, 5, 6});
    double result = dot(a, b);
    assert(result == 32.0); // 1*4 + 2*5 + 3*6
    std::cout << "Dot product of vectors test passed!" << std::endl;
}

void test_dot_matvec() {
    Matrix A = Matrix({
        {1, 2, 3},
        {4, 5, 6}
    });
    Vector x = Vector({7, 8, 9});
    Vector result = dot(A, x);
    assert(result == Vector({50, 122})); // {1*7 + 2*8 + 3*9, 4*7 + 5*8 + 6*9}
    std::cout << "Dot product of matrix and vector test passed!" << std::endl;
}

void test_dot_vecmat() {
    Vector x = Vector({1, 2});
    Matrix A = Matrix({
        {3, 4, 7},
        {5, 6, 8},
    });
    Vector result = dot(x, A);
    assert(result == Vector({13, 16, 23})); // {1*3 + 2*5, 1*4 + 2*6, 1*7 + 2*8}
    std::cout << "Dot product of vector and matrix test passed!" << std::endl;
}

void test_outer_product() {
    Vector a = Vector({1, 2});
    Vector b = Vector({3, 4});
    Matrix result = outer(a, b);
    assert(result == Matrix({
        {3, 4},
        {6, 8}
    })); // Outer product
    std::cout << "Outer product test passed!" << std::endl;
}

void test_norm() {
    Vector vec = Vector({3, 4});
    double result = norm(vec);
    assert(result == 5.0); // Euclidean norm
    std::cout << "Norm test passed!" << std::endl;
}

void test_sign() {
    double pos = 5.0;
    double neg = -3.0;
    double zero = 0.0;
    assert(sign(pos) == 1);
    assert(sign(neg) == -1);
    assert(sign(zero) == 1); // Convention: sign(0) = 1
    std::cout << "Sign function test passed!" << std::endl;
}

void test_hstack() {
    Matrix A = Matrix({
        {1, 2},
        {3, 4}
    });
    Matrix B = Matrix({
        {5, 6},
        {7, 8}
    });
    Matrix result = hstack(A, B);
    assert(result == Matrix({
        {1, 2, 5, 6},
        {3, 4, 7, 8}
    })); // Horizontal stack
    std::cout << "Horizontal stack test passed!" << std::endl;
}

void test_vstack() {
    Matrix A = Matrix({
        {1, 2},
        {3, 4}
    });
    Matrix B = Matrix({
        {5, 6},
        {7, 8}
    });
    Matrix result = vstack(A, B);
    assert(result == Matrix({
        {1, 2},
        {3, 4},
        {5, 6},
        {7, 8}
    })); // Vertical stack
    std::cout << "Vertical stack test passed!" << std::endl;
}

int main() {
    test_dot_vecvec();
    test_dot_matvec();
    test_dot_vecmat();
    test_outer_product();
    test_norm();
    test_sign();
    test_hstack();
    test_vstack();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}

