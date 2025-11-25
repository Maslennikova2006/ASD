// Copyright 2025 Mary Maslennikova

#ifndef LIB_ALGORITHMS_ALGORITHMS_H_
#define LIB_ALGORITHMS_ALGORITHMS_H_

#include "../lib_list/list.h"
#include <string>

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
        try {
            i++;
            j += 2;
        }
        catch (std::exception err) {
            std::cerr << err.what() << std::endl;
            return false;
        }
        if (i == j)
            return true;
    }
    return false;
}
template <class T>
bool is_looped_2(List<T>& list) {
    bool isLoop = false;
    Node<T>* startHead = list.head();
    
    Node<T>* cur = list.head();
    Node<T>* prev = nullptr;
    Node<T>* loopPoint = nullptr;
    while (cur != nullptr) {
        if (cur->next == startHead) {
            isLoop = true;
            loopPoint = cur;
            break;
        }
        Node<T>* next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    if (isLoop) {
        Node<T>* cur = prev;
        Node<T>* prev = nullptr;
        while (cur != nullptr && cur != loopPoint) {
            Node<T>* next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        if (cur == loopPoint && cur != nullptr) {
            if (prev != nullptr)
                cur->next = prev;
            else
                cur->next = startHead;
        }
    }
    else {
        cur = prev;
        prev = nullptr;
        while (cur != nullptr) {
            Node<T>* next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
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

bool check_brackets(std::string str);

void read_expression(std::string expression);

#endif  // LIB_ALGORITHMS_ALGORITHMS_H_
