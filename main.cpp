#include "matrix.h"
#include "vector.h"
#include "operations.h"
#include "slice.h"
#include <iostream>
#include <vector>

using namespace la;

int main() {
    matrix::Matrix A(
    {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    });

    std::cout << "Matrix A:\n" << A << std::endl;

    vector::Vector v({10, 11});

    std::cout << "Vector v:\n" << v<< std::endl;

    A.replace(Slice(std::nullopt, 2), 1, v);
    std::cout << "Matrix A after replacing top-left 2x2 with B:\n" << A << std::endl;

    return 0;
}
