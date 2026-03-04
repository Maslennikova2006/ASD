// Copyright 2026 Mary Maslennikova

#include <stdexcept>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>

#include "../lib_itable/itable.h"
#include "../lib_list/list.h"
#include "../lib_tvector/tvector.h"

#ifndef LIB_SKIP_LIST_SKIP_LIST_H_
#define LIB_SKIP_LIST_SKIP_LIST_H_

template <class TKey, class TValue>
struct SNode {
    Pair<TKey, TValue> data;
    SNode<TKey, TValue>** next;
    size_t level;

    SNode(size_t lvl = 0);
    SNode(const TKey& key, const TValue& val, size_t lvl);

    ~SNode();
};

template <class TKey, class TValue>
SNode<TKey, TValue>::SNode(size_t lvl) : data(), level(lvl) {
    next = new SNode<TKey, TValue>*[level + 1];
    for (size_t i = 0; i <= level; i++) {
        next[i] = nullptr;
    }
}
template <class TKey, class TValue>
SNode<TKey, TValue>::SNode(const TKey& key, const TValue& val, size_t lvl)
    : data(key, val), level(lvl) {
    next = new SNode<TKey, TValue>*[level + 1];
    for (int i = 0; i <= level; i++) {
        next[i] = nullptr;
    }
}

template <class TKey, class TValue>
SNode<TKey, TValue>::~SNode() {
    delete[] next;
}

template <class TKey, class TValue>
class SkipList {
    size_t _MAX_LVL;
    size_t _lvl;
    List<SNode<TKey, TValue>*> _heads;

public:
    SkipList(size_t max_lvl = -1);

    ~SkipList();

    void insert(const TKey&, const TValue&);
    void print() const noexcept;

protected:
    size_t flip_coin() const noexcept;
    SNode<TKey, TValue>** find_nearest(const TKey& key) const noexcept;
};

template <class TKey, class TValue>
SkipList<TKey, TValue>::SkipList(size_t max_lvl)
    : _heads(), _MAX_LVL(max_lvl), _lvl(0) {
    srand(time(0));
    SNode<TKey, TValue>* head_node = new SNode<TKey, TValue>();
    _heads.push_back(head_node);
}

template <class TKey, class TValue>
SkipList<TKey, TValue>::~SkipList() {
    if (_heads.is_empty()) 
        return;

    SNode<TKey, TValue>* head_node = _heads.tail()->value;

    SNode<TKey, TValue>* cur = head_node->next[0];
    while (cur != nullptr) {
        SNode<TKey, TValue>* next = cur->next[0];
        delete cur;
        cur = next;
    }

    Node<SNode<TKey, TValue>*>* head = _heads.head();
    while (head != nullptr) {
        delete head->value;
        head = head->next;
    }
}

template <class TKey, class TValue>
void SkipList<TKey, TValue>::insert(const TKey& key, const TValue& val) {
    SNode<TKey, TValue>** smaller_nodes = find_nearest(key);

    if (smaller_nodes[0] != nullptr &&
        smaller_nodes[0]->next[0] != nullptr &&
        smaller_nodes[0]->next[0]->data.first == key) {
        delete[] smaller_nodes;
        throw std::invalid_argument("There is already a value with this key!");
    }

    size_t new_level = flip_coin();

    if (new_level > _lvl) {
        for (size_t i = _lvl + 1; i <= new_level; i++) {
            SNode<TKey, TValue>* head_node = new SNode<TKey, TValue>(_MAX_LVL);
            _heads.push_front(head_node);
            smaller_nodes[i] = head_node;
            if (i > 0 && !_heads.is_empty()) {
                SNode<TKey, TValue>* prev_head = _heads.head()->next->value;
                for (size_t j = 0; j < i; j++) {
                    head_node->next[j] = prev_head->next[j];
                }
            }
        }
        _lvl = new_level;
    }

    SNode<TKey, TValue>* new_node = new SNode<TKey, TValue>(key, val, new_level);
    for (size_t i = 0; i <= new_level; i++) {
        if (i <= _lvl && smaller_nodes[i] != nullptr) {
            new_node->next[i] = smaller_nodes[i]->next[i];
            smaller_nodes[i]->next[i] = new_node;
        }
    }

    delete[] smaller_nodes;
}
template <class TKey, class TValue>
void SkipList<TKey, TValue>::print() const noexcept {
    if (_heads.is_empty()) {
        std::cout << "Empty Skip List" << std::endl;
        return;
    }

    SNode<TKey, TValue>* head_null_lvl = _heads.tail()->value;

    TVector<TKey> keys;
    SNode<TKey, TValue>* curr = head_null_lvl->next[0];
    while (curr != nullptr) {
        keys.push_back(curr->data.first);
        curr = curr->next[0];
    }

    size_t max_len = 0;
    for (int i = 0; i < keys.size(); i++) {
        max_len = std::max(max_len, std::to_string(keys[i]).length());
    }

    int level = _lvl;
    for (auto it = _heads.begin(); it != _heads.end(); it++, level--) {
        SNode<TKey, TValue>* head = *it;

        std::cout << "Level " << level << ": ";

        SNode<TKey, TValue>* node = head->next[level];
        size_t key_index = 0;

        while (key_index < keys.size()) {
            if (node != nullptr && node->data.first == keys[key_index]) {
                std::cout << "[" << std::setw(max_len) << node->data << "]";
                node = node->next[level];

                if (key_index < keys.size() - 1) {
                    std::cout << "->";
                }
            }
            else {
                std::cout << std::string(max_len + 5, '-');
                if (key_index < keys.size() - 1) {
                    std::cout << "->";
                }
            }
            key_index++;
        }

        while (node != nullptr) {
            std::cout << "->[" << node->data << "]";
            node = node->next[level];
        }

        std::cout << "->nullptr\n";
    }
}

template <class TKey, class TValue>
size_t SkipList<TKey, TValue>::flip_coin() const noexcept {
    size_t level = 0;
    while (level < _MAX_LVL && (rand() % 100 < 50)) {
        level++;
    }
    return level;
}
template <class TKey, class TValue>
SNode<TKey, TValue>** SkipList<TKey, TValue>::find_nearest(const TKey& key) const noexcept {
    SNode<TKey, TValue>** smaller_nodes = new SNode<TKey, TValue>* [_MAX_LVL + 1];
    for (size_t i = 0; i <= _MAX_LVL; i++) {
        smaller_nodes[i] = nullptr;
    }

    if (_heads.is_empty()) {
        return smaller_nodes;
    }

    SNode<TKey, TValue>* cur = _heads.head()->value;
    for (int i = static_cast<int>(_lvl); i >= 0; i--) {
        while (cur->next[i] != nullptr && cur->next[i]->data.first < key) {
            cur = cur->next[i];
        }
        smaller_nodes[i] = cur;
    }

    return smaller_nodes;
}
#endif  // LIB_SKIP_LIST_SKIP_LIST_H_
