// Copyright 2025 Mary Maslennikova

#ifndef LIB_POINT_POINT_H_
#define LIB_POINT_POINT_H_

class Point {
protected:
    int _x;
    int _y;

public:
    Point();
    Point(const int x, const int y);
    Point(const Point& other);

    const int get_x() const noexcept;
    const int get_y() const noexcept;

    void set_x(const int);
    void set_y(const int);

    bool operator==(const Point&) const;
};

#endif  // LIB_POINT_POINT_H_