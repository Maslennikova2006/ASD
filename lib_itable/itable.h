// Copyright 2026 Mary Maslennikova

#ifndef LIB_ITABLE_ITABLE_H_
#define LIB_ITABLE_ITABLE_H_

#include <stdexcept>

template <class TFirst, class TSecond>
struct Pair {
    TFirst first;
    TSecond second;

    Pair() {
        first = TFirst();
        second = TSecond();
    }
    Pair(const TFirst& f, const TSecond& s) {
        first = f;
        second = s;
    }

    Pair& operator=(const Pair& other) noexcept {
        first = other.first;
        second = other.second;
        return *this;
    }

    bool operator==(const Pair<TFirst, TSecond>& other) const {
        return first == other.first;
    }
    bool operator<(const Pair<TFirst, TSecond>& other) const {
        return first < other.first;
    }
    bool operator>(const Pair<TFirst, TSecond>& other) const {
        return first > other.first;
    }

    friend std::ostream& operator<<(std::ostream& os, const Pair<TFirst, TSecond>& pair) {
        os << pair.first << ":" << pair.second;
        return os;
    }
};

template <class TKey, class TValue>
class ITable {
public:
    virtual ~ITable() = default;

    virtual void insert(const TKey&, const TValue&) = 0;
    virtual void erase(const TKey&) = 0;
    virtual const TValue* found(const TKey&) const noexcept = 0;

    virtual bool is_empty() const noexcept = 0;
    virtual void print(std::ostream& os = std::cout) const noexcept = 0;
};
#endif  // LIB_ITABLE_ITABLE_H_
