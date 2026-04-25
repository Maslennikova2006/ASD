// Copyright 2026 Mary Maslennikova

#ifndef LIB_AVLTREE_AVLTREE_H_
#define LIB_AVLTREE_AVLTREE_H_

#include "../lib_itable/itable.h"
#include "../lib_tree/tree.h"
#include "../lib_bstree/bstree.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <algorithm>

template <class TKey, class TValue>
struct AVLNode {
    Pair<TKey, TValue> data;
    AVLNode<TKey, TValue>* left;
    AVLNode<TKey, TValue>* right;
    AVLNode<TKey, TValue>* parent;
    size_t height;

    AVLNode();
    AVLNode(const TKey& key, const TValue& val, AVLNode<TKey, TValue>* l = nullptr, AVLNode<TKey, TValue>* r = nullptr,
        AVLNode<TKey, TValue>* p = nullptr, size_t h = 1);
};

template <class TKey, class TValue>
AVLNode<TKey, TValue>::AVLNode() : data(), left(nullptr), right(nullptr), parent(nullptr), height(1) {}
template <class TKey, class TValue>
AVLNode<TKey, TValue>::AVLNode(const TKey& key, const TValue& val, AVLNode<TKey, TValue>* l, AVLNode<TKey, TValue>* r, AVLNode<TKey, TValue>* p, size_t h) :
    data(key, val), left(l), right(r), parent(p), height(h) {}

template <class TKey, class TValue>
class AVLTree : public BSTree<TKey, TValue, AVLNode<TKey, TValue>> {
public:
    AVLTree();
    ~AVLTree();

    void insert(const TKey& key, const TValue& val);  // +
    void erase(const TKey& key);  // +

private:
    void left_rotate(AVLNode<TKey, TValue>* node);
    void right_rotate(AVLNode<TKey, TValue>* node);

    void RR(AVLNode<TKey, TValue>* node);
    void LL(AVLNode<TKey, TValue>* node);
    void RL(AVLNode<TKey, TValue>* node);
    void LR(AVLNode<TKey, TValue>* node);

    int recalculate_balance(const AVLNode<TKey, TValue>* node) const noexcept;
    void recalculate_height(AVLNode<TKey, TValue>* node) noexcept;
    void restore_balance(AVLNode<TKey, TValue>* node) noexcept;
};

template <class TKey, class TValue>
AVLTree<TKey, TValue>::AVLTree() {
    _root = nullptr;
}
template <class TKey, class TValue>
AVLTree<TKey, TValue>::~AVLTree() {
    clear();
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::insert(const TKey& key, const TValue& val) {
    AVLNode<TKey, TValue>* parent = BSTree<TKey, TValue, AVLNode<TKey, TValue>>::insert(key, val);
    if (!parent) 
        return;

    AVLNode<TKey, TValue>* node = nullptr;
    if (parent->left && parent->left->data.first == key)
        node = parent->left;
    if (parent->right && parent->right->data.first == key)
        node = parent->right;

    if (!node) return;
    node->parent = parent;

    auto P = node->parent;
    recalculate_height(P);
    auto G = P->parent;
    if (!G)
        return;
    int balance = recalculate_balance(G);
    if (abs(balance) > 1) {
        restore_balance(G);
        return;
    }
    auto cur = G;
    size_t prev_height;
    while (cur) {
        prev_height = cur->height;
        recalculate_height(cur);
        int balance = recalculate_balance(cur);
        if (abs(balance) > 1) {
            restore_balance(cur);
            recalculate_height(cur);
        }
        if (prev_height == cur->height)
            break;
        cur = cur->parent;
    }
}
template <class TKey, class TValue>
void AVLTree<TKey, TValue>::erase(const TKey& key) {
    AVLNode<TKey, TValue>* parent = BSTree<TKey, TValue, AVLNode<TKey, TValue>>::erase(key);
    AVLNode<TKey, TValue>* cur = parent;
    if (!parent)
        cur = _root;
    while (cur) {
        auto parent = cur->parent;
        int prev_height = cur->height;
        recalculate_height(cur);
        int balance = recalculate_balance(cur);
        if (abs(balance) > 1) {
            restore_balance(cur);
            cur = parent;
        }
        else {
            if (prev_height == cur->height)
                break;
            cur = parent;
        }
    }
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::left_rotate(AVLNode<TKey, TValue>* node) {
    /*   G                               P
    *     \                             / \
    *      P     left_rotate(G) ->     G   C
    *     / \                           \
    *    T   C                           T
    */

    auto G = node;
    auto P = G->right;
    auto T = P->left;

    if (G->parent) {
        if (G == G->parent->left)
            G->parent->left = P;
        else
            G->parent->right = P;
    }

    G->right = T;
    if (T)
        T->parent = G;
    P->parent = G->parent;
    P->left = G;
    G->parent = P;

    if (!P->parent)
        _root = P;
    recalculate_height(G);
    recalculate_height(P);
}
template <class TKey, class TValue>
void AVLTree<TKey, TValue>::right_rotate(AVLNode<TKey, TValue>* node) {
    /*       G                             P
    *       /                             / \
    *      P     right_rotate(G) ->      C   G
    *     / \                               /
    *    C   T                             T
    */
    auto G = node;
    auto P = G->left;
    auto T = P->right;

    if (G->parent) {
        if (G == G->parent->left)
            G->parent->left = P;
        else
            G->parent->right = P;
    }

    G->left = T;
    if (T)
        T->parent = G;
    P->parent = G->parent;
    P->right = G;
    G->parent = P;

    if (!P->parent)
        _root = P;
    recalculate_height(G);
    recalculate_height(P);
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::RR(AVLNode<TKey, TValue>* node) {
    /*   G
    *     \
    *      P     left_rotate(G) ->       P
    *       \                           / \
    *        C                         G   C
    */
    auto G = node;
    left_rotate(G);
}
template <class TKey, class TValue>
void AVLTree<TKey, TValue>::LL(AVLNode<TKey, TValue>* node) {
    /*       G
    *       /
    *      P     right_rotate(G) ->       P
    *     /                              / \
    *    C                              C   G
    */
    auto G = node;
    right_rotate(G);
}
template <class TKey, class TValue>
void AVLTree<TKey, TValue>::RL(AVLNode<TKey, TValue>* node) {
    /*   G                         G
    *     \                         \
    *      P   right_rotate(P) ->    C   left_rotate(G)      C
    *     /                           \                     / \
    *    C                             P                   G   P
    */
    auto G = node;
    auto P = G->right;
    right_rotate(P);
    left_rotate(G);
}
template <class TKey, class TValue>
void AVLTree<TKey, TValue>::LR(AVLNode<TKey, TValue>* node) {
    /*       G                           G
    *       /                           /
    *      P     left_rotate(P) ->     C   right_rotate(G)   C
    *       \                         /                     / \
    *        C                       P                     P   G
    */
    auto G = node;
    auto P = G->left;
    left_rotate(P);
    right_rotate(G);
}

template <class TKey, class TValue>
int AVLTree<TKey, TValue>::recalculate_balance(const AVLNode<TKey, TValue>* node) const noexcept {
    if (!node || (!node->right && !node->left))
        return 0;
    else if (!node->right && node->left)
        return 0 - node->left->height;
    else if (!node->left && node->right)
        return node->right->height;
    else
        return node->right->height - node->left->height;
}
template <class TKey, class TValue>
void AVLTree<TKey, TValue>::recalculate_height(AVLNode<TKey, TValue>* node) noexcept {
    if (!node)
        return;
    else if (!node->right && !node->left)
        node->height = 1;
    else if (!node->left)
        node->height = 1 + node->right->height;
    else if (!node->right)
        node->height = 1 + node->left->height;
    else
        node->height = 1 + std::max<size_t>(node->left->height, node->right->height);
}
template <class TKey, class TValue>
void AVLTree<TKey, TValue>::restore_balance(AVLNode<TKey, TValue>* node) noexcept {
    int balance = recalculate_balance(node);
    if (balance == 2) {
        int balance_right_child = recalculate_balance(node->right);
        if (balance_right_child >= 0)
            RR(node);
        else
            RL(node);
    }
    else if (balance == -2) {
        int balance_left_child = recalculate_balance(node->left);
        if (balance_left_child <= 0)
            LL(node);
        else
            LR(node);
    }
    recalculate_height(node);
}
#endif  // LIB_AVLTREE_AVLTREE_H_
