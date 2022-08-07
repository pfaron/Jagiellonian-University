#include <iostream>
#include <vector>
#include <boost/type_index.hpp>

template<typename ... Ts>
class MultiVector {
public:
    void push_back() {}

    virtual void print(size_t n) const { std::cout << std::endl; }
};

template<typename T, typename... Ts>
class MultiVector<T, Ts...> : public MultiVector<Ts...> {
    std::vector<T> data;
public:
    using Base = MultiVector<Ts...>;
    using Base::push_back;

    MultiVector() : Base() {}

    void push_back(T t) {
        data.push_back(std::forward<T>(t));
    }

    void print(size_t n = 1) const {
        std::cout << n << ". [ {" << boost::typeindex::type_id_with_cvr<T>().pretty_name() << "} ";
        for (const auto &x: data) {
            std::cout << x << " ";
        }
        std::cout << "] ";
        Base::print(n + 1);
    }
};