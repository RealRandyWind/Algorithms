#pragma once

#include <Types>
#include <Functions>
#include <Iterator>

static const FSize SequenceInitSize = 8;

template<typename TypeElement>
struct TSequence;

template<typename TypeElement>
struct TSequence
{
	using FIterator = TIterator<TypeElement>;

	FSize _Size, _BufferSize;
	TypeElement *Data;

	inline FSize Size(
			FVoid
		)
	{
		return _Size;
	};

	inline FSize Size(
			FVoid
		) const
	{
		return _Size;
	};

	inline FSize BufferSize(
			FVoid
		)
	{
		return _BufferSize;
	};

	inline FSize BufferSize(
			FVoid
		) const
	{
		return _BufferSize;
	};

	FVoid Reserve(
			FSize ReserveSize
		)
	{
		_BufferSize = ReserveSize;
		Data = Resize(Data, _BufferSize);
	};

	TSequence(
			FVoid
		)
	{
		_Size = _BufferSize = 0;
		Data = NullPtr;
	};

	TSequence(
			FSize ReserveSize
		)
	{
		_Size = 0;
		_BufferSize = ReserveSize;
		Data = Make<TypeElement>(_BufferSize);
	};

	template<typename TypeRhs>
	TSequence(
			TListInitializer<TypeRhs> List
		)
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
	operator TSequence<TypeLhs>(
			FVoid
		) const
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

	FIterator Iterator(
			FVoid
		)
	{
		FIterator It;
		
		It._Size = _Size;
		It.Data = &Data[0];
		return It;
	};
};
