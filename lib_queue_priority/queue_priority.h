// Copyright 2026 Mary Maslennikova

#include <cstdlib>
#include <stdexcept>
#include <initializer_list>
#include <iostream>
#include <random>
#include "../lib_heap/heap.h"
#ifndef LIB_QUEUEPRIORITY_QUEUEPRIORITY_H_
#define LIB_QUEUEPRIORITY_QUEUEPRIORITY_H_

template <class TValue>
struct PairPriority {
    int priority;
    int order;
    TValue value;

    PairPriority();
    PairPriority(const int& key, const TValue& val, const int& ord);

    PairPriority<TValue>& operator=(const PairPriority<TValue>& other) noexcept;

    bool operator<(const PairPriority<TValue>& other) const;
    bool operator>(const PairPriority<TValue>& other) const;

    friend std::ostream& operator<<(std::ostream& os, const PairPriority<TValue>& pair) {
        os << pair.priority << ":" << pair.value;
        return os;
    }
};

template <class TValue>
PairPriority<TValue>::PairPriority() {
    priority = 0;
    value = TValue();
    order = 0;
}
template <class TValue>
PairPriority<TValue>::PairPriority(const int& key, const TValue& val, const int& ord) {
    priority = key;
    value = val;
    order = ord;
}

template <class TValue>
PairPriority<TValue>& PairPriority<TValue>::operator=(const PairPriority& other) noexcept {
    if (this != &other) {
        priority = other.priority;
        value = other.value;
    }
    return *this;
}

template <class TValue>
bool PairPriority<TValue>::operator<(const PairPriority<TValue>& other) const {
    if (priority == other.priority)
        return order < other.order;
    return priority < other.priority;
}
template <class TValue>
bool PairPriority<TValue>::operator>(const PairPriority<TValue>& other) const {
    if (priority == other.priority)
        return order > other.order;
    return priority > other.priority;
}

template <class T>
class QueuePriority {
    Heap<T> _heap;

public:
    QueuePriority();
    ~QueuePriority();

    const T& top() const;

    void insert(const T& elem) noexcept;
    void pop();

    bool is_empty() const noexcept;

    void print() const noexcept;
};

template <class T>
QueuePriority<T>::QueuePriority() : _heap() {}
template <class T>
QueuePriority<T>::~QueuePriority() {}

template <class T>
const T& QueuePriority<T>::top() const {
    return _heap.root();
}

template <class T>
void QueuePriority<T>::insert(const T& elem) noexcept {
    _heap.insert(elem);
}
template <class T>
void QueuePriority<T>::pop() {
    _heap.pop();
}

template <class T>
bool QueuePriority<T>::is_empty() const noexcept {
    return _heap.is_empty();
}

template <class T>
void QueuePriority<T>::print() const noexcept {
    _heap.print();
}
#endif  // LIB_QUEUEPRIORITY_QUEUEPRIORITY_H_