#pragma once

#include <Types>
#include <Functions>

template<FSize SizeData, typename TypeElement>
struct TPoint;
template<typename TypeElement>
struct TPoint2D;
template<typename TypeElement>
struct TPoint3D;
template<typename TypeElement>
struct TPoint4D;


template<FSize SizeData, typename TypeElement>
struct TPoint
{
	TypeElement Data[SizeData];

	inline FSize Size()
	{
		return SizeData;
	};

	template<FSize SizeLhs, typename TypeLhs>
	inline operator TPoint<SizeLhs, TypeLhs>() const
	{
		TPoint<SizeLhs, TypeLhs> Lhs;
		FSize Index, End;

		End = Min(SizeLhs, SizeData);
		for(Index = 0; Index < End; ++Index)
		{
			Lhs.Data[Index] = static_cast<TypeLhs>(Data[Index]);
		}	
		return Lhs;
	};

	template<typename TypeLhs>
	inline operator TPoint2D<TypeLhs>() const
	{
		TPoint2D<TypeLhs> Lhs;
		
		Lhs.Point = *this;
		return Lhs;
	};

	template<typename TypeLhs>
	inline operator TPoint3D<TypeLhs>() const
	{
		TPoint3D<TypeLhs> Lhs;
		
		Lhs.Point = *this;
		return Lhs;
	};

	template<typename TypeLhs>
	inline operator TPoint4D<TypeLhs>() const
	{
		TPoint4D<TypeLhs> Lhs;
		
		Lhs.Point = *this;
		return Lhs;
	};
};

template<typename TypeElement>
struct TPoint2D
{
	union
	{
		TPoint<2, TypeElement> Point;
		struct
		{
			TypeElement X, Y;
		};
	};

	#include "Point.members.incl"
};

template<typename TypeElement>
struct TPoint3D
{
	union
	{
		TPoint<3, TypeElement> Point;
		struct
		{
			TypeElement X, Y, Z;
		};
	};

	#include "Point.members.incl"
};

template<typename TypeElement>
struct TPoint4D
{
	union
	{
		TPoint<4, TypeElement> Point;
		struct
		{
			TypeElement X, Y, Z, W;
		};
	};

	#include "Point.members.incl"
};
