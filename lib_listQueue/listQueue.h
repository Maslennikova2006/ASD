// Copyright 2025 Mary Maslennikova

#ifndef LIB_LISTQUEUE_LISTQUEUE_H_
#define LIB_LISTQUEUE_LISTQUEUE_H_

#include <stdexcept>
#include "../lib_list/list.h"

template <class T>
class ListQueue {
    List<T> _data;
    int _size;

public:
    ListQueue();
    ListQueue(const int size);
    ListQueue(const ListQueue<T>& other);

    inline int get_size() const noexcept;

    void push(T val);
    void pop();
    T tail() const;
    T head() const;

    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;

    inline void clear() noexcept;
};

template <class T>
ListQueue<T>::ListQueue() {
    _data = List<T>();
    _size = -1;
}
template <class T>
ListQueue<T>::ListQueue(const int size) {
    if (size <= 0)
        throw std::invalid_argument("The size must be greater than zero!\n");
    _data = List<T>();
    _size = size;
}
template <class T>
ListQueue<T>::ListQueue(const ListQueue<T>& other) {
    if (&other == NULL)
        throw std::invalid_argument("The object was not received!\n");
    _size = other._size;
    _data = other._data;
}

template <class T>
inline int ListQueue<T>::get_size() const noexcept {
    return _size;
}

template <class T>
void ListQueue<T>::push(T val) {
    if (is_full())
        throw std::invalid_argument("The queue is full!\n");
    _data.push_back(val);
}
template <class T>
void ListQueue<T>::pop() {
    if (is_empty())
        throw std::invalid_argument("The queue is empty!\n");
    _data.pop_front();
}

template <class T>
T ListQueue<T>::head() const {
    if (is_empty())
        throw std::invalid_argument("The queue is empty!\n");
    return _data.head()->value;
}
template <class T>
T ListQueue<T>::tail() const {
    if (is_empty())
        throw std::invalid_argument("The queue is empty!\n");
    return _data.tail()->value;
}

template <class T>
inline bool ListQueue<T>::is_empty() const noexcept {
    return _data.is_empty();
}
template <class T>
inline bool ListQueue<T>::is_full() const noexcept {
    if (_size == -1)
        return false;
    return _data.get_count() == _size;
}

template <class T>
inline void ListQueue<T>::clear() noexcept {
    while (!is_empty()) {
        _data.pop_back();
    }
}

#endif  // LIB_LISTQUEUE_LISTQUEUE_H_