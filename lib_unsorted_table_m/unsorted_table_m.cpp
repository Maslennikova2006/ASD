// Copyright 2026 Mary Maslennikova

#include "../lib_unsorted_table_m/unsorted_table_m.h"

template <class TKey, class TValue>
UnsortedTableM<TKey, TValue>::UnsortedTableM() : _rows() {}

template <class TKey, class TValue>
UnsortedTableM<TKey, TValue>::~UnsortedTableM() {}

template <class TKey, class TValue>
void UnsortedTableM<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    Pair<TKey, TValue> pair(key, value);
    int ind = find_first_elem_by_index(_rows, pair);
    if (ind != -1)
        throw std::invalid_argument("The key is already in use in the table!");
    _rows.push_back(pair);
}

template <class TKey, class TValue>
void UnsortedTableM<TKey, TValue>::erase(const TKey& key) {
    Pair<TKey, TValue> pair(key, TValue());
    int ind = find_first_elem_by_index(_rows, pair);
    if (ind == -1)
        throw std::invalid_argument("The required key was not found!");
    erase(ind);
}

template <class TKey, class TValue>
const TValue& UnsortedTableM<TKey, TValue>::found(const TKey& key) const noexcept {  // что возвращать при -1? или поменять на указатель?
    Pair<TKey, TValue> pair(key, TValue());
    int ind = find_first_elem_by_index(_rows, pair);
    if (ind == -1)
        return TValue();
    return _rows[ind].second;
}

template <class TKey, class TValue>
bool UnsortedTableM<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}