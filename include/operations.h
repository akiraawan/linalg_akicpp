#ifndef LA_OPERATIONS_H
#define LA_OPERATIONS_H

#include "matrix.h"
#include "vector.h"
#include <vector>

using namespace la::matrix;
using namespace la::vector;

namespace la {

double dot(const Vector& a, const Vector& b);

Vector dot(const Matrix& A, const Vector& x);

Vector dot(const Vector& x, const Matrix& A);

Matrix outer(const Vector& a, const Vector& b);

Vector solve_Q(const Matrix& Q, const Vector& b);

double norm(const Vector& vec);

int sign(double value);

Matrix hstack(const Matrix& A, const Matrix& B);
Matrix hstack(const Matrix& A, const Vector& b);

Matrix vstack(const Matrix& A, const Matrix& B);
Matrix vstack(const Matrix& A, const Vector& b);

} // namespace la

#endif // LA_OPERATIONS_H