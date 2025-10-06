// Copyright 2025 Mary Maslennikova

#include <cstdlib>
#include <stdexcept>
#include <initializer_list>
#include <iostream>

#ifndef LIB_TRIANGLEMATRIX_TRIANGLEMATRIX_H_
#define LIB_TRIANGLEMATRIX_TRIANGLEMATRIX_H_

#include "../lib_matrix/matrix.h"

template <typename T>
class TriangleMatrix;

template <typename T> std::ostream& operator<<(std::ostream& os, const TriangleMatrix<T>& vec);
template <typename T> std::istream& operator>>(std::istream& is, TriangleMatrix<T>& vec);

template<typename T>
class TriangleMatrix : public Matrix<T> {

public:
    TriangleMatrix();  // +
    TriangleMatrix(size_t size);  // +
    TriangleMatrix(std::initializer_list<std::initializer_list<T>> lists);  // +
    TriangleMatrix(const Matrix<T>& matrix);  // +
    TriangleMatrix(const TriangleMatrix<T>& other);  // +

    TriangleMatrix<T> operator+(const TriangleMatrix<T>& other);  // +
    TriangleMatrix<T> operator-(const TriangleMatrix<T>& other);  // +
    TriangleMatrix<T> operator*(const TriangleMatrix<T>& other);  // +
    TriangleMatrix<T> operator*(const T& scalar);  // +
    MathVector<T> operator*(const MathVector<T>& vector);  // +

    TriangleMatrix<T>& operator+=(const TriangleMatrix<T>& other);  // +
    TriangleMatrix<T>& operator-=(const TriangleMatrix<T>& other);  // +
    TriangleMatrix<T>& operator*=(const TriangleMatrix<T>& other);  // +
    TriangleMatrix<T>& operator*=(const T& scalar);  // +

    TriangleMatrix<T>& operator=(const TriangleMatrix<T>& other);  // +

    bool operator==(const TriangleMatrix<T>& second) const;  // +
    bool operator!=(const TriangleMatrix<T>& second) const;  // +

    friend std::ostream& operator<< <T>(std::ostream& os, const TriangleMatrix<T>&);
    friend std::istream& operator>> <T>(std::istream& is, TriangleMatrix<T>&);
};

template <typename T>
TriangleMatrix<T>::TriangleMatrix() : Matrix<T>() {

}
template <typename T>
TriangleMatrix<T>::TriangleMatrix(size_t size) : Matrix<T>(size, size) {
    for (size_t i = 0; i < size; i++) {
        (*this)[i] = MathVector<T>(size - i, i);
    }
}
template <typename T>
TriangleMatrix<T>::TriangleMatrix(std::initializer_list<std::initializer_list<T>> lists) : Matrix<T>(lists) {
    if (_m != _n)
        throw std::invalid_argument("A triangular matrix has the same number of rows and columns!");
    size_t i = 0;
    for (auto it = lists.begin(); it != lists.end(); it++, i++) {
        (*this)[i] = MathVector<T>(*it, i);
    }
}
template <typename T>
TriangleMatrix<T>::TriangleMatrix(const Matrix<T>& matrix) : Matrix<T>(matrix) {
    for (size_t i = 0; i < this->get_m(); i++) {
        if ((*this)[i].size() != this->get_m() - i) {
            throw std::invalid_argument("Matrix is not triangular!");
        }
    }
}
template <typename T>
TriangleMatrix<T>::TriangleMatrix(const TriangleMatrix<T>& other) : Matrix<T>(other) {

}

template <typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator+(const TriangleMatrix<T>& other) {
    return TriangleMatrix<T>(Matrix<T>::operator+(other));
}
template <typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator-(const TriangleMatrix<T>& other) {
    return TriangleMatrix<T>(Matrix<T>::operator-(other));
}
template <typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(const TriangleMatrix<T>& other) {
    if (this->is_empty() || other.is_empty())
        throw std::invalid_argument("You cannot perform actions with an empty matrix!");
    if (_m != other._n)
        throw std::invalid_argument("You can only multiply triangular matrices of the same size!");
    TriangleMatrix<T> res(_n);
    for (size_t i = 0; i < _n; i++) {
        for (size_t j = i; j < _n; j++) {
            T sum = T();
            for (size_t k = i; k <= j; k++) {
                sum += (*this)[i][k] * other[k][j];
            }
            res[i][j] = sum;
        }
    }
    return res;
}
template <typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(const T& scalar) {
    return TriangleMatrix<T>(Matrix<T>::operator*(scalar));
}
template <typename T>
MathVector<T> TriangleMatrix<T>::operator*(const MathVector<T>& vector) {
    if (this->is_empty() || vector.is_empty())
        throw std::invalid_argument("You cannot perform actions with an empty matrix!");
    if (_n != vector.size())
        throw std::invalid_argument("The matrix and vector are not compatible in size!");
    MathVector<T> res(_n);
    for (size_t i = 0; i < _n; i++) {
        T sum = T();
        for (size_t j = i; j < _n; j++) {
            sum += (*this)[i][j] * vector[j];
        }
        res[i] = sum;
    }
    return res;
}

template <typename T>
TriangleMatrix<T>& TriangleMatrix<T>::operator+=(const TriangleMatrix<T>& other) {
    Matrix<T>::operator+=(other);
    return *this;
}
template <typename T>
TriangleMatrix<T>& TriangleMatrix<T>::operator-=(const TriangleMatrix<T>& other) {
    Matrix<T>::operator-=(other);
    return *this;
}
template <typename T>
TriangleMatrix<T>& TriangleMatrix<T>::operator*=(const TriangleMatrix<T>& other) {
    *this = *this * other;
    return *this;
}
template <typename T>
TriangleMatrix<T>& TriangleMatrix<T>::operator*=(const T& scalar) {
    Matrix<T>::operator*=(scalar);
    return *this;
}

template <typename T>
TriangleMatrix<T>& TriangleMatrix<T>::operator=(const TriangleMatrix<T>& other) {
    if (this != &other) {
        Matrix<T>::operator=(other);
    }
    return *this;
}

template <typename T>
bool TriangleMatrix<T>::operator==(const TriangleMatrix<T>& second) const {
    return Matrix<T>::operator==(second);
}
template <typename T>
bool TriangleMatrix<T>::operator!=(const TriangleMatrix<T>& second) const {
    return !(*this == second);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const TriangleMatrix<T>& matrix) {
    for (size_t i = 0; i < matrix.get_n(); i++) {
        for (size_t j = 0; j < i; j++) {
            os << "0 ";
        }
        for (size_t j = i; j < matrix.get_n(); j++) {
            os << matrix[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}
template <typename T>
std::istream& operator>>(std::istream& is, TriangleMatrix<T>& matrix) {
    for (size_t i = 0; i < matrix.get_n(); i++) {
        for (size_t j = i; j < matrix.get_n(); j++) {
            is >> matrix[i][j];
        }
    }
    return is;
}

#endif  // LIB_TRIANGLEMATRIX_TRIANGLEMATRIX_H_
