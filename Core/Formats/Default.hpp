#pragma once

#include <Types>
#include <Byte>

namespace Format
{
	namespace DefaultIO
	{
		struct FFormatHeader
		{
			TByte<4> Type;
			TByte<2> Endian;
			TByte<2> Base;
			TByte<1> HasTypes;
			TByte<1> HasReferences;
		};

		struct FTypeHeader
		{
			TByte<sizeof(FSize)> Type;
			TByte<sizeof(FSize)> Version;
		};

		struct FHeader
		{
			TByte<sizeof(FSize)> SizeOf;
			TByte<sizeof(FSize)> Size;
		};

		struct FReference
		{
			TByte<sizeof(FSize)> ID;
		};

		struct FEntry
		{
			FSize Reference;
			FPointer Pointer;
		};
	}

	struct FDefault : FFormat
	{
	};
}
