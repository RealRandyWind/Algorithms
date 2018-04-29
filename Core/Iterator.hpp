#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <Types>

template<typename TypeElement>
struct TIterator
{
	FSize _Size;
	TypeElement *Data;

	FSize Size()
	{
		return _Size;
	};

	TypeElement * begin()
	{
		return &Data[0];
	};

	TypeElement * begin() const
	{
		return &Data[0];
	};

	TypeElement * end()
	{
		return &Data[_Size];
	};

	TypeElement * end() const
	{
		return &Data[_Size];
	};

	TypeElement & operator[](FSize Index)
	{
		return Data[Index];
	};

	TypeElement & operator[](FSize Index) const
	{
		return Data[Index];
	};
};

#endif