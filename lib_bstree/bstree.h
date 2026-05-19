// Copyright 2026 Mary Maslennikova

#ifndef LIB_BSTREE_BSTREE_H_
#define LIB_BSTREE_BSTREE_H_

#include "../lib_itable/itable.h"
#include "../lib_tree/tree.h"
#include <iomanip>


template <class TKey, class TValue, class TNode = TreeNode<TKey, TValue>>
class BSTree {
protected:
    TNode* _root;

public:
    BSTree();
    ~BSTree();

    TNode* root() const noexcept;

    TNode* insert(const TKey& key, const TValue& val);  // +
    TValue* find(const TKey& key) const noexcept;  // +
    TNode* erase(const TKey& key);  // +
    void clear() noexcept;  // +

    bool is_empty() const noexcept;  // +

    void print_lcr() const noexcept;
    void print() const noexcept;

protected:
    TNode* find_parent(const TKey& key) const noexcept;
    TNode* find_max_left(TNode* node) const noexcept;

private:
    void print_lcr_rec(TNode* node) const noexcept;
    void clear_rec(TNode* node) noexcept;
    TNode* erase_node(TNode*& node, TNode* parent) noexcept;

    int get_height(TNode* node) const noexcept;
    void fill_matrix(TNode* node, TVector<TVector<std::string>>& matrix,
        int level, int left, int right) const noexcept;
};

template <class TKey, class TValue, class TNode>
BSTree<TKey, TValue, TNode>::BSTree() {
    _root = nullptr;
}

template <class TKey, class TValue, class TNode>
BSTree<TKey, TValue, TNode>::~BSTree() {
    clear_rec(_root);
}

template <class TKey, class TValue, class TNode>
TNode* BSTree<TKey, TValue, TNode>::root() const noexcept {
    return _root;
}

template <class TKey, class TValue, class TNode>
TNode* BSTree<TKey, TValue, TNode>::insert(const TKey& key, const TValue& val) {
    auto parent = find_parent(key);
    if (!_root) {
        _root = new TNode(key, val);
        return nullptr;
    }
    if (parent->data.first < key && !parent->right) {
        parent->right = new TNode(key, val);
        return parent;
    }
    else if (parent->data.first > key && !parent->left) {
        parent->left = new TNode(key, val);
        return parent;
    }
    throw std::invalid_argument("The key is already in use in the tree!");
}
template <class TKey, class TValue, class TNode>
TValue* BSTree<TKey, TValue, TNode>::find(const TKey& key) const noexcept {
    TNode* parent = find_parent(key);
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
template <class TKey, class TValue, class TNode>
TNode* BSTree<TKey, TValue, TNode>::erase(const TKey& key) {
    TNode* parent = find_parent(key);
    if (!parent)
        throw std::invalid_argument("You can't delete it from an empty tree!");
    
    TNode* parent_real_deleted = nullptr;
    if (parent->data.first < key) {
        if (!parent->right || parent->right->data.first != key)
            throw std::invalid_argument("The item was not found!");
        parent_real_deleted = erase_node(parent->right, parent);
    }
    else if (parent->data.first > key) {
        if (!parent->left || parent->left->data.first != key)
            throw std::invalid_argument("The item was not found!");
        parent_real_deleted = erase_node(parent->left, parent);
    }
    else {
        TNode* prev_root = _root;
        parent_real_deleted = erase_node(_root, nullptr);

        if (_root != prev_root)
            return _root;
    }
    return parent_real_deleted;
}
template <class TKey, class TValue, class TNode>
void BSTree<TKey, TValue, TNode>::clear() noexcept {
    clear_rec(_root);
    _root = nullptr;
}

template <class TKey, class TValue, class TNode>
bool BSTree<TKey, TValue, TNode>::is_empty() const noexcept {
    return _root == nullptr;
}

template <class TKey, class TValue, class TNode>
void BSTree<TKey, TValue, TNode>::print_lcr() const noexcept {
    print_lcr_rec(_root);
}

template <class TKey, class TValue, class TNode>
TNode* BSTree<TKey, TValue, TNode>::find_parent(const TKey& key) const noexcept {
    if (is_empty())
        return nullptr;
    if (_root->data.first == key)
        return _root;
    TNode* cur = _root;
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

template <class TKey, class TValue, class TNode>
void BSTree<TKey, TValue, TNode>::print_lcr_rec(TNode* node) const noexcept {
    if (node == nullptr) return;

    print_lcr_rec(node->left);
    std::cout << node->data.second << " ";
    print_lcr_rec(node->right);
}

template <class TKey, class TValue, class TNode>
void BSTree<TKey, TValue, TNode>::clear_rec(TNode* node) noexcept {
    if (node == nullptr) return;

    clear_rec(node->left);
    clear_rec(node->right);
    delete node;
}

template <class TKey, class TValue, class TNode>
TNode* BSTree<TKey, TValue, TNode>::erase_node(TNode*& node, TNode* parent) noexcept {
    TNode* parent_real_deleted = nullptr;
    if (!node->left && !node->right) {
        parent_real_deleted = parent;
        delete node;
        node = nullptr;
        return parent_real_deleted;
    }
    else if (!node->left) {
        parent_real_deleted = parent;
        auto deleted_node = node;
        node = node->right;
        delete deleted_node;
        return parent_real_deleted;
    }
    else if (!node->right) {
        parent_real_deleted = parent;
        auto deleted_node = node;
        node = node->left;
        delete deleted_node;
        return parent_real_deleted;
    }
    else {
        auto replacer = find_max_left(node);
        auto tmp = replacer->data;
        auto parent_replacer = find_parent(replacer->data.first);
        parent_real_deleted = parent_replacer;

        if (parent_replacer->left == replacer)
            erase_node(parent_replacer->left, parent_replacer);
        else
            erase_node(parent_replacer->right, parent_replacer);
        node->data = tmp;

        return parent_real_deleted;
    }
}

template <class TKey, class TValue, class TNode>
TNode* BSTree<TKey, TValue, TNode>::find_max_left(TNode* node) const noexcept {
    if (!node || !node->left)
        return nullptr;
    auto cur = node->left;
    while (cur->right != nullptr) {
        cur = cur->right;
    }
    return cur;
}

template <class TKey, class TValue, class TNode>
int BSTree<TKey, TValue, TNode>::get_height(TNode* node) const noexcept {
    if (node == nullptr) return 0;
    return 1 + std::max(get_height(node->left), get_height(node->right));
}
template <class TKey, class TValue, class TNode>
void BSTree<TKey, TValue, TNode>::fill_matrix(TNode* node, TVector<TVector<std::string>>& matrix,
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
template <class TKey, class TValue, class TNode>
void BSTree<TKey, TValue, TNode>::print() const noexcept {
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
#endif  // LIB_BSTREE_BSTREE_H_