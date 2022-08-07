#include <iostream>
#include <algorithm>
#include <iomanip>
#include <utility>
#include "Matrix.h"

using namespace std;

class MatrixWithLabel : Matrix {
protected:
    string label = "A";
public:
    using Matrix::Matrix;

    MatrixWithLabel(string label, unsigned n, unsigned m) : Matrix(n, m), label(std::move(label)) {
        cout << "Label dimensions constructor\n";
    }

    MatrixWithLabel(string label, const std::initializer_list<std::initializer_list<double>> &val)
            : Matrix(val), label(std::move(label)) {
        cout << "Label initializer list constructor\n";
    }

    void setLabel(string newLabel) {
        label = std::move(newLabel);
    }

    string getLabel() {
        return label;
    }
};