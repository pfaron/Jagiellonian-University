#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

class Printer {
    std::ostream &out;
    std::string prefix;
    std::string postfix;

public:
    Printer(std::ostream &o, std::string pre, std::string post) : out(o), prefix(std::move(pre)),
                                                                  postfix(std::move(post)) {}

    template<typename T>
    void operator()(T t) const {
        out << prefix << t << postfix;
    };
};

int main() {
    /// Creates unary functor that takes one argument x (of any type)
    /// and outputs to given stream x surrounded by given prefix na postfix
    /// e.g. in the following  [ x ]
    /// Hint: define function template.
    Printer printer(std::cout, "[ ", " ] ");
    printer("hello");    // [ hello ]
    std::cout << "\nv = ";
    std::vector<int> v = {1, 2, 3, 4};
    std::for_each(v.begin(), v.end(), printer);  // v = [ 1 ] [ 2 ] [ 3 ] [ 4 ]

    std::ofstream file("myFile.txt");
    Printer filePrinter(file, "- ", "\n");
    filePrinter(5);
    filePrinter("My text");
    return 0;
}
/** myFile.txt
- 5
- My text
*/
