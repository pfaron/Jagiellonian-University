#include <iostream>
#include <vector>
#include <functional>

template<typename... Ts>
auto average(Ts ... args) {
    return (args + ... + 0.0) / (sizeof...(args));
}

template<typename F, typename... Ts>
auto computeSum(F f, Ts ... args) -> typename decltype(std::function{f})::result_type {
    return (f(args) + ...);
}

template<typename V, typename... Ts>
void insert(V &container, Ts ... args) {
    (container.push_back(args), ...);
}