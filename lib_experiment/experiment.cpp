// Copyright 2026 Mary Maslennikova

#include "../lib_experiment/experiment.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>


GeneratorPolynoms::GeneratorPolynoms(int time) {
    _time = time;
    srand(_time);
}

Monom GeneratorPolynoms::create_monom(int max_power, double max_coeff) const noexcept {
    double coeff = random_coeff(max_coeff);
    int x = random_power(max_power);
    int y = random_power(max_power);
    int z = random_power(max_power);
    int powers[3] = { x, y, z };

    return Monom(coeff, powers);
}
Polynom GeneratorPolynoms::create_polynom(int count, int max_power, double max_coeff) const noexcept {
    Polynom result;

    for (int i = 0; i < count; i++) {
        Monom m = create_monom(max_power, max_coeff);
        result += m;
    }
    return result;
}

TVector<Pair<int, Polynom>> GeneratorPolynoms::generate_data(int count, int monom_count) const noexcept {
    TVector<Pair<int, Polynom>> data;
    data.reserve(count);

    for (int i = 0; i < count; i++) {
        Polynom p = create_polynom(monom_count);
        data.push_back(Pair<int, Polynom>(i, p));
    }
    shuffle(data);
    return data;
}

int GeneratorPolynoms::random_power(int max) const noexcept {
    return rand() % (max + 1);
}
double GeneratorPolynoms::random_coeff(double max) const noexcept {
    int intMax = static_cast<int>(max * 10);
    double coeff = (rand() % (2 * intMax + 1) - intMax) / 10.0;
    if (coeff > -0.01 && coeff < 0.01) 
        coeff = 1.0;
    return coeff;
}