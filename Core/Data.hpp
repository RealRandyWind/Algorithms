#pragma once

#include <Types>
#include <Iterator>
#include <Sequence>

template<typename TypeData>
struct TData;

template<typename TypeData>
struct TData
{
	FSize _Size;
	TypeData *Data;

	using FIterator = TIterator<TypeData>;

	inline FSize Size(
			FVoid
		)
	{
		return _Size;
	};

	TIterator<FIterator> Partition(
			TSequence<FReal> Ratios,
			FSize BatchSize
		)
	{
		TIterator<FIterator> It;

		return It;
	};

	TIterator<FIterator> Partition(
			TSequence<FReal> Ratios
		)
	{
		TIterator<FIterator> It;

		return It;
	};

	FIterator Iterator(
			FVoid
		)
	{
		FIterator It;

		return It;
	};
};
