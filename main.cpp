#include "matrix.h"
#include "vector.h"
#include "operations.h"
#include "slice.h"
#include <iostream>
#include <vector>

using namespace la;

int main() {
   vector::Vector a1({1.0, 2.0, 3.0, 4.0});
    std::cout << "a1: " << a1 << std::endl; // Should print [1.0, 2.0, 3.0, 4.0]

    vector::Vector a2 = a1(la::Slice(1, 3)); // Should slice to [2.0, 3.0]
    std::cout << "a2: " << a2 << std::endl; // Should print [2.0, 3.0]

    return 0;
}
