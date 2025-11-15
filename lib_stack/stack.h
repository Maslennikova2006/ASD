// Copyright 2025 Mary Maslennikova

#include <cstdlib>
#include <stdexcept>
#include <initializer_list>
#include <iostream>
#include <random>
#ifndef LIB_STACK_STACK_H_
#define LIB_STACK_STACK_H_

#define CAPACITY 15

template <class T>

class Stack {
    T* _data;
    int _size;
    int _top;

public:
    Stack();  // +
    Stack(const int size);  // +
    Stack(const Stack& other);  // +

    ~Stack();

    inline const int get_top() const noexcept;
    inline const int get_size() const noexcept;

    void push(const T& val);  // +
    void pop();  // +
    T top() const;  // +

    inline bool is_empty() const noexcept;  // +
    inline bool is_full() const noexcept;  // +

    void clear() noexcept;  // +
};

template <class T>
Stack<T>::Stack() {
    _size = CAPACITY;
    _data = new T[_size];
    _top = -1;
}

template <class T>
Stack<T>::Stack(const int size) {
    if (size <= 0)
        throw std::invalid_argument("The size must be greater than zero!\n");
    _data = new T[size];
    _size = size;
    _top = -1;
}
template <class T>
Stack<T>::Stack(const Stack& other) {
    if (&other == NULL)
        throw std::invalid_argument("The object was not received!\n");
    _size = other._size;
    _top = other._top;
    _data = new T[_size];
    for (int i = 0; i <= _top; i++) {
        _data[i] = other._data[i];
    }
}

template <class T>
Stack<T>::~Stack() {
    delete[] _data;
}

template <class T>
inline const int Stack<T>::get_top() const noexcept {
    return _top;
}
template <class T>
inline const int Stack<T>::get_size() const noexcept {
    return _size;
}

template <class T>
void Stack<T>::push(const T& val) {
    if (is_full())
        throw std::invalid_argument("The stack is full!\n");
    _data[++_top] = val;
}
template <class T>
void Stack<T>::pop() {
    if (is_empty())
        throw std::invalid_argument("The stack is empty!\n");
    _top--;
}
template <class T>
T Stack<T>::top() const {
    if (is_empty())
        throw std::invalid_argument("The stack is empty!\n");
    return _data[_top];
}

template <class T>
bool Stack<T>::is_empty() const noexcept {
    return _top == -1;
}
template <class T>
bool Stack<T>::is_full() const noexcept {
    return _top == _size - 1;
}

template <class T>
void Stack<T>::clear() noexcept {
    _top = -1;
}
#endif  // LIB_STACK_STACK_H_
