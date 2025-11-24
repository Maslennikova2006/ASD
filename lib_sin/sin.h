// Copyright 2025 Mary Maslennikova

#ifndef LIB_SIN_SIN_H_
#define LIB_SIN_SIN_H_

class Sin {
    double _x;
    size_t _N;

public:
    Sin(double x = 0.0, size_t N = 10);
    
    double calculate();
};


#endif  // LIB_SIN_SIN_H_