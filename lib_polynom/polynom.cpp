// Copyright 2026 Mary Maslennikova

#include "../lib_polynom/polynom.h"

Polynom::Polynom() {
    Monom zero;
    _polynom.push_back(zero);
}
Polynom::Polynom(const Monom& monom) {
    _polynom.push_back(monom);
}
Polynom::Polynom(const Polynom& other) {
    _polynom = List<Monom>(other._polynom);
}

Polynom::~Polynom() {}
