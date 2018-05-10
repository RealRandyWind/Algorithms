#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <Types>
#include <Functions>
#include <Iterator>

static const FSize SequenceInitSize = 8;

template<typename TypeElement>
struct TSequence
{
	using FIterator = TIterator<TypeElement>;

	FSize _Size, _BufferSize;
	TypeElement *Data;

	inline FSize Size()
	{
		return _Size;
	};

	inline FSize BufferSize()
	{
		return _BufferSize;
	};

	TSequence()
	{
		_Size = _BufferSize = 0;
		Data = NullPtr;
	};

	template<typename TypeRhs>
	TSequence(TListInitializer<TypeRhs> List)
	{
		Data = Make<TypeElement>(List.size());
		for (auto Value : List)
		{
			Data[_Size] = static_cast<TypeElement>(Value);
			++_Size;
		}
		_BufferSize = _Size;
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

	inline FIterator Iterator()
	{
		FIterator It;
		
		It._Size = _Size;
		It.Data = &Data[0];
		return It;
	};
};

#endif