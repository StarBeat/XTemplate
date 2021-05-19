
/*
#Copyright 2021 xyang.
*/

#pragma once

namespace x::delta::alpha
{
    template<typename List, typename T, std::size_t N = 0, bool found = false>
    struct Find;

    template<typename List, template<typename>class Op, std::size_t N = 0, bool found = false>
    struct FindIf;

    template<typename List, template <typename I, typename X> class Op, typename I, bool = IsEmpty_v<List>>
    struct Accumulate;

    template<typename List, bool haveSame = false>
    struct IsUnique;
}  // namespace x::delta::alpha
namespace x::delta
{
template<typename List>
struct IsUnique : alpha::IsUnique<List> {};

template<typename List, typename T>
struct Find : alpha::Find<List, T> { };

template<typename List, template<typename>class Op>
struct FindIf : alpha::FindIf<List, Op> { };

template<typename List, template <typename I, typename X> class Op, typename I>
struct Accumulate : alpha::Accumulate<List, Op, I> {};

template<template<typename T> class Op, typename... Ts>
struct Transform<TypeList<Ts...>, Op> : std::type_identity<TypeList<typename Op<Ts>::type...>> {};

template<typename List, template<typename>class Test>
struct Filter {
 private:
    template<typename I, typename X>
    struct PushFrontIf : std::conditional<Test<X>::value, PushFront_t<I, X>, I> {};
 public:
    using type = Accumulate_t<List, PushFrontIf, TypeList<>>;
};

template<template<typename X, typename Y>typename Less>
struct QuickSort<TypeList<>, Less> : std::type_identity<TypeList<>> {};
template<template<typename X, typename Y>typename Less, typename T>
struct QuickSort<TypeList<T>, Less> : std::type_identity<TypeList<T>> {};
template<template<typename X, typename Y>typename Less, typename Head, typename... Tail>
struct QuickSort<TypeList<Head, Tail...>, Less> {
 private:
    template<typename X>
    using LessThanHead = Less<X, Head>;
    template<typename X>
    using GEThanHead = std::integral_constant<bool, !Less<X, Head>::value>;
    using LessList = Filter_t<TypeList<Tail...>, LessThanHead>;
    using GEList = Filter_t<TypeList<Tail...>, GEThanHead>;
 public:
    using type = Concat_t<
        typename QuickSort<LessList, Less>::type,
        PushFront_t<typename QuickSort<GEList, Less>::type, Head>>;
};
}  // namespace x::delta
namespace x::delta::alpha
{
template<typename List>
struct IsUnique<List, true> : std::false_type {};
template<>
struct IsUnique<TypeList<>, false> : std::true_type {};
template<typename Head, typename... Tail>
struct IsUnique<TypeList<Head, Tail...>, false> : IsUnique<TypeList<Tail...>, Contain_v<TypeList<Tail...>, Head>> {};

template<typename T, std::size_t N, typename... Ts>
struct Find<TypeList<Ts...>, T, N, true> : std::integral_constant<std::size_t, N - 1> {};
template<typename T, std::size_t N>
struct Find<TypeList<>, T, N, false> : std::integral_constant<std::size_t, KFind_fail> {};
template<typename T, typename Head, std::size_t N, typename... Tail>
struct Find<TypeList<Head, Tail...>, T, N, false> : Find<TypeList<Tail...>, T, N + 1, std::is_same_v<T, Head>> {};

template<template<typename>class Op, std::size_t N, typename... Ts>
struct FindIf<TypeList<Ts...>, Op, N, true> : std::integral_constant<std::size_t, N - 1> {};
template<template<typename>class Op, std::size_t N>
struct FindIf<TypeList<>, Op, N, false> : std::integral_constant<std::size_t, KFind_fail> {};
template<template<typename>class Op, typename Head, std::size_t N, typename... Tail>
struct FindIf<TypeList<Head, Tail...>, Op, N, false> : FindIf<TypeList<Tail...>, Op, N + 1, Op<Head>::value> {};

template<typename List, template <typename I, typename X> class Op, typename I>
struct Accumulate<List, Op, I, false> : Accumulate<PopFront_t<List>, Op, typename Op<I, Front_t<List>>::type> { };
template<typename List, template <typename X, typename Y> class Op, typename I>
struct Accumulate<List, Op, I, true>
{
    using type = I;
};
}  // namespace x::delta::alpha
