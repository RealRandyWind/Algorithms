#pragma once

#include <stdlib.h>
#include <Types>

template<typename Type>
inline Type Max(
		const Type &Lhs,
		const Type &Rhs
	)
{
	return (Lhs < Rhs ? Rhs : Lhs);
}

template<typename Type>
inline Type Min(
		const Type &Lhs,
		const Type &Rhs
	)
{
	return (Lhs < Rhs ? Lhs : Rhs);
}

template<typename Type>
inline Type Swap(
		Type &Lhs,
		Type &Rhs
	)
{
	Type Tmp;

	Tmp = Lhs;
	Lhs = Rhs;
	Rhs = Tmp;
	return Lhs;
}

inline FVoid * _Make(
		FSize Bytes
	)
{
	FVoid *Rhs;

	Rhs = (FVoid *) malloc(Bytes);
	if(!Rhs)
	{
		exit(Failure);
	}
	return Rhs;
}

template<typename Type>
inline Type * Make(
		FSize Size = 1
	)
{
	return (Type *) _Make(Size * sizeof(Type));
}

inline FVoid * _Resize(
		FVoid *Rhs,
		FSize Bytes
	)
{
	Rhs = realloc(Rhs, Bytes);
	if(!Rhs)
	{
		exit(Failure);
	}
	return Rhs;
}

template<typename Type>
inline Type * Resize(
		Type *Rhs,
		FSize Size
	)
{
	return (Type *) _Resize(Rhs, Size * sizeof(Type));
}

inline FVoid * _Remove(
		FVoid *Data
	)
{
	free(Data);
	return NullPtr;
}

template<typename Type>
inline Type * Remove(
		Type *Data
	)
{
	return (Type *) _Remove(Data);
}

inline FVoid * _Copy(
		FVoid *Lhs,
		const FVoid *Rhs,
		FSize Bytes
	)
{
	FRaw *PtrLhs, *PtrRhs;
	FSize Index, End;

	if (!Rhs)
	{
		exit(Failure);
	}

	if (!Lhs)
	{
		Lhs = _Make(Bytes);
	}
	
	PtrLhs = (FRaw *) Lhs;
	PtrRhs = (FRaw *) Rhs;
	End = Bytes;
	for (Index = 0; Index < End; ++Index)
	{
		PtrLhs[Index] = PtrRhs[Index];
	}
	return Lhs;
}

template<typename Type>
inline Type * Copy(
		Type *Lhs,
		const Type *Rhs,
		FSize Size = 1
	)
{
	return (Type *) _Copy(Lhs, Rhs, Size * sizeof(Type));
}

inline FVoid * _Move(
		FVoid *Lhs,
		FVoid *Rhs,
		FSize Bytes
	)
{
	FRaw *PtrLhs, *PtrRhs;
	FSize Index, End;

	if (!Rhs)
	{
		exit(Failure);
	}

	if (!Lhs)
	{
		Lhs = _Make(Bytes);
	}

	PtrLhs = (FRaw *) Lhs;
	PtrRhs = (FRaw *) Rhs;
	End = Bytes;
	for (Index = 0; Index < End; ++Index)
	{
		PtrLhs[Index] = PtrRhs[Index];
		PtrRhs[Index] = 0;
	}
	return Lhs;
}

template<typename Type>
inline Type * Move(
		Type *Lhs,
		Type *Rhs,
		FSize Size = 1
	)
{
	return (Type *) _Move(Lhs, Rhs, Size * sizeof(Type));
}