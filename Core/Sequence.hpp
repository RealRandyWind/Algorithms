#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <Types>

template<typename TypeElement>
struct TSequence
{
	FSize _Size, _BufferSize;
	TypeElement *Data;

	inline FSize Size()
	{
		return _Size;
	};

	template<typename TypeLhs>
	inline operator TSequence<TypeLhs>() const
	{
		
		TSequence<TypeLhs> Lhs;
		FSize Index, End;

		End = Min(SizeLhs, _Size);
		for(Index = 0; Index < End; ++Index)
		{
			Lhs.Data[Index] = static_cast<TypeLhs>(Data[Index]);
		}	
		return Lhs;
	};
};

#endif