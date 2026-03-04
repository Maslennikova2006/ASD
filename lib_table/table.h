// Copyright 2026 Mary Maslennikova

#ifndef LIB_TABLE_TABLE_H_
#define LIB_TABLE_TABLE_H_

#include "../lib_itable/itable.h"
#include <iostream>
#include <sstream>
#include <string>

#define KEY_WIDTH 10
#define VALUE_WIDTH 40
#define DIVIDER_WIDTH 3
#define TOTAL_WIDTH KEY_WIDTH + VALUE_WIDTH + DIVIDER_WIDTH

template <class TKey, class TValue>
class Table : public ITable<TKey, TValue> {
public:
    virtual ~Table() = default;

    virtual void insert(const TKey&, const TValue&) override = 0;
    virtual void erase(const TKey&) override = 0;
    virtual const TValue* found(const TKey&) const noexcept override = 0;
    virtual bool is_empty() const noexcept override = 0;
    virtual void print(std::ostream& os = std::cout) const noexcept override = 0;

    friend std::ostream& operator<<(std::ostream& os, const Table<TKey, TValue>& table) {
        table.print(os);
        return os;
    }

protected:
    void print_title() const noexcept;
    void print_line() const noexcept;
    void print_key(TKey key, int width) const noexcept;
    void print_value(TValue val, int width) const noexcept;
};

template <class TKey, class TValue>
void Table<TKey, TValue>::print_title() const noexcept {
    std::cout << "|";
    std::cout << " KEY";
    for (int i = 0; i < KEY_WIDTH - 4; i++) {
        std::cout << " ";
    }
    std::cout << "|";

    std::cout << " VALUE";
    for (int i = 0; i < VALUE_WIDTH - 6; i++) {
        std::cout << " ";
    }
    std::cout << "|\n";
}
template <class TKey, class TValue>
void Table<TKey, TValue>::print_line() const noexcept {
    std::cout << "+";
    for (int i = 0; i < TOTAL_WIDTH - 2; i++) {
        std::cout << "-";
    }
    std::cout << "+\n";
}
template <class TKey, class TValue>
void Table<TKey, TValue>::print_key(TKey key, int width) const noexcept {
    std::ostringstream out;
    out << key;
    std::string str = out.str();
    std::cout << " " << str;
    for (int i = 0; i < width - str.length() - 1; i++) {
        std::cout << " ";
    }
    std::cout << "|";
}
template <class TKey, class TValue>
void Table<TKey, TValue>::print_value(TValue val, int width) const noexcept {
    std::ostringstream out;
    out << val;
    std::string str = out.str();
    std::cout << " " << str;
    for (int i = 0; i < width - str.length() - 1; i++) {
        std::cout << " ";
    }
    std::cout << "|";
}

#endif  // LIB_TABLE_TABLE_H_
