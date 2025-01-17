#pragma once

#include <string.h>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <initializer_list>
#include <chrono>

template<typename TypeElement>
using TListInitializer = std::initializer_list<TypeElement>;

using FIStream = std::istream;
using FOStream = std::ostream;

using FString = std::string;
using FRaw = uint8_t;
using FPointer = void *;
using FReal = float;
using FSize = size_t;
using FBool = bool;
using FNatural = unsigned int;
using FInteger = int;
using FTime = std::chrono::high_resolution_clock::time_point;
using FDuration = std::chrono::high_resolution_clock::duration;
using FReturn = decltype(EXIT_SUCCESS);
using FVoid = void;

#define Null NULL
static const decltype("") NullStr = "";
static const decltype('\0') NullChr = '\0';
static const decltype(true) True = true;
static const decltype(false) False = false;
static const decltype(nullptr) NullPtr = nullptr;
static const decltype(EXIT_SUCCESS) Success = EXIT_SUCCESS;
static const decltype(EXIT_FAILURE) Failure = EXIT_FAILURE;

static decltype(std::cin) &InStream = std::cin;
static decltype(std::cout) &OutStream = std::cout;
static decltype(std::cerr) &ErrorStream = std::cerr;
static decltype(std::clog) &LogStream = std::clog;

struct FFStream : std::fstream
{
	FReturn Open(
			FString Path
		)
	{
		return Open(Path, True);
	}

	FReturn Open(
			FString Path,
			FBool IsBinary
		)
	{
		open(Path, in | out | (IsBinary ? binary : 0));
		return Success;
	}

	FReturn OpenRead(
			FString Path,
			FBool IsBinary
		)
	{
		open(Path, in | (IsBinary ? binary : 0));
		return Success;
	}

	FReturn OpenWrite(
			FString Path,
			FBool IsBinary
		)
	{
		open(Path, out | (IsBinary ? binary : 0));
		return Success;
	}

	FReturn Check(
			FVoid
		)
	{
		return (is_open() ? Success : Failure);
	}

	FReturn Close(
			FVoid
		)
	{
		close();
		return Success;
	}

	FReturn Flush(
			FVoid
		)
	{
		flush();
		return Success;
	}

	FReturn Seek(
			FSize Position
		)
	{
		seekg(Position);
		return Success;
	}

	FSize Tell(
			FVoid
		)
	{
		return tellg();
	}

	FBool IsEnd(
			FVoid
		)
	{
		return eof();
	}
};
