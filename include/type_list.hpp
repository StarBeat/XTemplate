#include "util.hpp"

namespace X
{
    namespace Delta
    {
        using namespace Util;
        template<typename... Ts>
        struct TypeList {};
#pragma region const value
        constexpr std::size_t Find_fail = static_cast<std::size_t>(-1);

#pragma endregion
#pragma region property
        template<typename List>
        struct Length;
        template<typename... Ts>
        struct Length<TypeList<Ts...>> : std::integral_constant<std::size_t, sizeof...(Ts)> {};
        template<typename List>
        constexpr std::size_t Length_v = Length<List>::value;

        template<typename List>
        struct IsEmpty : std::integral_constant<bool, Length_v<List> == 0> {};
        template<typename List>
        constexpr bool IsEmpty_v = IsEmpty<List>::value;

        template<typename List>
        struct IsUnique;
        template<typename List>
        constexpr bool IsUnique_v = IsUnique<List>::value;

        template<typename List>
        struct IsTypeList : is_instance_of<List, TypeList> {};
        template<typename List>
        constexpr bool IsTypeList_v = IsTypeList<List>::value;
#pragma endregion



#pragma region method
        template<typename List, typename T>
        struct Find;
        template<typename List, typename T> 
        constexpr std::size_t Find_v = Find<List, T>::value;

        template<typename List, template<typename>class Op>
        struct FindIf;
        template<typename List, template<typename>class Op> 
        constexpr std::size_t FindIf_v = FindIf<List, Op>::value;

        template<typename List, typename T>
        struct Contain : std::integral_constant<bool, Find_v<List, T> != Find_fail> {};
        template<typename List, typename T> 
        constexpr bool Contain_v = Contain<List, T>::value;

        template<typename List, typename... Ts>
        struct ContainTs : std::integral_constant<bool, (Contain_v<List, Ts> &&...)> {};
        template<typename List, typename... Ts> 
        constexpr bool ContainTs_v = ContainTs<List, Ts...>::value;

        template<typename List0, typename List1> 
        struct ContainList;
        template<typename List, typename... Ts>
        struct ContainList<List, TypeList<Ts...>> : std::integral_constant<bool, (Contain_v<List, Ts> &&...)> {};
        template<typename List0, typename List1> 
        constexpr bool ContainList_v = ContainList<List0, List1>::value;

        template<typename List>
        struct Front;
        template<typename Head, typename... Tail>
        struct Front<TypeList<Head, Tail...>> : std::type_identity<Head> {};
        template<typename List>
        using Front_t = typename Front<List>::type;

        template<typename List> 
        struct PopFront;
        template<typename Head, typename... Tail>
        struct PopFront<TypeList<Head, Tail...>> : std::type_identity<TypeList<Tail...>> {};
        template<typename List> 
        using PopFront_t = typename PopFront<List>::type;

        template<typename List, typename T> 
        struct PushFront;
        template<typename T, typename... Ts>
        struct PushFront<TypeList<Ts...>, T> : std::type_identity<TypeList<T, Ts...>> {};
        template<typename List, typename T> 
        using PushFront_t = typename PushFront<List, T>::type;

        template<typename List, typename T> 
        struct PushBack;
        template<typename T, typename... Ts>
        struct PushBack<TypeList<Ts...>, T> : std::type_identity<TypeList<Ts..., T>> {};
        template<typename List, typename T> 
        using PushBack_t = typename PushBack<List, T>::type;

        template<typename List, std::size_t N>
        struct At;
        template<typename List>
        struct At<List, 0> : std::type_identity<Front_t<List>> {};
        template<typename List, std::size_t N>
        struct At : At<PopFront_t<List>, N - 1> {};
        template<typename List, std::size_t N>
        using At_t = typename At<List, N>::type;

        template<typename List, std::size_t... indices>
        struct Select : std::type_identity<TypeList<At_t<List, indices>...>> {};
        template<typename List, std::size_t... indices>
        using Select_t = typename Select<List, indices...>::type;

        template<typename List, template <typename I, typename X> class Op, typename I>
        struct Accumulate;
        template<typename List, template <typename I, typename X> class Op, typename I>
        using Accumulate_t = typename Accumulate<List, Op, I>::type;

        template<typename List>
        struct Reverse : Accumulate<List, PushFront, TypeList<>> {};
        template<typename List> 
        using Reverse_t = typename Reverse<List>::type;


        template<typename List0, typename List1>
        struct Concat;
        template<typename List0, typename List1>
        struct Concat : Accumulate<List1, PushBack, List0> {};
        template<typename List0, typename List1>
        using Concat_t = typename Concat<List0, List1>::type;

        template<typename List, template<typename>class Op> 
        struct Filter;
        template<typename List, template<typename>class Op>
        using Filter_t = typename Filter<List, Op>::type;

        template<typename List, template<typename> class Op> 
        struct Transform;
        template<typename List, template<typename> class Op> 
        using Transform_t = typename Transform<List, Op>::type;

        template<typename List, template<typename X, typename Y>typename Less>
        struct QuickSort;
        template<typename List, template<typename X, typename Y>typename Less>
        using QuickSort_t = typename QuickSort<List, Less>::type;

#pragma endregion
    }
}

#include "type_list.inl"