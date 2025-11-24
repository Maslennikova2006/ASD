// Copyright 2025 Mary Maslennikova

#ifndef LIB_TG_TG_H_
#define LIB_TG_TG_H_

class Tg {
    double _x;
    size_t _N;

public:
    Tg(double x = 0.0, size_t N = 10);

    double calculate();
};


#endif  // LIB_TG_TG_H_