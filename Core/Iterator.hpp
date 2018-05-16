#pragma once

#include <Types>

template<typename TypeElement>
struct TIterator
{
	FSize _Size;
	TypeElement *Data;

	FSize Size(
			FVoid
		)
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

	TypeElement & operator[](
			FSize Index
		)
	{
		return Data[Index];
	};

	TypeElement & operator[](
			FSize Index
		) const
	{
		return Data[Index];
	};
};
