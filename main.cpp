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

    matrix::Matrix R = algorithms::GS_classical(A);

    std::cout << "Matrix R:\n" << R << std::endl;
    return 0;
}
