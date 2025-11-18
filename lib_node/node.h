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

    Node<T>& operator=(const Node<T>&);
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
//template <class T>
//Node<T>& Node<T>::operator=(const Node<T>& other) {
//    if (this != &other) {
//        value = other.value;
//        next = other.next;
//    }
//    return *this;
//}
#endif  // LIB_NODE_NODE_H_
