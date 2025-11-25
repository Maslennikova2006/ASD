// Copyright 2025 Mary Maslennikova

#include "../lib_dsu/dsu.h"

Dsu::Dsu(size_t size) {
    _size = size;
    _parent = new int[_size];
    _rank = new int[_size];
    for (size_t i = 0; i < _size; i++) {
        _parent[i] = i;
        _rank[i] = 0;
    }
}

Dsu::~Dsu() {
    delete[] _parent;
    delete[] _rank;
}

void Dsu::union_set(int x, int y) {
    if (x < 0 || y < 0 || x >= _size || y >= _size)
        throw std::invalid_argument("Invalid element value!");

    int parent_x = find(x);
    int parent_y = find(y);

    if (_rank[parent_x] >= _rank[parent_y])
        _parent[parent_y] = parent_x;
    else
        _parent[parent_x] = parent_y;

    if (_rank[parent_x] == _rank[parent_y])
        _rank[parent_x]++;
}
int Dsu::find(int elem) { // протаскивать ранг
    if (elem < 0 || elem >= _size)
        throw std::invalid_argument("Invalid element value!");
    return elem = find_rec(_parent[elem]);
}

int Dsu::find_rec(int elem) {
    if (_parent[elem] == elem)
        return elem;
    return elem = find_rec(_parent[elem]);
}