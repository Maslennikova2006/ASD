// Copyright 2026 Mary Maslennikova

#ifndef LIB_MONOM_MONOM_H_
#define LIB_MONOM_MONOM_H_

#include <stdexcept>
#define VAR_COUNT 3

// + вычисление монома в точке

class Monom {
    double _coeff;
    int _powers[VAR_COUNT];

public:
    Monom(double coeff = 0.0, const int* powers = nullptr);
    Monom(const Monom& other);
    Monom(const std::string& str);

    ~Monom();

    const double get_coeff() const noexcept;
    const int* get_powers() const noexcept;

    void set_coeff(double coeff) noexcept;
    void set_power(int ind, int value) noexcept;

    Monom& operator+=(const Monom& second);  // +
    Monom& operator-=(const Monom& second);  // +
    Monom& operator*=(const Monom& second);  // +
    Monom& operator/=(const Monom& second);  // +
    Monom& operator*=(const double scalar);  // +
    Monom& operator/=(const double scalar);  // +

    Monom operator+(const Monom& second) const;  // +
    Monom operator-(const Monom& second) const;  // +
    Monom operator-() const;  // +
    Monom operator*(const Monom& second) const;  // +
    Monom operator/(const Monom& second) const;  // +
    Monom operator*(const double scalar);  // +
    Monom operator/(const double scalar);  // +

    bool operator==(const Monom& second) const noexcept;  // +
    bool operator!=(const Monom& second) const noexcept;  // +
    bool operator>(const Monom& second) const noexcept;  // +
    bool operator<(const Monom& second) const noexcept;  // +

    Monom& operator=(const Monom& second);  // +

    double calculate(double x, double y, double z) const noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Monom& monom);
    friend std::istream& operator>>(std::istream& is, Monom& monom);
};

#endif  // LIB_MONOM_MONOM_H_
