// Copyright 2025 Mary Maslennikova

#include <cstdlib>
#include <stdexcept>
#include <initializer_list>
#include <iostream>

#ifndef LIB_MATRIX_MATRIX_H_
#define LIB_MATRIX_MATRIX_H_

#include "../lib_mathvector/mathvector.h"

template <class T>
class Matrix;

template <class T>
class MathVector;

template <class T> MathVector<T> operator*(const MathVector<T>& vec, const Matrix<T>& matrix);
template <class T> std::ostream& operator<<(std::ostream& os, const Matrix<T>& vec);
template <class T> std::istream& operator>>(std::istream& is, Matrix<T>& vec);

template <class T>
class Matrix : public MathVector<MathVector<T>> {
protected:
    size_t _m;
    size_t _n;

public:
    Matrix();  // +
    Matrix(size_t m, size_t n);  // +
    Matrix(std::initializer_list<std::initializer_list<T>> lists);  // +
    Matrix(const MathVector<MathVector<T>>& matrix);  // +
    Matrix(const Matrix<T>& other);  // +

    ~Matrix();

    void set_m(const size_t m);
    void set_n(const size_t n);

    const size_t get_m() const noexcept;
    const size_t get_n() const noexcept;

    bool is_empty() const noexcept;

    Matrix<T> Trans() const noexcept;

    Matrix<T> operator+(const Matrix<T>& other);  // +
    Matrix<T> operator-(const Matrix<T>& other);  // +
    Matrix<T> operator*(const Matrix<T>& other);  // +
    Matrix<T> operator*(const T scalar);  // +
    MathVector<T> operator*(const MathVector<T>& vector);  // +

    Matrix<T>& operator+=(const Matrix<T>& second);  // +
    Matrix<T>& operator-=(const Matrix<T>& second);  // +
    Matrix<T>& operator*=(const Matrix<T>& second);  // +
    Matrix<T>& operator*=(const T scalar); // +

    MathVector<T>& operator[](size_t index);  // +
    const MathVector<T>& operator[](size_t index) const;  // +

    Matrix<T>& operator=(const Matrix<T>& other);  // +

    bool operator==(const Matrix<T>& second) const;  // +
    bool operator!=(const Matrix<T>& second) const;  // +

    friend MathVector<T> operator* <T>(const MathVector<T>& vec, const Matrix<T>& matrix);

    friend std::ostream& operator<< <T>(std::ostream& os, const Matrix<T>&);
    friend std::istream& operator>> <T>(std::istream& is, Matrix<T>&);
};

template <typename T>
Matrix<T>::Matrix() : MathVector<MathVector<T>>() {
    _m = 0;
    _n = 0;
}
template <typename T>
Matrix<T>::Matrix(size_t m, size_t n) : MathVector<MathVector<T>>(m), _m(m), _n(n) {
    for (int i = 0; i < m; i++) {
        (*this)[i] = MathVector<T>(n);
    }
}
template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> lists) : 
    MathVector<MathVector<T>>(lists.size()) {
    _m = lists.size();
    _n = (_m > 0) ? lists.begin()->size() : 0;

    auto it = lists.begin();
    for (size_t i = 0; i < _m; i++) {
        (*this)[i] = MathVector<T>(*it);
        it++;
    }
}
template <typename T>
Matrix<T>::Matrix(const MathVector<MathVector<T>>& matrix) 
    : MathVector<MathVector<T>>(matrix) {
    _m = matrix.size();
    _n = (_m > 0) ? matrix[0].size() : 0;
}
template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other) : MathVector<MathVector<T>>(other) {
    _m = other._m;
    _n = other._n;
}

template <typename T>
Matrix<T>::~Matrix() {

}

template <typename T>
void Matrix<T>::set_m(const size_t m) {
    if (m <= 0)
        throw std::invalid_argument("The size cannot be less than or equal to 0!");
    _m = m;
}
template <typename T>
void Matrix<T>::set_n(const size_t n) {
    if (n <= 0)
        throw std::invalid_argument("The size cannot be less than or equal to 0!");
    _n = n;
}

template <typename T>
const size_t Matrix<T>::get_m() const noexcept {
    return _m;
}
template <typename T>
const size_t Matrix<T>::get_n() const noexcept {
    return _n;
}

template <typename T>
bool Matrix<T>::is_empty() const noexcept {
    return (_m == 0 && _n == 0);
}

template <typename T>
Matrix<T> Matrix<T>::Trans() const noexcept {
    if (this->is_empty())
        return *this;
    Matrix<T> res(_n, _m);
    for (size_t i = 0; i < _m; i++) {
        for (size_t j = 0; j < _n; j++) {
            res[j][i] = (*this)[i][j];
        }
    }
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) {
    if (this->is_empty() || other.is_empty())
        throw std::invalid_argument("You cannot perform actions with an empty matrix!");
    if (_m != other._m || _n != other._n)
        throw std::invalid_argument("The matrices are not compatible in size!");
    return Matrix<T>(this->MathVector<MathVector<T>>::operator+(other));
}
template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) {
    if (this->is_empty() || other.is_empty())
        throw std::invalid_argument("You cannot perform actions with an empty matrix!");
    if (_m != other._m || _n != other._n)
        throw std::invalid_argument("The matrices are not compatible in size!");
    return Matrix<T>(this->MathVector<MathVector<T>>::operator-(other));
}
template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) {
    if (this->is_empty() || other.is_empty())
        throw std::invalid_argument("You cannot perform actions with an empty matrix!");
    if (_n != other._m)
        throw std::invalid_argument("The matrices are not compatible in size!");
    Matrix<T> res(_m, other._n);
    Matrix<T> matrix_trans = other.Trans();
    for (size_t i = 0; i < _m; i++) {
        for (size_t j = 0; j < other._n; j++) {
            res[i][j] = (*this)[i] * matrix_trans[j];
        }
    }
    return res;
}
template <typename T>
Matrix<T> Matrix<T>::operator*(const T scalar) {
    if (this->is_empty())
        throw std::invalid_argument("You can't multiply an empty matrix by a scalar!");
    Matrix<T> res(_m, _n);
    for (size_t i = 0; i < _m; i++) {
        res[i] = (*this)[i] * scalar;
    }
    return res;
}
template <typename T>
MathVector<T> Matrix<T>::operator*(const MathVector<T>& vector) {
    if (this->is_empty() || vector.is_empty())
        throw std::invalid_argument("You cannot perform actions with an empty matrix!");
    if (_n != vector.size())
        throw std::invalid_argument("The matrix and vector are not compatible in size!");
    MathVector<T> res(_m);
    for (size_t i = 0; i < _m; i++) {
        res[i] = (*this)[i] * vector;
    }
    return res;
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& second) {
    if (this->is_empty() || second.is_empty())
        throw std::invalid_argument("You cannot perform actions with an empty matrix!");
    if (_m != second._m || _n != second._n)
        throw std::invalid_argument("The matrices are not compatible in size!");
    this->MathVector<MathVector<T>>::operator+=(second);
    return *this;
}
template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& second) {
    if (this->is_empty() || second.is_empty())
        throw std::invalid_argument("You cannot perform actions with an empty matrix!");
    if (_m != second._m || _n != second._n)
        throw std::invalid_argument("The matrices are not compatible in size!");
    this->MathVector<MathVector<T>>::operator-=(second);
    return *this;
}
template <typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& second) {
    if (this->is_empty() || second.is_empty())
        throw std::invalid_argument("You cannot perform actions with an empty matrix!");
    if (_m != _n || _m != second._m || second._m != second._n)
        throw std::invalid_argument("The matrices are not compatible in size!");
    *this = (*this) * second;
    return *this;
}
template <typename T>
Matrix<T>& Matrix<T>::operator*=(const T scalar) {
    if (this->is_empty())
        throw std::invalid_argument("You cannot perform actions with an empty matrix!");
    for (size_t i = 0; i < _m; i++) {
        (*this)[i] *= scalar;
    }
    return *this;
}

template <typename T>
MathVector<T>& Matrix<T>::operator[](size_t index) {
    return MathVector<MathVector<T>>::operator[](index);
}
template <typename T>
const MathVector<T>& Matrix<T>::operator[](size_t index) const {
    return MathVector<MathVector<T>>::operator[](index);
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
    if (this != &other) {
        MathVector<MathVector<T>>::operator=(other);
        _m = other._m;
        _n = other._n;
    }
    return *this;
}

template <typename T>
bool Matrix<T>::operator==(const Matrix<T>& second) const {
    if (_m != second._m || _n != second._n)
        return false;

    for (size_t i = 0; i < _m; ++i) {
        if (!((*this)[i] == second[i]))
            return false;
    }
    return true;
}
template <typename T>
bool Matrix<T>::operator!=(const Matrix<T>& second) const {
    return !(this->operator==(second));
}
template <typename T>
MathVector<T> operator*(const MathVector<T>& vec, const Matrix<T>& matrix) {
    if (vec.is_empty() || matrix.is_empty())
        throw std::invalid_argument("You cannot perform actions with an empty matrix!");
    if (vec.size() != matrix.get_m())
        throw std::invalid_argument("The matrix and vector are not compatible in size!");
    MathVector<T> res(matrix.get_n());
    Matrix<T> trans_matrix = matrix.Trans();
        for (size_t i = 0; i < matrix.get_n(); i++) {
        res[i] = vec * trans_matrix[i];
        }
    return res;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
    for (size_t i = 0; i < matrix.get_m(); i++) {
        os << matrix[i];
        if (i < matrix.get_m() - 1) 
            os << "\n";
    }
    return os;
}
template <typename T>
std::istream& operator>>(std::istream& is, Matrix<T>& matrix) {
    for (size_t i = 0; i < matrix.get_m(); i++) {
        is >> matrix[i];
    }
    return is;
}
#endif  // LIB_MATRIX_MATRIX_H_
