// Copyright 2026 Mary Maslennikova

#ifndef LIB_AVLTREE_AVLTREE_H_
#define LIB_AVLTREE_AVLTREE_H_

#include "../lib_itable/itable.h"
#include "../lib_tree/tree.h"
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
class AVLTree {
    AVLNode<TKey, TValue>* _root;

public:
    AVLTree();
    ~AVLTree();

    AVLNode<TKey, TValue>* root() const noexcept;

    void insert(const TKey& key, const TValue& val);  // +
    TValue* find(const TKey& key) const noexcept;  // +
    void erase(const TKey& key);  // +
    void clear() noexcept;  // +

    bool is_empty() const noexcept;  // +

    void print_lcr() const noexcept;
    void print() const noexcept;

private:
    void print_lcr_rec(AVLNode<TKey, TValue>* node) const noexcept;

    void left_rotate(AVLNode<TKey, TValue>* node);
    void right_rotate(AVLNode<TKey, TValue>* node);

    void RR(AVLNode<TKey, TValue>* node);
    void LL(AVLNode<TKey, TValue>* node);
    void RL(AVLNode<TKey, TValue>* node);
    void LR(AVLNode<TKey, TValue>* node);

    AVLNode<TKey, TValue>* BSTree_insert(const TKey& key, const TValue& val);
    AVLNode<TKey, TValue>* BSTree_erase(const TKey& key);
    AVLNode<TKey, TValue>* erase_node(AVLNode<TKey, TValue>*& node) noexcept;
    AVLNode<TKey, TValue>* find_max_left(AVLNode<TKey, TValue>* node) const noexcept;

    int recalculate_balance(const AVLNode<TKey, TValue>* node) const noexcept;
    void recalculate_height(AVLNode<TKey, TValue>* node) noexcept;
    void restore_balance(AVLNode<TKey, TValue>* node) noexcept;

    void clear_rec(AVLNode<TKey, TValue>* node) noexcept;

    int get_height(AVLNode<TKey, TValue>* node) const noexcept;
    void fill_matrix(AVLNode<TKey, TValue>* node, TVector<TVector<std::string>>& matrix,
        int level, int left, int right) const noexcept;
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
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::root() const noexcept {
    return _root;
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::insert(const TKey& key, const TValue& val) {
    auto node = BSTree_insert(key, val);

    if (node == _root) return;

    auto P = node->parent;
    auto G = P->parent;
    recalculate_height(P);
    if (!G)
        return;

    int balance = recalculate_balance(G);
    if (abs(balance) > 1) {
        restore_balance(G);  // внутри изменять высоты
        return;
    }

    auto cur = G;
    while (cur) {
        int prev_height = cur->height;
        recalculate_height(cur);

        if (abs(recalculate_balance(cur)) > 1) {
            restore_balance(cur);
            recalculate_height(cur);
        }
        if (prev_height == cur->height)
            break;
        cur = cur->parent;
    }
}
template <class TKey, class TValue>
TValue* AVLTree<TKey, TValue>::find(const TKey& key) const noexcept {
    auto cur = _root;
    while (cur) {
        if (cur->data.first == key)
            return &cur->data.second;
        else if (cur->data.first > key)
            cur = cur->left;
        else
            cur = cur->right;
    }
    return nullptr;
}
template <class TKey, class TValue>
void AVLTree<TKey, TValue>::erase(const TKey& key) {
    auto node = BSTree_erase(key);
    if (!node)
        return;
    auto cur = node;
    while (cur) {
        auto parent = cur->parent;
        int old_height = cur->height;
        recalculate_height(cur);
        int balance = recalculate_balance(cur);
        if (abs(balance) > 1) {
            restore_balance(cur);
            cur = parent;
        }
        else {
            if (old_height == cur->height)
                break;
            cur = parent;
        }
    }
}
template <class TKey, class TValue>
void AVLTree<TKey, TValue>::clear() noexcept {
    clear_rec(_root);
    _root = nullptr;
}

template <class TKey, class TValue>
bool AVLTree<TKey, TValue>::is_empty() const noexcept {
    return _root == nullptr;
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::print_lcr() const noexcept {
    print_lcr_rec(_root);
}
template <class TKey, class TValue>
void AVLTree<TKey, TValue>::print() const noexcept {
    if (is_empty()) return;

    int height = get_height(_root);
    int width = pow(2, height) - 1;

    TVector<TVector<std::string>> matrix;
    for (int i = 0; i < height * 2 - 1; i++) {
        TVector<std::string> row;
        for (int j = 0; j < width; j++) {
            row.push_back("   ");
        }
        matrix.push_back(row);
    }

    fill_matrix(_root, matrix, 0, 0, width - 1);
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            std::cout << matrix[i][j];
        }
        std::cout << std::endl;
    }
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::print_lcr_rec(AVLNode<TKey, TValue>* node) const noexcept {
    if (node == nullptr) return;

    print_lcr_rec(node->left);
    std::cout << node->data.second << " ";
    print_lcr_rec(node->right);
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
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::BSTree_insert(const TKey& key, const TValue& val) {
    if (!_root) {
        _root = new AVLNode<TKey, TValue>(key, val);
        return _root;
    }
    auto cur = _root;
    while (cur) {
        if (key < cur->data.first) {
            if (!cur->left) {
                cur->left = new AVLNode<TKey, TValue>(key, val, nullptr, nullptr, cur);
                return cur->left;
            }
            cur = cur->left;
        }
        else if (key > cur->data.first) {
            if (!cur->right) {
                cur->right = new AVLNode<TKey, TValue>(key, val, nullptr, nullptr, cur);
                return cur->right;
            }
            cur = cur->right;
        }
        else {
            throw std::invalid_argument("The key is already in use in the tree!");
        }
    }
    return nullptr;
}
template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::BSTree_erase(const TKey& key) {
    if (!_root)
        throw std::invalid_argument("You can't delete it from an empty tree!");

    auto node_to_delete = _root;
    while (node_to_delete) {
        if (key < node_to_delete->data.first) {
            node_to_delete = node_to_delete->left;
        }
        else if (key > node_to_delete->data.first) {
            node_to_delete = node_to_delete->right;
        }
        else {
            break;
        }
    }

    if (!node_to_delete)
        throw std::invalid_argument("The key was not found!");

    AVLNode<TKey, TValue>* parent_real_deleted = nullptr;

    if (node_to_delete == _root)
        parent_real_deleted = erase_node(_root);

    else {
        auto parent = node_to_delete->parent;
        if (parent->left == node_to_delete)
            parent_real_deleted = erase_node(parent->left);
        else
            parent_real_deleted = erase_node(parent->right);
    }

    return parent_real_deleted;
}
template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::erase_node(AVLNode<TKey, TValue>*& node) noexcept {
    AVLNode<TKey, TValue>* parent_real_deleted = nullptr;
    if (!node->left && !node->right) {
        parent_real_deleted = node->parent;
        delete node;
        node = nullptr;
    }
    else if (!node->left) {
        parent_real_deleted = node->parent;
        auto right_child = node->right;
        right_child->parent = node->parent;
        delete node;
        node = right_child;
    }
    else if (!node->right) {
        parent_real_deleted = node->parent;
        auto left_child = node->left;
        left_child->parent = node->parent;
        delete node;
        node = left_child;
    }
    else {
        auto replacer = find_max_left(node);
        node->data = replacer->data;

        parent_real_deleted = replacer->parent;

        if (replacer->parent->left == replacer)
            replacer->parent->left = replacer->left;
        else
            replacer->parent->right = replacer->left;

        if (replacer->left)
            replacer->left->parent = replacer->parent;

        delete replacer;
    }
    return parent_real_deleted;
}
template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::find_max_left(AVLNode<TKey, TValue>* node) const noexcept {
    if (!node || !node->left)
        return nullptr;
    auto cur = node->left;
    while (cur->right != nullptr) {
        cur = cur->right;
    }
    return cur;
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
        node->height = 1 + std::max(node->left->height, node->right->height);
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

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::clear_rec(AVLNode<TKey, TValue>* node) noexcept {
    if (node == nullptr) return;

    clear_rec(node->left);
    clear_rec(node->right);
    delete node;
}

template <class TKey, class TValue>
int AVLTree<TKey, TValue>::get_height(AVLNode<TKey, TValue>* node) const noexcept {
    if (node == nullptr) return 0;
    return 1 + std::max(get_height(node->left), get_height(node->right));
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::fill_matrix(AVLNode<TKey, TValue>* node, TVector<TVector<std::string>>& matrix,
    int level, int left, int right) const noexcept {

    if (node == nullptr || level >= matrix.size()) return;

    int mid = (left + right) / 2;
    int row = level * 2;

    matrix[row][mid] = " " + std::to_string(node->data.first);

    if (node->left) {
        int left_mid = (left + mid - 1) / 2;
        for (int i = left_mid + 1; i < mid; ++i) {
            matrix[row][i] = "___";
        }
        if (row + 1 < matrix.size()) {
            matrix[row + 1][left_mid] = " / ";
        }
    }

    if (node->right) {
        int right_mid = (mid + 1 + right) / 2;
        for (int i = mid + 1; i < right_mid; ++i) {
            matrix[row][i] = "___";
        }
        if (row + 1 < matrix.size()) {
            matrix[row + 1][right_mid] = " \\ ";
        }
    }

    fill_matrix(node->left, matrix, level + 1, left, mid - 1);
    fill_matrix(node->right, matrix, level + 1, mid + 1, right);
}
#endif  // LIB_AVLTREE_AVLTREE_H_