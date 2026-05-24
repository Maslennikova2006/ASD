// Copyright 2026 Mary Maslennikova

#ifndef LIB_EXPERIMENT_EXPERIMENT_H_
#define LIB_EXPERIMENT_EXPERIMENT_H_

#include "../lib_polynom/polynom.h"
#include "../lib_tvector/tvector.h"
#include "../lib_itable/itable.h"
#include <vector>
#include <cstdlib>
#include <ctime>

class GeneratorPolynoms {
    int _time;

public:
    GeneratorPolynoms(int time = 0);

    Monom create_monom(int max_power = 10, double max_coeff = 100.0) const noexcept;
    Polynom create_polynom(int count = 5, int max_power = 10, double max_coeff = 100.0) const noexcept;

    TVector<Pair<int, Polynom>> generate_data(int count, int monom_count = 5) const noexcept;

private:
    int random_power(int max) const noexcept;
    double random_coeff(double max) const noexcept;
};

#endif  // LIB_EXPERIMENT_EXPERIMENT_H_