#include "matrix.h"
#include "vector.h"
#include "operations.h"
#include "slice.h"
#include <iostream>
#include <vector>

using namespace la;

int main() {
    vector::Vector a1 = vector::Vector({1.0, 2.0, 3.0}); // used initializer list
    std::cout << "Vector a1: " << a1 << std::endl;

    a1.replace(Slice(1, 3), vector::Vector({4.0, 5.0})); // replace elements at indices 1 and 2
    std::cout << "Vector a1 after replace: " << a1 << std::endl;

    return 0;
}
