#pragma once

#include <Types>
#include <Iterator>

template<typename TypeData>
struct TData;

template<typename TypeData>
struct TData
{
	FSize _Size;
	TypeData *Data;

	using FIterator = TIterator<TypeData>;

	inline FSize Size()
	{
		return _Size;
	};

	TIterator<FIterator> Partition(FSequence<FReal> Ratios, FSize BatchSize)
	{
		TIterator<FIterator> It;

		return It;
	};

	TIterator<FIterator> Partition(FSequence<FReal> Ratios)
	{
		TIterator<FIterator> It;

		return It;
	};

	FIterator Iterator()
	{
		FIterator It;

		return It;
	};
};
