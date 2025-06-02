#include "algorithms.h"
#include "matrix.h"
#include "vector.h"

using namespace la::matrix;
using namespace la::vector;

namespace la {
namespace algorithms {

Matrix GS_classical(Matrix& A) {
    size_t n = A.cols;
    size_t m = A.rows;
    if (n > m) {
        throw std::invalid_argument("Number of columns must be less than or equal to the number of rows.");
    }
    Matrix R = Matrix::zeros(n, n);

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

Matrix GS_modified(Matrix& A) {
    size_t n = A.cols;
    Matrix R = Matrix::zeros(n, n);

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

void householder(Matrix& A) {
    size_t m = A.rows;
    size_t n = A.cols;

    for (size_t k = 0; k < std::min(m, n); ++k) {
        Vector x = A(Slice(k, std::nullopt), k);

        Vector e1 = Vector::zeros_like(x);
        e1(0) = 1.0;

        Vector vk = x + (e1 * norm(x) * sign(x(0)));

        if (norm(vk) == 0) continue;

        vk = vk * (1.0 / norm(vk));
        A.replace(
            Slice(k, std::nullopt),
            Slice(k, std::nullopt),
            A(Slice(k, std::nullopt), Slice(k, std::nullopt)) - 2 * outer(vk, dot(vk, A(Slice(k, std::nullopt), Slice(k, std::nullopt))))
        );
    }
}

Matrix solve_U(Matrix& U, Matrix& B) {
    if (U.rows != U.cols) {
        throw std::invalid_argument("Matrix U must be square.");
    }
    size_t m = U.rows;
    Matrix X = Matrix::zeros(B.rows, B.cols);

    X.replace(
        m-1,
        Slice(),
        B(m-1, Slice()) * (1.0 / U(m-1, m-1))
    );

    for (int i = m-2; i >= 0; --i) {
        X.replace(
            i,
            Slice(),
            (B(i, Slice()) - dot(U(i, Slice(i+1, std::nullopt)), X(Slice(i+1, std::nullopt), Slice()))) * (1.0 / U(i, i))
        );
    }
    return X;
}

std::tuple<Matrix, Matrix> householder_qr(Matrix& A) {
    if (A.rows < A.cols) {
        throw std::invalid_argument("Number of rows must be greater than or equal to the number of columns.");
    }
    size_t m = A.rows;
    size_t n = A.cols;

    Matrix A_hat = hstack(A, Matrix::identity(m));

    householder(A_hat);

    Matrix R = A_hat(Slice(), Slice(0, n));
    Matrix Q = A_hat(Slice(), Slice(n, std::nullopt));
    Q = Q.transpose();

    return std::make_tuple(Q, R);
}

vector::Vector householder_ls(Matrix& A, vector::Vector& b) {
    size_t m = A.rows;
    size_t n = A.cols;

    if (m < n) {
        throw std::invalid_argument("Number of rows must be greater than or equal to the number of columns.");
    }

    Matrix A_hat = hstack(A, b);
    householder(A_hat);

    Matrix R = A_hat(Slice(0, n), Slice(0, n));
    Matrix B = A_hat(Slice(0, n), Slice(n, std::nullopt));

    vector::Vector x = solve_U(R, B).flatten();

    return x;
}

void hessenberg(Matrix& A) {
    if (A.rows != A.cols) {
        throw std::invalid_argument("Matrix A must be square.");
    }
    size_t m = A.rows;

    for (size_t k = 0; k < m - 2; ++k) {
        Vector x = A(Slice(k + 1, std::nullopt), k);

        Vector e1 = Vector::zeros_like(x);
        e1(0) = 1.0;

        Vector vk = x + (e1 * norm(x) * sign(x(0)));
        vk = vk * (1.0 / norm(vk));

        A.replace(
            Slice(k + 1, std::nullopt),
            Slice(k, std::nullopt),
            A(Slice(k + 1, std::nullopt), Slice(k, std::nullopt)) - 2 * outer(vk, dot(vk, A(Slice(k + 1, std::nullopt), Slice(k, std::nullopt))))
        );
        A.replace(
            Slice(),
            Slice(k + 1, std::nullopt),
            A(Slice(), Slice(k + 1, std::nullopt)) - 2 * outer(dot(A(Slice(), Slice(k + 1, std::nullopt)), vk), vk)
        );
    }
}

Matrix hessenbergQ(Matrix& A) {
    if (A.rows != A.cols) {
        throw std::invalid_argument("Matrix A must be square.");
    }
    size_t m = A.rows;
    Matrix Q = Matrix::identity(m);

    for (size_t k = 0; k < m - 2; ++k) {
        vector::Vector x = A(Slice(k + 1, std::nullopt), k);
        vector::Vector e1 = vector::Vector::zeros_like(x);
        e1(0) = 1.0;
        vector::Vector vk = x + (e1 * norm(x) * sign(x(0)));
        vk = vk * (1.0 / norm(vk));
        A.replace(
            Slice(k + 1, std::nullopt),
            Slice(k, std::nullopt),
            A(Slice(k + 1, std::nullopt), Slice(k, std::nullopt)) - 2 * outer(vk, dot(vk, A(Slice(k + 1, std::nullopt), Slice(k, std::nullopt))))
        );
        A.replace(
            Slice(),
            Slice(k + 1, std::nullopt),
            A(Slice(), Slice(k + 1, std::nullopt)) - 2 * outer(dot(A(Slice(), Slice(k + 1, std::nullopt)), vk), vk)
        );

        Q.replace(
            Slice(),
            Slice(k + 1, std::nullopt),
            Q(Slice(), Slice(k + 1, std::nullopt)) - 2 * outer(dot(Q(Slice(), Slice(k + 1, std::nullopt)), vk), vk)
        );
    }

    return Q;
}

std::tuple<Vector, double> pow_it(const Matrix& A, const Vector& x0, double tol, size_t max_iter) {
    size_t m = A.rows;
    size_t n = A.cols;
    if (n != m) {
        throw std::invalid_argument("Matrix A must be square.");
    }
    if (m != x0.size) {
        throw std::invalid_argument("Vector size must match matrix rows.");
    }

    Vector x = x0;
    double lambda = 0.0;

    for (size_t iter = 0; iter < max_iter; ++iter) {
        Vector w = dot(A, x);

        x = w * (1.0 / norm(w));

        lambda = dot(x, w);

        Vector r = w - (x * lambda);

        if (norm(r) < tol) {
            break;
        }
    }

    return std::make_tuple(x, lambda);
}

} // namespace algorithms
} // namespace la