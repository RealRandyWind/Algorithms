#pragma once

#include <Types>
#include <Functions>
#include <Iterator>

static const FSize SequenceInitSize = 8;

template<typename TypeElement>
struct TSequence;

template<typename TypeElement>
struct TSequence : public TIterator<TypeElement>
{
	TSequence(
			FVoid
		)
	{
		_Size = _BufferSize = 0;
		Data = NullPtr;
	}

	TSequence(
			FSize ReserveSize
		) : TSequence()
	{
		_Size = 0;
		_BufferSize = ReserveSize;
		Data = Make<TypeElement>(_BufferSize);
	}

	template<typename TypeRhs>
	TSequence(
			TListInitializer<TypeRhs> List
		) : TSequence()
	{
		Data = Make<TypeElement>(List.size());
		for (auto Value : List)
		{
			Data[_Size] = static_cast<TypeElement>(Value);
			++_Size;
		}
		_BufferSize = _Size;
	}

	TSequence(
			const TSequence &Rhs
		) : TSequence()
	{
		FSize Index;

		_BufferSize = Rhs._BufferSize;
		_Size = Rhs._Size;
		Data = Make<TypeElement>(_BufferSize);
		for(Index = 0; Index < _Size; ++Index)
		{
			Data[Index] = Rhs.Data[Index];
		}
	}
	
	TSequence(
			TSequence &&Rhs
		) : TSequence()
	{
		_BufferSize = Rhs._BufferSize;
		_Size = Rhs._Size;
		Data = Rhs.Data;
		Rhs._BufferSize = Rhs._Size = 0;
		Rhs.Data = NullPtr;
	}

	~TSequence(
			FVoid
		)
	{
		if (Data)
		{
			Remove(Data);
			Data = NullPtr;
			_Size = _BufferSize = 0;
		}
	}

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
	}
};
