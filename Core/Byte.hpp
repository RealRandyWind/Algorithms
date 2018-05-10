#ifndef BYTE_HPP
#define BYTE_HPP

#include <Types>
#include <Functions>

template<FSize SizeBytes>
struct TByte
{
	FRaw Data[SizeBytes];

	inline FSize Size()
	{
		return SizeBytes;
	};

	inline friend TIStream & operator>>(TIStream &In, TByte<SizeBytes> &Bytes)
	{
		FSize Index;
		
		for (Index = 0; Index < SizeBytes; ++Index)
		{
			In >> Bytes.Data[Index];
		}
		return In;
	};

	inline friend TOStream & operator<<(TOStream &Out, const TByte<SizeBytes> &Bytes)
	{
		FSize Index;

		for (Index = 0; Index < SizeBytes; ++Index)
		{
			Out << Bytes.Data[Index];
		}
		return Out;
	};

	template<typename TypeLhs>
	inline operator TypeLhs() const
	{
		TypeLhs Lhs;
		FRaw* PtrLhs;
		FSize Index, End;

		PtrLhs = (FRaw *) &Lhs;
		End = Min(SizeBytes, sizeof(TypeLhs));
		for(Index = 0; Index < End; ++Index)
		{
			PtrLhs[Index] = Data[Index];
		}
		return *PtrLhs;
	};
};

template<typename TypeLhs, FSize SizeBytes>
inline FBool operator==(const TypeLhs &Lhs, const TByte<SizeBytes> &Rhs)
{
	FSize Index, End;
	const FRaw* PtrLhs;

	PtrLhs = (FRaw *) &Lhs;
	End = Min(SizeBytes, sizeof(TypeLhs));
	for(Index = 0; Index < End; ++Index)
	{
		if(Rhs.Data[Index] != PtrLhs[Index])
		{
			return False;
		}
	}
	return True;
};

template<FSize SizeBytes, typename TypeRhs>
inline FBool operator==(const TByte<SizeBytes> &Lhs, const TypeRhs &Rhs)
{
	return (Rhs == Lhs);
};

template<FSize SizeBytes, typename TypeLhs>
inline FBool operator!=(const TypeLhs &Lhs, const TByte<SizeBytes> &Rhs)
{
	FSize Index, End;
	const FRaw* PtrLhs;

	PtrLhs = (FRaw *) &Lhs;
	End = Min(SizeBytes, sizeof(TypeLhs));
	for(Index = 0; Index < End; ++Index)
	{
		if(Rhs.Data[Index] == PtrLhs[Index])
		{
			return False;
		}
	}
	return True;
};

template<FSize SizeBytes, typename TypeRhs>
inline FBool operator!=(const TByte<SizeBytes> &Lhs, const TypeRhs &Rhs)
{
	return (Rhs != Lhs);
};

template<FSize SizeBytes>
inline FBool operator!(const TByte<SizeBytes> &Rhs)
{
	FSize Index;

	for(Index = 0; Index < SizeBytes; ++Index)
	{
		if(Rhs.Data[Index])
		{
			return False;
		}
	}
	return True;
};

#endif