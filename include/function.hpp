#include <type_traits>
#include "type_list.hpp"

namespace X::Delta
{
	template<typename T> struct FuncTraits;

	template<typename T> using FuncTraits_Class = typename FuncTraits<T>::Class;
	template<typename T> using FuncTraits_ArgList = typename FuncTraits<T>::ArgList;
	template<typename T> using FuncTraits_Return = typename FuncTraits<T>::Return;
	template<typename T> using FuncTraits_Signature = typename FuncTraits<T>::Signature;
	template<typename T> using FuncTraits_Function = typename FuncTraits<T>::Function;


}

#include "function.inl"