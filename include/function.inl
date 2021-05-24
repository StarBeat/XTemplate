/*
#Copyright 2021 xyang.
*/

#pragma once

namespace x::delta::alpha
{
template<bool is_const, bool is_volatile, ReferenceMode ref_mode, bool is_noexcept, typename Sig>
struct FuncTraitsBase;
template<bool is_const, bool is_volatile, ReferenceMode ref_mode, bool is_noexcept, typename Ret, typename... Args>
struct FuncTraitsBase<is_const, is_volatile, ref_mode, is_noexcept, Ret(Args ...)>
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
struct FuncTraits<Ret(Args...)> : alpha::FuncTraitsBase<false, false, ReferenceMode::EnumNone, false, Ret(Args...)> {};

template<typename Ret, typename... Args>
struct FuncTraits<Ret(Args...)const> : alpha::FuncTraitsBase<true, false, ReferenceMode::EnumNone, false, Ret(Args...)> {};

template<typename Ret, typename... Args>
struct FuncTraits<Ret(Args...)volatile> : alpha::FuncTraitsBase<false, true, ReferenceMode::EnumNone, false, Ret(Args...)> {};

template<typename Ret, typename... Args>
struct FuncTraits<Ret(Args...)const volatile> : alpha::FuncTraitsBase<true, true, ReferenceMode::EnumNone, false, Ret(Args...)> {};

template<typename Ret, typename... Args>
struct FuncTraits<Ret(Args...)&> : alpha::FuncTraitsBase<false, false, ReferenceMode::EnumLeft, false, Ret(Args...)> {};

template<typename Ret, typename... Args>
struct FuncTraits<Ret(Args...)const&> : alpha::FuncTraitsBase<true, false, ReferenceMode::EnumLeft, false, Ret(Args...)> {};

template<typename Ret, typename... Args>
struct FuncTraits<Ret(Args...)volatile&> : alpha::FuncTraitsBase<false, true, ReferenceMode::EnumLeft, false, Ret(Args...)> {};

template<typename Ret, typename... Args>
struct FuncTraits<Ret(Args...)const volatile&> : alpha::FuncTraitsBase<true, true, ReferenceMode::EnumLeft, false, Ret(Args...)> {};

template<typename Ret, typename... Args>
struct FuncTraits<Ret(Args...)&&> : alpha::FuncTraitsBase<false, false, ReferenceMode::EnumRight, false, Ret(Args...)> {};

template<typename Ret, typename... Args>
struct FuncTraits<Ret(Args...)const&&> : alpha::FuncTraitsBase<true, false, ReferenceMode::EnumRight, false, Ret(Args...)> {};

template<typename Ret, typename... Args>
struct FuncTraits<Ret(Args...)volatile&&> : alpha::FuncTraitsBase<false, true, ReferenceMode::EnumRight, false, Ret(Args...)> {};

template<typename Ret, typename... Args>
struct FuncTraits<Ret(Args...)const volatile&&> : alpha::FuncTraitsBase<true, true, ReferenceMode::EnumRight, false, Ret(Args...)> {};

template<typename Ret, typename... Args>
struct FuncTraits<Ret(Args...)noexcept> : alpha::FuncTraitsBase<false, false, ReferenceMode::EnumNone, true, Ret(Args...)> {};

template<typename Ret, typename... Args>
struct FuncTraits<Ret(Args...)const noexcept> : alpha::FuncTraitsBase<true, false, ReferenceMode::EnumNone, true, Ret(Args...)> {};

template<typename Ret, typename... Args>
struct FuncTraits<Ret(Args...)volatile noexcept> : alpha::FuncTraitsBase<false, true, ReferenceMode::EnumNone, true, Ret(Args...)> {};

template<typename Ret, typename... Args>
struct FuncTraits<Ret(Args...)const volatile noexcept> : alpha::FuncTraitsBase<true, true, ReferenceMode::EnumNone, true, Ret(Args...)> {};

template<typename Ret, typename... Args>
struct FuncTraits<Ret(Args...)& noexcept> : alpha::FuncTraitsBase<false, false, ReferenceMode::EnumLeft, true, Ret(Args...)> {};

template<typename Ret, typename... Args>
struct FuncTraits<Ret(Args...)const & noexcept> : alpha::FuncTraitsBase<true, false, ReferenceMode::EnumLeft, true, Ret(Args...)> {};

template<typename Ret, typename... Args>
struct FuncTraits<Ret(Args...)volatile& noexcept> : alpha::FuncTraitsBase<false, true, ReferenceMode::EnumLeft, true, Ret(Args...)> {};

template<typename Ret, typename... Args>
struct FuncTraits<Ret(Args...)const volatile & noexcept> : alpha::FuncTraitsBase<true, true, ReferenceMode::EnumLeft, true, Ret(Args...)> {};

template<typename Ret, typename... Args>
struct FuncTraits<Ret(Args...) && noexcept> : alpha::FuncTraitsBase<false, false, ReferenceMode::EnumRight, true, Ret(Args...)> {};

template<typename Ret, typename... Args>
struct FuncTraits<Ret(Args...)const&& noexcept> : alpha::FuncTraitsBase<true, false, ReferenceMode::EnumRight, true, Ret(Args...)> {};

template<typename Ret, typename... Args>
struct FuncTraits<Ret(Args...)volatile&& noexcept> : alpha::FuncTraitsBase<false, true, ReferenceMode::EnumRight, true, Ret(Args...)> {};

template<typename Ret, typename... Args>
struct FuncTraits<Ret(Args...)const volatile&& noexcept> : alpha::FuncTraitsBase<true, true, ReferenceMode::EnumRight, true, Ret(Args...)> {};

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

template<class Obj, typename Func>
struct MemFuncOf
{
    static_assert(std::is_function_v<Func>);
    static constexpr auto get(Func Obj::* func)
    {
        return func;
    }
};

template<typename Func>
struct FuncOf
{
    static_assert(std::is_function_v<Func>);
    static constexpr auto get(Func* func)
    {
        return func;
    }
};
}  // namespace x::delta
namespace x::delta::alpha
{

}  // namespace x::delta::alpha
