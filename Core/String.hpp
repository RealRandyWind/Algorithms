#pragma once

#include <Types>
#include <Functions>

static const FSize StringInitSize = 8;

template<typename TypeSymbol>
struct TString;

template<typename TypeSymbol>
struct TString
{
	FSize _SizeBuffer, _Size;
	TypeSymbol *Data;

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

	inline FSize SizeBuffer(
		FVoid
		)
	{
		return _SizeBuffer;
	};

	inline FSize SizeBuffer(
		FVoid
		) const
	{
		return _SizeBuffer;
	};

	TString(
			FVoid
		)
	{
		_SizeBuffer = _Size = 0;
		Data = NullPtr;
	};

	TString(
			const TString &Rhs
		)
	{
		FSize Index;

		_SizeBuffer = Rhs._SizeBuffer;
		_Size = Rhs._Size;
		Data = Make<TypeSymbol>(_SizeBuffer);
		for(Index = 0; Index < _Size; ++Index)
		{
			Data[Index] = Rhs.Data[Index];
		};
	};
	
	TString(
			TString &&Rhs
		)
	{
		_SizeBuffer = Rhs._SizeBuffer;
		_Size = Rhs._Size;
		Data = Rhs.Data;
		Rhs._SizeBuffer = Rhs._Size = 0;
		Rhs.Data = NullPtr;
	};

	template<typename TypeRhs>
	TString(
			TListInitializer<TypeRhs> List
		) : TString()
	{
		Data = Make<TypeSymbol>(List.size());
		for (auto Value : List)
		{
			Data[_Size] = static_cast<TypeSymbol>(Value);
			++_Size;
		}
		_BufferSize = _Size;
	};

	/*
	TString(const TypeSymbol *Rhs) : TString()
	{
		if(!Rhs || !*Rhs) { return; }

		_SizeBuffer = StringInitSize
		Data = Make<TypeSymbol>(_SizeBuffer);

		for(_Size = 0; Data[_Size] = Rhs[_Size]; ++_Size)
		{
			if(_Size <= _SizeBuffer)
			{
				Data = Resize(Data, _SizeBuffer += StringInitSize);
			}
		}

		Data[_Size] = TypeSymbol();
	};
	*/

	~TString(
			FVoid
		)
	{ 
		Data = Remove(Data);
	};

	friend FIStream & operator>>(
			FIStream &In,
			TString &String
		)
	{
		FSize Index;
		
		for (Index = 0; Index < String._Size; ++Index)
		{
			In >> String.Data[Index];
		}
		return In;
	};

	friend FOStream & operator<<(
			FOStream &Out,
			const TString &String
		)
	{
		FSize Index;

		for (Index = 0; Index < String._Size; ++Index)
		{
			Out << String.Data[Index];
		}
		return Out;
	};
};
