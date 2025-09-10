// Copyright 2025 Mary Maslennikova

#ifndef LIB_POINT3D_POINT3D_H_
#define LIB_POINT3D_POINT3D_H_

#include "../lib_point/point.h"

class Point3D : public Point {
    int _z;

public:
    Point3D();
    Point3D(const Point&, const int z);
    Point3D(const int x, const int y, const int z);
    Point3D(const Point3D&);

    void set_z(const int);

    const int get_z() const noexcept;

    bool operator==(const Point3D&) const;
};
#endif  // LIB_POINT3D_POINT3D_H_
