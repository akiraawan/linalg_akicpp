#ifndef LA_OPERATIONS_H
#define LA_OPERATIONS_H

#include "matrix.h"
#include "vector.h"
#include <iostream>
#include <vector>

namespace la {

double dot(const vector::Vector& a, const vector::Vector& b);

vector::Vector dot(const matrix::Matrix& A, const vector::Vector& x);

vector::Vector dot(const vector::Vector& x, const matrix::Matrix& A);

matrix::Matrix outer(const vector::Vector& a, const vector::Vector& b);

}

#endif // LA_OPERATIONS_H