// Copyright 2026 Mary Maslennikova

#ifndef LIB_UNSORTEDTABLEM_UNSORTEDTABLEM_H_
#define LIB_UNSORTEDTABLEM_UNSORTEDTABLEM_H_

#include "../lib_itable/itable.h"
#include "../lib_tvector/tvector.h"
#include <utility>

template <class TKey, class TValue>
class UnsortedTableM : public ITable<TKey, TValue> {
    TVector<Pair<TKey, TValue>> _rows;
public:
    UnsortedTableM();

    ~UnsortedTableM();

    void insert(const TKey&, const TValue&) override;
    void erase(const TKey&) override;
    const TValue& found(const TKey&) const noexcept override;
    bool is_empty() const noexcept override;
};
#endif  // LIB_UNSORTEDTABLEM_UNSORTEDTABLEM_H_
