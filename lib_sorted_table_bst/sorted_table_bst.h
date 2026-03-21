// Copyright 2026 Mary Maslennikova

#ifndef LIB_SORTEDTABLEBST_SORTEDTABLEBST_H_
#define LIB_SORTEDTABLEBST_SORTEDTABLEBST_H_

#include "../lib_table/table.h"
#include "../lib_bstree/bstree.h"

template <class TKey, class TValue>
class SortedTableBST : public Table<TKey, TValue> {
    BSTree<TKey, TValue> _rows;
public:
    SortedTableBST();

    ~SortedTableBST();

    const BSTree<TKey, TValue>& get_rows() const noexcept;

    void insert(const TKey&, const TValue&) override;  // +
    void erase(const TKey&) override;  // +
    const TValue* found(const TKey&) const noexcept override;  // +

    bool is_empty() const noexcept override;  // +
    void print(std::ostream& os = std::cout) const noexcept override;

private:
    void print_lcr_rec(TreeNode<TKey, TValue>* node) const noexcept;
};

template <class TKey, class TValue>
SortedTableBST<TKey, TValue>::SortedTableBST() : _rows() {}

template <class TKey, class TValue>
SortedTableBST<TKey, TValue>::~SortedTableBST() {}

template <class TKey, class TValue>
const BSTree<TKey, TValue>& SortedTableBST<TKey, TValue>::get_rows() const noexcept {
    return _rows;
}

template <class TKey, class TValue>
void SortedTableBST<TKey, TValue>::insert(const TKey& key, const TValue& val) {
    auto node = _rows.find(key);
    if (node)
        throw std::invalid_argument("The key is already in use in the table!");
    _rows.insert(key, val);
}
template <class TKey, class TValue>
void SortedTableBST<TKey, TValue>::erase(const TKey& key) {
    auto node = _rows.find(key);
    if (!node)
        throw std::invalid_argument("The required key was not found!");
    _rows.erase(key);
}
template <class TKey, class TValue>
const TValue* SortedTableBST<TKey, TValue>::found(const TKey& key) const noexcept {
    return _rows.find(key);
}
template <class TKey, class TValue>
bool SortedTableBST<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}
template <class TKey, class TValue>
void SortedTableBST<TKey, TValue>::print(std::ostream& os) const noexcept {
    print_line();
    print_title();
    print_line();
    print_lcr_rec(_rows.root());
    print_line();
}

template <class TKey, class TValue>
void SortedTableBST<TKey, TValue>::print_lcr_rec(TreeNode<TKey, TValue>* node) const noexcept {
    if (node == nullptr) return;

    print_lcr_rec(node->left);
    std::cout << "|";
    print_key(node->data.first, KEY_WIDTH);
    print_value(node->data.second, VALUE_WIDTH);
    std::cout << std::endl;
    print_lcr_rec(node->right);
}
#endif  // LIB_SORTEDTABLEBST_SORTEDTABLEBST_H_
