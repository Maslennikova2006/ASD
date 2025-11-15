// Copyright 2025 Mary Maslennikova

#ifndef LIB_ALGORITHMS_ALGORITHMS_H_
#define LIB_ALGORITHMS_ALGORITHMS_H_

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

bool check_brackets(std::string str);

void read_expression(std::string expression);

#endif  // LIB_ALGORITHMS_ALGORITHMS_H_
