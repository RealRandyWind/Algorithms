#pragma once

#include <string.h> /*<String>*/
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <initializer_list>

template<typename TypeElement=char>
using TListInitializer = std::initializer_list<TypeElement>;

using FString = std::wstring; /*TString<wchar_t>*/
using FIStream = std::istream;
using FOStream = std::ostream;
using FFStream = std::fstream;

using FEnum = uint16_t;
using FRaw = uint8_t;
using FPointer = void *;
using FReal = float;
using FSize = size_t;
using FBool = bool;
using FNatural = unsigned int;
using FInteger = int;
using FTime = time_t;
using FReturn = decltype(EXIT_SUCCESS);
using FVoid = void;

static const decltype("") NullStr = "";
static const decltype('\0') NullChr = '\0';
static const decltype(true) True = true;
static const decltype(false) Fasle = false;
static const decltype(nullptr) NullPtr = nullptr;
static const decltype(EXIT_SUCCESS) Success = EXIT_SUCCESS;
static const decltype(EXIT_FAILURE) Failure = EXIT_FAILURE;

static decltype(std::wcin) &InStream = std::wcin;
static decltype(std::wcout) &OutStream = std::wcout;
static decltype(std::wcerr) &ErrorStream = std::wcerr;
static decltype(std::wclog) &LogStream = std::wclog;