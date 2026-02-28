// Copyright 2026 Mary Maslennikova

#ifndef LIB_POLYNOM_POLYNOM_H_
#define LIB_POLYNOM_POLYNOM_H_

#include <stdexcept>
#include "../lib_list/list.h"
#include "../lib_monom/monom.h"


class Polynom {
    List<Monom> _polynom;

public:
    Polynom();  // +
    explicit Polynom(const Monom& monom);  // +
    Polynom(const Polynom& other);  // +
    explicit Polynom(const std::string& str);  // +

    ~Polynom();

    List<Monom> get_monoms() const noexcept;

    Polynom& operator+=(const Polynom& second);  // +
    Polynom& operator-=(const Polynom& second);  // +
    Polynom& operator*=(const Polynom& second);  // +
    Polynom& operator*=(const double scalar);  // +
    Polynom& operator/=(const double scalar);  // +

    Polynom operator+(const Polynom& second) const;  // +
    Polynom operator-(const Polynom& second) const;  // +
    Polynom operator-() const;  // +
    Polynom operator*(const Polynom& second) const;  // +
    Polynom operator*(const double scalar) const;  // +
    Polynom operator/(const double scalar) const;  // +

    Polynom& operator+=(const Monom& monom);  // +
    Polynom& operator-=(const Monom& monom);  // +
    Polynom& operator*=(const Monom& monom);  // +
    Polynom& operator/=(const Monom& monom);  // +

    Polynom operator+(const Monom& monom) const;  // +
    Polynom operator-(const Monom& monom) const;  // +
    Polynom operator*(const Monom& monom) const;  // +
    Polynom operator/(const Monom& monom) const;  // +

    bool operator==(const Polynom& second) const noexcept;  // +
    bool operator!=(const Polynom& second) const noexcept;  // +
    bool operator>(const Polynom& second) const noexcept;  // +
    bool operator<(const Polynom& second) const noexcept;  // +

    Polynom& operator=(const Polynom& second);  // +

    double calculate(double x, double y, double z) const noexcept;  // +
    std::string toString() const noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Polynom& polynom);
    friend std::istream& operator>>(std::istream& is, Polynom& polynom);

    friend Polynom operator+(const Monom& monom, const Polynom& polynom);  // +
    friend Polynom operator-(const Monom& monom, const Polynom& polynom);  // +
    friend Polynom operator*(const Monom& monom, const Polynom& polynom);  // +

    friend Polynom operator*(const double scalar, const Polynom& polynom);  // +
};

#endif  // LIB_POLYNOM_POLYNOM_H_
