#include "matrix/matrix.h"
#include "vector/vector.h"
#include <iostream>
#include <vector>

int main() {
    la::vector::Vector v1(3, 1.0);

    std::cout << "v1: " << v1 << std::endl;

    double value = v1(1);
    std::cout << "v1(1): " << value << std::endl;

    v1(1) = 2.0;
    std::cout << "v1 after setting v1(1) to 2.0: " << v1 << std::endl;

    return 0;
}
