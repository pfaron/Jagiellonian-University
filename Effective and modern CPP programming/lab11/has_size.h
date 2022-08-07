#include <type_traits>

template<typename... Ts>
using void_t = void;

template<typename T, typename = void>
struct has_size : std::false_type {
};

template<typename T>
struct has_size<T, void_t<decltype(std::declval<T>().size())>> : std::true_type {
};

template<typename T>
inline constexpr bool has_size_v = has_size<T>::value;