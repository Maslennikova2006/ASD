// Copyright 2025 Mary Maslennikova

#ifndef LIB_DSU_DSU_H_
#define LIB_DSU_DSU_H_

#include <cstdlib>
#include <stdexcept>

class Dsu {
    int* _parent;
    int* _rank;
    size_t _size;

public:
    Dsu(size_t size);

    ~Dsu();

    void union_set(int x, int y);
    int find(int elem);

private:
    int find_rec(int elem);
};

#endif  // LIB_DSU_DSU_H_