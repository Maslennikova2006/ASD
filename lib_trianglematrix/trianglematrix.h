// Copyright 2025 Mary Maslennikova

#include <cstdlib>
#include <stdexcept>
#include <initializer_list>
#include <iostream>

#ifndef LIB_TRIANGLEMATRIX_TRIANGLEMATRIX_H_
#define LIB_TRIANGLEMATRIX_TRIANGLEMATRIX_H_

#include "../lib_matrix/matrix.h"

template <class T>
class TriangleMatrix;
template <class T>
class MathVector;

template <class T> MathVector<T> operator*(const MathVector<T>& vec, const TriangleMatrix<T>& matrix);
template <class T> std::ostream& operator<<(std::ostream& os, const TriangleMatrix<T>& vec);
template <class T> std::istream& operator>>(std::istream& is, TriangleMatrix<T>& vec);

template <class T>
class TriangleMatrix : public Matrix<T> {

public:
    TriangleMatrix();  // +
    TriangleMatrix(const size_t size);  // +
    TriangleMatrix(std::initializer_list<std::initializer_list<T>> lists);  // +
    TriangleMatrix(const Matrix<T>& matrix);  // +
    TriangleMatrix(const TriangleMatrix<T>& other);  // +

    TriangleMatrix<T> operator+(const TriangleMatrix<T>& other) const;  // +
    TriangleMatrix<T> operator-(const TriangleMatrix<T>& other) const;  // +
    TriangleMatrix<T> operator*(const TriangleMatrix<T>& other) const;  // +
    TriangleMatrix<T> operator*(const T& scalar) const;  // +
    MathVector<T> operator*(const MathVector<T>& vector) const;  // +

    TriangleMatrix<T>& operator+=(const TriangleMatrix<T>& other);  // +
    TriangleMatrix<T>& operator-=(const TriangleMatrix<T>& other);  // +
    TriangleMatrix<T>& operator*=(const TriangleMatrix<T>& other);  // +
    TriangleMatrix<T>& operator*=(const T& scalar);  // +

    TriangleMatrix<T>& operator=(const TriangleMatrix<T>& other) noexcept;  // +

    bool operator==(const TriangleMatrix<T>& second) const noexcept;  // +
    bool operator!=(const TriangleMatrix<T>& second) const noexcept;  // +

    friend MathVector<T> operator*(const MathVector<T>& vec, const TriangleMatrix<T>& matrix);

    friend std::ostream& operator<< <T>(std::ostream& os, const TriangleMatrix<T>&);
    friend std::istream& operator>> <T>(std::istream& is, TriangleMatrix<T>&);
};

template <class T>
TriangleMatrix<T>::TriangleMatrix() : Matrix<T>() {

}
template <class T>
TriangleMatrix<T>::TriangleMatrix(const size_t size) : Matrix<T>(size, size) {
    for (size_t i = 0; i < size; i++) {
        (*this)[i] = MathVector<T>(size - i, i);
    }
}
template <class T>
TriangleMatrix<T>::TriangleMatrix(std::initializer_list<std::initializer_list<T>> lists) : Matrix<T>(lists) {
    if (_m != _n)
        throw std::invalid_argument("A triangular matrix has the same number of rows and columns!");
    size_t i = 0;
    for (auto it = lists.begin(); it != lists.end(); it++, i++) {
        (*this)[i] = MathVector<T>(*it, i);
    }
}
template <class T>
TriangleMatrix<T>::TriangleMatrix(const Matrix<T>& matrix) : Matrix<T>(matrix) {
    for (size_t i = 0; i < this->get_m(); i++) {
        if ((*this)[i].size() != this->get_m() - i) {
            throw std::invalid_argument("Matrix is not triangular!");
        }
    }
}
template <class T>
TriangleMatrix<T>::TriangleMatrix(const TriangleMatrix<T>& other) : Matrix<T>(other) {

}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator+(const TriangleMatrix<T>& other) const {
    return TriangleMatrix<T>(Matrix<T>::operator+(other));
}
template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator-(const TriangleMatrix<T>& other) const {
    return TriangleMatrix<T>(Matrix<T>::operator-(other));
}
template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(const TriangleMatrix<T>& other) const {
    TriangleMatrix<T> res(*this);
    res *= other;
    return res;
}
template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(const T& scalar) const {
    return TriangleMatrix<T>(Matrix<T>::operator*(scalar));
}
template <class T>
MathVector<T> TriangleMatrix<T>::operator*(const MathVector<T>& vector) const {
    return this->Matrix<T>::operator*(vector);
}

template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator+=(const TriangleMatrix<T>& other) {
    Matrix<T>::operator+=(other);
    return *this;
}
template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator-=(const TriangleMatrix<T>& other) {
    Matrix<T>::operator-=(other);
    return *this;
}
template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator*=(const TriangleMatrix<T>& other) {
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
    (*this) = res;
    return *this;
}
template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator*=(const T& scalar) {
    Matrix<T>::operator*=(scalar);
    return *this;
}

template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator=(const TriangleMatrix<T>& other) noexcept {
    if (this != &other) {
        this->Matrix<T>::operator=(other);
    }
    return *this;
}

template <class T>
bool TriangleMatrix<T>::operator==(const TriangleMatrix<T>& second) const noexcept {
    return this->Matrix<T>::operator==(second);
}
template <class T>
bool TriangleMatrix<T>::operator!=(const TriangleMatrix<T>& second) const noexcept {
    return !(*this == second);
}

template <class T>
MathVector<T> operator*(const MathVector<T>& vec, const TriangleMatrix<T>& matrix) {
    if (vec.is_empty() || matrix.is_empty())
        throw std::invalid_argument("You cannot perform actions with an empty matrix!");
    if (vec.size() != matrix.get_m())
        throw std::invalid_argument("The matrix and vector are not compatible in size!");
    MathVector<T> res(matrix.get_m());
    for (size_t i = 0; i < matrix.get_n(); i++) {
        T sum = T();
        for (size_t j = 0; j < matrix.get_m(); j++) {
            sum += vec[j] * matrix[j][i];
        }
        res[i] = sum;
    }
    return res;
}

template <class T>
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
template <class T>
std::istream& operator>>(std::istream& is, TriangleMatrix<T>& matrix) {
    for (size_t i = 0; i < matrix.get_n(); i++) {
        for (size_t j = i; j < matrix.get_n(); j++) {
            is >> matrix[i][j];
        }
    }
    return is;
}

#endif  // LIB_TRIANGLEMATRIX_TRIANGLEMATRIX_H_
