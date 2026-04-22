// Copyright 2026 Mary Maslennikova

#ifndef LIB_HASHTABLEOA_HASHTABLEOA_H_
#define LIB_HASHTABLEOA_HASHTABLEOA_H_

#include "../lib_table/table.h"
#include "../lib_tvector/tvector.h"
#include "../lib_list/list.h"
#include <string>
#include <algorithm> 

template <class TValue>
struct HashData {
    State state;
    Pair<std::string, TValue> pair;

    HashData(const std::string& key = "", const TValue& val = TValue(), State s = empty);

    HashData& operator=(const HashData& other) noexcept;
    bool operator==(const HashData<TValue>& other) const noexcept;
};
template <class TValue>
HashData<TValue>::HashData(const std::string& key, const TValue& val, State s) {
    state = s;
    pair = Pair<std::string, TValue>(key, val);
}
template <class TValue>
HashData<TValue>& HashData<TValue>::operator=(const HashData& other) noexcept {
    if (this != &other) {
        state = other.state;
        pair = other.pair;
    }
    return *this;
}
template <class TValue>
bool HashData<TValue>::operator==(const HashData<TValue>& other) const noexcept {
    return state == other.state && pair == other.pair;
}

template <class TValue>
class HashTableOA : public Table<std::string, TValue> {
    TVector<HashData<TValue>> _rows;
    size_t _size;
    size_t _count;
    size_t _shift;
public:
    HashTableOA(size_t size = 15);

    ~HashTableOA();

    void insert(const std::string& key, const TValue& val) override;
    void erase(const std::string& key) override;
    const TValue* found(const std::string& key) const noexcept override;

    bool is_empty() const noexcept override;
    bool is_full() const noexcept;
    void print(std::ostream& os = std::cout) const noexcept override;

private:
    size_t h(const std::string& key) const noexcept;
    size_t hh(size_t hash) const noexcept;
};

bool is_mutually_simple(size_t first, size_t second) noexcept;
size_t gcd(size_t first, size_t second) noexcept;

template <class TValue>
HashTableOA<TValue>::HashTableOA(size_t size) : _rows(size), _size(size), _count(0) {
    for (size_t i = std::max<size_t>(2, size / 15); i < size; i++) {
        if (is_mutually_simple(i, size)) {
            _shift = i;
            return;
        }
    }
}
template <class TValue>
HashTableOA<TValue>::~HashTableOA() {}

template <class TValue>
void HashTableOA<TValue>::insert(const std::string& key, const TValue& val) {
    if (is_full())
        throw std::invalid_argument("The table is full!");
    size_t hash = h(key);
    while (1) {
        if (_rows[hash].state != busy) {
            _rows[hash] = HashData<TValue>(key, val, busy);
            _count++;
            return;
        }
        if (_rows[hash].pair.first == key)
            throw std::invalid_argument("Key is already exist!");
        hash = hh(hash);
    }
}
template <class TValue>
void HashTableOA<TValue>::erase(const std::string& key) {
    size_t hash = h(key);
    size_t first_hash = hash;
    while (1) {
        if (_rows[hash].state == empty)
            break;
        if (_rows[hash].state == busy && _rows[hash].pair.first == key) {
            _rows[hash].state = deleted;
            _count--;
            return;
        }
        hash = hh(hash);
        if (first_hash == hash)
            break;
    }
    throw std::invalid_argument("Key is not exist!");
}
template <class TValue>
const TValue* HashTableOA<TValue>::found(const std::string& key) const noexcept {
    size_t hash = h(key);
    size_t index = hash;

    while (_rows[index].state != empty) {
        if (_rows[index].state == busy && _rows[index].pair.first == key) {
            return &_rows[index].pair.second;
        }
        index = hh(index);

        if (index == hash) break;
    }

    return nullptr;
}

template <class TValue>
bool HashTableOA<TValue>::is_empty() const noexcept {
    return _count == 0;
}
template <class TValue>
bool HashTableOA<TValue>::is_full() const noexcept {
    return _count == _size;
}
template <class TValue>
void HashTableOA<TValue>::print(std::ostream& os) const noexcept {
    print_line();
    print_title();
    print_line();

    for (int i = 0; i < _rows.size(); i++) {
        if (_rows[i].state == busy) {
            std::cout << "|";
            print_key(_rows[i].pair.first, KEY_WIDTH);
            print_value(_rows[i].pair.second, VALUE_WIDTH);
            std::cout << std::endl;
        }
    }

    print_line();
}

template <class TValue>
size_t HashTableOA<TValue>::h(const std::string& key) const noexcept {
    size_t hash = 0;
    for (size_t i = 0; i < key.length(); i++) {
        hash += key[i];
    }
    hash %= _size;
    return hash;
}
template <class TValue>
size_t HashTableOA<TValue>::hh(size_t hash) const noexcept {
    return (hash + _shift) % _size;
}


bool is_mutually_simple(size_t first, size_t second) noexcept {
    return gcd(first, second) == 1;
}
size_t gcd(size_t first, size_t second) noexcept {
    while (second != 0) {
        size_t temp = second;
        second = first % second;
        first = temp;
    }
    return first;
}

#endif  // LIB_HASHTABLEOA_HASHTABLEOA_H_