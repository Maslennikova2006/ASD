#include "../lib_mathvector/mathvector.h"

template <typename T>
class Matrix : public MathVector<MathVector<T>> {

public:
    Matrix() {}
    Matrix(size_t m, size_t n) {}
    Matrix(const Matrix<T>& other) {}

    Matrix<T> operator+(const Matrix<T>& other) {
        Matrix<T> res;
        return res;
    }
    Matrix<T> operator-(const Matrix<T>& other) {
        Matrix<T> res;
        return res;
    }
    Matrix<T> operator*(const Matrix<T>& other) {
        Matrix<T> res;
        return res;
    }
    Matrix<T> operator*(const T& scalar) {
        Matrix<T> res;
        return res;
    }
    MathVector<T> operator*(const MathVector<T>& vector) {
        MathVector<T> res;
        return res;
    }

    Matrix<T>& operator=(const Matrix<T>& other) {
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix&) {
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Matrix&) {
        return is;
    }
};