// Copyright 2025 Mary Maslennikova

#ifndef LIB_NODE_NODE_H_
#define LIB_NODE_NODE_H_

template <class T> 
struct Node {
public:
    T value;
    Node<T>* next;

    Node();
    Node(T val, Node<T>* next_ = nullptr);
};

template <class T>
Node<T>::Node() {
    value = T();
    next = nullptr;
}
template <class T>
Node<T>::Node(T val, Node<T>* next_) {
    value = val;
    next = next_;
}
#endif  // LIB_NODE_NODE_H_
