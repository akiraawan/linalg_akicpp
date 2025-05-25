#include "la/matrix.h"
#include <iostream>
#include <vector>

int main() {
    // Create a 3x3 matrix using the constructor with dimensions
    la::Matrix matrix1(3, 3);
    matrix1.set(0, 0, 1.0);
    matrix1.set(1, 1, 2.0);
    matrix1.set(2, 2, 3.0);
        
    // std::cout << "Matrix 1:\n" << matrix1 << std::endl;
    matrix1.print();

    //     // Create a matrix using the constructor with a 2D vector
    //     std::vector<std::vector<double>> data = {
    //         {4.0, 5.0, 6.0},
    //         {7.0, 8.0, 9.0},
    //         {10.0, 11.0, 12.0}
    //     };
    //     la::Matrix matrix2(ata);
        
    //     std::cout << "Matrix 2:\n" << matrix2 << std::endl;

    // } catch (const std::exception& e) {
    //     std::cerr << "Error: " << e.what() << std::endl;
    // }

    return 0;

}