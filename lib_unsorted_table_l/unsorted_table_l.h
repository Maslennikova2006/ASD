// Copyright 2026 Mary Maslennikova

#ifndef LIB_UNSORTEDTABLEL_UNSORTEDTABLEL_H_
#define LIB_UNSORTEDTABLEL_UNSORTEDTABLEL_H_

#include "../lib_table/table.h"
#include "../lib_list/list.h"
#include "../lib_node/node.h"

template <class TKey, class TValue>
class UnsortedTableL : public Table<TKey, TValue> {
    List<Pair<TKey, TValue>> _rows;
public:
    UnsortedTableL();  // +

    ~UnsortedTableL();

    void insert(const TKey&, const TValue&) override;  // +
    void erase(const TKey&) override;  // +
    const TValue* found(const TKey&) const noexcept override;  // +
    bool is_empty() const noexcept override;  // +
    void print(std::ostream& os = std::cout) const noexcept override;

private:
    Node<Pair<TKey, TValue>>* find_node(const Pair<TKey, TValue>& pair) const noexcept;
};

template <class TKey, class TValue>
UnsortedTableL<TKey, TValue>::UnsortedTableL() : _rows() {}

template <class TKey, class TValue>
UnsortedTableL<TKey, TValue>::~UnsortedTableL() {}

template <class TKey, class TValue>
void UnsortedTableL<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    Pair<TKey, TValue> pair(key, value);
    auto node = find_node(pair);
    if (node)
        throw std::invalid_argument("The key is already use in the table!");
    _rows.push_back(pair);
}

template <class TKey, class TValue>
void UnsortedTableL<TKey, TValue>::erase(const TKey& key) {
    Pair<TKey, TValue> pair(key, TValue());
    auto node = find_node(pair);
    if (node) {
        _rows.erase(node);
        return;
    }
    throw std::invalid_argument("The required key was not found!");
}

template <class TKey, class TValue>
const TValue* UnsortedTableL<TKey, TValue>::found(const TKey& key) const noexcept {
    Pair<TKey, TValue> pair(key, TValue());
    auto node = find_node(pair);
    if (node)
        return &node->value.second;
    return nullptr;
}

template <class TKey, class TValue>
bool UnsortedTableL<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <class TKey, class TValue>
void UnsortedTableL<TKey, TValue>::print(std::ostream& os) const noexcept {
    print_line();
    print_title();
    print_line();

    auto cur = _rows.head();
    while (cur != nullptr) {
        std::cout << "|";
        print_key(cur->value.first, KEY_WIDTH);
        print_value(cur->value.second, VALUE_WIDTH);
        std::cout << std::endl;
        cur = cur->next;
    }
    print_line();
}

template <class TKey, class TValue>
Node<Pair<TKey, TValue>>* UnsortedTableL<TKey, TValue>::find_node(const Pair<TKey, TValue>& pair) const noexcept {
    auto cur = _rows.head();
    while (cur != nullptr) {
        if (cur->value == pair)
            return cur;
        cur = cur->next;
    }
    return nullptr;
}
#endif  // LIB_UNSORTEDTABLEL_UNSORTEDTABLEL_H_
