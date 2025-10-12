// Copyright 2025 Mary Maslennikova

#include <cstdlib>
#include <stdexcept>
#include <initializer_list>
#include <iostream>
#include <random>
#ifndef LIB_QUEUE_QUEUE_H_
#define LIB_QUEUE_QUEUE_H_

template <class T>

class Queue {
    T* _data;
    int _size;
    int _head;
    int _tail;
    //  int _count;

public:
    Queue() = default;
    Queue(const int size);
    Queue(const Queue& other);

    ~Queue();

    void push(T val);
    void pop();
    T tail() const;
    T head() const;
    
    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;
};

#endif  // LIB_QUEUE_QUEUE_H_