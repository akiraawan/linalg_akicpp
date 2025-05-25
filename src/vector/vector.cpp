#include "vector/vector.h"
#include <iostream>
#include <vector>

namespace la {

namespace vector {

Vector::Vector(size_t size)
    : size(size), data(size) {}

Vector::Vector(size_t size, double value)
    : size(size), data(size, value) {}

Vector::Vector(const std::vector<double>& data)
    : size(data.size()), data(data) {
    if (size == 0) {
        throw std::invalid_argument("Vector size must be greater than zero.");
    }
}

Vector::Vector(const Vector& other)
    : size(other.size), data(other.data) {}

Vector::Vector(Vector&& other) noexcept
    : size(other.size), data(std::move(other.data)) {
    other.size = 0;
}

void Vector::set(size_t index, double value) {
    if (index >= size) {
        throw std::out_of_range("Index out of range.");
    }
    data[index] = value;
}

double Vector::get(size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range.");
    }
    return data[index];
}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        size = other.size;
        data = other.data;
    }
    return *this;
}

Vector& Vector::operator=(Vector&& other) noexcept {
    if (this != &other) {
        size = other.size;
        data = std::move(other.data);
        other.size = 0;
    }
    return *this;
}

Vector Vector::operator+(const Vector& other) const {
    if (size != other.size) {
        throw std::invalid_argument("Vectors must have the same size for addition.");
    }
    Vector result(size);
    for (size_t i = 0; i < size; ++i) {
        result.data[i] = data[i] + other.data[i];
    }
    return result;
}

Vector Vector::operator-(const Vector& other) const {
    if (size != other.size) {
        throw std::invalid_argument("Vectors must have the same size for subtraction.");
    }
    Vector result(size);
    for (size_t i = 0; i < size; ++i) {
        result.data[i] = data[i] - other.data[i];
    }
    return result;
}

double Vector::operator*(const Vector& other) const {
    if (size != other.size) {
        throw std::invalid_argument("Vectors must have the same size for dot product.");
    }
    double result = 0.0;
    for (size_t i = 0; i < size; ++i) {
        result += data[i] * other.data[i];
    }
    return result;
}

Vector Vector::operator*(double scalar) const {
    Vector result(size);
    for (size_t i = 0; i < size; ++i) {
        result.data[i] = data[i] * scalar;
    }
    return result;
}

bool Vector::operator==(const Vector& other) const {
    if (size != other.size) {
        return false;
    }
    for (size_t i = 0; i < size; ++i) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}

bool Vector::operator!=(const Vector& other) const {
    return !(*this == other);
}

Vector Vector::zeros(size_t size) {
    return Vector(size, 0.0);
}

Vector Vector::ones(size_t size) {
    return Vector(size, 1.0);
}

std::ostream& operator<<(std::ostream& os, const Vector& vector) {
    os << "[";
    for (size_t i = 0; i < vector.size; ++i) {
        os << vector.data[i];
        if (i < vector.size - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

} // namespace vector

} // namespace la