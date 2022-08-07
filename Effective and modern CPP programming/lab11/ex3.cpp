#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <forward_list>
#include <deque>

template<typename C>
double get_median(C cont, std::forward_iterator_tag) {
    std::cout << "Getting median - forward_iterator_tag" << std::endl;

    cont.sort();
    const auto size = std::distance(cont.begin(), cont.end());
    auto iter = cont.begin();

    if (size % 2 == 0) {
        std::advance(iter, size / 2 - 1);
        auto first_val = *iter;
        auto second_val = *(++iter);
        return (first_val + second_val) / 2.;

    } else {
        std::advance(iter, size / 2);
        return *iter;
    }
}

template<typename C>
double get_median(C cont, std::bidirectional_iterator_tag) {
    std::cout << "Getting median - bidirectional_iterator_tag" << std::endl;

    cont.sort();
    const auto size = cont.size();
    auto iter = cont.begin();

    if (size % 2 == 0) {
        std::advance(iter, size / 2 - 1);
        auto first_val = *iter;
        auto second_val = *(++iter);
        return (first_val + second_val) / 2.;

    } else {
        std::advance(iter, size / 2);
        return *iter;
    }
}

template<typename C>
double get_median(C cont, std::random_access_iterator_tag) {
    std::cout << "Getting median - random_access_iterator_tag" << std::endl;

    std::sort(cont.begin(), cont.end());
    const auto size = cont.size();
    if (size % 2 == 0) {
        return (cont[size / 2 - 1] + cont[size / 2]) / 2.;
    } else {
        return cont[size / 2];
    }
}

template<typename C>
double median(C c) {
    return get_median(c, typename std::iterator_traits<typename C::iterator>::iterator_category());
}

int main() {
    std::list<int> a{3, 2, 5, 1, 4};
    std::cout << median(a) << std::endl; // 3
    std::vector<int> v{3, 1, 4, 2};
    std::cout << "first element: " << v[0] << std::endl; // 3
    std::cout << median(v) << std::endl; // 2.5
    std::cout << "first element: " << v[0] << std::endl; // 3
    std::forward_list<int> f{3, 1, 4, 2, 7};
    std::cout << median(f) << std::endl; // 3
    std::deque<int> d{5, 1, 6, 2};
    std::cout << median(d) << std::endl; // 3.5
    return 0;
}
