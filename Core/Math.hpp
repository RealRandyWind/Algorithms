#pragma once

#include <math>
#include <Point>

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

/* Vector @ Vector */

template<FSize Size, typename Type>
TPoint<Size, Type> operator-(
		const TPoint<Size, Type> &Lhs,
		const TPoint<Size, Type> &Rhs
	)
{
	FSize Index;
	TPoint<Size, Type> Result = {0};

	for (Index = 0; Index < Size; ++Index)
	{
		Result[Index] = Lhs[Index] - Rhs[Index];
	}
	return Result;
}

/* Vector @= Vector */

template<FSize Size, typename Type>
TPoint<Size, Type> & operator+=(
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
	TPoint<Size, Type> Result = {0};

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
	TPoint<Size, Type> Result = {0};

	for (Index = 0; Index < Size; ++Index)
	{
		Result[Index] = Lhs - Rhs[Index];
	}
	return Result;
}

/* Vector @ Alpha */

/* Vector @= Alpha */