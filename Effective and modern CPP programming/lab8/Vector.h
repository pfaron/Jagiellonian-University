#include <memory>
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
#include "VectorPolicies.h"

template<typename T,
        size_t N,
        typename Policy = SafePolicy>
class Vector {
    T data[N];
public:
    typedef std::size_t size_type;
    typedef typename VectorTraits<T>::basic_type value_type;
    typedef typename VectorTraits<T>::scalar_type scalar_type;
    typedef typename VectorTraits<T>::pass_type pass_type;

    Vector() {
        Policy::init(data, N);
    };

    Vector(const Vector &v) = default;

    Vector &operator=(const Vector &m) = default;

    Vector(const std::initializer_list<T> &list) : Vector() {
        Policy::checkInit(list.size(), N);
        auto min = std::min(list.size(), N);
        std::copy(list.begin(), list.begin() + min, data);
    }

    [[nodiscard]] size_type size() const {
        return N;
    }

    pass_type get(size_type index) const {
        Policy::checkIndex(index, N);
        return data[index];
    }

    void set(size_type index, pass_type value) {
        Policy::checkIndex(index, N);
        data[index] = value;
    }

    friend Vector operator*(scalar_type x, const Vector &v) {
        Vector result;
        for (int i = 0; i < v.size(); ++i) {
            result.set(i, VectorTraits<T>::multiply(x, v.get(i)));
        }
        return result;
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector &v) {
        for (int i = 0; i < v.size(); ++i) {
            out << v.get(i) << " ";
        }
        return out;
    }

    friend std::istream &operator>>(std::istream &in, Vector &v) {
        Vector::value_type value;
        for (int i = 0; i < v.size(); ++i) {
            in >> value;
            if (in)
                v.set(i, value);
        }
        return in;
    }
};