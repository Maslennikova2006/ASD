// Copyright 2026 Mary Maslennikova

#ifndef LIB_ADJACENCY_LIST_GRAPH_H_
#define LIB_ADJACENCY_LIST_GRAPH_H_

#include "../lib_itable/itable.h"
#include "../lib_tvector/tvector.h"
#include "../lib_list/list.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <algorithm>

template <class T>
class AdjacencyListGraph {
    TVector<List<Pair<T, int>>> _graph;
    bool _isDirected;
    bool _isWeighted;

public:
    AdjacencyListGraph(bool isDirected = false, bool isWeighted = false);
    AdjacencyListGraph(TVector<Pair<Pair<T, T>, int>> graph, bool isDirected = false, bool isWeighted = false);
    AdjacencyListGraph(std::initializer_list<Pair<Pair<T, T>, int>> graph, bool isDirected = false, bool isWeighted = false);

    int count_vertex() noexcept;
    const TVector<List<Pair<T, int>>> get_graph() const noexcept;
    const TVector<T> get_vertices() const noexcept;

    void add_edge(const T& from, const T& to, int weight = 1);
    void delete_edge(const T& from, const T& to);
    void delete_vertex(const T& vertex);

    void print() const noexcept;

private:
    int find_index(const T& vertex) const noexcept;
};

template <class T>
AdjacencyListGraph<T>::AdjacencyListGraph(bool isDirected, bool isWeighted) : _graph(), _isDirected(isDirected), _isWeighted(isWeighted) {}
template <class T>
AdjacencyListGraph<T>::AdjacencyListGraph(TVector<Pair<Pair<T, T>, int>> graph, bool isDirected, bool isWeighted) 
: _isDirected(isDirected), _isWeighted(isWeighted) {
    for (size_t i = 0; i < graph.size(); i++) {
        add_edge(graph[i].first.first, graph[i].first.second, graph[i].second);
    }
}
template <class T>
AdjacencyListGraph<T>::AdjacencyListGraph(std::initializer_list<Pair<Pair<T, T>, int>> graph, bool isDirected, bool isWeighted)
    : _isDirected(isDirected), _isWeighted(isWeighted) {

    for (auto it = graph.begin(); it != graph.end(); it++) {
        add_edge(it->first.first, it->first.second, it->second);
    }
}

template <class T>
int AdjacencyListGraph<T>::count_vertex() noexcept {
    return _graph.size();
}
template <class T>
const TVector<List<Pair<T, int>>> AdjacencyListGraph<T>::get_graph() const noexcept {
    return _graph;
}
template <class T>
const TVector<T> AdjacencyListGraph<T>::get_vertices() const noexcept {
    TVector<T> vertices(_graph.size());
    for (int i = 0; i < _graph.size(); i++) {
        vertices[i] = _graph[i].head()->value.first;
    }
    return vertices;
}

template <class T>
void AdjacencyListGraph<T>::add_edge(const T& from, const T& to, int weight) {
    int from_ind = find_index(from);
    int to_ind = find_index(to);
    if (_graph.size() != 0 && from_ind == -1 && to_ind == -1)
        throw std::invalid_argument("You cannot create an unconnected edge!");

    if (from_ind == -1) {
        List<Pair<T, int>> list;
        list.push_back(Pair<T, int>(from, 0));
        _graph.push_back(list);
        from_ind = _graph.size() - 1;
    }
    if (to_ind == -1) {
        List<Pair<T, int>> list;
        list.push_back(Pair<T, int>(to, 0));
        _graph.push_back(list);
        to_ind = _graph.size() - 1;
    }

    int w = weight;
    if (!_isWeighted)
        w = 1;

    bool edgeExists = false;
    auto it = _graph[from_ind].begin();
    it++;

    for (it; it != _graph[from_ind].end(); it++) {
        if (it->first == to) {
            it->second = w;
            edgeExists = true;
            break;
        }
    }
    if (!edgeExists)
        _graph[from_ind].push_back(Pair<T, int>(to, w));

    if (!_isDirected && from != to) {
        bool reverseExists = false;
        auto it2 = _graph[to_ind].begin();
        it2++;

        for (it2; it2 != _graph[to_ind].end(); it2++) {
            if (it2->first == from) {
                it2->second = w;
                reverseExists = true;
                break;
            }
        }
        if (!reverseExists)
            _graph[to_ind].push_back(Pair<T, int>(from, w));
    }
}
template <class T>
void AdjacencyListGraph<T>::delete_edge(const T& from, const T& to) {
    int from_ind = find_index(from);
    if (from_ind == -1)
        throw std::invalid_argument("The edge does not exist!");

    bool isDeleted = false;
    auto it = _graph[from_ind].begin();
    it++;
    int i = 1;
    for (it; it != _graph[from_ind].end(); it++) {
        if (it->first == to) {
            _graph[from_ind].erase(i);
            isDeleted = true;
            break;
        }
        i++;
    }

    if (!isDeleted)
        throw std::invalid_argument("The edge does not exist!");

    if (!_isDirected && from != to) {
        int to_ind = find_index(to);
        if (to_ind != -1) {
            auto it2 = _graph[to_ind].begin();
            it2++;
            int j = 1;
            for (it2; it2 != _graph[to_ind].end(); it2++) {
                if (it2->first == from) {
                    _graph[to_ind].erase(j);
                    break;
                }
                j++;
            }
        }
    }
}
template <class T>
void AdjacencyListGraph<T>::delete_vertex(const T& vertex) {
    int ver_ind = find_index(vertex);
    if (ver_ind == -1)
        throw std::invalid_argument("The peak does not exist!");

    for (size_t i = 0; i < _graph.size(); i++) {
        if (i == ver_ind) continue;

        auto it = _graph[i].begin();
        it++;

        int pos = 1;
        for (it; it != _graph[i].end(); it++) {
            if (it->first == vertex) {
                _graph[i].erase(pos);
                break;
            }
            pos++;
        }
    }
    _graph.erase(ver_ind);
}

template <class T>
void AdjacencyListGraph<T>::print() const noexcept {
    _graph.print();
}

template <class T>
int AdjacencyListGraph<T>::find_index(const T& vertex) const noexcept {
    for (size_t i = 0; i < _graph.size(); i++) {
        if (_graph[i].head()->value.first == vertex)
            return i;
    }
    return -1;
}
#endif  // LIB_ADJACENCY_LIST_GRAPH_H_
