#include <iostream>
#include <iomanip>
#include "dynamicVector.h"

using namespace std;

template<int N>
using SVector = Vector<double, N>;
using DVector = Vector<double, 0>;

int main() {
    cout << fixed << setprecision(2);

    DVector m1 = {1, 2, 3};    // dynamic from initialization_list
    cout << m1 << endl;

    SVector<3> m2 = {1, -1, 0};  // static
    cout << m2 << endl;

    auto m3 = (SVector<2>) (m1);  // conversion from dynamic to static
    cout << m3 << endl;

    auto m3_2 = (SVector<4>) (m1);  // conversion from dynamic to static
    cout << m3_2 << endl;

    auto m4 = m1 + m2 + m1;
    cout << m4 << endl;

    auto m5 = static_cast<DVector>(m4);
    cout << m5 << endl;

    return 0;
}

/** expected result

1.00 2.00 3.00
1.00 -1.00 0.00
1.00 2.00
1.00 2.00 3.00 0.00
3.00 3.00 6.00
3.00 3.00 6.00
 */