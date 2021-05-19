/*
#Copyright 2021 xyang.
*/


#include <iostream>
#include "function.hpp"

using namespace std;  // NOLINT
using namespace x::delta; // NOLINT

struct MyStruct
{
    void Fun1(int i) {}
    static void Fun2() {}
    void Fun3(int i, char* a, char b) {}
    int operator()()
    {
        return 0;
    }
};
int main()
{
    using list = TypeList<int, float, bool>;

    static_assert(IsTypeList_v<list>);
    static_assert(!IsTypeList_v<float>);

    static_assert(Length_v<list> == 3);

    static_assert(!IsEmpty_v<list>);
    static_assert(IsEmpty_v<TypeList<>>);

    static_assert(is_same_v<Front_t<list>, int>);
    static_assert(is_same_v<At_t<list, 1>, float>);
    static_assert(is_same_v<Select_t<list, 0, 2>, TypeList<int, bool>>);

    static_assert(Find_v<list, float> == 1);
    static_assert(Find_v<list, char> == KFind_fail);

    static_assert(Contain_v<list, int>);
    static_assert(!Contain_v<list, int64_t>);

    static_assert(ContainTs_v<list, int, float>);
    static_assert(!ContainTs_v<list, int, int64_t>);

    static_assert(ContainList_v<list, TypeList<>>);
    static_assert(ContainList_v<list, TypeList<int, float>>);
    static_assert(!ContainList_v<list, TypeList<char, int>>);

    static_assert(is_same_v<PushFront_t<list, double>, TypeList<double, int, float, bool>>);
    static_assert(is_same_v<PushBack_t<list, double>, TypeList<int, float, bool, double>>);
    static_assert(is_same_v<PopFront_t<list>, TypeList<float, bool>>);
    static_assert(is_same_v<Reverse_t<list>, TypeList<bool, float, int>>);
    static_assert(is_same_v<Filter_t<list, is_floating_point>, TypeList<float>>);
    static_assert(is_same_v<Concat_t<list, TypeList<char, double>>, TypeList<int, float, bool, char, double>>);
    static_assert(is_same_v<Transform_t<list, add_const>, TypeList<const int, const float, const bool>>);

    static_assert(IsUnique_v<list>);
    static_assert(!IsUnique_v<PushFront_t<list, float>>);
    MyStruct s;
    static_assert(is_same_v<void, FuncTraits_Return<decltype(MyStruct::Fun2)>>);
    static_assert(is_same_v<void, FuncTraits_Return<decltype(&MyStruct::Fun2)>>);
    static_assert(is_same_v<TypeList<int>, FuncTraits_ArgList<decltype(&MyStruct::Fun1)>>);
    static_assert(is_same_v<TypeList<int, char*, char>, FuncTraits_ArgList<decltype(&MyStruct::Fun3)>>);
    static_assert(is_same_v<MyStruct, FuncTraits_Class<decltype(&MyStruct::operator())>>);
    static_assert(std::is_member_function_pointer_v<decltype(&MyStruct::operator())>);
    static_assert(std::is_member_pointer_v<int64_t(MyStruct::*)>);
    static_assert(is_same_v < MyStruct, decltype(s) >);
    static_assert(std::is_same_v<void(int), FuncTraits_Signature<decltype(&MyStruct::Fun1)>>);
    return 0;
}
