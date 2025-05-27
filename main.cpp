#include "matrix.h"
#include "vector.h"
#include "operations.h"
#include <iostream>
#include <vector>

using namespace la;

int main() {
    vector::Vector v1(3, 1.0);

    std::cout << "Vector v1:\n " << v1 << std::endl;

    vector::Vector v2(3, 2.0);

    std::cout << "Vector v2:\n " << v2 << std::endl;

    matrix::Matrix res = la::outer(v1, v2);

    std::cout << "Outer product of v1 and v2:\n " << res << std::endl;

    return 0;
}
