// Copyright 2026 Mary Maslennikova

#ifndef LIB_AVLTREE_AVLTREE_H_
#define LIB_AVLTREE_AVLTREE_H_

#include "../lib_itable/itable.h"
#include "../lib_tree/tree.h"
#include <iomanip>

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
class AVLTree {
    AVLNode<TKey, TValue>* _root;

public:
    AVLTree();
    ~AVLTree();

    AVLTree<TKey, TValue>* root() const noexcept;

    void insert(const TKey& key, const TValue& val);
    TValue* find(const TKey& key) const noexcept;
    void erase(const TKey& key);
    void clear() noexcept;

    bool is_empty() const noexcept;

    void print_lcr() const noexcept;
    void print() const noexcept;

private:
    void left_rotate(const AVLNode<TKey, TValue>* node);
    void right_rotate(const AVLNode<TKey, TValue>* node);

    void RR(const AVLNode<TKey, TValue>* node);
    void LL(const AVLNode<TKey, TValue>* node);
    void RL(const AVLNode<TKey, TValue>* node);
    void LR(const AVLNode<TKey, TValue>* node);
};

template <class TKey, class TValue>
AVLTree<TKey, TValue>::AVLTree() {
    _root = nullptr;
}
template <class TKey, class TValue>
AVLTree<TKey, TValue>::~AVLTree() {
    clear_rec(_root);
}



template <class TKey, class TValue>
void AVLTree<TKey, TValue>::left_rotate(const AVLNode<TKey, TValue>* node) {
    /*   G
    *     \
    *      P     left_rotate(G) ->       P
    *       \                           / \
    *        C                         G   C
    */
    auto G = node;
    auto P = G->right;

    G->right = nullptr;
    P->parent = G->parent;
    P->left = G;
    G->parent = P;
}
template <class TKey, class TValue>
void AVLTree<TKey, TValue>::right_rotate(const AVLNode<TKey, TValue>* node) {
    /*       G
    *       /
    *      P     right_rotate(G) ->       P
    *     /                              / \
    *    C                              C   G
    */
    auto G = node;
    auto P = G->left;

    G->left = nullptr;
    P->parent = G->parent;
    P->right = G;
    G->parent = P;
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::RR(const AVLNode<TKey, TValue>* node) {
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
void AVLTree<TKey, TValue>::LL(const AVLNode<TKey, TValue>* node) {
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
void AVLTree<TKey, TValue>::RL(const AVLNode<TKey, TValue>* node) {
    /*   G                         G
    *     \                         \
    *      P   right_rotate(P) ->    C   left_rotate(G)      C
    *     /                           \                     / \
    *    C                             P                   G   P
    */
    auto G = node;
    P = G->right;
    right_rotate(P);
    left_rotate(G);
}
template <class TKey, class TValue>
void AVLTree<TKey, TValue>::LR(const AVLNode<TKey, TValue>* node) {
    /*       G                           G
    *       /                           /
    *      P     left_rotate(P) ->     C   right_rotate(G)   C
    *       \                         /                     / \
    *        C                       P                     P   G
    */
    auto G = node;
    P = G->right;
    left_rotate(P);
    right_rotate(G);
}


#endif  // LIB_AVLTREE_AVLTREE_H_