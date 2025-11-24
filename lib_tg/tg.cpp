// Copyright 2025 Mary Maslennikova

#include "../lib_tg/tg.h"
#include "../lib_sin/sin.h"
#include "../lib_cos/cos.h"

Tg::Tg(double x, size_t N) {
    _x = x;
    _N = N;
}

double Tg::calculate() {
    Sin sin(_x, _N);
    Cos cos(_x, _N);
    return sin.calculate() / cos.calculate();
}