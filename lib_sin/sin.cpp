// Copyright 2025 Mary Maslennikova

#include "../lib_sin/sin.h"

Sin::Sin(double x, size_t N) {
    _x = x;
    _N = N;
}

double Sin::calculate() {
    double res = _x;
    double term = _x;

    for (int n = 1; n <= _N; n++) {
        term *= (-1) * _x * _x / ((2 * n) * (2 * n + 1));
        res += term;
    }
    return res;
}