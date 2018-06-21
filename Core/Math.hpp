#pragma once

#include <math>
#include <Point>
#include <Functions>

/* Functions */

template<FSize Size, typename Type>
Type Norm2(
		const TPoint<Size, Type> &Rhs
	)
{
	FSize Index;
	Type Result = Type();

	for (Index = 0; Index < Size; ++Index)
	{
		Result += Rhs.Data[Index] * Rhs.Data[Index];
	}

	return Result;
}

template<FSize Size, typename Type>
Type Norm(
		const TPoint<Size, Type> &Rhs

	)
{
	return sqrt(Norm2(Rhs));
}

template<FSize Size, typename Type>
TPoint<Size, Type> Min(
		const TPoint<Size, Type> &Lhs,
		const TPoint<Size, Type> &Rhs
	)
{
	FSize Index;
	TPoint<Size, Type> Result;

	for (Index = 0; Index < Size; ++Index)
	{
		Result[Index] = Min(Lhs[Index], Rhs[Index]);
	}
	return Result;
}

template<FSize Size, typename Type>
TPoint<Size, Type> Max(
		const TPoint<Size, Type> &Lhs,
		const TPoint<Size, Type> &Rhs
	)
{
	FSize Index;
	TPoint<Size, Type> Result;

	for (Index = 0; Index < Size; ++Index)
	{
		Result[Index] = Max(Lhs[Index], Rhs[Index]);
	}
	return Result;
}

/* Vector @ Vector */

template<FSize Size, typename Type>
TPoint<Size, Type> operator-(
		const TPoint<Size, Type> &Lhs,
		const TPoint<Size, Type> &Rhs
	)
{
	FSize Index;
	TPoint<Size, Type> Result;

	for (Index = 0; Index < Size; ++Index)
	{
		Result[Index] = Lhs[Index] - Rhs[Index];
	}
	return Result;
}

/* Vector @= Vector */

template<FSize Size, typename Type>
TPoint<Size, Type> &operator+=(
		TPoint<Size, Type> &Lhs,
		const TPoint<Size, Type> &Rhs
	)
{
	FSize Index;

	for (Index = 0; Index < Size; ++Index)
	{
		Lhs[Index] += Rhs[Index];
	}
	return Lhs;
}

/* Alpha @ Vector */

template<FSize Size, typename Type>
TPoint<Size, Type> operator*(
		const Type &Lhs,
		const TPoint<Size, Type> &Rhs
	)
{
	FSize Index;
	TPoint<Size, Type> Result;

	for (Index = 0; Index < Size; ++Index)
	{
		Result[Index] = Lhs * Rhs[Index];
	}
	return Result;
}

template<FSize Size, typename Type>
TPoint<Size, Type> operator-(
		const Type &Lhs,
		const TPoint<Size, Type> &Rhs
	)
{
	FSize Index;
	TPoint<Size, Type> Result;

	for (Index = 0; Index < Size; ++Index)
	{
		Result[Index] = Lhs - Rhs[Index];
	}
	return Result;
}

/* Vector @ Alpha */

template<FSize Size, typename Type>
TPoint<Size, Type> operator*(
		const TPoint<Size, Type> &Lhs,
		const Type &Rhs
	)
{
	FSize Index;
	TPoint<Size, Type> Result;

	for (Index = 0; Index < Size; ++Index)
	{
		Result[Index] = Rhs * Lhs[Index];
	}
	return Result;
}

/* Vector @= Alpha */

template<FSize Size, typename Type>
TPoint<Size, Type> &operator*=(
		TPoint<Size, Type> &Lhs,
		const Type &Rhs
	)
{
	FSize Index;

	for (Index = 0; Index < Size; ++Index)
	{
		Lhs[Index] *= Rhs;
	}
	return Lhs;
}