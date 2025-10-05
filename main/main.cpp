// Copyright 2025 Mary Maslennikova

//#define EASY_EXAMPLE
#define CIRCLE
//#define SPHERE

#ifdef EASY_EXAMPLE
#include <iostream>
#include <iomanip>
#include "../lib_easy_example/easy_example.h"

int main() {
  int a, b;
  float result;

  a = 1; b = 4;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  a = 1; b = 0;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }
  return 0;
}
#endif  // EASY_EXAMPLE

#ifdef CIRCLE
#include "../lib_circle/circle.h"
#include "../lib_algorithms/algorithms.h"
#include <clocale>

int main() {
    setlocale(LC_ALL, "rus");
    Point point1(5, 8);
    Circle c1(point1, 9);
    Circle c2(3, 8, 6);
    show_position(check_position(c1, c2));
    Point point2(0, 0);
    Circle c3(point2, 3);
    Circle c4(15, 8, 2);
    show_position(check_position(c3, c4));
    Point point3(0, 0);
    Circle c5(point3, 3);
    Circle c6(8, 0, 5);
    show_position(check_position(c5, c6));
    Circle c7(0, 0, 5);
    Circle c8(3, 0, 4);
    show_position(check_position(c7, c8));
    Point point5(-2, 2);
    Circle c9(point5, 3);
    Circle c10(-2, 2, 3);
    show_position(check_position(c9, c10));
    return 0;
}
#endif  // CIRCLE

#ifdef SPHERE
#include "../lib_sphere/sphere.h"
#include "../lib_algorithms/algorithms.h"
#include <clocale>

int main() {
    setlocale(LC_ALL, "rus");
    Point3D point1(-2, 2, 2);
    Sphere s1(point1, 3);
    Sphere s2(-2, 2, 2, 3);
    show_position(check_position(s1, s2));
    Point3D point2(-2, 2, 2);
    Sphere s3(point2, 3);
    Sphere s4(-5, 8, 7, 2);
    show_position(check_position(s3, s4));
    Point point3(0, 3);
    Sphere s5(point3, 5, 3);
    Sphere s6(0, 3, 4, 2);
    show_position(check_position(s5, s6));
    Point point(0, 0);
    Sphere s7(point, 0, 3);
    Sphere s8(0, 1, 0, 1);
    show_position(check_position(s7, s8));
    Sphere s9(0, 0, 0, 2);
    Sphere s10(3, 0, 0, 1);
    show_position(check_position(s9, s10));
    return 0;
}
#endif  // SPHERE