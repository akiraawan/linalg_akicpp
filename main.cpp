#include "matrix.h"
#include "vector.h"
#include "operations.h"
#include <iostream>
#include <vector>

using namespace la;

int main() {
    vector::Vector v1({1.0, 2.0, 3.0, 4.0, 5.0});

    std::cout << "Vector v1: " << v1 << std::endl;

    vector::Vector v2 = v1(Slice(1, 4)); // Slicing from index 1 to 3
    std::cout << "Sliced Vector v2: " << v2 << std::endl;

    return 0;
}
