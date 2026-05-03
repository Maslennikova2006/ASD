// Copyright 2026 Mary Maslennikova

#ifndef LIB_SORTEDTABLERB_SORTEDTABLERB_H_
#define LIB_SORTEDTABLERB_SORTEDTABLERB_H_

#include "../lib_table/table.h"
#include "../lib_rbtree/rbtree.h"

template <class TKey, class TValue>
class SortedTableRB : public Table<TKey, TValue> {
    RBTree<TKey, TValue> _rows;
public:
    SortedTableRB();

    ~SortedTableRB();

    const RBTree<TKey, TValue>& rows() const noexcept;

    void insert(const TKey&, const TValue&) override;  // +
    void erase(const TKey&) override {}
    const TValue* found(const TKey&) const noexcept override;  // +

    bool is_empty() const noexcept override;  // +
    void print(std::ostream& os = std::cout) const noexcept override;

private:
    void print_lcr_rec(RBNode<TKey, TValue>* node) const noexcept;
};

template <class TKey, class TValue>
SortedTableRB<TKey, TValue>::SortedTableRB() : _rows() {}

template <class TKey, class TValue>
SortedTableRB<TKey, TValue>::~SortedTableRB() {}

template <class TKey, class TValue>
const RBTree<TKey, TValue>& SortedTableRB<TKey, TValue>::rows() const noexcept {
    return _rows;
}

template <class TKey, class TValue>
void SortedTableRB<TKey, TValue>::insert(const TKey& key, const TValue& val) {
    auto node = _rows.find(key);
    if (node)
        throw std::invalid_argument("The key is already in use in the table!");
    _rows.insert(key, val);
}
template <class TKey, class TValue>
const TValue* SortedTableRB<TKey, TValue>::found(const TKey& key) const noexcept {
    return _rows.find(key);
}
template <class TKey, class TValue>
bool SortedTableRB<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}
template <class TKey, class TValue>
void SortedTableRB<TKey, TValue>::print(std::ostream& os) const noexcept {
    print_line();
    print_title();
    print_line();
    print_lcr_rec(_rows.root());
    print_line();
}

template <class TKey, class TValue>
void SortedTableRB<TKey, TValue>::print_lcr_rec(RBNode<TKey, TValue>* node) const noexcept {
    if (node == nullptr) return;

    print_lcr_rec(node->left);
    std::cout << "|";
    print_key(node->data.first, KEY_WIDTH);
    print_value(node->data.second, VALUE_WIDTH);
    std::cout << std::endl;
    print_lcr_rec(node->right);
}
#endif  // LIB_SORTEDTABLERB_SORTEDTABLERB_H_
