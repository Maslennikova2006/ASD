// Copyright 2026 Mary Maslennikova

#include <stdexcept>
#include <iostream>
#include <random>
#include <set>
#include <string>

#include "../lib_itable/itable.h"
#include "../lib_list/list.h"

#ifndef LIB_SKIP_LIST_SKIP_LIST_H_
#define LIB_SKIP_LIST_SKIP_LIST_H_

template <class TKey, class TValue>
struct SNode {
    Pair<TKey, TValue> data;
    SNode<TKey, TValue>** next;
    size_t size;

    SNode();
    SNode(const TKey& key, const TValue& val, size_t lvl);

    ~SNode();
};

template <class TKey, class TValue>
SNode<TKey, TValue>::SNode() {
    data = Pair<TKey, TValue>();
    next = nullptr;
    size = 0;
}
template <class TKey, class TValue>
SNode<TKey, TValue>::SNode(const TKey& key, const TValue& val, size_t lvl) {
    Pair<TKey, TValue> pair(key, val);
    data = pair;
    size = lvl + 1;
    next = new SNode<TKey, TValue>*[size];
    for (int i = 0; i < size; i++) {
        next[i] = nullptr;
    }
}

template <class TKey, class TValue>
SNode<TKey, TValue>::~SNode() {
    // удалять каждый узел отдельно ещё
    delete[] next;
}

template <class TKey, class TValue>
class SkipList {
    size_t _MAX_LVL;
    size_t _lvl;
    List<SNode<TKey, TValue>*> _heads;

public:
    SkipList(size_t max_lvl);

    ~SkipList();

    void insert(const TKey&, const TValue&);
    void print() const noexcept;

protected:
    size_t flip_coin() const noexcept;
    SNode<TKey, TValue>* find_nearest(const TKey& key) const noexcept;
    int rand_generation(int min, int max) const noexcept;
};

template <class TKey, class TValue>
SkipList<TKey, TValue>::SkipList(size_t max_lvl) : _heads(), _MAX_LVL(max_lvl) {
    _lvl = flip_coin();
    for (int i = 0; i <= _lvl; i++) {
        SNode<TKey, TValue>* head_node = new SNode<TKey, TValue>();
        head_node->next = new SNode<TKey, TValue>* [_lvl + 1];
        for (int j = 0; j <= _lvl; j++) {
            head_node->next[j] = nullptr;
        }
        _heads.push_back(head_node);
    }
}

template <class TKey, class TValue>
SkipList<TKey, TValue>::~SkipList() {
    if (!_heads.is_empty()) {
        SNode<TKey, TValue>* cur = _heads.head()->value->next[0];
        while (cur != nullptr) {
            SNode<TKey, TValue>* next = cur->next[0];
            delete cur;
            cur = next;
        }
    }

    Node<SNode<TKey, TValue>*>* cur_head = _heads.head();
    while (cur_head != nullptr) {
        delete cur_head->value;
        cur_head = cur_head->next;
    }
}

template <class TKey, class TValue>
void SkipList<TKey, TValue>::insert(const TKey& key, const TValue& val) {
    Pair<TKey, TValue> pair(key, TValue());
    SNode<TKey, TValue>* found_elem = find_nearest(key);
    if (found_elem == nullptr) {
        throw std::runtime_error("find_nearest returned nullptr");
    }
    if (found_elem->next[0] != nullptr && found_elem->next[0]->data.first == key) {
        throw std::invalid_argument("There is already a value with this key!");
    }

    size_t lvl = flip_coin();
    if (lvl > _lvl) {
        for (int i = _lvl + 1; i <= lvl; i++) {
            SNode<TKey, TValue>* head_node = new SNode<TKey, TValue>();
            head_node->size = lvl + 1;
            head_node->next = new SNode<TKey, TValue>* [lvl+1];
            for (size_t j = 0; j <= lvl; j++) {
                head_node->next[j] = nullptr;
            }
            _heads.push_front(head_node);
        }
        _lvl = lvl;
    }

    SNode<TKey, TValue>** smaller_nodes = new SNode<TKey, TValue>* [lvl + 1];
    SNode<TKey, TValue>* cur = _heads.head()->value;
    Node<SNode<TKey, TValue>*>* current_head_node = _heads.head();
    for (int i = lvl; i >= 0; i--) {
        while (cur->next[i] != nullptr && cur->next[i]->data < pair) {
            cur = cur->next[i];
        }
        smaller_nodes[i] = cur;
        //?
        if (i > 0) {
            current_head_node = current_head_node->next;
            cur = current_head_node->value;
        }
    }

    SNode<TKey, TValue>* new_node = new SNode<TKey, TValue>(key, val, lvl);
    for (int i = lvl; i >= 0; i--) {
        new_node->next[i] = smaller_nodes[i]->next[i];
        smaller_nodes[i]->next[i] = new_node;
    }

}
template <class TKey, class TValue>
void SkipList<TKey, TValue>::print() const noexcept {

}

template <class TKey, class TValue>
size_t SkipList<TKey, TValue>::flip_coin() const noexcept {
    size_t level = 0;
    while (level < _MAX_LVL) {
        int gen = rand_generation(1, 100);
        if (gen > 50)
            break;
        level++;
    }
    return level;
}
template <class TKey, class TValue>
SNode<TKey, TValue>* SkipList<TKey, TValue>::find_nearest(const TKey& key) const noexcept {
    Pair<TKey, TValue> pair(key, TValue());
    Node<SNode<TKey, TValue>*>* current_head_node = _heads.head();  //?
    SNode<TKey, TValue>* cur = _heads.head()->value;
    for (int i = _lvl; i >= 0; i--) {
        while (cur->next[i] != nullptr && cur->next[i]->data < pair) {
            cur = cur->next[i];
        }
        // ?
        if (i > 0) {
            current_head_node = current_head_node->next;
            SNode<TKey, TValue>* temp = cur;
            cur = current_head_node->value;

            while (cur->next[i - 1] != nullptr && cur->next[i - 1] != temp->next[i]) {
                cur = cur->next[i - 1];
            }
        }
    }
    return cur;
}
template <class TKey, class TValue>
int SkipList<TKey, TValue>::rand_generation(int min, int max) const noexcept {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(min, max);
    return dist(gen);
}
#endif  // LIB_SKIP_LIST_SKIP_LIST_H_
