#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "matrix.h"
#include "vector.h"
#include "slice.h"
#include "operations.h"
#include <tuple>

using namespace la::matrix;

namespace la {
namespace algorithms {

Matrix GS_classical(Matrix& A);

Matrix GS_modified(Matrix& A);

void householder(Matrix& A);

Matrix solve_U(Matrix& , Matrix& B);

std::tuple<Matrix, Matrix> householder_qr(Matrix& A);

} // namespace algorithms
} // namespace la

#endif // ALGORITHMS_H