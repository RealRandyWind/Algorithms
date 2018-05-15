#pragma once

#include <stdlib.h>
#include <Types>

template<typename Type>
inline Type Max(const Type &Lhs, const Type &Rhs)
{
	return (Lhs < Rhs ? Rhs : Lhs);
};

template<typename Type>
inline Type Min(const Type &Lhs, const Type &Rhs)
{
	return (Lhs < Rhs ? Lhs : Rhs);
};

template<typename Type>
inline Type Swap(Type &Lhs, Type &Rhs)
{
	Type Tmp;

	Tmp = Lhs;
	Lhs = Rhs;
	Rhs = Tmp;
	return Lhs;
};

template<typename Type>
inline Type * Make(FSize Size)
{
	Type *Rhs;

	Rhs = (Type *) malloc(Size * sizeof(Type));
	if(!Rhs)
	{
		exit(EXIT_FAILURE);
	}
	return Rhs;
};

template<typename Type>
inline Type * Resize(Type *Rhs, FSize Size)
{
	Rhs = (Type *) realloc(Rhs, Size * sizeof(Type));
	if(!Rhs)
	{
		exit(EXIT_FAILURE);
	}
	return Rhs;
};

template<typename Type>
inline Type * Remove(Type *Data)
{
	free(Data);
	return NullPtr;
};
