#pragma once

#include <Types>
#include <String>

template<typename TypeElement>
struct TIterator;
template<typename TypeElement>
struct TDistribution;

template<typename TypeElement>
struct TIterator
{
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

	TypeElement * begin(
			FVoid
		)
	{
		return &Data[0];
	};

	TypeElement * begin(
			FVoid
		) const
	{
		return &Data[0];
	};

	TypeElement * end(
			FVoid
		)
	{
		return &Data[_Size];
	};

	TypeElement * end(
			FVoid
		) const
	{
		return &Data[_Size];
	};

	inline TypeElement & operator[](
			FSize Index
		)
	{
		return Data[Index];
	};

	inline TypeElement & operator[](
			FSize Index
		) const
	{
		return Data[Index];
	};
};