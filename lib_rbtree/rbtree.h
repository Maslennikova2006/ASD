// Copyright 2026 Mary Maslennikova

#ifndef LIB_RBTREE_RBTREE_H_
#define LIB_RBTREE_RBTREE_H_

#include "../lib_itable/itable.h"
#include "../lib_tree/tree.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <algorithm>

template <class TKey, class TValue>
struct RBNode {
    Pair<TKey, TValue> data;
    RBNode<TKey, TValue>* left;
    RBNode<TKey, TValue>* right;
    RBNode<TKey, TValue>* parent;
    size_t height;

    RBNode();
    RBNode(const TKey& key, const TValue& val, RBNode<TKey, TValue>* l = nullptr, RBNode<TKey, TValue>* r = nullptr,
        RBNode<TKey, TValue>* p = nullptr, size_t h = 1);
};

template <class TKey, class TValue>
RBNode<TKey, TValue>::RBNode() : data(), left(nullptr), right(nullptr), parent(nullptr), height(1) {}
template <class TKey, class TValue>
RBNode<TKey, TValue>::RBNode(const TKey& key, const TValue& val, RBNode<TKey, TValue>* l, RBNode<TKey, TValue>* r, RBNode<TKey, TValue>* p, size_t h) :
    data(key, val), left(l), right(r), parent(p), height(h) {}

template <class TKey, class TValue>
class RBTree {
    RBNode<TKey, TValue>* _root;

public:
    RBTree();
    ~RBTree();

    RBNode<TKey, TValue>* root() const noexcept;

    void insert(const TKey& key, const TValue& val);  // +
    TValue* find(const TKey& key) const noexcept;  // +
    void erase(const TKey& key);  // +
    void clear() noexcept;  // +

    bool is_empty() const noexcept;  // +

    void print_lcr() const noexcept;
    void print() const noexcept;

private:
    

    int get_height(RBNode<TKey, TValue>* node) const noexcept;
    void fill_matrix(RBNode<TKey, TValue>* node, TVector<TVector<std::string>>& matrix,
        int level, int left, int right) const noexcept;
};

#endif  // LIB_RBTREE_RBTREE_H_