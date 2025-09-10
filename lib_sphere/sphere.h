// Copyright 2025 Mary Maslennikova

#ifndef LIB_SPHERE_SPHERE_H_
#define LIB_SPHERE_SPHERE_H_

#include "../lib_circle/circle.h"
#include "../lib_point3D/point3D.h"

class Sphere : public Circle {
    Point3D _point3D;

public:
    Sphere();
    Sphere(const Point3D& point, const float rad);
    Sphere(const Point& point, const int z, const float rad);
    Sphere(const int x, const int y, const int z, const float rad);
    Sphere(const Sphere& other);

    void set_point3D(const Point3D& point);

    const Point3D get_point3D() const noexcept;

    const int calculate_distance(const Sphere& other) const noexcept;
};

#endif  // LIB_SPHERE_SPHERE_H_