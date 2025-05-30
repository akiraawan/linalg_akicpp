#include "algorithms.h"
#include "matrix.h"
#include "vector.h"

namespace la {
namespace algorithms {

matrix::Matrix GS_classical(matrix::Matrix& A) {
    size_t n = A.cols;
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
            A(Slice(), j) * (1.0 / R(j, j))
        );

        std::cout << "Step " << j + 1 << ": R = \n" << R << ", A = \n" << A << std::endl;
    }
    return R;
}

matrix::Matrix GS_modified(matrix::Matrix& A) {
    size_t n = A.cols;
    matrix::Matrix R = matrix::Matrix::zeros(n, n);

    for (size_t i = 0; i < n; ++i) {
        R(i, i) = norm(A(Slice(), i));

        A.replace(
            Slice(),
            i,
            A(Slice(), i) * (1 / R(i, i))
        );

        R.replace(
            i,
            Slice(i+1, std::nullopt),
            dot(A(Slice(), i), A(Slice(), Slice(i+1, std::nullopt)))
        );

        A.replace(
            Slice(),
            Slice(i+1, std::nullopt),
            A(Slice(), Slice(i+1, std::nullopt)) - outer(A(Slice(), i), R(i, Slice(i+1, std::nullopt)))
        );
    }
    return R;
}

} // namespace algorithms
} // namespace la