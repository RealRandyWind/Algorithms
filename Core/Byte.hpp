#pragma once

#include <Types>
#include <Functions>

template<FSize SizeBytes>
struct TByte;

template<FSize SizeBytes>
struct TByte
{
	FRaw Data[SizeBytes];

	inline FSize Size(
			FVoid
		)
	{
		return SizeBytes;
	};

	inline FSize Size(
			FVoid
		) const
	{
		return SizeBytes;
	};

	friend FIStream & operator>>(
			FIStream &In,
			TByte<SizeBytes> &Bytes
		)
	{
		FSize Index;
		
		for (Index = 0; Index < SizeBytes; ++Index)
		{
			In >> Bytes.Data[Index];
		}
		return In;
	};

	friend FOStream & operator<<(
			FOStream &Out,
			const TByte<SizeBytes> &Bytes
		)
	{
		FSize Index;

		for (Index = 0; Index < SizeBytes; ++Index)
		{
			Out << Bytes.Data[Index];
		}
		return Out;
	};

	template<typename TypeLhs>
	operator TypeLhs(
			FVoid
		) const
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
FBool operator==(
		const TypeLhs &Lhs,
		const TByte<SizeBytes> &Rhs
	)
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
inline FBool operator==(
		const TByte<SizeBytes> &Lhs,
		const TypeRhs &Rhs
	)
{
	return (Rhs == Lhs);
};

template<FSize SizeBytes, typename TypeLhs>
FBool operator!=(
		const TypeLhs &Lhs,
		const TByte<SizeBytes> &Rhs
	)
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
inline FBool operator!=(
		const TByte<SizeBytes> &Lhs,
		const TypeRhs &Rhs
	)
{
	return (Rhs != Lhs);
};

template<FSize SizeBytes>
FBool operator!(
		const TByte<SizeBytes> &Rhs
	)
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
