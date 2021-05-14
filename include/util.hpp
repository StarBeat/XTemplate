#include <type_traits>
namespace X
{
    namespace Delta
    {
        namespace Util
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
        }
    }
}