
#include "../lib_tvector/tvector.h"

template <typename T>
class MathVector : private TVector<T> {

public:
    MathVector() {}
    MathVector(const MathVector<T>& other) {}

    MathVector<T>& operator=(const MathVector<T>& other) {
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const MathVector&) {
        return os;
    }
    friend std::istream& operator>>(std::istream& is, MathVector&) {
        return is;
    }
};