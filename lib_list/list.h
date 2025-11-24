// Copyright 2025 Mary Maslennikova

#ifndef LIB_LIST_LIST_H_
#define LIB_LIST_LIST_H_

#include <stdexcept>

#include "../lib_node/node.h"

template <class T>
class List {
    Node<T>* _head;
    Node<T>* _tail;
    size_t _count;

public:
    List();  // +
    List(const List<T>& other);  // +

    ~List();

    class Iterator {
        Node<T>* _current;
    public:
        Iterator() {
            _current = nullptr;
        }
        Iterator(Node<T>* node) {
            _current = node;
        }

        Iterator next() {
            return _current->next;
        }

        Iterator& operator++() {
            if (_current != nullptr) {
                _current = _current->next;
            }
            return *this;
        }
        Iterator operator++(int) {
            Iterator tmp = *this;
            if (_current != nullptr) {
                _current = _current->next;
            }
            return tmp;
        }
        Iterator& operator+=(int num) {
            for (int i = 0; i < num && _current != nullptr; i++) {
                _current = _current->next;
            }
            return *this;
        }
        Iterator& operator=(const Iterator& other) {
            if (this != &other)
                _current = other._current;
            return *this;
        }
        T& operator*() {
            if (_current == nullptr)
                throw std::invalid_argument("You can't dereference an empty pointer!");
            return _current->value;
        }
        /*Iterator* operator->() {
            if (_current == nullptr)
                throw std::invalid_argument("You can't dereference an empty pointer!");
            return _current;
        }*/
        bool operator!=(const Iterator& other) {
            return _current != other._current;
        }
        bool operator==(const Iterator& other) {
            return _current == other._current;
        }
    };

    Iterator begin() {
        return Iterator(_head);
    }
    Iterator end() {
        return Iterator(nullptr);
    }
    const Iterator begin() const {
        return Iterator(_head);
    }
    const Iterator end() const {
        return Iterator(nullptr);
    }

    inline Node<T>* head() const noexcept;
    inline Node<T>* tail() const noexcept;

    inline const size_t get_count() const noexcept;

    inline bool is_empty() const noexcept;  // +

    void push_back(const T& val) noexcept;  // +
    void push_front(const T& val) noexcept;  // +
    void insert(Node<T>* node, const T& val);  // +
    void insert(size_t pos, const T& val);  // +

    void pop_back();  // +
    void pop_front();  // +
    void erase(Node<T>* node);  // +
    void erase(size_t pos);  // +
};

template <class T>
List<T>::List() {
    _head = nullptr;
    _tail = nullptr;
    _count = 0;
}
template <class T>
List<T>::List(const List<T>& other) {
    _head = nullptr;
    _tail = nullptr;
    _count = 0;

    Node<T>* cur = other._head;
    for (int i = 0; i < other._count; i++) {
        push_back(cur->value);
        cur = cur->next;
    }
}

template <class T>
List<T>::~List() {
    Node<T>* cur = _head;
    while (cur != nullptr) {
        Node<T>* next_node = cur->next;
        delete cur;
        cur = next_node;
    }
    _head = nullptr;
    _tail = nullptr;
    _count = 0;
}

template <class T>
inline Node<T>* List<T>::head() const noexcept {
    return _head;
}
template <class T>
inline Node<T>* List<T>::tail() const noexcept {
    return _tail;
}

template <class T>
inline const size_t List<T>::get_count() const noexcept {
    return _count;
}

template <class T>
inline bool List<T>::is_empty() const noexcept {
    return _head == nullptr;
}

template <class T>
void List<T>::push_back(const T& val) noexcept {
    Node<T>* node = new Node<T>(val);
    if (is_empty()) {
        _head = node;
        _tail = node;
        _count++;
        return;
    }
    _tail->next = node;
    _tail = node;
    _count++;
}
template <class T>
void List<T>::push_front(const T& val) noexcept {
    Node<T>* node = new Node<T>(val, _head);
    if (is_empty())
        _tail = node;
    _head = node;
    _count++;
}
template <class T>
void List<T>::insert(Node<T>* node, const T& val) {
    if (node == nullptr || is_empty())
        throw std::invalid_argument("You can't insert it by following the pointer!\n");
    Node<T>* new_node = new Node<T>(val);
    new_node->next = node->next;
    node->next = new_node;
    if (node == _tail)
        _tail = new_node;
    _count++;
}
template <class T>
void List<T>::insert(size_t pos, const T& val) {
    if (pos == 0) {
        push_front(val);
        return;
    }
    if (pos == _count) {
        push_back(val);
        return;
    }
    Node<T>* cur = _head;
    size_t cur_pos = 0;
    while (cur != nullptr) {
        if (cur_pos == pos - 1)
            break;
        cur_pos++;
        cur = cur->next;
    }
    if (cur == nullptr)
        throw std::invalid_argument("Wrong position!\n");
    insert(cur, val);
}

template <class T>
void List<T>::pop_back() {
    if (is_empty())
        throw std::invalid_argument("You can't delete it from an empty list!\n");
    if (_head == _tail) {
        delete _head;
        _head = nullptr;
        _tail = nullptr;
        _count--;
        return;
    }
    Node<T>* cur = _head;
    while (cur->next != _tail) {
        cur = cur->next;
    }
    delete _tail;
    _tail = cur;
    cur->next = nullptr;
    _count--;
}
template <class T>
void List<T>::pop_front()  {
    if (is_empty())
        throw std::invalid_argument("You can't delete it from an empty list!\n");
    if (_head == _tail) {
        delete _head;
        _head = nullptr;
        _tail = nullptr;
        _count--;
        return;
    }
    Node<T>* node = _head->next;
    delete _head;
    _head = node;
    _count--;
}
template <class T>
void List<T>::erase(Node<T>* node) {
    if (node == nullptr || is_empty())
        throw std::invalid_argument("You can't erase an item based on a pointer!\n");
    Node<T>* node_del = node->next;
    Node<T>* new_node = node_del->next;
    node->next = new_node;
    if (node_del == _tail) {
        _tail = node;
    }
    delete node_del;
    _count--;
}
template <class T>
void List<T>::erase(size_t pos) {
    if (pos == 0) {
        pop_front();
        return;
    }
    if (pos == _count - 1) {
        pop_back();
        return;
    }
    Node<T>* cur = _head;
    size_t cur_pos = 0;
    while (cur != nullptr) {
        if (cur_pos == pos - 1)
            break;
        cur_pos++;
        cur = cur->next;
    }
    if (cur == nullptr)
        throw std::invalid_argument("Wrong position!\n");
    erase(cur);
}

#endif  // LIB_LIST_LIST_H_