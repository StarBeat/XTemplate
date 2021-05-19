/*
#Copyright 2021 xyang.
*/

#pragma once

namespace x::delta::alpha
{
template<typename Sig>
struct FuncTraitsBase;
template<typename Ret, typename... Args>
struct FuncTraitsBase<Ret(Args ...)>
{
    using ArgList = TypeList<Args...>;
    using Return = Ret;
    using Signature = Ret(Args...);
};
template<bool is_function, typename T> struct FuncTraitsDispatch;
template<typename T> struct FuncTraitsDispatch<false, T> : FuncTraits<decltype(&std::decay_t<T>::operator())> {};
template<typename T> struct FuncTraitsDispatch<true, T> : FuncTraits<T>
{
    using Function = T;
};
}  // namespace x::delta::alpha
namespace x::delta
{

template<typename Ret, typename... Args>
struct FuncTraits<Ret(Args...)> : alpha::FuncTraitsBase<Ret(Args...)> {};
template<typename Func>
struct FuncTraits<Func*> : FuncTraits<Func>
{
    using Class = void;
    using Function = Func;
};
template<typename T, typename Func>
struct FuncTraits<Func T::*> : FuncTraits<Func>
{
    using Class = T;
    using Function = Func;
};
template<typename T>
struct FuncTraits : alpha::FuncTraitsDispatch<std::is_function_v<T>, T> {};

}  // namespace x::delta
namespace x::delta::alpha
{

}  // namespace x::delta::alpha
