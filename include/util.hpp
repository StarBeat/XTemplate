/*
#Copyright 2021 xyang.
*/

#pragma once

#include <type_traits>
namespace x
{
namespace delta
{
namespace util
{
template<typename Instance, template<typename...> class T>
struct is_instance_of : std::false_type {};
template<typename... Args, template<typename...> class T>
struct is_instance_of<T<Args...>, T> : std::true_type {};
template<typename Instance, template<typename...> class T>
constexpr bool is_instance_of_v = is_instance_of<Instance, T>::value;

template<typename Void, typename T, typename... Args>
struct is_list_initializable : std::false_type {};
template<typename T, typename... Args>
struct is_list_initializable < std::void_t<decltype(T{ std::declval<Args>()... }) > , T, Args... > : std::true_type {};

template<typename Void, typename T>
struct is_function_pointer : std::false_type {};
template<typename T>
struct is_function_pointer<std::enable_if_t<std::is_pointer_v<T>&& std::is_function_v<std::remove_pointer_t<T>>>, T> : std::true_type {};

template<typename T>
concept HasDefauleConstructorClass = requires(T * t)
{
    t = new T();
};

template<HasDefauleConstructorClass T>
struct Single
{
    static inline T instance = T();
};
}  // namespace util
}  // namespace delta
}  // namespace x
