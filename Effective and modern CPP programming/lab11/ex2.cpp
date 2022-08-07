#include <iostream>
#include <vector>
#include "has_size.h"

namespace v1 {
    template<typename T>
    std::enable_if_t<has_size_v<T>, size_t>
    get_size(T t) {
        return t.size() * sizeof(typename T::value_type);
    }

    template<typename T>
    std::enable_if_t<!has_size_v<T>, size_t>
    get_size(T t) {
        return sizeof(t);
    }
}

namespace v2 {
    template<typename T>
    size_t get_size(T t) {
        if constexpr(has_size_v<T>) {
            return t.size() * sizeof(typename T::value_type);
        } else {
            return sizeof(t);
        }
    }
}

int main() {
    std::vector<int> v{1, 2, 3, 4, 5};
    std::cout << v1::get_size(5) << std::endl; // 4
    std::cout << v1::get_size(v) << std::endl; // 20
    std::cout << v2::get_size(5) << std::endl; // 4
    std::cout << v2::get_size(v) << std::endl; // 20
    return 0;
}
