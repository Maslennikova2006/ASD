// Copyright 2025 Mary Maslennikova

#include "../lib_functions/functions.h"
#include <stdexcept>

double Functions::abs(double x) {
    if (x < 0) return -x;
    return x;
}
double Functions::sin(double x) {
    double rad = reduction_to_radians(x);
    double res = rad;
    double term = rad;
    int n = 1;
    while (abs(term) > EPSILON) {
        term = -term * rad * rad / ((2 * n + 1) * (2 * n));
        res += term;
        n++;
    }
    return res;
}
double Functions::cos(double x) {
    double rad = reduction_to_radians(x);
    double res = 1.0;
    double term = 1.0;
    int n = 1;
    while (abs(term) > EPSILON) {
        term = -term * rad * rad / ((2 * n) * (2 * n - 1));
        res += term;
        n++;
    }
    return res;
}
double Functions::tg(double x) {
    if (Functions::cos(x) == 0)
        throw std::invalid_argument("Division by zero is impossible!\n");
    return Functions::sin(x) / Functions::cos(x);
}
double Functions::reduction_to_radians(double x) {
    return (x * PI) / 180;
}