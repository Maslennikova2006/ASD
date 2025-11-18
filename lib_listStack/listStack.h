// Copyright 2025 Mary Maslennikova

#ifndef LIB_LISTSTACK_LISTSTACK_H_
#define LIB_LISTSTACK_LISTSTACK_H_

#include <stdexcept>
#include "../lib_list/list.h"

template <class T>
class ListStack {
    List<T> _data;
    int _size;

public:
    ListStack();
    ListStack(const int size);
    ListStack(const ListStack<T>& other);

    inline const int get_size() const noexcept;

    void push(const T& val);
    void pop();
    T top() const;

    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;

    void clear() noexcept;
};

template <class T>
ListStack<T>::ListStack() {
    _data = List<T>();
    _size = -1;
}
template <class T>
ListStack<T>::ListStack(const int size) {
    if (size <= 0)
        throw std::invalid_argument("The size must be greater than zero!\n");
    _data = List<T>();
    _size = size;
}
template <class T>
ListStack<T>::ListStack(const ListStack<T>& other) {
    _data = other._data;
    _size = other._size;
}

template <class T>
inline const int ListStack<T>::get_size() const noexcept {
    return _size;
}

template <class T>
void ListStack<T>::push(const T& val) {
    if (is_full())
        throw std::invalid_argument("The stack is full!\n");
    _data.push_back(val);
}
template <class T>
void ListStack<T>::pop() {
    if (is_empty())
        throw std::invalid_argument("The stack is empty!\n");
    _data.pop_back();
}
template <class T>
T ListStack<T>::top() const {
    if (is_empty())
        throw std::invalid_argument("The stack is empty!\n");
    return _data.tail()->value;
}

template <class T>
inline bool ListStack<T>::is_empty() const noexcept {
    return _data.is_empty();
}
template <class T>
inline bool ListStack<T>::is_full() const noexcept {
    if (_size == -1)
        return false;
    return _data.get_count() == _size;
}

template <class T>
void ListStack<T>::clear() noexcept {
    while (!is_empty())
        _data.pop_back();
}


#endif  // LIB_LISTSTACK_LISTSTACK_H_