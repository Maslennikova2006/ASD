// Copyright 2025 Mary Maslennikova

#include "../lib_point/point.h"
#include <iostream>

Point::Point() {
    _x = 0;
    _y = 0;
}
Point::Point(const int x, const int y) {
    _x = x;
    _y = y;
}
Point::Point(const Point& other) {
    if (&other == NULL)
        throw std::logic_error("The object has not been received!\n");
    _x = other._x;
    _y = other._y;
}

const int Point::get_x() const noexcept {
    return _x;
}
const int Point::get_y() const noexcept {
    return _y;
}

void Point::set_x(const int x) {
    _x = x;
}
void Point::set_y(const int y) {
    _y = y;
}

bool Point::operator==(const Point& other) const {
    if (_x == other._x && _y == other._y)
        return true;
    else
        return false;
}