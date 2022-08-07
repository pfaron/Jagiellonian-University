#include "staticVector.h"

template<typename T>
class Vector<T, 0> {
public:
    typedef T value_type;
    typedef T *reference_type;

private:
    size_t sz;
    std::unique_ptr<value_type[]> dataPtr;

public:

    explicit Vector(size_t s) : sz(s), dataPtr(std::make_unique<value_type[]>(sz)) {
        static value_type default_object;
        std::fill(dataPtr.get(), dataPtr.get() + sz, default_object);
    }

    Vector(DoNotFillConstructor p, size_t s) : sz(s), dataPtr(std::make_unique<value_type[]>(sz)) {}

    Vector(const Vector &vec) : sz(vec.sz), dataPtr(std::make_unique<value_type[]>(sz)) {
        std::copy(vec.getData(), vec.getData() + sz, dataPtr.get());
    }

    Vector(const std::initializer_list<value_type> &list) : sz(list.size()),
                                                            dataPtr(std::make_unique<value_type[]>(sz)) {
        std::copy(list.begin(), list.end(), dataPtr.get());
    }

    template<size_t N>
    explicit operator Vector<value_type, N>() const {
        Vector<value_type, N> v{DoNotFillConstructor{}};
        if (N <= sz) {
            std::copy(dataPtr.get(), dataPtr.get() + N, v.getData());
        } else {
            static value_type default_object;
            std::copy(dataPtr.get(), dataPtr.get() + sz, v.getData());
            std::fill(v.getData() + sz, v.getData() + N, default_object);
        }

        return v;
    }

    value_type operator[](size_t i) const {
        return dataPtr[i];
    }

    value_type &operator[](size_t i) {
        return dataPtr[i];
    }

    reference_type getData() const {
        return dataPtr.get();
    }

    reference_type getData() {
        return dataPtr.get();
    }

    friend Vector operator+(Vector lhs, const Vector &rhs) {
        if (lhs.size() != rhs.size())
            throw VectorException("incompatible sizes in Vector::operator+");
        for (auto i = 0; i < lhs.sz; i++) {
            lhs[i] += rhs[i];
        }
        return lhs;
    }

    [[nodiscard]] int size() const {
        return sz;
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector &vector) {
        for (auto i = 0; i < vector.size(); i++) {
            os << vector[i] << " ";
        }
        return os;
    }

    void resize(size_t new_sz) {
        value_type temp[sz];
        std::copy(dataPtr.get(), dataPtr.get() + sz, temp);

        dataPtr = std::make_unique<value_type[]>(new_sz);

        if (new_sz <= sz) {
            std::copy(temp, temp + new_sz, dataPtr.get());
        } else {
            static value_type default_object;
            std::copy(temp, temp + sz, dataPtr.get());
            std::fill(dataPtr.get() + sz, dataPtr.get() + new_sz, default_object);
        }
        sz = new_sz;
    }

};

template<typename T, size_t N>
inline Vector<T, N> operator+(Vector<T, N> lhs, const Vector<T, 0> &rhs) {
    if (N != rhs.size())
        throw VectorException("Cannot add static vector and dynamic vector. Incompatible sizes.");
    for (auto i = 0; i < N; i++) {
        lhs[i] += rhs[i];
    }
    return lhs;
}

template<typename T, size_t N>
inline Vector<T, N> operator+(const Vector<T, 0> &lhs, Vector<T, N> rhs) {
    if (N != rhs.size())
        throw VectorException("Cannot add dynamic vector and static vector. Incompatible sizes.");
    for (auto i = 0; i < N; i++) {
        rhs[i] += lhs[i];
    }
    return rhs;
}
