// Copyright 2025 Mary Maslennikova

#ifndef LIB_ALGORITHMS_ALGORITHMS_H_
#define LIB_ALGORITHMS_ALGORITHMS_H_

#include "../lib_list/list.h"
#include <string>
#include "../lib_adjacency_list_graph/adjacency_list_graph.h"
#include "../lib_tvector/tvector.h"
#include "../lib_queue_priority/queue_priority.h"

enum Position { intersect, inside, no_point, match, touch };

template<class T>
Position check_position(const T& first, const T& second) {
    int d = first.calculate_distance(second);
    if (first.get_rad() == second.get_rad() && first.get_point() == second.get_point())
        return match;
    else if (d == first.get_rad() + second.get_rad())
        return touch;
    else if ((d < first.get_rad() - second.get_rad()) && d > 0)
        return inside;
    else if (d > second.get_rad() + first.get_rad())
        return no_point;
    else
        return intersect;
}

void show_position(Position pos);

template <class T>
bool is_looped(List<T>& list) {
    List<T>::Iterator i, j;
    i = list.begin();
    j = list.begin();

    while (j != list.end() && i != list.end()) {
        i++;
        j++;
        if (j == nullptr)
            return false;
        j++;
        if (i == j) 
            return true;
    }
    return false;
}
template <class T>
bool is_looped2(List<T>& list) {
    Node<T>* startHead = list.head();
    Node<T>* cur = list.head();
    Node<T>* prev = nullptr;
    bool isLoop = false;

    while (cur != nullptr) {
        if (cur->next == startHead) {
            isLoop = true;
            break;
        }
        Node<T>* next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    while (prev != nullptr) {
        Node<T>* next = prev->next;
        prev->next = cur;
        cur = prev;
        prev = next;
    }
    return isLoop;
}
template <class T>
Node<T>* find_loop(List<T>& list) {
    Node<T>* i = list.head();
    Node<T>* j = list.head();

    bool isLoop = false;
    while (j != nullptr && j->next != nullptr) {
        i = i->next;
        j = j->next->next;

        if (i == j) {
            isLoop = true;
            break;
        }
    }
    if (!isLoop) 
        return nullptr;

    i = list.head();
    while (i != j) {
        i = i->next;
        j = j->next;
    }
    return i;
}

bool check_brackets(const std::string& str);

void read_expression(const std::string& expression);

void sort_vector();

template <class T>
int get_index(TVector<Pair<T, int>>& value_to_index, T vertex) {
    for (int i = 0; i < value_to_index.size(); i++) {
        if (value_to_index[i].first == vertex) {
            return value_to_index[i].second;
        }
    }
    return -1;
}
template <class T>
TVector<T> algorithm_Dijkstra_Q(AdjacencyListGraph<T>& graph, T start, T final) {
    int count = graph.count_vertex();
    TVector<size_t> lengths(count);
    TVector<bool> visited(count);
    TVector<int> prevs(count);
    TVector<T> vertices = graph.get_vertices();

    TVector<Pair<T, int>> value_to_index(count);
    for (int i = 0; i < count; i++) {
        value_to_index[i] = Pair<T, int>(vertices[i], i);
    }

    int start_ind = get_index(value_to_index, start);
    int final_ind = get_index(value_to_index, final);

    TVector<T> path;
    if (start_ind == -1 || final_ind == -1) {
        return path;
    }

    for (int i = 0; i < count; i++) {
        lengths[i] = -1;
        visited[i] = false;
        prevs[i] = -1;
    }
    lengths[start_ind] = 0;

    QueuePriority<PairPriority<int>> q;
    auto g = graph.get_graph();
    int order = 0;

    q.insert(PairPriority<int>(0, start_ind, order++));
    while (!q.is_empty()) {
        auto cur = q.top();
        q.pop();

        int cur_ind = cur.value;
        size_t cur_len = cur.priority;

        if (visited[cur_ind])
            continue;

        visited[cur_ind] = true;

        if (cur_ind == final_ind)
            break;

        int ind = -1;
        for (int i = 0; i < g.size(); i++) {
            if (g[i].head()->value.first == vertices[cur_ind]) {
                ind = i;
                break;
            }
        }
        if (ind == -1)
            continue;

        auto it = g[ind].begin();
        it++;

        while (it != g[ind].end()) {
            int neighbor_ind = get_index(value_to_index, it->first);
            if (neighbor_ind != -1) {
                size_t new_len = lengths[cur_ind] + it->second;
                if (new_len < lengths[neighbor_ind]) {
                    lengths[neighbor_ind] = new_len;
                    prevs[neighbor_ind] = cur_ind;
                    q.insert(PairPriority<int>(new_len, neighbor_ind, order++));
                }
            }
            it++;
        }
    }
    if (lengths[final_ind] == -1)
        return path;

    TVector<int> reverse_path_ind;
    for (int i = final_ind; i != -1; i = prevs[i]) {
        reverse_path_ind.push_back(i);
    }

    for (int i = reverse_path_ind.size() - 1; i >= 0; i--) {
        path.push_back(vertices[reverse_path_ind[i]]);
    }

    return path;
}
template <class T>
TVector<int> algorithm_Dijkstra(AdjacencyListGraph<T>& graph, T start, T final) {
    int count = graph.count_vertex();
    TVector<size_t> lengths(count);
    TVector<bool> visited(count);
    TVector<int> prevs(count);
    TVector<T> vertices = graph.get_vertices();

    TVector<Pair<T, int>> value_to_index(count);
    for (int i = 0; i < count; i++) {
        value_to_index[i] = Pair<T, int>(vertices[i], i);
    }

    int start_ind = get_index(value_to_index, start);
    int final_ind = get_index(value_to_index, final);

    TVector<T> path;
    if (start_ind == -1 || final_ind == -1)
        return path;

    for (int i = 0; i < count; i++) {
        lengths[i] = -1;
        visited[i] = false;
        prevs[i] = -1;
    }
    lengths[start_ind] = 0;

    auto g = graph.get_graph();

    for (int i = 0; i < count; i++) {
        int min_vertex_ind = -1;
        size_t min_len = -1;

        for (int j = 0; j < count; j++) {
            if (!visited[j] && lengths[j] != -1 && lengths[j] < min_len) {
                min_len = lengths[j];
                min_vertex_ind = j;
            }
        }

        if (min_vertex_ind == -1) break;

        visited[min_vertex_ind] = true;

        if (min_vertex_ind == final_ind) break;

        auto cur = vertices[min_vertex_ind];

        // Ќаходим список смежности дл€ этого значени€
        int ind = -1;
        for (int j = 0; j < g.size(); j++) {
            if (g[j].head()->value.first == cur) {
                ind = j;
                break;
            }
        }

        if (ind == -1) continue;

        auto it = g[ind].begin();
        it++;

        while (it != g[ind].end()) {
            int neighbor_ind = get_index(value_to_index, it->first);

            if (neighbor_ind != -1) {
                size_t new_len = lengths[min_vertex_ind] + it->second;
                if (new_len < lengths[neighbor_ind] || lengths[neighbor_ind] == -1) {
                    lengths[neighbor_ind] = new_len;
                    prevs[neighbor_ind] = min_vertex_ind;
                }
            }
            it++;
        }
    }

    if (lengths[final_ind] == -1)
        return path;

    TVector<int> reverse_path_ind;
    for (int i = final_ind; i != -1; i = prevs[i]) {
        reverse_path_ind.push_back(i);
    }

    for (int i = reverse_path_ind.size() - 1; i >= 0; i--) {
        path.push_back(vertices[reverse_path_ind[i]]);
    }

    return path;
}

#endif  // LIB_ALGORITHMS_ALGORITHMS_H_
