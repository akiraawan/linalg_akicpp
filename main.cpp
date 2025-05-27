#include "matrix.h"
#include "vector.h"
#include "operations.h"
#include "slice.h"
#include <iostream>
#include <vector>

using namespace la;

int main() {
    matrix::Matrix A({{1.0, 2.0, 3.0},
                      {4.0, 5.0, 6.0},
                      {7.0, 8.0, 9.0}});

    std::cout << "Matrix A:\n" << A << std::endl;

    matrix::Matrix B = A(la::Slice(), la::Slice(1, 3));
    
    std::cout << "Matrix B: \n" << B << std::endl; // Extracting a submatrix

    return 0;
}
