// Copyright 2025 Mary Maslennikova

#include <cstdlib>
#include <stdexcept>
#include <initializer_list>
#include <iostream>

#ifndef LIB_MATHVECTOR_MATHVECTOR_H_
#define LIB_MATHVECTOR_MATHVECTOR_H_

#include "../lib_tvector/tvector.h"

template <typename T>
class MathVector;

template <typename T> std::ostream& operator<<(std::ostream& os, const MathVector<T>& vec);
template <typename T> std::istream& operator>>(std::istream& is, MathVector<T>& vec);

template <typename T>
class MathVector : private TVector<T> {
protected:
    size_t _start_index;

public:
    MathVector();  // םו גûהוכÿעü ןאלÿעü
    explicit MathVector(size_t size);
    MathVector(size_t size, size_t start_index);
    MathVector(size_t size, const T* data);
    MathVector(size_t size, std::initializer_list<T> data);
    MathVector(std::initializer_list<T> data, size_t start_index);
    MathVector(std::initializer_list<T> data);
    MathVector(const MathVector<T>& other);

    ~MathVector();

    inline T* data() noexcept;
    inline size_t size() const noexcept;
    inline size_t capacity() const noexcept;
    inline const T* data() const noexcept;

    void set_start_index(const size_t ind);

    const size_t get_start_index() const noexcept;

    bool is_empty() const noexcept;

    MathVector<T> operator+(const MathVector<T>& second) const;  // +
    MathVector<T> operator-(const MathVector<T>& second) const;  // +
    T operator*(const MathVector<T>& second) const;  // +
    MathVector<T> operator*(const T scalar) const;  // +

    MathVector<T>& operator+=(const MathVector<T>& second);  // +
    MathVector<T>& operator-=(const MathVector<T>& second);  // +
    MathVector<T>& operator*=(const T scalar);  // +

    MathVector<T>& operator=(const MathVector<T>& other);

    const T& operator[](size_t index) const;
    T& operator[](size_t index);
    const T& at(size_t index) const;

    bool operator==(const MathVector<T>& second) const;
    bool operator!=(const MathVector<T>& second) const;

    friend std::ostream& operator<< <T>(std::ostream& os, const MathVector<T>& vec);
    friend std::istream& operator>> <T>(std::istream& is, MathVector<T>& vec);
};

template <class T>
MathVector<T>::MathVector() {  // ???
    _start_index = 0;
}
template <class T>
MathVector<T>::MathVector(size_t size) : TVector<T>(size) {
    _start_index = 0;
    shrink_to_fit();
}
template <class T>
MathVector<T>::MathVector(size_t size, size_t start_index) : TVector<T>(size) {
    _start_index = start_index;
    shrink_to_fit();
}
template <class T>
MathVector<T>::MathVector(size_t size, const T* data) : TVector<T>(size, data) {
    _start_index = 0;
    shrink_to_fit();
}
template <class T>
MathVector<T>::MathVector(size_t size, std::initializer_list<T> data) : TVector<T>(size, data) {
    _start_index = 0;
    shrink_to_fit();
}
template <class T>
MathVector<T>::MathVector(std::initializer_list<T> data) : TVector<T>(data) {
    _start_index = 0;
    shrink_to_fit();
}
template <class T>
MathVector<T>::MathVector(std::initializer_list<T> data, size_t start_index) : TVector<T>(data) {
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
T* MathVector<T>::data() noexcept {
    return TVector<T>::data();
}
template <class T>
size_t MathVector<T>::size() const noexcept {
    return TVector<T>::size();
}
template <class T>
size_t MathVector<T>::capacity() const noexcept{
    return TVector<T>::capacity();
}
template <class T>
inline const T* MathVector<T>::data() const noexcept {
    return TVector<T>::data();
}

template <class T>
void MathVector<T>::set_start_index(const size_t ind) {
    _start_index = ind;
}

template <class T>
const size_t MathVector<T>::get_start_index() const noexcept {
    return _start_index;
}

template <class T>
bool MathVector<T>::is_empty() const noexcept {
    return TVector<T>::is_empty();
}

template <class T>
MathVector<T> MathVector<T>::operator+(const MathVector<T>& second) const { // start_index
    if (this->is_empty() || second.is_empty())
        throw std::invalid_argument("You cannot perform actions with an empty vector!");
    if (this->size() != second.size() || _start_index != second._start_index)
        throw std::invalid_argument("The length of the vectors must match!");
    MathVector<T> res(this->size(), _start_index);
    for (size_t i = _start_index; i < _start_index + this->size(); i++) {
        res[i] = (*this)[i] + second[i];
    }
    return res;
}
template <class T>
MathVector<T> MathVector<T>::operator-(const MathVector<T>& second) const {
    if (this->is_empty() || second.is_empty())
        throw std::invalid_argument("You cannot perform actions with an empty vector!");
    if (this->size() != second.size() || _start_index != second._start_index)
        throw std::invalid_argument("The length of the vectors must match!");
    MathVector<T> res(this->size(), _start_index);
    for (size_t i = _start_index; i < _start_index + this->size(); i++) {
        res[i] = (*this)[i] - second[i];
    }
    return res;
}
template <class T>
T MathVector<T>::operator*(const MathVector<T>& second) const {
    if (this->is_empty() || second.is_empty())
        throw std::invalid_argument("You cannot perform actions with an empty vector!");
    if (this->size() != second.size() || _start_index != second._start_index)
        throw std::invalid_argument("The length of the vectors must match!");
    T res = T();
    for (size_t i = _start_index; i < _start_index + this->size(); i++) {
        res += (*this)[i] * second[i];
    }
    return res;
}
template <class T>
MathVector<T> MathVector<T>::operator*(const T scalar) const {
    if (this->is_empty())
        throw std::invalid_argument("You cannot perform actions with an empty vector!");
    MathVector<T> res(this->size(), _start_index);
    for (size_t i = _start_index; i < _start_index + this->size(); i++) {
        res[i] = (*this)[i] * scalar;
    }
    return res;
}

template <class T>
MathVector<T>& MathVector<T>::operator+=(const MathVector<T>& second) { // +
    if (this->is_empty() || second.is_empty())
        throw std::invalid_argument("You cannot perform actions with an empty vector!");
    if (this->size() != second.size() || _start_index != second._start_index)
        throw std::invalid_argument("The length of the vectors must match!");
    for (size_t i = _start_index; i < _start_index + this->size(); i++) {
        (*this)[i] += second[i];
    }
    return *this;
}
template <class T>
MathVector<T>& MathVector<T>::operator-=(const MathVector<T>& second) {
    if (this->is_empty() || second.is_empty())
        throw std::invalid_argument("You cannot perform actions with an empty vector!");
    if (this->size() != second.size() || _start_index != second._start_index)
        throw std::invalid_argument("The length of the vectors must match!");
    for (size_t i = _start_index; i < _start_index + this->size(); i++) {
        (*this)[i] -= second[i];
    }
    return *this;
}
template <class T>
MathVector<T>& MathVector<T>::operator*=(const T scalar) {
    if (this->is_empty())
        throw std::invalid_argument("You cannot perform actions with an empty vector!");
    for (size_t i = _start_index; i < _start_index + this->size(); i++) {
        (*this)[i] *= scalar;
    }
    return *this;
}

template <class T>
MathVector<T>& MathVector<T>::operator=(const MathVector<T>& other) {
    if (this != &other) {
        this->TVector<T>::operator=(other);
        _start_index = other._start_index;
    }
    return *this;
}

template <class T>
const T& MathVector<T>::operator[](size_t index) const {
    if (index < _start_index || index >= _start_index + size()) {
        return static const T();
    }
    return TVector<T>::operator[](index - _start_index);
}
template <class T>
T& MathVector<T>::operator[](size_t index) {
    if (index < _start_index || index >= _start_index + size()) {
        static T val = T();
        return val;
    }
    return TVector<T>::operator[](index - _start_index);
}
template <class T>
const T& MathVector<T>::at(size_t index) const {
    return TVector<T>::at(index - _start_index);
}

template <class T>
bool MathVector<T>::operator==(const MathVector<T>& second) const {
    return TVector<T>::operator==(second) && _start_index == second._start_index;
}
template <class T>
bool MathVector<T>::operator!=(const MathVector<T>& second) const { // !
    return TVector<T>::operator!=(second) || _start_index != second._start_index;
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
