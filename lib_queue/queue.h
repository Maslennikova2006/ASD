// Copyright 2025 Mary Maslennikova

#include <cstdlib>
#include <stdexcept>
#include <initializer_list>
#include <iostream>
#include <random>
#ifndef LIB_QUEUE_QUEUE_H_
#define LIB_QUEUE_QUEUE_H_

#define CAPACITY 15

template <class T>
class Queue {
    T* _data;
    int _size;
    int _head;
    int _count;

public:
    Queue();  // +
    Queue(const int size);  // +
    Queue(const Queue& other);  // +

    ~Queue();

    inline int get_size() const noexcept;
    inline int get_count() const noexcept;
    inline int get_head() const noexcept;

    void push(T val);  // +
    void pop();  // +
    T tail() const;  // +
    T head() const;  // +
    
    inline bool is_empty() const noexcept;  // +
    inline bool is_full() const noexcept;  // +

    inline void clear() noexcept;  // +
};

template <class T>
Queue<T>::Queue() {
    _size = CAPACITY;
    _data = new T[_size];
    _head = 0;
    _count = 0;
}
template <class T>
Queue<T>::Queue(const int size) {
    if (size <= 0)
        throw std::invalid_argument("The size must be greater than zero!\n");
    _size = size;
    _data = new T[_size];
    _head = 0;
    _count = 0;
}
template <class T>
Queue<T>::Queue(const Queue& other) {
    if (&other == NULL)
        throw std::invalid_argument("The object was not received!\n");
    _size = other._size;
    _head = other._head;
    _count = other._count;
    _data = new T[_size];
    for (int i = 0; i < _size; i++) {
        _data[i] = other._data[i];
    }
}

template <class T>
Queue<T>::~Queue() {
    delete[] _data;
}

template <class T>
inline int Queue<T>::get_size() const noexcept {
    return _size;
}
template <class T>
inline int Queue<T>::get_count() const noexcept {
    return _count;
}
template <class T>
inline int Queue<T>::get_head() const noexcept {
    return _head;
}

template <class T>
void Queue<T>::push(T val) {
    if (is_full())
        throw std::invalid_argument("The queue is full!\n");
    _data[(_count + _head) % _size] = val;
    _count++;
}
template <class T>
void Queue<T>::pop() {
    if (is_empty())
        throw std::invalid_argument("The queue is empty!\n");
    _head = (_head + 1) % _size;
    _count--;
}
template <class T>
T Queue<T>::tail() const {
    if (is_empty())
        throw std::invalid_argument("The queue is empty!\n");
    return _data[(_count + _head) % _size - 1];
}
template <class T>
T Queue<T>::head() const {
    if (is_empty())
        throw std::invalid_argument("The queue is empty!\n");
    return _data[_head];
}

template <class T>
inline bool Queue<T>::is_empty() const noexcept {
    return _count == 0;
}
template <class T>
inline bool Queue<T>::is_full() const noexcept {
    return _count == _size;
}

template <class T>
inline void Queue<T>::clear() noexcept {
    _head = 0;
    _count = 0;
}
#endif  // LIB_QUEUE_QUEUE_H_
