#include <iostream>
#include <typeinfo>
#include <boost/type_index.hpp>

template<typename... Ts>
void showTypes(Ts &&... args) {
    using boost::typeindex::type_id_with_cvr;
    ((std::cout << type_id_with_cvr<Ts>().pretty_name() << " [" << typeid(Ts).name() << "] = " << args << '\n'), ...);
}

template<typename F>
class Proxy {
private:
    F func;
public:
    explicit Proxy(F &&f) : func(std::forward<F>(f)) {}

    template<typename ... Ts>
    auto operator()(Ts &&... args) const {
        std::cout << "\nProxy\n";
        showTypes(std::forward<Ts>(args)...);
        return func(std::forward<Ts>(args)...);
    }

};

template<typename F>
explicit Proxy(F &&f) -> Proxy<F>;

template<typename F>
Proxy<F> make_proxy(F &&f) {
    return Proxy<F>(std::forward<F>(f));
}