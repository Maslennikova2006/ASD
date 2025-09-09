// Copyright 2025 Mary Maslennikova

#ifndef LIB_CIRCLE_CIRCLE_H_
#define LIB_CIRCLE_CIRCLE_H_

#include "../lib_point/point.h"

class Circle {
protected:
    Point _point;
    float _rad;

public:
    Circle();
    Circle(const Point& point, const float rad);
    Circle(const int x, const int y, const float rad);
    Circle(const Circle& other);

    void set_point(const Point&);
    void set_rad(const float rad);

    const Point get_point() const noexcept;
    const float get_rad() const noexcept;

    const float calculate_distance(const Circle& other) const noexcept;
};


#endif  // LIB_CIRCLE_CIRCLE_H_