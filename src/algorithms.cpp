#include "algorithms.h"
#include "matrix.h"
#include "vector.h"

namespace la {
namespace algorithms {

matrix::Matrix GS_classical(matrix::Matrix A) {
    size_t n = A.rows;
    matrix::Matrix R = matrix::Matrix::zeros(n, n);

    for (size_t j = 0; j < n; ++j) {
        R.replace(
            Slice(std::nullopt, j),
            j,
            dot(A(Slice(), Slice(std::nullopt, j)).transpose(), A(Slice(), j))
        );

        A.replace(
            Slice(),
            j,
            A(Slice(), j) - dot(A(Slice(), Slice(std::nullopt, j)), R(Slice(std::nullopt, j), j))
        );

        R(j, j) = norm(A(Slice(), j));

        A.replace(
            Slice(),
            j,
            A(Slice(), j) * (1 / R(j, j))
        );
    }
    return R;
}

} // namespace algorithms
} // namespace la