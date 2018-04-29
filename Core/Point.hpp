#ifndef POINT_HPP
#define POINT_HPP

#include <Types>
#include <Constants>
#include <Functions>

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
};

#endif