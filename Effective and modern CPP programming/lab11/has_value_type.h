#include <type_traits>

template<typename... Ts>
using void_t = void;

template<typename T, typename = void>
struct has_value_type : std::false_type {
};

template<typename T>
struct has_value_type<T, void_t<typename T::value_type>> : std::true_type {
};

template<typename T>
inline constexpr bool has_value_type_v = has_value_type<T>::value;