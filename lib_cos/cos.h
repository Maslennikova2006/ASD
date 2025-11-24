// Copyright 2025 Mary Maslennikova

#ifndef LIB_COS_COS_H_
#define LIB_COS_COS_H_

class Cos {
    double _x;
    size_t _N;

public:
    Cos(double x = 0.0, size_t N = 10);

    double calculate();
};


#endif  // LIB_COS_COS_H_