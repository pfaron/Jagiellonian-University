#include <iostream>
#include <type_traits>
#include <vector>
#include "has_size.h"
#include "has_value_type.h"

int main() {
    std::cout << std::boolalpha;
    std::cout << has_size<int>::value << std::endl; // false
    std::cout << has_size<std::vector<int> >::value << std::endl; //true
    std::cout << has_value_type<int>::value << std::endl; // false
    std::cout << has_value_type<std::vector<int> >::value << std::endl; //true
    return 0;
}
