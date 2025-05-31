#include "matrix.h"
#include "vector.h"
#include "operations.h"
#include "slice.h"
#include "algorithms.h"
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

    std::cout << "Original Matrix A:\n" << A << std::endl;

    auto [Q, R] = algorithms::householder_qr(A);

    std::cout << "Matrix Q after householder:\n" << Q << std::endl;

    std::cout << "Matrix R after householder:\n" << R << std::endl;


    return 0;
}
