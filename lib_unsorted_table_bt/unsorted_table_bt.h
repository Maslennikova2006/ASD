// Copyright 2026 Mary Maslennikova

#ifndef LIB_UNSORTEDTABLEBT_UNSORTEDTABLEBT_H_
#define LIB_UNSORTEDTABLEBT_UNSORTEDTABLEBT_H_

#include "../lib_table/table.h"
#include "../lib_tree/tree.h"

template <class TKey, class TValue>
class UnsortedTableBT : public Table<TKey, TValue> {
    Tree<TKey, TValue> _rows;
public:
    UnsortedTableBT();  // +

    ~UnsortedTableBT();

    void insert(const TKey&, const TValue&) override;  // +
    void erase(const TKey&) override;  // +
    const TValue* found(const TKey&) const noexcept override;  // +

    bool is_empty() const noexcept override;  // +
    void print(std::ostream& os = std::cout) const noexcept override;
};

template <class TKey, class TValue>
UnsortedTableBT<TKey, TValue>::UnsortedTableBT() : _rows() {}

template <class TKey, class TValue>
UnsortedTableBT<TKey, TValue>::~UnsortedTableBT() {}

template <class TKey, class TValue>
void UnsortedTableBT<TKey, TValue>::insert(const TKey& key, const TValue& val) {
    auto node = _rows.find(key);
    if (node)
        throw std::invalid_argument("The key is already in use in the table!");
    _rows.insert(key, val);
}
template <class TKey, class TValue>
void UnsortedTableBT<TKey, TValue>::erase(const TKey& key) {
    auto node = _rows.find(key);
    if (!node)
        throw std::invalid_argument("The required key was not found!");
    _rows.erase(key);
}
template <class TKey, class TValue>
const TValue* UnsortedTableBT<TKey, TValue>::found(const TKey& key) const noexcept {
    return _rows.find(key);
}
template <class TKey, class TValue>
bool UnsortedTableBT<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}
template <class TKey, class TValue>
void UnsortedTableBT<TKey, TValue>::print(std::ostream& os) const noexcept {
    print_line();
    print_title();
    print_line();

    Queue<TreeNode<TKey, TValue>*> q;
    TreeNode<TKey, TValue>* cur = nullptr;
    q.push(_rows.root());

    while (!q.is_empty()) {
        cur = q.head();
        std::cout << "|";
        print_key(cur->data.first, KEY_WIDTH);
        print_value(cur->data.second, VALUE_WIDTH);
        std::cout << std::endl;
        q.pop();
        if (cur->left)
            q.push(cur->left);
        if (cur->right)
            q.push(cur->right);
    }
    print_line();
}
#endif  // LIB_UNSORTEDTABLEBT_UNSORTEDTABLEBT_H_
