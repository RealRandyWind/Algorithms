#pragma once

#include <Types>
#include <Iterator>
#include <Sequence>
#include <Byte>

template<typename TypeData>
struct TData;

template<typename TypeData>
struct TData : public TIterator<TypeData>
{
	TData(
			FVoid
		)
	{
		_Size = _BufferSize = 0;
		Data = NullPtr;
	}

	TData(
			FSize ReserveSize
		)
	{
		_Size = 0;
		_BufferSize = ReserveSize;
		Data = Make<TypeData>(_BufferSize);
	}

	TData(
			FString Path,
			FBool IsBinary = True
		) : TData()
	{
		Load(Path, IsBinary);
	}

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
		}
	}
	
	TData(
			TData &&Rhs
		)
	{
		_BufferSize = Rhs._BufferSize;
		_Size = Rhs._Size;
		Data = Rhs.Data;
		Rhs._BufferSize = Rhs._Size = 0;
		Rhs.Data = NullPtr;
	}

	~TData(
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

	FVoid Reserve(
			FSize ReserveSize
		)
	{
		_BufferSize = ReserveSize;
		Data = Resize(Data, _BufferSize);
	}

	FVoid Save(
			FString Path,
			FBool IsBinary = True
		)
	{
		FFStream File;
		File.OpenWrite(Path, IsBinary);
		File << *this;
		File.Close();
	}

	FVoid Load(
			FString Path,
			FBool IsBinary = True
		)
	{
		FFStream File;
		File.OpenRead(Path, IsBinary);
		File >> *this;
		File.Close();
	}

	friend FOStream & operator<<(
			FOStream &Out,
			TData<TypeData> &Rhs
		)
	{
		TByte<sizeof(FSize)> RawElementSize, RawDataSize;
		TByte<sizeof(TypeData)> RawElement;

		RawElementSize = RawElement.Size();
		RawDataSize = Rhs.Size();
		
		Out << RawElementSize;
		Out << RawDataSize;

		for(const auto &Element : Rhs)
		{
			RawElement = Element;
			Out << RawElement;
		}
		return Out;
	}

	friend FIStream & operator>>(
			FIStream &In,
			TData<TypeData> &Rhs
		)
	{
		TByte<sizeof(FSize)> RawElementSize, RawDataSize;
		TByte<sizeof(TypeData)> RawElement;

		In >> RawElementSize;
		In >> RawDataSize;

		Rhs.Reserve((FSize)RawDataSize);
		for(auto &Element : Rhs)
		{
			In >> RawElement;
			Element = RawElement;
		}
		return In;
	}
};
