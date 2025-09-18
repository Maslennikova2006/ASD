#include "../lib_matrix/matrix.h"

template<typename T>
class TriangleMatrix : public Matrix<T> {

public:
    TriangleMatrix() {}
    TriangleMatrix(size_t m) {}
    TriangleMatrix(const TriangleMatrix<T>& other) {}

    TriangleMatrix<T> operator+(const TriangleMatrix<T>& other) {
        TriangleMatrix<T> res;
        return res;
    }
    TriangleMatrix<T> operator-(const TriangleMatrix<T>& other) {
        TriangleMatrix<T> res;
        return res;
    }
    TriangleMatrix<T> operator*(const TriangleMatrix<T>& other) {
        TriangleMatrix<T> res;
        return res;
    }
    TriangleMatrix<T> operator*(const T& scalar) {
        TriangleMatrix<T> res;
        return res;
    }
    MathVector<T> operator*(const MathVector<T>& vector) {
        MathVector<T> res;
        return res;
    }

    TriangleMatrix<T>& operator=(const TriangleMatrix<T>& other) {
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const TriangleMatrix&) {
        return os;
    }
    friend std::istream& operator>>(std::istream& is, TriangleMatrix&) {
        return is;
    }
};