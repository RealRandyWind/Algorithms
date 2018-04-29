#ifndef POINT_HPP
#define POINT_HPP

#include <Types>
#include <Constants>
#include <Functions>

#define STRING_INIT_SIZE 8;

template<typename TypeSymbol>
struct TString
{
	FSize _SizeBuffer, _Size;
	TypeSymbol *Data;

	inline FSize Size()
	{
		return _Size;
	};

	TString()
	{
		_SizeBuffer = _Size = 0;
		Data = NullPtr;
	};

	TString(const TString &Rhs)
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
	
	TString(TString &&Rhs)
	{
		_SizeBuffer = Rhs._SizeBuffer;
		_Size = Rhs._Size;
		Data = Rhs.Data;
		Rhs._SizeBuffer = Rhs._Size = 0;
		Rhs.Data = NullPtr;
	};

	/* init constructor */
	TString(const TypeSymbol *Rhs) : TString()
	{
		if(!Rhs || !*Rhs) { return; }

		_SizeBuffer = STRING_INIT_SIZE
		Data = Make<TypeSymbol>(_SizeBuffer);

		for(_Size = 0; Data[_Size] = Rhs[_Size]; ++_Size)
		{
			if(_Size <= _SizeBuffer)
			{
				Data = Resize(Data, _SizeBuffer += STRING_INIT_SIZE);
			}
		}

		Data[_Size] = TypeSymbol();
	};

	~TString()
	{ 
		Data = rm(Data);
	};

	inline friend TFStream & operator>>(TFStream &In, TString &String)
	{
		FSize Index;
		
		for (Index = 0; Index < String._Size; ++Index)
		{
			In >> String.Data[Index];
		}
		return In;
	};

	inline friend TOStream & operator<<(TOStream &Out, const TString &String)
	{
		FSize Index;

		for (Index = 0; Index < String._Size; ++Index)
		{
			Out << String.Data[Index];
		}
		return Out;
	};
};

#endif