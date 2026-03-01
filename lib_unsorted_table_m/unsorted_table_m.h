// Copyright 2026 Mary Maslennikova

#ifndef LIB_UNSORTEDTABLEM_UNSORTEDTABLEM_H_
#define LIB_UNSORTEDTABLEM_UNSORTEDTABLEM_H_

#include "../lib_table/table.h"
#include "../lib_tvector/tvector.h"

template <class TKey, class TValue>
class UnsortedTableM : public Table<TKey, TValue> {
    TVector<Pair<TKey, TValue>> _rows;
public:
    UnsortedTableM();

    ~UnsortedTableM();

    void insert(const TKey&, const TValue&) override;  // +
    void erase(const TKey&) override;  // +
    const TValue* found(const TKey&) const noexcept override;  // +
    bool is_empty() const noexcept override;
    void print(std::ostream& os = std::cout) const noexcept override;
};

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
    _rows.erase(ind);
}

template <class TKey, class TValue>
const TValue* UnsortedTableM<TKey, TValue>::found(const TKey& key) const noexcept {
    Pair<TKey, TValue> pair(key, TValue());
    int ind = find_first_elem_by_index(_rows, pair);
    if (ind == -1)
        return nullptr;
    return &_rows[ind].second;
}

template <class TKey, class TValue>
bool UnsortedTableM<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <class TKey, class TValue>
void UnsortedTableM<TKey, TValue>::print(std::ostream& os) const noexcept {
    print_line();
    print_title();
    print_line();

    for (int i = 0; i < _rows.size(); i++) {
        std::cout << "|";
        print_data(std::to_string(_rows[i].first), KEY_WIDTH);
        print_data(_rows[i].second, VALUE_WIDTH);
        std::cout << std::endl;
    }

    print_line();
}
#endif  // LIB_UNSORTEDTABLEM_UNSORTEDTABLEM_H_
