/*
#Copyright 2021 xyang.
*/

#pragma once
#include <type_traits>
#include "type_list.hpp"

namespace x::delta
{
    template<typename T>
    struct FuncTraits;

    template<typename T>
    using FuncTraits_Class = typename FuncTraits<T>::Class;
    template<typename T>
    using FuncTraits_ArgList = typename FuncTraits<T>::ArgList;
    template<typename T>
    using FuncTraits_Return = typename FuncTraits<T>::Return;
    template<typename T>
    using FuncTraits_Signature = typename FuncTraits<T>::Signature;
    template<typename T>
    using FuncTraits_Function = typename FuncTraits<T>::Function;

    template<typename Obj, typename Func>
    struct MemFuncOf;
    template<typename Func>
    struct FuncOf;

}  // namespace x::delta

#include "function.inl"
