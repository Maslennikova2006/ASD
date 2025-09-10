#include "../lib_sphere/sphere.h"
#include <iostream>

Sphere::Sphere() : Circle() {
    _point3D = Point3D();
}
Sphere::Sphere(const Point3D& point, const float rad) {
    _point3D = point;
    if (rad < 0)
        throw std::logic_error("The radius cannot be less than zero!");
    else
        _rad = rad;
}
Sphere::Sphere(const Point& point, const int z, const float rad) {
    _point3D = Point3D(point, z);
    if (rad < 0)
        throw std::logic_error("The radius cannot be less than zero!");
    else
        _rad = rad;
}
Sphere::Sphere(const int x, const int y, const int z, const float rad) {
    _point3D = Point3D(x, y, z);
    if (rad < 0)
        throw std::logic_error("The radius cannot be less than zero!");
    else
        _rad = rad;
}
Sphere::Sphere(const Sphere& other) : Circle(other) {
    _point3D = other._point3D;
}

void Sphere::set_point3D(const Point3D& point) {
    _point3D = point;
}

const Point3D Sphere::get_point3D() const noexcept {
    return _point3D;
}

const int Sphere::calculate_distance(const Sphere& other) const noexcept {
    int dx = _point3D.get_x() - other.get_point3D().get_x();
    int dy = _point3D.get_y() - other.get_point3D().get_y();
    int dz = _point3D.get_z() - other.get_point3D().get_z();
    int d = sqrt(dx * dx + dy * dy + dz * dz);
    return d;
}