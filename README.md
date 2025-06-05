# mylinalgcpp

The `mylinalgcpp` library is a C++ library consisting of its own `Matrix` Class and a `Vector`Class, and various operations and Numerical Linear Algebra algorithms, inspired by NumPy (Python) and Computational Linear Algebra (MATH60024) from Imperial College Mathematics.

## Requirements

- g++ v13.1.0 or newer

## Matrix/Vector Class

The `Matrix` and `Vector` Class is very similar to a 2-D and 1-D numpy array respectively. 

- Contructors:
    ```
    Matrix A(3, 4); // Creates a 3x4 matrix 
    Vector v(3); // Creates a vector of size 3

    Matrix A(3, 4, 3.0) // Creates a 3x4 matrix with all elements 3.0
    Vector v(3, 3.0) // Creates a vector of size 3 with all elements 3.0

    Matrix A(3); // Creates a 3x3 square matrix

    Matrix A(
        {{1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}}
    ) // Creates a Matrix defined by a std::Vector<std::Vector>
    Vector v({1, 2, 3}); // Creates a Vector defined by std::Vector

    A(3, 4); // Returns the (4, 5)th element
    A(3, 4) = 5; // Assigns 5 to teh (4, 5)th element

    v(3); // Returns the 2nd element
    v(3) = 5; // Assigns 5 to the 2nd position
    ```
- Slicing using `Slice` Class:

    `Slice` Class
    ```
    Slice(start, end) // Represents a slice with indices [start, end)
    e.g Slice(2, 5) represents indices 2, 3, 4

    Slice() // Represents [first_element, last_element]
    Slice(std::nullopt, 5) // Represents [0, 5)
    Slice(2, std::nullopt) // Represents [2, last_element]
    ```

    Using with `Matrix`/`Vector` Class
    ```
    A(Slice(2, 5), 2) // Returns a Vector representing the 2-4th row index with the 2nd column index

    A(2, Slice(2, 5)) // Returns a Vector representing the 2nd row index with 2-4th column index

    A(Slice(2, 5), Slice(1, 3)) // Returns a Matrix representing the 2-4th row index with 1-2 column index

    v(Slice(2, 5)) // Returns a Vector representing the 2-4th index
    ```

    Changing values of a subMatrix/subVector of a Matrix/Vector
    ```
    A.replace(2, Slice(2, 5), Vector(3)) // Replaces the 2nd row index with 2-4th column index values with Vector(3) of size 3

    A.replace(Slice(2, 5), 2, Vector(3)) // Replaces the 2-4th row index with 2nd column index with Vector(3) of size 3

    A.replace(Slice(2, 5), Slice(1, 3), Matrix(3, 2)) // Replaces the 2-4th row index with 1-2 column index with Matrix(3, 2) of size 3x2
    ```

- Useful functions/operations:

    `Vector`
    ```
    v1 + v2; vector addition

    v1 - v2; vector subtraction

    v1 * v2; dot product

    2 * v; scalar multiplication
    v * 2;

    Vector::zeros(3); // zero vector of size 3

    Vector::ones(3); // one vector of size 3

    Vector::zeros_like(v); // zero vector of same size as v
    ```

    `Matrix`
    ```
    A + B; matrix addition

    A - B; matrix subtraction

    A * B; matrix multiplication

    A * 2; scalar multiplication
    2 * A;

    A.transpose(); transpose of A

    A.inverse(); inverse of A

    A.adjugate(); adjugate of A

    A.cofactor(); cofactor of A

    A.minor(); minor of A

    A.determinant(); determinant of A

    A.trace(); trace of A

    A.flatten(); flatten vector of A

    Matrix::zeros(3, 2); zero matrix of size 3x2

    Matrix::ones(3, 2); one matrix of size 3x2

    Matrix::identity(3); identity matrix of size 3x3
    ```

    `operations`
    ```
    dot(v1, v2); vector dot product

    dot(A, v); A x v, matrix x vector multiplication

    dot(v, A); v.T x A, row vector x matrix multiplication

    outer(v1, v2); outer product of vectors, v1 x v2.T

    norm(v); L2 norm of v

    sign(a); sign of float a. sign(0) = 1

    hstack(A, B); stacks matrix A and B horizontally
    hstack(A, b); stacks matrix A and vector b horizontally

    vstack(A, B); stacks matrix A and B vertically
    vstack(A, b); stacks matrix A and vetor B vertically
    ```

## Algorithms
- `GS_classical`

    ```
    Matrix R = GS_classical(A); // returns the R matrix and converts A into Q
    ```
    
    The classical Gram-Schmidt algorithm for QR factoristaion is motivated by the column space interpretation of the matrix-matrix multiplication $A = QR$, namely the jth column $a_j$ of $A$ is a linear combination of the orthonormal columns of Q, with the coefficients given by the jth column $r_j$ of $R$.

    $$
    q_1 = \frac{a_1}{r_{11}}\\

    q_2 = \frac{a_2 - r_{12}q_1}{r_{22}}\\

    .\\
    .\\
    .\\

    q_n = \frac{a_n - \sum_{i=1}^{n-1}r_{in}q_i}{r_{nn}}
    $$

    and for $R$,

    $$
    r_{ij} = q_i^*a_j, \; i > j\\

    |r_{jj}| = \left\|a_j - \sum_{i=1}^{j-1}r_{ij}q_i|| \right\|
    $$

    Where Q, R is the reduced QR matrices. 

- `GS_modified`

    ```
    Matrix R = GS_modified(A); // returns the R matrix and converts A into Q
    ```

    The classical Gram-Schmidt algorithm is unstable. The modified Gram-Schmidt algorithm for QR factorisation is motivated by the projector interpretation.

    $$
    P_j = P_{\bot q_{j-1}} \dots P_{\bot q_2}P_{\bot q_1}
    $$

    where $P_{\bot q_{j}} = I - q_jq_j^*$

    Then,

    $$
    v_j = P_ja_j = P_{\bot q_{j-1}} \dots P_{\bot q_2}P_{\bot q_1}a_j
    $$

    By doing this, we gradually transform A to unitary matrix. Where Q, R is the reduced QR matrices. 

- `householder`

    ```
    householder(A); // Converts A into R using householder
    ```

- `solve_Q`

    ```
    Vector x = solve_Q(Q, b); solves Qx = b
    ```

    Solves the linear system $Qx = b$, where Q is a unitary matrix.

- `solve_U`

    ```
    Vector x = solve_Q(U, b); solves Ux = b
    ```

    Solves the linear system $Ux = b$, where U is an upper triangular matrix.

- `householder_qr`

    ```
    auto [Q, R] = householder_qr(A); Returns the Q, R factorisation of A using householder algorithm
    ```

    Solves the QR factorisation $A = QR$ using householder. Where Q, R is the full QR matrices. 

- `householder_ls`

    ```
    Vector x = householder_ls(A, b); // 
    ```

    solves the least squares problem:

    $$
    ||Ax - b||^2
    $$

    using householder algorithm.

    If b is not in the column space of A, then we cannot find a point $x$ such that $Ax = b$. Instead, the nearest point in the range of $A$ to $b$ is $Pb$, where $P$ is the orthogonal projector onto the range of A, and $P = \hat{Q}\hat{Q}^*$, where $\hat{Q}$ from the reduced QR factorisation has the same column space as A.

    $$
    Ax = Pb
    $$

    $$
    \hat{Q}\hat{R}x = \hat{Q}\hat{Q}^*b
    $$

    $$
    \hat{R}x = \hat{Q}^*b
    $$

    This is an upper triangular system that can be solved using `solve_U`.

- `hessenberg`

    ```
    hessenberg(A); \\ Converts A into H, a hessenberg matrix such that A = QHQ*
    ```

    Hessenberg matrix is a matrix that is close to an upper triangular matrix. 

- `hessenbergQ`

    ```
    Matrix Q = hessenbergQ(A); \\ Returns the unitary matrix Q and Converts A into H, a hessenberg matrix such that A = QHQ*
    ```

    Hessenberg matrix is a matrix that is close to an upper triangular matrix. 

- `pow_it`

    ```
    auto [v, lam] pow_it(A, x0); // Returns the eigenvector and eigenvalue with the largest magnitude of the eigenvalue of A.
    ```

    Power Iteration is a numerical method used to find an eigenvector and the corresponding eigenvalue with the largest magnitude.
