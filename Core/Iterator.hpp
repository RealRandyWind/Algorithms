#pragma once

#include <Types>
#include <Functions>

template<typename TypeElement>
struct TIterator;

template<typename TypeElement>
struct TIterator
{
	using FIterator = TIterator<TypeElement>;

	FBool _DestroyData;
	FSize _Size, _BufferSize;
	FSize _Index, _BufferIndex, _ActiveIndex;
	TypeElement *Data;

	TIterator(
			FVoid
		)
	{
		_DestroyData = False;
		_Size = _BufferSize = 0;
		_Index = _ActiveIndex = 0;
		_BufferIndex = 1;
		Data = NullPtr;
	}

	TIterator(
			FSize ReserveSize
		) : TIterator()
	{
		_DestroyData = True;
		_BufferIndex = ReserveSize;
		Reserve();
	}

	~TIterator(
				FVoid
			)
	{
		if (_DestroyData && !Data)
		{
			Remove(Data);
		}
	}

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
		It.Data = &Data[_BufferIndex];
		It._Size = _BufferSize - _BufferIndex;
		It._BufferSize = It._Size;
		return It;
	}

	FIterator Buffer(
			FVoid
		)
	{
		FIterator It;
		
		It._Index = 0;
		It.Data = &Data[0];
		It._Size = It._BufferSize = _BufferSize;
		return It;
	}

	FVoid Reserve(
			FSize ReserveSize
		)
	{
		_BufferSize = ReserveSize;
		Data = Make<TypeElement>(_BufferSize);
	}

	FVoid Swap(
			TypeElement Rhs
		)
	{
		if(_Size < _BufferSize)
		{
			++_Size;
		}
		++_BufferIndex;
		if(_BufferIndex >= _BufferSize)
		{
			_BufferIndex = 0;
		}
		_ActiveIndex = _BufferIndex;
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

	FVoid Reset(
			FVoid
		)
	{
		_Index = _ActiveIndex = _BufferIndex = 0;
	}

	TypeElement &operator[](
			FSize Index
		)
	{
		Cache(Index);
		return Data[_ActiveIndex];
	}

	const TypeElement &operator[](
			FSize Index
		) const
	{
		Cache(Index);
		return Data[_ActiveIndex];
	}

	TypeElement& operator*(
			FVoid
		)
	{
		Cache(_Index);
		return Data[_ActiveIndex];
	}

	const TypeElement& operator*(
			FVoid
		) const
	{
		Cache(_Index);
		return Data[_ActiveIndex];
	}

	FIterator &operator++(
			FVoid
		)
	{
		++_Index;
		return *this;
	}

	FIterator &begin(
			FVoid
		)
	{
		return *this;
	}

	FIterator &end(

		)
	{
		return *this;
	}

	const FIterator &begin(
			FVoid
		) const
	{
		return *this;
	}

	const FIterator &end(

		) const
	{
		return *this;
	}

	FBool operator!=(
			const FIterator &Rhs
		) const
	{
		return _Size != _Index;
	}

	virtual FVoid Cache(
			FSize Index
		)
	{
		if (Index == _ActiveIndex)
		{
			return;
		}

		if (Index >= _BufferSize)
		{
			_BufferSize = Index + 1;
			Data = Resize(Data, _BufferSize);
		}

		if (Index >= _BufferIndex)
		{
			_BufferIndex = Index;
		}

		_ActiveIndex = Index;
	}
};

