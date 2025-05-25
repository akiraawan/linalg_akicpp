#include "la/matrix.h"
#include "la/vector.h"
#include <iostream>
#include <vector>


int main() {
    la::Vector v1(3, 1.0);

    std::cout << "Vector v1: " << v1 << std::endl;

    la::Matrix m1(2, 3, 2.0);
    std::cout << "Matrix m1: \n" << m1 << std::endl;

    return 0;
}