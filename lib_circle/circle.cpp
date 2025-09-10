// Copyright 2025 Mary Maslennikova

#include "../lib_circle/circle.h"
#include <iostream>

Circle::Circle() {
    _point = Point();
    _rad = 0;
}
Circle::Circle(const Point& point, const float rad) {
    _point = point;
    if (rad < 0)
        throw std::logic_error("The radius cannot be less than zero!");
    else
        _rad = rad;
}
Circle::Circle(const int x, const int y, const float rad) {
    _point = Point(x, y);
    if (rad < 0)
        throw std::logic_error("The radius cannot be less than zero!");
    else
        _rad = rad;
}
Circle::Circle(const Circle& other) {
    if (&other == NULL)
        throw std::logic_error("The object has not been received!\n");
    _point = other._point;
    _rad = other._rad;
}

void Circle::set_point(const Point& point) {
    _point = point;
}
void Circle::set_rad(const float rad) {
    if (rad < 0)
        throw std::logic_error("The radius cannot be less than zero!");
    else
        _rad = rad;
}

const Point Circle::get_point() const noexcept {
    return _point;
}
const float Circle::get_rad() const noexcept {
    return _rad;
}

const float Circle::calculate_distance(const Circle& other) const noexcept {
    int dx = _point.get_x() - other.get_point().get_x();
    int dy = _point.get_y() - other.get_point().get_y();
    int d = sqrt(dx * dx + dy * dy);
    return d;
}