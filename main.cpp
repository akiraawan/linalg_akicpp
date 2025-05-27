#include "matrix.h"
#include "vector.h"
#include "operations.h"
#include <iostream>
#include <vector>

using namespace la;

int main() {
    matrix::Matrix m1({{1.0, 2.0, 3.0, 4.0},
                       {6.0, 5.0, 9.0, 5.0},
                       {8.0, 3.0, 2.0, 1.0},
                       {7.0, 5.0, 10.0, 6.0}});

    std::cout << "Matrix m1:\n" << m1 << std::endl;
    
    matrix::Matrix m2 = m1.inverse();
    std::cout << "Inverse of m1: " << m2 << std::endl;

    return 0;
}
