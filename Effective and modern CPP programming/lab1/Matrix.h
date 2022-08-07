#include <iostream>
#include <algorithm>
#include <iomanip>
#include <utility>

using namespace std;

class Matrix {
protected:
    size_t n = 0;
    size_t m = 0;
    double *data = nullptr;

public:
    Matrix() {
        cout << "Standard constructor\n";
    }

    Matrix(unsigned n, unsigned m) : n(n), m(m), data(new double[n * m]) {
        cout << "Dimensions constructor " << n << " " << m << "\n";
        std::fill_n(data, n * m, 0.0);
    }

    Matrix(const std::initializer_list<std::initializer_list<double>> &val) {
        cout << "Initializer list constructor\n";

        size_t max = val.begin()->size();
        for (const auto &row: val) {
            max = std::max(max, row.size());
        }

        n = val.size();
        m = max;
        data = new double[n * m];

        double *p = data;
        for (const auto &row: val) {
            auto last = std::copy(row.begin(), row.end(), p);
            std::fill(last, p + m, 0.0);
            p += m;
        }
    }

    Matrix(const Matrix &matrix) : n(matrix.n), m(matrix.m), data(new double[n * m]) {
        cout << "Copy constructor\n";
        std::copy_n(matrix.data, n * m, data);
    }

    Matrix(Matrix &&matrix) noexcept: n(matrix.n), m(matrix.m), data(std::move(matrix.data)) {
        cout << "Move constructor\n";
    }

    Matrix &operator=(const Matrix &matrix) {
        cout << "Copy assign operator\n";
        if (this == &matrix)
            return *this;
        n = matrix.n;
        m = matrix.m;
        delete[] data;
        data = new double[n * m];
        std::copy_n(matrix.data, n * m, data);
        return *this;
    }

    Matrix &operator=(Matrix &&matrix) noexcept {
        cout << "Move assign operator\n";
        n = matrix.n;
        m = matrix.m;
        std::swap(data, matrix.data);
        return *this;
    }

    ~Matrix() {
        cout << "Destructor\n";
        delete[] data;
    }

    double operator()(unsigned row, unsigned col) const {
        return data[(row - 1) * m + (col - 1)];
    }

    double &operator()(unsigned row, unsigned col) {
        return data[(row - 1) * m + (col - 1)];
    }

    friend ostream &operator<<(ostream &out, const Matrix &matrix) {
        double *p = matrix.data;
        out << "[\n";
        for (unsigned int i = 0; i < matrix.n; i++) {
            for (unsigned int j = 0; j < matrix.m; j++) {
                out << std::setw(4) << *p++ << " ";
            }
            out << std::endl;
        }
        out << "]\n";
        return out;
    }

    Matrix operator-() {
        Matrix temp(n, m);
        for (unsigned int i = 0; i < n; i++) {
            for (unsigned int j = 0; j < m; j++) {
                temp(i + 1, j + 1) = -data[i * m + j];
            }
        }
        return temp;
    }
};