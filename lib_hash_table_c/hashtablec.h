// Copyright 2026 Mary Maslennikova

#ifndef LIB_HASHTABLEC_HASHTABLEC_H_
#define LIB_HASHTABLEC_HASHTABLEC_H_

#include "../lib_table/table.h"
#include "../lib_tvector/tvector.h"
#include "../lib_list/list.h"
#include <string>

template <class TValue>
class HashTableC : public Table<std::string, TValue> {
    TVector<List<Pair<std::string, TValue>>> _rows;
    size_t _size;
    size_t _count;
public:
    HashTableC(size_t size = 15);  // +

    ~HashTableC();

    void insert(const std::string& key, const TValue& val) override;  // +
    void erase(const std::string& key) override;  // +
    const TValue* found(const std::string& key) const noexcept override;  // +

    bool is_empty() const noexcept override;  // +
    void print(std::ostream& os = std::cout) const noexcept override;

private:
    size_t h(const std::string& key) const noexcept;
};

template<class TValue>
inline HashTableC<TValue>::HashTableC(size_t size) : _rows(size), _size(size), _count(0) {}
template <class TValue>
HashTableC<TValue>::~HashTableC() {}

template <class TValue>
void HashTableC<TValue>::insert(const std::string& key, const TValue& val) {
    size_t hash = h(key);
    const Node<Pair<std::string, TValue>>* found = _rows[hash].find(Pair<std::string, TValue>(key, val));
    if (found)
        throw std::invalid_argument("Key is already exist!");
    _rows[hash].push_back(Pair<std::string, TValue>(key, val));
    _count++;
}
template <class TValue>
void HashTableC<TValue>::erase(const std::string& key) {
    size_t hash = h(key);
    if (_rows[hash].is_empty())
        throw std::invalid_argument("Key is not exist!");
    if (_rows[hash].head()->value.first == key) {
        _rows[hash].pop_front();
        _count--;
        return;
    }
    for (auto i = _rows[hash].head(); i->next != nullptr; i = i->next) {
        if (i->next->value.first == key) {
            _rows[hash].erase(i);
            _count--;
            return;
        }
    }
    throw std::invalid_argument("Key is not exist!");
}
template <class TValue>
const TValue* HashTableC<TValue>::found(const std::string& key) const noexcept {
    size_t hash = h(key);
    const Node<Pair<std::string, TValue>>* found = _rows[hash].find(Pair<std::string, TValue>(key, TValue()));
    if (!found)
        return nullptr;
    return &found->value.second;
}

template <class TValue>
bool HashTableC<TValue>::is_empty() const noexcept {
    return _count == 0;
}
template <class TValue>
void HashTableC<TValue>::print(std::ostream& os) const noexcept {
    print_line();
    print_title();
    print_line();

    for (int i = 0; i < _rows.size(); i++) {
        auto it = _rows[i].begin();
        while (it != _rows[i].end()) {
            std::cout << "|";
            print_key(it->first, KEY_WIDTH);
            print_value(it->second, VALUE_WIDTH);
            std::cout << std::endl;
            it++;
        }
    }

    print_line();
}

template <class TValue>
size_t HashTableC<TValue>::h(const std::string& key) const noexcept {
    size_t hash = 0;
    for (size_t i = 0; i < key.length(); i++) {
        hash += key[i];
    }
    hash %= _size;
    return hash;
}

#endif  // LIB_HASHTABLEC_HASHTABLEC_H_