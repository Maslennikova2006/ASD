// Copyright 2025 Mary Maslennikova

#ifndef LIB_DLIST_DLIST_H_
#define LIB_DLIST_DLIST_H_

#include <stdexcept>
#include "../lib_list/list.h"

template <class T>
struct DNode {
public:
    T value;
    DNode<T>* next;
    DNode<T>* prev;

    DNode() {
        value = T();
        next = nullptr;
        prev = nullptr;
    }
    DNode(T val, DNode<T>* next_ = nullptr, DNode<T>* prev_ = nullptr) {
        value = val;
        next = next_;
        prev = prev_;
    }
};

template <class T>
class DList {
    DNode<T>* _head;
    DNode<T>* _tail;
    size_t _count;

public:
    DList();
    DList(const DList<T>& other);

    ~DList();

    class Iterator {
        DNode<T>* _current;
    public:
        Iterator() {
            _current = nullptr;
        }
        Iterator(DNode<T>* node) {
            _current = node;
        }

        Iterator& operator++() {
            if (_current == nullptr)
                throw std::invalid_argument("You can't increment end iterator!\n");
            _current = _current->next;
            return *this;
        }
        Iterator operator++(int) {
            Iterator tmp = *this;
            if (_current == nullptr)
                throw std::invalid_argument("You can't increment end iterator!\n");
            _current = _current->next;
            return tmp;
        }
        Iterator& operator+=(int num) {
            for (int i = 0; i < num; i++) {
                if (_current == nullptr)
                    throw std::invalid_argument("You can't increment end iterator!\n");
                _current = _current->next;
            }
            return *this;
        }
        Iterator& operator--() {
            if (_current == nullptr)
                throw std::invalid_argument("You can't decrement begin iterator!\n");
            _current = _current->prev;
            return *this;
        }
        Iterator operator--(int) {
            Iterator tmp = *this;
            if (_current == nullptr)
                throw std::invalid_argument("You can't decrement begin iterator!\n");
            _current = _current->prev;
            return tmp;
        }
        Iterator& operator-=(int num) {
            for (int i = 0; i < num; i++) {
                if (_current == nullptr)
                    throw std::invalid_argument("You can't decrement begin iterator!\n");
                _current = _current->prev;
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
        bool operator!=(const Iterator& other) const noexcept {
            return _current != other._current;
        }
        bool operator==(const Iterator& other) const noexcept {
            return _current == other._current;
        }
    };

    Iterator begin() {
        return Iterator(_head);
    }
    Iterator end() {
        return Iterator(nullptr);
    }

    inline DNode<T>* head() const noexcept;
    inline DNode<T>* tail() const noexcept;

    inline const size_t get_count() const noexcept;

    inline bool is_empty() const noexcept;

    void push_back(const T& val) noexcept;
    void push_front(const T& val) noexcept;
    void insert(DNode<T>* node, const T& val);
    void insert(size_t pos, const T& val);

    void pop_back();
    void pop_front();
    void erase(DNode<T>* node);
    void erase(size_t pos);
};

template <class T>
DList<T>::DList() {
    _head = nullptr;
    _tail = nullptr;
    _count = 0;
}
template <class T>
DList<T>::DList(const DList<T>& other) {
    _head = nullptr;
    _tail = nullptr;
    _count = 0;

    DNode<T>* cur = other._head;
    while (cur != nullptr) {
        push_back(cur->value);
        cur = cur->next;
    }
}

template <class T>
DList<T>::~DList() {
    DNode<T>* cur = _head;
    while (cur != nullptr) {
        DNode<T>* next_node = cur->next;
        delete cur;
        cur = next_node;
    }
    _head = nullptr;
    _tail = nullptr;
    _count = 0;
}

template <class T>
inline DNode<T>* DList<T>::head() const noexcept {
    return _head;
}
template <class T>
inline DNode<T>* DList<T>::tail() const noexcept {
    return _tail;
}

template <class T>
inline const size_t DList<T>::get_count() const noexcept {
    return _count;
}

template <class T>
inline bool DList<T>::is_empty() const noexcept {
    return _head == nullptr;
}

template <class T>
void DList<T>::push_back(const T& val) noexcept {
    DNode<T>* node = new DNode<T>(val);
    if (is_empty()) {
        _head = node;
        _tail = node;
    }
    else {
        node->prev = _tail;
        _tail->next = node;
        _tail = node;
    }
    _count++;
}
template <class T>
void DList<T>::push_front(const T& val) noexcept {
    DNode<T>* node = new DNode<T>(val, _head);
    if (is_empty()) {
        _tail = node;
        _head = node;
    }
    else {
        _head->prev = node;
        _head = node;
    }
    _count++;
}
template <class T>
void DList<T>::insert(DNode<T>* node, const T& val) {
    if (node == nullptr || is_empty())
        throw std::invalid_argument("You can't insert it by following the pointer!\n");
    DNode<T>* new_node = new DNode<T>(val);
    new_node->prev = node;
    new_node->next = node->next;
    node->next = new_node;
    if (new_node->next != nullptr)
        new_node->next->prev = new_node;
    if (node == _tail)
        _tail = new_node;
    _count++;
}
template <class T>
void DList<T>::insert(size_t pos, const T& val) {
    if (pos == 0) {
        push_front(val);
        return;
    }
    if (pos == _count) {
        push_back(val);
        return;
    }
    DNode<T>* cur = _head;
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
void DList<T>::pop_back() {
    if (is_empty())
        throw std::invalid_argument("You can't delete it from an empty list!\n");
    if (_head == _tail) {
        delete _head;
        _head = nullptr;
        _tail = nullptr;
    }
    else {
        DNode<T>* new_tail = _tail->prev;
        delete _tail;
        _tail = new_tail;
        _tail->next = nullptr;
    }
    _count--;
}
template <class T>
void DList<T>::pop_front() {
    if (is_empty())
        throw std::invalid_argument("You can't delete it from an empty list!\n");
    if (_head == _tail) {
        delete _head;
        _head = nullptr;
        _tail = nullptr;
    }
    else {
        DNode<T>* new_head = _head->next;
        delete _head;
        _head = new_head;
        _head->prev = nullptr;
    }
    _count--;
}
template <class T>
void DList<T>::erase(DNode<T>* node) {
    if (node == nullptr || is_empty())
        throw std::invalid_argument("You can't erase an item based on a pointer!\n");
    
    if (node->prev != nullptr)
        node->prev->next = node->next;
    else
        _head = node->next;

    if (node->next != nullptr)
        node->next->prev = node->prev;
    else
        _tail = node->prev;
    _count--;
}
template <class T>
void DList<T>::erase(size_t pos) {
    if (pos == 0) {
        pop_front();
        return;
    }
    if (pos == _count - 1) {
        pop_back();
        return;
    }
    DNode<T>* cur = _head;
    size_t cur_pos = 0;
    while (cur != nullptr) {
        if (cur_pos == pos)
            break;
        cur_pos++;
        cur = cur->next;
    }
    if (cur == nullptr)
        throw std::invalid_argument("Wrong position!\n");
    erase(cur);
}
#endif  // LIB_DLIST_DLIST_H_
