#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

template<typename T, size_t N, size_t M>
class Matrix {

    T data[N * M];

public:
    [[nodiscard]] constexpr size_t numberOfRows() const { return N; }

    [[nodiscard]] constexpr size_t numberOfColumns() const { return M; }

    Matrix(size_t n_rows = N, size_t n_cols = M) {
        std::fill_n(data, N * M, T{});
    }

    Matrix(const std::initializer_list<std::initializer_list<T>> &list) {
        T *p = data;
        for (const auto &row: list) {
            T *p2 = std::copy(row.begin(), row.end(), p);
            std::fill(p2, p += M, T{});
        }
    }

    Matrix(const Matrix &m) {
        std::copy_n(m.data, N * M, data);
    }

    Matrix &operator=(const Matrix &m) {
        if (&m != this) {
            std::copy_n(m.data, N * M, data);
        }
        return *this;
    }

    T &operator()(size_t i, size_t j) {
        return data[(i - 1) * M + j - 1];
    }

    T operator()(size_t i, size_t j) const {
        return data[(i - 1) * M + j - 1];
    }

    friend Matrix operator+(const Matrix &a, const Matrix &b) {
        Matrix r;
        for (size_t i = 1; i <= N; ++i) {
            for (size_t j = 1; j <= M; ++j) {
                r(i, j) = a(i, j) + b(i, j);
            }
        }
        return r;
    }

    class Iterator;

    class ConstIterator;

    using iterator = Iterator;
    using const_iterator = ConstIterator;
    using row_iterator = Iterator;
    using col_iterator = Iterator;

    class Iterator {
    private:
        using value_type = T;
        using pointer_type = T *;
        using reference_type = T &;

        pointer_type curr_el;
        size_t step;

    public:
        explicit Iterator(pointer_type curr_el, size_t step = 1) : curr_el(curr_el), step(step) {}

        Iterator &operator++() {
            curr_el += step;
            return *this;
        }

        Iterator operator++(int) {
            Iterator ret{*this};
            ++(*this);
            return ret;
        }

        reference_type operator*() const {
            return *curr_el;
        }

        pointer_type operator->() const {
            return curr_el;
        }

        bool operator==(Iterator other) const { return curr_el == other.curr_el; }

        bool operator!=(Iterator other) const { return !operator==(other); }

    };

    class ConstIterator {
    private:
        using value_type = const T;
        using pointer_type = const T *;
        using reference_type = const T &;

        pointer_type curr_el;
        size_t step;

    public:
        explicit ConstIterator(pointer_type curr_el, size_t step = 1) : curr_el(curr_el), step(step) {}

        ConstIterator &operator++() {
            curr_el += step;
            return *this;
        }

        ConstIterator operator++(int) {
            Iterator ret = *this;
            ++(*this);
            return ret;
        }

        reference_type operator*() const {
            return *curr_el;
        }

        pointer_type operator->() const {
            return curr_el;
        }

        bool operator==(ConstIterator other) const { return curr_el == other.curr_el; }

        bool operator!=(ConstIterator other) const { return !operator==(other); }

    };

    iterator begin() {
        return Iterator(data);
    }

    iterator end() {
        return Iterator(data + N * M);
    }

    const_iterator begin() const {
        return ConstIterator(data);
    }

    const_iterator end() const {
        return ConstIterator(data + N * M);
    }

    row_iterator row_begin(size_t n) {
        return Iterator(data + (n - 1) * M);
    }

    row_iterator row_end(size_t n) {
        return Iterator(data + n * M);
    }

    col_iterator col_begin(size_t n) {
        return Iterator(data + (n - 1), M);
    }

    col_iterator col_end(size_t n) {
        return Iterator(data + N * M + (n - 1));
    }

};

template<typename T, size_t N, size_t M>
void printMatrix(const Matrix<T, N, M> &m, int width = 10) {
    for (size_t i = 1; i <= m.numberOfRows(); ++i) {
        for (size_t j = 1; j <= m.numberOfColumns(); ++j) {
            if (j != 1)
                cout << " ";
            cout << setw(width) << m(i, j);
        }
        cout << endl;
    }
}
