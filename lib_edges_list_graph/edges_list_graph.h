// Copyright 2026 Mary Maslennikova

#ifndef LIB_EDGES_LIST_GRAPH_H_
#define LIB_EDGES_LIST_GRAPH_H_

#include "../lib_itable/itable.h"
#include "../lib_tvector/tvector.h"
#include "../lib_list/list.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <algorithm>

template <class T>
class EdgesListGraph {
    TVector<Pair<Pair<T, T>, int>> _graph;
    bool _isDirected;
    bool _isWeighted;

public:
    EdgesListGraph(bool isDirected = false, bool isWeighted = false);
    EdgesListGraph(TVector<Pair<Pair<T, T>, int>> graph, bool isDirected = false, bool isWeighted = false);
    EdgesListGraph(std::initializer_list<Pair<Pair<T, T>, int>> graph, bool isDirected = false, bool isWeighted = false);

    void add_edge(const T& from, const T& to, int weight = 1);
    void delete_edge(const T& from, const T& to);
    void delete_vertex(const T& vertex);

    void print() const noexcept;

private:
    bool vertex_exists(const T& vertex) const noexcept;
};

template <class T>
EdgesListGraph<T>::EdgesListGraph(bool isDirected, bool isWeighted) : _graph(), _isDirected(isDirected), _isWeighted(isWeighted) {}
template <class T>
EdgesListGraph<T>::EdgesListGraph(TVector<Pair<Pair<T, T>, int>> graph, bool isDirected, bool isWeighted)
    : _isDirected(isDirected), _isWeighted(isWeighted) {
    for (size_t i = 0; i < graph.size(); i++) {
        add_edge(graph[i].first.first, graph[i].first.second, graph[i].second);
    }
}
template <class T>
EdgesListGraph<T>::EdgesListGraph(std::initializer_list<Pair<Pair<T, T>, int>> graph, bool isDirected, bool isWeighted)
    : _isDirected(isDirected), _isWeighted(isWeighted) {
    for (auto it = graph.begin(); it != graph.end(); it++) {
        add_edge(it->first.first, it->first.second, it->second);
    }
}

template <class T>
void EdgesListGraph<T>::add_edge(const T& from, const T& to, int weight) {
    int w = weight;
    if (!_isWeighted)
        w = 1;

    if (_graph.size() != 0 && !vertex_exists(from) && !vertex_exists(to))
            throw std::invalid_argument("You cannot create an unconnected edge!");

    for (size_t i = 0; i < _graph.size(); i++) {
        if (_graph[i].first.first == from && _graph[i].first.second == to) {
            _graph[i].second = w;
            return;
        }
    }
    _graph.push_back(Pair<Pair<T, T>, int>(Pair<T, T>(from, to), w));
    
    if (!_isDirected && from != to) {
        bool reverse_exists = false;
        for (size_t i = 0; i < _graph.size(); i++) {
            if (_graph[i].first.first == to && _graph[i].first.second == from) {
                reverse_exists = true;
                break;
            }
        }
        if (!reverse_exists)
            _graph.push_back(Pair<Pair<T, T>, int>(Pair<T, T>(to, from), w));
    }
}
template <class T>
void EdgesListGraph<T>::delete_edge(const T& from, const T& to) {
    bool isDeleted = false;
    for (size_t i = 0; i < _graph.size(); i++) {
        if (_graph[i].first.first == from && _graph[i].first.second == to) {
            _graph.erase(i);
            isDeleted = true;
            break;
        }
    }
    
    if (!isDeleted)
        throw std::invalid_argument("Such an edge does not exist!");
    
    if (!_isDirected && from != to) {
        for (size_t i = 0; i < _graph.size(); i++) {
            if (_graph[i].first.first == to && _graph[i].first.second == from) {
                _graph.erase(i);
                break;
            }
        }
    }
}
template <class T>
void EdgesListGraph<T>::delete_vertex(const T& vertex) {
    bool isDeleted = false;
    for (int i = _graph.size() - 1; i >= 0; i--) {
        if (_graph[i].first.first == vertex || _graph[i].first.second == vertex) {
            _graph.erase(i);
            isDeleted = true;
        }
    }
    if (!isDeleted)
        throw std::invalid_argument("Such a peak does not exist!");
}

template <class T>
void EdgesListGraph<T>::print() const noexcept {
    _graph.print();
}

template <class T>
bool EdgesListGraph<T>::vertex_exists(const T& vertex) const noexcept {
    for (size_t i = 0; i < _graph.size(); i++) {
        if (_graph[i].first.first == vertex || _graph[i].first.second == vertex)
            return true;
    }
    return false;
}
#endif  // LIB_EDGES_LIST_GRAPH_H_
