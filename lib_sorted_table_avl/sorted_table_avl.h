// Copyright 2026 Mary Maslennikova

#ifndef LIB_SORTEDTABLEAVL_SORTEDTABLEAVL_H_
#define LIB_SORTEDTABLEAVL_SORTEDTABLEAVL_H_

#include "../lib_table/table.h"
#include "../lib_avltree/avltree.h"

template <class TKey, class TValue>
class SortedTableAVL: public Table<TKey, TValue> {
    AVLTree<TKey, TValue> _rows;
public:
    SortedTableAVL();

    ~SortedTableAVL();

    const AVLTree<TKey, TValue>& rows() const noexcept;

    void insert(const TKey&, const TValue&) override;  // +
    void erase(const TKey&) override;  // +
    const TValue* found(const TKey&) const noexcept override;  // +

    bool is_empty() const noexcept override;  // +
    void print(std::ostream& os = std::cout) const noexcept override;

private:
    void print_lcr_rec(AVLNode<TKey, TValue>* node) const noexcept;
};

template <class TKey, class TValue>
SortedTableAVL<TKey, TValue>::SortedTableAVL() : _rows() {}

template <class TKey, class TValue>
SortedTableAVL<TKey, TValue>::~SortedTableAVL() {}

template <class TKey, class TValue>
const AVLTree<TKey, TValue>& SortedTableAVL<TKey, TValue>::rows() const noexcept {
    return _rows;
}

template <class TKey, class TValue>
void SortedTableAVL<TKey, TValue>::insert(const TKey& key, const TValue& val) {
    auto node = _rows.find(key);
    if (node)
        throw std::invalid_argument("The key is already in use in the table!");
    _rows.insert(key, val);
}
template <class TKey, class TValue>
void SortedTableAVL<TKey, TValue>::erase(const TKey& key) {
    auto node = _rows.find(key);
    if (!node)
        throw std::invalid_argument("The required key was not found!");
    _rows.erase(key);
}
template <class TKey, class TValue>
const TValue* SortedTableAVL<TKey, TValue>::found(const TKey& key) const noexcept {
    return _rows.find(key);
}
template <class TKey, class TValue>
bool SortedTableAVL<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}
template <class TKey, class TValue>
void SortedTableAVL<TKey, TValue>::print(std::ostream& os) const noexcept {
    print_line();
    print_title();
    print_line();
    print_lcr_rec(_rows.root());
    print_line();
}

template <class TKey, class TValue>
void SortedTableAVL<TKey, TValue>::print_lcr_rec(AVLNode<TKey, TValue>* node) const noexcept {
    if (node == nullptr) return;

    print_lcr_rec(node->left);
    std::cout << "|";
    print_key(node->data.first, KEY_WIDTH);
    print_value(node->data.second, VALUE_WIDTH);
    std::cout << std::endl;
    print_lcr_rec(node->right);
}
#endif  // LIB_SORTEDTABLEAVL_SORTEDTABLEAVL_H_
