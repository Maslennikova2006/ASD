// Copyright 2026 Mary Maslennikova

#ifndef LIB_TREE_TREE_H_
#define LIB_TREE_TREE_H_

#include "../lib_itable/itable.h"
#include "../lib_queue/queue.h"

template <class TKey, class TValue>
struct TreeNode {
    Pair<TKey, TValue> data;
    TreeNode<TKey, TValue>* left;
    TreeNode<TKey, TValue>* right;

    TreeNode();
    TreeNode(const TKey& key, const TValue& val, TreeNode<TKey, TValue>* l = nullptr, TreeNode<TKey, TValue>* r = nullptr);
};

template <class TKey, class TValue>
TreeNode<TKey, TValue>::TreeNode() : data(), left(nullptr), right(nullptr) {}
template <class TKey, class TValue>
TreeNode<TKey, TValue>::TreeNode(const TKey& key, const TValue& val, TreeNode<TKey, TValue>* l, TreeNode<TKey, TValue>* r) {
    Pair<TKey, TValue> pair(key, val);
    data = pair;
    left = l;
    right = r;
}

template <class TKey, class TValue>
class Tree {
    TreeNode<TKey, TValue>* _root;

public:
    Tree();
    ~Tree();

    void insert(const TKey& key, const TValue& val);
    TValue* find(const TKey&) const noexcept;
    void erase(const TKey& key);
    void clear() noexcept;

    bool is_empty() const noexcept;

    void print_w() const noexcept;
    void print_lcr() const noexcept;
    void print_lrc() const noexcept;
    void print_clr() const noexcept;

private:
    void print_lcr_rec(TreeNode<TKey, TValue>* node) const noexcept;
    void print_clr_rec(TreeNode<TKey, TValue>* node) const noexcept;
    void print_lrc_rec(TreeNode<TKey, TValue>* node) const noexcept;

    void clear_rec(TreeNode<TKey, TValue>* node);  // обход в ширину нельзя, используем lrc
};

template <class TKey, class TValue>
Tree<TKey, TValue>::Tree() {
    _root = nullptr;
}

template <class TKey, class TValue>
Tree<TKey, TValue>::~Tree() {
    clear_rec(_root);
    _root = nullptr;
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    auto node = new TreeNode<TKey, TValue>(key, value);

    if (is_empty()) {
        _root = node;
        return;
    }

    TreeNode<TKey, TValue>* cur = nullptr;
    Queue<TreeNode<TKey, TValue>*> q;
    q.push(_root);
    while (1) {
        cur = q.head();
        q.pop();
        if (!cur->left) {
            cur->left = node;
            return;
        }
        if (!cur->right) {
            cur->right = node;
            return;
        }

        q.push(cur->left);
        q.push(cur->right);
    }
}
template <class TKey, class TValue>
void Tree<TKey, TValue>::clear() noexcept {
    clear_rec(_root);
}

template <class TKey, class TValue>
bool Tree<TKey, TValue>::is_empty() const noexcept {
    return _root == nullptr;
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_w() const noexcept {  // O(N), память - количество элементов
    if (is_empty()) return;
    Queue<TreeNode<TKey, TValue>*> q;
    TreeNode<TKey, TValue>* cur = nullptr;
    q.push(_root);

    while (!q.is_empty()) {
        cur = q.head();
        std::cout << cur->data.second << " ";  // либо перегрузить вывод в ноде
        q.pop();
        if (cur->left)
            q.push(cur->left);
        if (cur->right)
            q.push(cur->right);
    }
}
template <class TKey, class TValue>
void Tree<TKey, TValue>::print_lcr() const noexcept {
    print_lcr_rec(_root);
}
template <class TKey, class TValue>
void Tree<TKey, TValue>::print_lrc() const noexcept {
    print_lrc_rec(_root);
}
template <class TKey, class TValue>
void Tree<TKey, TValue>::print_clr() const noexcept {
    print_clr_rec(_root);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_clr_rec(TreeNode<TKey, TValue>* node) const noexcept {
    if (node == nullptr) return;

    std::cout << node->data.second << " ";
    print_clr_rec(node->left);  // можно добавить условие проверки на nullptr и убрать проверку из начала
    print_clr_rec(node->right);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_lcr_rec(TreeNode<TKey, TValue>* node) const noexcept {
    if (node == nullptr) return;

    print_lcr_rec(node->left);
    std::cout << node->data.second << " ";
    print_lcr_rec(node->right);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_lrc_rec(TreeNode<TKey, TValue>* node) const noexcept {
    if (node == nullptr) return;

    print_lrc_rec(node->left);
    print_lrc_rec(node->right);
    std::cout << node->data.second << " ";
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::clear_rec(TreeNode<TKey, TValue>* node) {
    if (node == nullptr) return;

    clear_rec(node->left);
    clear_rec(node->right);
    delete node;
}
#endif  // LIB_TREE_TREE_H_
