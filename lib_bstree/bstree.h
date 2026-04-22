// Copyright 2026 Mary Maslennikova

#ifndef LIB_BSTREE_BSTREE_H_
#define LIB_BSTREE_BSTREE_H_

#include "../lib_itable/itable.h"
#include "../lib_tree/tree.h"
#include <iomanip>

template <class TKey, class TValue>
class BSTree {
    TreeNode<TKey, TValue>* _root;

public:
    BSTree();
    ~BSTree();

    TreeNode<TKey, TValue>* root() const noexcept;

    void insert(const TKey& key, const TValue& val);  // +
    TValue* find(const TKey& key) const noexcept;  // +
    void erase(const TKey& key);  // +
    void clear() noexcept;  // +

    bool is_empty() const noexcept;  // +

    void print_lcr() const noexcept;

private:
    void print_lcr_rec(TreeNode<TKey, TValue>* node) const noexcept;
    TreeNode<TKey, TValue>* find_parent(const TKey& key) const noexcept;
    void clear_rec(TreeNode<TKey, TValue>* node) noexcept;
    void erase_node(TreeNode<TKey, TValue>*& node) noexcept;
    TreeNode<TKey, TValue>* find_max_left(TreeNode<TKey, TValue>* node) const noexcept;
};

template <class TKey, class TValue>
BSTree<TKey, TValue>::BSTree() {
    _root = nullptr;
}

template <class TKey, class TValue>
BSTree<TKey, TValue>::~BSTree() {
    clear_rec(_root);
}

template <class TKey, class TValue>
TreeNode<TKey, TValue>* BSTree<TKey, TValue>::root() const noexcept {
    return _root;
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::insert(const TKey& key, const TValue& val) {
    auto parent = find_parent(key);
    if (!parent) {
        _root = new TreeNode<TKey, TValue>(key, val);
        return;
    }
    if (parent->data.first < key && !parent->right) {
        parent->right = new TreeNode<TKey, TValue>(key, val);
        return;
    }
    else if (parent->data.first > key && !parent->left) {
        parent->left = new TreeNode<TKey, TValue>(key, val);
        return;
    }
    throw std::invalid_argument("The key is already in use in the tree!");
}
template <class TKey, class TValue>
TValue* BSTree<TKey, TValue>::find(const TKey& key) const noexcept {
    TreeNode<TKey, TValue>* parent = find_parent(key);
    if (!parent)
        return nullptr;
    if (parent->left && parent->left->data.first == key)
        return &parent->left->data.second;
    else if (parent->right && parent->right->data.first == key)
        return &parent->right->data.second;
    else if (parent == _root && _root->data.first == key)  // для вставки в таблицу
        return &_root->data.second;
    return nullptr;
}
template <class TKey, class TValue>
void BSTree<TKey, TValue>::erase(const TKey& key) {
    TreeNode<TKey, TValue>* parent = find_parent(key);
    if (!parent)
        throw std::invalid_argument("You can't delete it from an empty tree!");

    if (parent->data.first < key) {
        if (!parent->right || parent->right->data.first != key)
            throw std::invalid_argument("The item was not found!");
        erase_node(parent->right);
    }
    else if (parent->data.first > key) {
        if (!parent->left || parent->left->data.first != key)
            throw std::invalid_argument("The item was not found!");
        erase_node(parent->left);
    }
    else {
        erase_node(_root);
    }
}
template <class TKey, class TValue>
void BSTree<TKey, TValue>::clear() noexcept {
    clear_rec(_root);
    _root = nullptr;
}

template <class TKey, class TValue>
bool BSTree<TKey, TValue>::is_empty() const noexcept {
    return _root == nullptr;
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::print_lcr() const noexcept {
    print_lcr_rec(_root);
}

template <class TKey, class TValue>
TreeNode<TKey, TValue>* BSTree<TKey, TValue>::find_parent(const TKey& key) const noexcept {
    if (is_empty())
        return nullptr;
    if (_root->data.first == key)
        return _root;
    TreeNode< TKey, TValue>* cur = _root;
    while (1) {
        if (cur->data.first > key) {
            if (!cur->left)
                return cur;
            if (cur->left->data.first == key)
                return cur;
            else
                cur = cur->left;
        }
        else if (cur->data.first < key) {
            if (!cur->right)
                return cur;
            if (cur->right->data.first == key)
                return cur;
            else
                cur = cur->right;
        }
    }
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::print_lcr_rec(TreeNode<TKey, TValue>* node) const noexcept {
    if (node == nullptr) return;

    print_lcr_rec(node->left);
    std::cout << node->data.second << " ";
    print_lcr_rec(node->right);
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::clear_rec(TreeNode<TKey, TValue>* node) noexcept {
    if (node == nullptr) return;

    clear_rec(node->left);
    clear_rec(node->right);
    delete node;
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::erase_node(TreeNode<TKey, TValue>*& node) noexcept {
    if (!node->left && !node->right) {
        delete node;
        node = nullptr;
    }
    else if (!node->left) {
        auto deleted_node = node;
        node = node->right;
        delete deleted_node;
    }
    else if (!node->right) {
        auto deleted_node = node;
        node = node->left;
        delete deleted_node;
    }
    else {
        auto replacer = find_max_left(node);
        auto tmp = replacer->data;
        auto parent_replacer = find_parent(replacer->data.first);
        if (parent_replacer->left == replacer)
            erase_node(parent_replacer->left);
        else
            erase_node(parent_replacer->right);
        node->data = tmp;
    }
}

template <class TKey, class TValue>
TreeNode<TKey, TValue>* BSTree<TKey, TValue>::find_max_left(TreeNode<TKey, TValue>* node) const noexcept {
    if (!node || !node->left)
        return nullptr;
    auto cur = node->left;
    while (cur->right != nullptr) {
        cur = cur->right;
    }
    return cur;
}
#endif  // LIB_BSTREE_BSTREE_H_