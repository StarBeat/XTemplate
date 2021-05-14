#include <type_traits>
#include "type_list.hpp"

namespace X
{
    namespace Delta
    {
        template<typename Sig>
        struct FuncTraitsBase;
        template<typename Ret, typename... Args>
        struct FuncTraitsBase<Ret(Args ...)>{
            using ArgList = TypeList<Args...>;
            using Return = Ret;
            using Signature = Ret(Args...);
        };

 /*       template<bool is_function,typename T>
        struct FuncTraits: FuncTraitsBase;
        template<typename T>
        struct FuncTraits<false, T> : FuncTraits<decltype(&std::decay_t<T>::operator())> {};
        template<typename T>
        struct FuncTraits<true, T> : FuncTraits<T> 
        {
            using Function = T;
        };*/


    }
}