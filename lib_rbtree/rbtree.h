// Copyright 2026 Mary Maslennikova

#ifndef LIB_RBTREE_RBTREE_H_
#define LIB_RBTREE_RBTREE_H_

#include "../lib_itable/itable.h"
#include "../lib_tree/tree.h"
#include "../lib_bstree/bstree.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <algorithm>

enum Color {red, black};

template <class TKey, class TValue>
struct RBNode {
    Pair<TKey, TValue> data;
    RBNode<TKey, TValue>* left;
    RBNode<TKey, TValue>* right;
    RBNode<TKey, TValue>* parent;
    Color color;

    RBNode();
    RBNode(const TKey& key, const TValue& val, RBNode<TKey, TValue>* l = nullptr, RBNode<TKey, TValue>* r = nullptr,
        RBNode<TKey, TValue>* p = nullptr, Color c = red);
};

template <class TKey, class TValue>
RBNode<TKey, TValue>::RBNode() : data(), left(nullptr), right(nullptr), parent(nullptr), color(red) {}
template <class TKey, class TValue>
RBNode<TKey, TValue>::RBNode(const TKey& key, const TValue& val, RBNode<TKey, TValue>* l, RBNode<TKey, TValue>* r,
    RBNode<TKey, TValue>* p, Color c) :
    data(key, val), left(l), right(r), parent(p), color(c) {}

template <class TKey, class TValue>
class RBTree : public BSTree<TKey, TValue, RBNode<TKey, TValue>> {

public:
    RBTree();

    void insert(const TKey& key, const TValue& val);  // +
    void erase(const TKey& key);

private:
    void recolor(RBNode<TKey, TValue>* node);
    void swap_colors(RBNode<TKey, TValue>* first, RBNode<TKey, TValue>* second);

    void left_rotate(RBNode<TKey, TValue>* node);
    void right_rotate(RBNode<TKey, TValue>* node);

    void RR(RBNode<TKey, TValue>* node);
    void LL(RBNode<TKey, TValue>* node);
    void RL(RBNode<TKey, TValue>* node);
    void LR(RBNode<TKey, TValue>* node);

    void recover_balance(RBNode<TKey, TValue>* node);
};

template <class TKey, class TValue>
RBTree<TKey, TValue>::RBTree() : BSTree<TKey, TValue, RBNode<TKey, TValue>>() {}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::insert(const TKey& key, const TValue& val) {
    RBNode<TKey, TValue>* parent = BSTree::insert(key, val);
    if (!parent) {
        recolor(_root);
        return;
    }
    RBNode<TKey, TValue>* node = nullptr;
    if (parent->right && parent->right->data.first == key)
        node = parent->right;
    else if (parent->left && parent->left->data.first == key)
        node = parent->left;
    if (!node) return;
    node->parent = parent;

    if (parent->color == red)
        recover_balance(node);
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::recolor(RBNode<TKey, TValue>* node) {
    node->color = (node->color == red) ? black : red;
}
template <class TKey, class TValue>
void RBTree<TKey, TValue>::swap_colors(RBNode<TKey, TValue>* first, RBNode<TKey, TValue>* second) {
    Color first_color = first->color;
    first->color = second->color;
    second->color = first_color;
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::left_rotate(RBNode<TKey, TValue>* node) {
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
}
template <class TKey, class TValue>
void RBTree<TKey, TValue>::right_rotate(RBNode<TKey, TValue>* node) {
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
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::RR(RBNode<TKey, TValue>* node) {
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
void RBTree<TKey, TValue>::LL(RBNode<TKey, TValue>* node) {
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
void RBTree<TKey, TValue>::RL(RBNode<TKey, TValue>* node) {
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
void RBTree<TKey, TValue>::LR(RBNode<TKey, TValue>* node) {
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
void RBTree<TKey, TValue>::recover_balance(RBNode<TKey, TValue>* node) {
    if (!node) return;
    auto C = node;
    auto P = C->parent;
    if (!P) return;
    auto G = P->parent;
    if (!G) return;
    auto U = (G->right == P) ? G->left : G->right;

    while (P->color == red && U && U->color == red) {
        recolor(U);
        recolor(P);
        if (_root == G)
            break;
        recolor(G);
        C = G;
        P = C->parent;
        if (!P) break;
        G = P->parent;
        if (!G) break;
        U = (G->right == P) ? G->left : G->right;
    }
    if (!P || P->color == black) return;

    if (G->right == P && P->right == C) {
        RR(G);
        swap_colors(G, P);
    }
    else if (G->right == P && P->left == C) {
        RL(G);
        swap_colors(G, C);
    }
    else if (G->left == P && P->left == C) {
        LL(G);
        swap_colors(G, P);
    }
    else if (G->left == P && P->right == C) {
        LR(G);
        swap_colors(G, C);
    }
}
#endif  // LIB_RBTREE_RBTREE_H_