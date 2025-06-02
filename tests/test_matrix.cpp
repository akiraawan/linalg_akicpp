#include <iostream>
#include <cassert>
#include "matrix.h"
#include "vector.h"
#include "slice.h"

using namespace la::matrix;
using namespace la::vector;
using namespace la;

void test_constructors() {
    Matrix m1(2, 3);
    assert(m1(0, 0) == 0.0 && m1(1, 2) == 0.0);

    Matrix m2(2, 2, 5.0);
    assert(m2(0, 0) == 5.0 && m2(1, 1) == 5.0);

    std::vector<std::vector<double>> data = {{1, 2}, {3, 4}};
    Matrix m3(data);
    assert(m3(0, 0) == 1.0 && m3(1, 1) == 4.0);

    Matrix m4(m3);
    assert(m4 == m3);

    Matrix m5 = std::move(m4);
    assert(m5 == m3);
}

void test_operators() {
    Matrix a(2, 2, 1.0);
    Matrix b(2, 2, 2.0);
    Matrix c = a + b;
    assert(c(0, 0) == 3.0 && c(1, 1) == 3.0);

    Matrix d = b - a;
    assert(d(0, 0) == 1.0 && d(1, 1) == 1.0);

    Matrix e = a * 3.0;
    assert(e(0, 0) == 3.0);

    Matrix f = 2.0 * a;
    assert(f(1, 1) == 2.0);

    Matrix g(2, 3, 1.0);
    Matrix h(3, 2, 2.0);
    Matrix mult = g * h;
    assert(mult.rows == 2 && mult.cols == 2);
    assert(mult(0, 0) == 6.0);

    assert(a == a);
    assert(a != b);
}

void test_transpose_and_identity() {
    Matrix m(2, 3);
    m(0, 1) = 5.0;
    Matrix t = m.transpose();
    assert(t.rows == 3 && t.cols == 2);
    assert(t(1, 0) == 5.0);

    Matrix id = Matrix::identity(3);
    for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 3; ++j)
            assert(id(i, j) == (i == j ? 1.0 : 0.0));
}

void test_determinant_inverse_trace() {
    Matrix m({{4, 7}, {2, 6}});
    double det = m.determinant();
    assert(det == 10.0);

    Matrix inv = m.inverse();
    assert(std::abs(inv(0, 0) - 0.6) < 1e-9);
    assert(std::abs(inv(1, 0) + 0.2) < 1e-9);

    double tr = m.trace();
    assert(tr == 10.0);
}

void test_slicing_and_replace() {
    Matrix m({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Slice row_slice{1, 3};
    Slice col_slice{0, 2};
    Matrix sub = m(row_slice, col_slice);
    assert(sub.rows == 2 && sub.cols == 2);
    assert(sub(0, 0) == 4 && sub(1, 1) == 8);

    Matrix rep(2, 2, 0.0);
    m.replace(row_slice, col_slice, rep);
    assert(m(1, 0) == 0.0 && m(2, 1) == 0.0);

    Vector v(2);
    v.data[0] = 10; v.data[1] = 20;
    m.replace(Slice{0, 2}, 2, v);
    assert(m(0, 2) == 10 && m(1, 2) == 20);

    Vector rowv = m(0, Slice{0, 2});
    assert(rowv.size == 2 && rowv.data[0] == m(0, 0));
}

void test_flatten() {
    Matrix m({{1, 2}, {3, 4}});
    Vector v = m.flatten();
    assert(v.size == 4);
    assert(v.data[0] == 1 && v.data[3] == 4);
}

int main() {
    test_constructors();
    test_operators();
    test_transpose_and_identity();
    test_determinant_inverse_trace();
    test_slicing_and_replace();
    test_flatten();
    std::cout << "All Matrix tests passed!" << std::endl;
    return 0;
}