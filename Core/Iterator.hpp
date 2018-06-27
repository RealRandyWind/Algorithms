#pragma once

#include <Types>

template<typename TypeElement>
struct TIterator;

template<typename TypeElement>
struct TIterator
{
	using FIterator = TIterator<TypeElement>;

	FSize _Size, _BufferSize, _Index, _ActiveIndex;
	TypeElement *Data, *Current;

	inline FSize Size(
			FVoid
		)
	{
		return _Size;
	}

	inline FSize Size(
			FVoid
		) const
	{
		return _Size;
	}

	inline FSize BufferSize(
			FVoid
		)
	{
		return _BufferSize;
	}

	inline FSize BufferSize(
			FVoid
		) const
	{
		return _BufferSize;
	}

	FIterator Undefined(
			FVoid
		)
	{
		FIterator It;

		It._Index = 0;
		It.Data = It.Current = &Data[_Size];
		It._Size = _BufferSize - _Size;
		It._BufferSize = It._Size;
		
		return It;
	}

	FIterator Buffer(
			FVoid
		)
	{
		FIterator It;
		
		It._Index = 0;
		It.Data = It.Current = &Data[0];
		It._Size = It._BufferSize = _BufferSize;
		return It;
	}

	FVoid Add(
			TypeElement Rhs
		)
	{
		Data[_Size] = Rhs;
		++_Size;
	}

	FVoid Swap(
			TypeElement Rhs
		)
	{
		if(_Size < _BufferSize)
		{
			++_Size;
		}
		++_ActiveIndex;
		if(_ActiveIndex >= _BufferSize)
		{
			_ActiveIndex = 0;
		}
		Data[_ActiveIndex] = Rhs;
	}

	TypeElement &Active(
			FVoid
		)
	{
		return Data[_ActiveIndex];
	}

	const TypeElement &Active(
			FVoid
		) const
	{
		return Data[_ActiveIndex];
	}

	inline TypeElement &operator[](
			FSize Index
		)
	{
		return Data[Index];
	}

	inline const TypeElement &operator[](
			FSize Index
		) const
	{
		return Data[Index];
	}

	TypeElement *begin(
			FVoid
		)
	{
		return &Data[0];
	}

	TypeElement *begin(
			FVoid
		) const
	{
		return &Data[0];
	}

	TypeElement *end(
			FVoid
		)
	{
		return &Data[_Size];
	}

	TypeElement *end(
			FVoid
		) const
	{
		return &Data[_Size];
	}
};