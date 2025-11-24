// Copyright 2025 Mary Maslennikova

#include "../lib_cos/cos.h"

Cos::Cos(double x, size_t N) {
    _x = x;
    _N = N;
}

double Cos::calculate() {
    double res = 1.0;
    double term = 1.0;

    for (int n = 1; n <= _N; n++) {
        term *= (-1) * _x * _x / ((2 * n - 1) * (2 * n));
        res += term;
    }
    return res;
}