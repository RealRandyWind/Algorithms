#pragma once

#include <Types>
#include <Iterator>
#include <Sequence>

template<typename TypeData>
struct TData;

template<typename TypeData>
struct TData
{
	FSize _Size, _BufferSize;
	TypeData *Data;

	using FIterator = TIterator<TypeData>;

	TData(
			FVoid
		)
	{
		_Size = _BufferSize = 0;
		Data = NullPtr;
	};

	TData(
			FSize ReserveSize
		)
	{
		_Size = 0;
		_BufferSize = ReserveSize;
		Data = Make<TypeData>(_BufferSize);
	};

	TData(
			FString FilePath
		)
	{
		
		/* TODO */
	};

	TData(
			const TData &Rhs
		)
	{
		FSize Index;

		_BufferSize = Rhs._BufferSize;
		_Size = Rhs._Size;
		Data = Make<TypeData>(_BufferSize);
		for(Index = 0; Index < _Size; ++Index)
		{
			Data[Index] = Rhs.Data[Index];
		};
	};
	
	TData(
			TData &&Rhs
		)
	{
		_BufferSize = Rhs._BufferSize;
		_Size = Rhs._Size;
		Data = Rhs.Data;
		Rhs._BufferSize = Rhs._Size = 0;
		Rhs.Data = NullPtr;
	};

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

	TIterator<FIterator> Partition(
			TSequence<FReal> Ratios,
			FSize BatchSize
		)
	{
		TIterator<FIterator> It;

		/* TODO */

		return It;
	};

	TIterator<FIterator> Partition(
			TSequence<FReal> Ratios
		)
	{
		TIterator<FIterator> It;

		/* TODO */

		return It;
	};

	FIterator Iterator(
			FVoid
		)
	{
		FIterator It;

		It.Data = Data;
		It._Size = _Size;
		return It;
	};

	FIterator Iterator(
			FSize IteratorSize
		)
	{
		FIterator It;

		It.Data = Data;
		It._Size = IteratorSize;
		return It;
	};

	inline operator FIterator(
			FVoid
		)
	{
		return Iterator();
	};

	inline TypeData & operator[](
			FSize Index
		)
	{
		return Data[Index];
	};

	inline TypeData & operator[](
			FSize Index
		) const
	{
		return Data[Index];
	};
};
