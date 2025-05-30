#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "matrix.h"
#include "vector.h"
#include "slice.h"
#include "operations.h"
#include <tuple>

namespace la {
namespace algorithms {

matrix::Matrix GS_classical(matrix::Matrix& A);

matrix::Matrix GS_modified(matrix::Matrix& A);

} // namespace algorithms
} // namespace la

#endif // ALGORITHMS_H