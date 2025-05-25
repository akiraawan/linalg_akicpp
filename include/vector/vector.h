#ifndef LA_VECTOR_H
#define LA_VECTOR_H

#include <iostream>
#include <vector>

namespace la {

namespace vector {

class Vector {
public:
    size_t size;
    std::vector<double> data;

    Vector(size_t size); // Constructor to create a vector with specified size
    Vector(size_t size, double value); // Constructor to create a vector with specified size and initial value
    Vector(const std::vector<double>& data); // Constructor to create a vector from a 1D vector
    Vector(const Vector& other); // Copy constructor
    Vector(Vector&& other) noexcept; // Move constructor
    ~Vector() = default; // Default destructor

    void set(size_t index, double value);
    double get(size_t index) const;

    Vector& operator=(const Vector& other); // Copy assignment operator
    Vector& operator=(Vector&& other) noexcept; // Move assignment operator

    Vector operator+(const Vector& other) const; // Vector addition
    Vector operator-(const Vector& other) const; // Vector subtraction
    double operator*(const Vector& other) const; // Dot product
    Vector operator*(double scalar) const; // Scalar multiplication

    bool operator==(const Vector& other) const; // Equality comparison
    bool operator!=(const Vector& other) const; // Inequality comparison

    static Vector zeros(size_t size);
    static Vector ones(size_t size);

    friend std::ostream& operator<<(std::ostream& os, const Vector& vector); // Overloaded output operator for printing
};

} // namespace vector

} // namespace la

#endif // LA_VECTOR_H