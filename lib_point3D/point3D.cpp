// Copyright 2025 Mary Maslennikova

#include "../lib_point3D/point3D.h"
#include <iostream>

Point3D::Point3D() : Point() {
    _z = 0;
}
Point3D::Point3D(const Point& point2D, const int z) : Point(point2D) {
    _z = z;
}
Point3D::Point3D(const int x, const int y, const int z) {
    _x = x;
    _y = y;
    _z = z;
}
Point3D::Point3D(const Point3D& other) : Point(other) {
    _z = other._z;
}

void Point3D::set_z(const int z) {
    _z = z;
}

const int Point3D::get_z() const noexcept {
    return _z;
}

bool Point3D::operator==(const Point3D& other) const {
    return Point::operator==(other) && _z == other._z;
}