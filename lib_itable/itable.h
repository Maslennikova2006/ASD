// Copyright 2026 Mary Maslennikova

#ifndef LIB_ITABLE_ITABLE_H_
#define LIB_ITABLE_ITABLE_H_

template <class TFirst, class TSecond>
struct Pair {
    TFirst first;
    TSecond second;

    Pair(TFirst f, TSecond s) {
        first = f;
        second = s;
    }
    bool operator=(const Pair& other) {
        return first == other.first;
    }
};

template <class TKey, class TValue>
class ITable {
public:
    virtual void insert(const TKey&, const TValue&);
    virtual void erase(const TKey&);
    virtual TValue& found(const TKey&) const noexcept;
    virtual bool is_empty() const noexcept;
};
#endif  // LIB_ITABLE_ITABLE_H_
