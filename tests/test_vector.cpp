#include <iostream>
#include <cassert>
#include "vector.h" // Adjust the include path as needed
#include "slice.h"

using namespace la::vector;
using namespace la;

void test_vector_construction() {
    Vector v1(3);
    assert(v1.size == 3);
    for (size_t i = 0; i < v1.size; ++i)
        assert(v1(i) == 0);

    Vector v2{1.0, 2.0, 3.0};
    assert(v2.size == 3);
    assert(v2(0) == 1.0 && v2(1) == 2.0 && v2(2) == 3.0);

    Vector v3 = v2;
    assert(v3.size == v2.size);
    for (size_t i = 0; i < v3.size; ++i)
        assert(v3(i) == v2(i));
}

void test_vector_assignment() {
    Vector v1{1.0, 2.0, 3.0};
    Vector v2(3);
    v2 = v1;
    for (size_t i = 0; i < v2.size; ++i)
        assert(v2(i) == v1(i));
}

void test_vector_addition() {
    Vector v1{1.0, 2.0, 3.0};
    Vector v2{4.0, 5.0, 6.0};
    Vector v3 = v1 + v2;
    assert(v3(0) == 5.0 && v3(1) == 7.0 && v3(2) == 9.0);
}

void test_vector_scalar_multiplication() {
    Vector v1{1.0, 2.0, 3.0};
    Vector v2 = v1 * 2.0;
    assert(v2(0) == 2.0 && v2(1) == 4.0 && v2(2) == 6.0);
}

void test_vector_slice() {
    Vector v{1.0, 2.0, 3.0, 4.0, 5.0};
    Slice slice(1, 4); // Slice from index 1 to 3
    Vector subvec = v(slice);
    assert(subvec.size == 3);
    assert(subvec(0) == 2.0 && subvec(1) == 3.0 && subvec(2) == 4.0);
}

int main() {
    test_vector_construction();
    test_vector_assignment();
    test_vector_addition();
    test_vector_scalar_multiplication();
    test_vector_slice();
    std::cout << "All vector tests passed!" << std::endl;
    return 0;
}