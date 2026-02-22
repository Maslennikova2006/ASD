// Copyright 2026 Mary Maslennikova

#ifndef LIB_SORTEDTABLEM_UNSORTEDTABLEM_H_
#define LIB_SORTEDTABLEM_UNSORTEDTABLEM_H_

#include "../lib_table/table.h"
#include "../lib_tvector/tvector.h"

template <class TKey, class TValue>
class SortedTableM : public Table<TKey, TValue> {
    TVector<Pair<TKey, TValue>> _rows;
public:
    SortedTableM();

    ~SortedTableM();

    void insert(const TKey&, const TValue&) override;
    void erase(const TKey&) override;
    const TValue* found(const TKey&) const noexcept override;
    bool is_empty() const noexcept override;
    void print(std::ostream& os = std::cout) const noexcept override;

private:
    int binary_search(const Pair<TKey, TValue>& pair) const noexcept;
    int nearest_search(const Pair<TKey, TValue>& pair) const noexcept;
};

template <class TKey, class TValue>
SortedTableM<TKey, TValue>::SortedTableM() : _rows() {}

template <class TKey, class TValue>
SortedTableM<TKey, TValue>::~SortedTableM() {}

template <class TKey, class TValue>
void SortedTableM<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    Pair<TKey, TValue> pair(key, value);
    int ind = binary_search(pair);
    if (ind != -1)
        throw std::invalid_argument("The key is already in use in the table!");
    ind = nearest_search(pair);
    _rows.insert(ind + 1, pair);
}

template <class TKey, class TValue>
void SortedTableM<TKey, TValue>::erase(const TKey& key) {
    Pair<TKey, TValue> pair(key, TValue());
    int ind = binary_search(pair);
    if (ind == -1)
        throw std::invalid_argument("The required key was not found!");
    _rows.erase(ind);
}

template <class TKey, class TValue>
const TValue* SortedTableM<TKey, TValue>::found(const TKey& key) const noexcept {
    Pair<TKey, TValue> pair(key, TValue());
    int ind = binary_search(pair);
    if (ind == -1)
        return nullptr;
    return &_rows[ind].second;
}

template <class TKey, class TValue>
bool SortedTableM<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <class TKey, class TValue>
void SortedTableM<TKey, TValue>::print(std::ostream& os) const noexcept {
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

template <class TKey, class TValue>
int SortedTableM<TKey, TValue>::binary_search(const Pair<TKey, TValue>& pair) const noexcept {
    if (_rows.is_empty())
        return -1;
    int left = 0;
    int right = _rows.size() - 1;
    int middle = (left + right) / 2;
    while (left <= right) {
        if (_rows[middle] == pair)
            return middle;
        else if (_rows[middle] < pair)
            left = middle + 1;
        else
            right = middle - 1;
        middle = (left + right) / 2;
    }
    return -1;
}
template <class TKey, class TValue>
int SortedTableM<TKey, TValue>::nearest_search(const Pair<TKey, TValue>& pair) const noexcept {
    if (_rows.is_empty())
        return -1;
    int left = 0;
    int right = _rows.size() - 1;
    int middle = (left + right) / 2;
    int res = -1;
    while (left <= right) {
        if (_rows[middle] == pair)
            return middle;
        else if (_rows[middle] < pair) {
            res = middle;
            left = middle + 1;
        }
        else
            right = middle - 1;
        middle = (left + right) / 2;
    }
    return res;
}
#endif  // LIB_SORTEDTABLEM_SORTEDTABLEM_H_
