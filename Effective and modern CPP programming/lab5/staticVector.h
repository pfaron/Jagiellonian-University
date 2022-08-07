class VectorException : public std::runtime_error {
public :
    explicit VectorException(const std::string &what_arg) : std::runtime_error(what_arg) {}

    explicit VectorException(const char *what_arg) : std::runtime_error(what_arg) {}
};

struct DoNotFillConstructor {
};

template<typename T, size_t N>
class Vector {
public:
    typedef T value_type;
    typedef T *reference_type;

private:
    value_type arr[N];

public:

    Vector() {
        static value_type default_object;
        std::fill(arr, arr + N, default_object);
    }

    explicit Vector(DoNotFillConstructor p) {}

    explicit Vector(size_t) : Vector() {}

    Vector(const Vector<value_type, N> &vec) {
        std::copy(vec.arr, vec.arr + N, arr);
    }

    Vector(const std::initializer_list<value_type> &list) {
        std::copy(list.begin(), list.end(), arr);
    }

    explicit operator Vector<value_type, 0>() const {
        Vector<value_type, 0> v(DoNotFillConstructor{}, N);
        std::copy(arr, arr + N, v.getData());
        return v;
    }

    template<typename S, size_t M>
    explicit operator Vector<S, M>() const {
        auto min = std::min(N, M);
        Vector<S, M> v{DoNotFillConstructor{}};
        for (auto i = 0; i < min; i++) {
            v[i] = static_cast<S> (arr[i]);
        }
        if (min < M) {
            static value_type default_object;
            std::fill(v.getData() + min, v.getData() + M, default_object);
        }
        return v;
    }

    value_type operator[](size_t i) const {
        return arr[i];
    }

    value_type &operator[](size_t i) {
        return arr[i];
    }

    reference_type getData() const {
        return arr;
    }

    reference_type getData() {
        return arr;
    }


    friend Vector<value_type, N> operator+(Vector<value_type, N> lhs, const Vector<value_type, N> &rhs) {
        for (auto i = 0; i < N; i++) {
            lhs[i] += rhs[i];
        }
        return lhs;
    }

    [[nodiscard]] int size() const {
        return N;
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector<value_type, N> &vector) {
        for (auto el: vector.arr) {
            os << el << " ";
        }
        return os;
    }

};