#ifndef POINT_HPP
#define POINT_HPP

#include <Types>
#include <Constants>
#include <Iterator>

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

#endif