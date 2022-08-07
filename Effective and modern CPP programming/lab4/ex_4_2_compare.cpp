#include <iostream>
#include <cstring>

using namespace std;

struct Rational {
    int nominator = 0, denominator = 1;

    friend bool operator<(const Rational &a, const Rational &b) {
        return a.nominator * b.denominator < b.nominator * a.denominator;
    }
};

template<typename T>
int compare(T a, T b) {
    return a < b ? 1 : (b < a) ? -1 : 0;
}

template<typename T>
int compare(const T *a, const T *b) {
    return (*a) < (*b) ? 1 : ((*b) < (*a)) ? -1 : 0;
}

template<>
int compare(const char *a, const char *b) {
    auto temp = strcmp(a, b);
    return temp < 0 ? 1 : (temp > 0) ? -1 : 0;
}


int main() {
    int a = 1, b = -6;
    float y = 1.0 + 1e20 - 1e20, x = 1.0;
    Rational p{2}, q{1, 4}, r{8, 4};
    cout << "values\n";
    cout << compare(a, b) << " " << compare(b, a) << " " << compare(a, a) << endl;
    cout << compare(x, y) << " " << compare(y, x) << " " << compare(x, x) << endl;
    cout << compare(p, q) << " " << compare(q, p) << " " << compare(p, r) << endl;
    cout << "pointers\n";
    cout << compare(&a, &b) << " " << compare(&b, &a) << " " << compare(&a, &a) << endl;
    cout << compare(&x, &y) << " " << compare(&y, &x) << " " << compare(&x, &x) << endl;
    cout << compare(&p, &q) << " " << compare(&q, &p) << " " << compare(&p, &r) << endl;

    const char *s = "Alpha", *t = "Alfa", *t2 = "Alfa";
    cout << "C-strings\n";
    cout << compare(s, t) << " " << compare(t, s) << " " << compare(t, t)
         << " " << compare(t, t2) << " " << compare(t, "Beta") << endl;

    return 0;
}
