// Copyright 2026 Mary Maslennikova

#ifndef LIB_HEAP_HEAP_H_
#define LIB_HEAP_HEAP_H_

#include <stdexcept>
#include "../lib_itable/itable.h"
#include "../lib_tvector/tvector.h"

template <class T>
class Heap {
    TVector<T> _data;

public:
    Heap();
    ~Heap();

    const T& root() const;

    void insert(const T& elem) noexcept;
    void pop();

    bool is_empty() const noexcept;

    void print() const noexcept;

private:
    void ascent() noexcept;
    void dive() noexcept;
};

template <class T>
Heap<T>::Heap() : _data() {}
template <class T>
Heap<T>::~Heap() {}

template <class T>
const T& Heap<T>::root() const {
    if (is_empty())
        throw std::runtime_error("The heap is empty!");
    return _data[0];
}

template <class T>
void Heap<T>::insert(const T& elem) noexcept {
    _data.push_back(elem);
    ascent();
}

template <class T>
void Heap<T>::pop() {
    if (is_empty())
        throw std::runtime_error("Cannot be deleted from an empty heap!");

    _data[0] = _data[_data.size() - 1];
    _data.pop_back();
    dive();
}

template <class T>
bool Heap<T>::is_empty() const noexcept {
    return _data.size() == 0;
}

template <class T>
void Heap<T>::print() const noexcept {
    _data.print();
}

template <class T>
void Heap<T>::ascent() noexcept {
    int i = _data.size() - 1;
    while (i > 0 && _data[i] < _data[(i - 1) / 2]) {
        auto tmp = _data[i];
        _data[i] = _data[(i - 1) / 2];
        _data[(i - 1) / 2] = tmp;
        i = (i - 1) / 2;
    }
}

template <class T>
void Heap<T>::dive() noexcept {
    if (is_empty()) return;

    int i = 0;
    int size = _data.size();

    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int small = i;

        if (left < size && _data[left] < _data[small])
            small = left;

        if (right < size && _data[right] < _data[small])
            small = right;

        if (small != i) {
            auto temp = _data[i];
            _data[i] = _data[small];
            _data[small] = temp;
            i = small;
        }
        else
            break;
    }
}

#endif  // LIB_HEAP_HEAP_H_