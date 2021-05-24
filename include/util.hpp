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
enum class ReferenceMode
{
    EnumNone,
    EnumLeft,
    EnumRight
};
enum class CVRefMode : std::uint8_t
{
    EnumNone = 0b0000,
    EnumLeft = 0b0001,
    EnumRight = 0b0010,
    EnumConst = 0b0100,
    EnumConstLeft = 0b0101,
    EnumConstRight = 0b0110,
    EnumVolatile = 0b1000,
    EnumVolatileLeft = 0b1001,
    EnumVolatileRight = 0b1010,
    EnumCV = 0b1100,
    EnumCVLeft = 0b1101,
    EnumCVRight = 0b1110,
};

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
