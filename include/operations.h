#ifndef LA_OPERATIONS_H
#define LA_OPERATIONS_H

#include "matrix.h"
#include "vector.h"
#include <vector>

namespace la {

double dot(const vector::Vector& a, const vector::Vector& b);

vector::Vector dot(const matrix::Matrix& A, const vector::Vector& x);

vector::Vector dot(const vector::Vector& x, const matrix::Matrix& A);

matrix::Matrix outer(const vector::Vector& a, const vector::Vector& b);

vector::Vector solve_Q(const matrix::Matrix& Q, const vector::Vector& b);

} // namespace la

#endif // LA_OPERATIONS_H