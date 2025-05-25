#include "matrix/matrix.h"
#include "vector/vector.h"
#include <iostream>
#include <vector>

int main() {
    la::matrix::Matrix v1(3, 2, 2);

    std::cout << "Matrix v1: \n" << v1 << std::endl;

    double a = v1(1, 0);
    std::cout << "Element at (0, 1): " << a << std::endl;

    v1(0, 1) = 5;
    std::cout << "Updated Matrix v1: \n" << v1 << std::endl;

    return 0;
}
