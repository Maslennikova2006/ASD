// Copyright 2025 Mary Maslennikova

#include <cstdlib>
#include <stdexcept>
#include <initializer_list>
#include <iostream>

#ifndef LIB_MATHVECTOR_MATHVECTOR_H_
#define LIB_MATHVECTOR_MATHVECTOR_H_

#include "../lib_tvector/tvector.h"

template <class T>
class MathVector;

template <class T> std::ostream& operator<<(std::ostream& os, const MathVector<T>& vec);
template <class T> std::istream& operator>>(std::istream& is, MathVector<T>& vec);

template <class T>
class MathVector : private TVector<T> {
protected:
    size_t _start_index;

public:
    MathVector();
    MathVector(const size_t size, const size_t start_index = 0);
    MathVector(const size_t size, const T* data, const size_t start_index = 0);
    MathVector(const size_t size, std::initializer_list<T> data, const size_t start_index = 0);
    MathVector(std::initializer_list<T> data, const size_t start_index = 0);
    MathVector(const MathVector<T>& other);

    ~MathVector();

    inline T* data() noexcept;
    inline size_t size() const noexcept;
    inline size_t capacity() const noexcept;
    inline const T* data() const noexcept;

    inline void set_start_index(const size_t ind);

    inline const size_t get_start_index() const noexcept;

    inline bool is_empty() const noexcept;

    MathVector<T> operator+(const MathVector<T>& second) const;  // +
    MathVector<T> operator-(const MathVector<T>& second) const;  // +
    T operator*(const MathVector<T>& second) const;  // +
    MathVector<T> operator*(const T scalar) const;  // +

    MathVector<T>& operator+=(const MathVector<T>& second);  // +
    MathVector<T>& operator-=(const MathVector<T>& second);  // +
    MathVector<T>& operator*=(const T scalar);  // +

    MathVector<T>& operator=(const MathVector<T>& other) noexcept;

    const T& operator[](const size_t index) const noexcept;  // +
    T& operator[](const size_t index) noexcept;  // +
    const T& at(const size_t index) const;  // +

    bool operator==(const MathVector<T>& second) const noexcept;  // +
    bool operator!=(const MathVector<T>& second) const noexcept;  // +

    friend std::ostream& operator<< <T>(std::ostream& os, const MathVector<T>& vec);
    friend std::istream& operator>> <T>(std::istream& is, MathVector<T>& vec);
};

template <class T>
MathVector<T>::MathVector() {
    _start_index = 0;
}
template <class T>
MathVector<T>::MathVector(const size_t size, const size_t start_index) : TVector<T>(size) {
    _start_index = start_index;
    shrink_to_fit();
}
template <class T>
MathVector<T>::MathVector(const size_t size, const T* data, const size_t start_index) : TVector<T>(size, data) {
    _start_index = start_index;
    shrink_to_fit();
}
template <class T>
MathVector<T>::MathVector(const size_t size, std::initializer_list<T> data, const size_t start_index) : TVector<T>(size, data) {
    _start_index = start_index;
    shrink_to_fit();
}
template <class T>
MathVector<T>::MathVector(std::initializer_list<T> data, const size_t start_index) : TVector<T>(data) {
    _start_index = start_index;
    shrink_to_fit();
}
template <class T>
MathVector<T>::MathVector(const MathVector<T>& other) : TVector<T>(other) {
    _start_index = other._start_index;
    shrink_to_fit();
}

template <class T>
MathVector<T>::~MathVector() {}

template <class T>
inline T* MathVector<T>::data() noexcept {
    return this->TVector<T>::data();
}
template <class T>
inline size_t MathVector<T>::size() const noexcept {
    return this->TVector<T>::size();
}
template <class T>
inline size_t MathVector<T>::capacity() const noexcept{
    return this->TVector<T>::capacity();
}
template <class T>
inline const T* MathVector<T>::data() const noexcept {
    return this->TVector<T>::data();
}

template <class T>
inline void MathVector<T>::set_start_index(const size_t ind) {
    _start_index = ind;
}

template <class T>
inline const size_t MathVector<T>::get_start_index() const noexcept {
    return _start_index;
}

template <class T>
inline bool MathVector<T>::is_empty() const noexcept {
    return this->TVector<T>::is_empty();
}

template <class T>
MathVector<T> MathVector<T>::operator+(const MathVector<T>& second) const {
    MathVector<T> res(*this);
    res += second;
    return res;
}
template <class T>
MathVector<T> MathVector<T>::operator-(const MathVector<T>& second) const {
    MathVector<T> res(*this);
    res -= second;
    return res;
}
template <class T>
T MathVector<T>::operator*(const MathVector<T>& second) const {
    if (is_empty() || second.is_empty())
        throw std::invalid_argument("You cannot perform actions with an empty vector!");
    if (size() + _start_index != second.size() + second._start_index)
        throw std::invalid_argument("The length of the vectors must match!");

    size_t max_index = std::max(_start_index, second._start_index);
    T res = T();
    for (size_t i = max_index; i < _start_index + size(); i++) {
        res += (*this)[i] * second[i];
    }
    return res;
}
template <class T>
MathVector<T> MathVector<T>::operator*(const T scalar) const {
    MathVector<T> res(*this);
    res *= scalar;
    return res;
}

template <class T>
MathVector<T>& MathVector<T>::operator+=(const MathVector<T>& second) {
    if (is_empty() || second.is_empty())
        throw std::invalid_argument("You cannot perform actions with an empty vector!");
    if (size() + _start_index != second.size() + second._start_index)
        throw std::invalid_argument("The length of the vectors must match!");

    size_t min_index = std::min(_start_index, second._start_index);
    size_t max_size = std::max(size(), second.size());
    MathVector<T> result(max_size, min_index);
    for (size_t i = min_index; i < size() + _start_index; i++) {
        result[i] = (*this)[i] + second[i];
    }
    *this = result;
    return *this;
}
template <class T>
MathVector<T>& MathVector<T>::operator-=(const MathVector<T>& second) {
    if (is_empty() || second.is_empty())
        throw std::invalid_argument("You cannot perform actions with an empty vector!");
    if (size() + _start_index != second.size() + second._start_index)
        throw std::invalid_argument("The length of the vectors must match!");

    size_t min_index = std::min(_start_index, second._start_index);
    size_t max_size = std::max(size(), second.size());
    MathVector<T> result(max_size, min_index);
    for (size_t i = min_index; i < size() + _start_index; i++) {
        result[i] = (*this)[i] - second[i];
    }
    *this = result;
    return *this;
}
template <class T>
MathVector<T>& MathVector<T>::operator*=(const T scalar) {
    if (is_empty())
        throw std::invalid_argument("You cannot perform actions with an empty vector!");

    for (size_t i = _start_index; i < size() + _start_index; i++) {
        (*this)[i] *= scalar;
    }
    return *this;
}

template <class T>
MathVector<T>& MathVector<T>::operator=(const MathVector<T>& other) noexcept {
    if (this != &other) {
        this->TVector<T>::operator=(other);
        _start_index = other._start_index;
    }
    return *this;
}

template <class T>
const T& MathVector<T>::operator[](const size_t index) const noexcept {
    const T zero = T();
    if (index < _start_index || index >= _start_index + size()) {
        return zero;
    }
    return this->TVector<T>::operator[](index - _start_index);
}
template <class T>
T& MathVector<T>::operator[](const size_t index) noexcept {
    T zero = T();
    if (index < _start_index || index >= _start_index + size()) {
        return zero;
    }
    return this->TVector<T>::operator[](index - _start_index);
}
template <class T>
const T& MathVector<T>::at(const size_t index) const {
    return this->TVector<T>::at(index - _start_index);
}

template <class T>
bool MathVector<T>::operator==(const MathVector<T>& second) const noexcept {
    return this->TVector<T>::operator==(second) && _start_index == second._start_index;
}
template <class T>
bool MathVector<T>::operator!=(const MathVector<T>& second) const noexcept {
    return !((*this) == second);
}

template <class T>
std::ostream& operator<<(std::ostream& os, const MathVector<T>& vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        os << vec[i] << " ";
    }
    return os;
}
template <class T>
std::istream& operator>>(std::istream& is, MathVector<T>& vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        is >> vec[i];
    }
    return is;
}
#endif  // LIB_MATHVECTOR_MATHVECTOR_H_
