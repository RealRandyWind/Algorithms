#pragma once

#include <cstdlib>
#include <cstdint>
#include <fstream>
#include <initializer_list>

template<typename TypeElement>
using TListInitializer = std::initializer_list<TypeElement>;

template<typename TypeElement>
using TIStream = std::basic_istream<TypeElement>;

template<typename TypeElement>
using TOStream = std::basic_ostream<TypeElement>;

using FEnum = uint16_t;
using FRaw = uint8_t;
using FPointer = void *;
using FReal = float;
using FSize = size_t;
using FBool = bool;
using FNatural = unsigned int;
using FInteger = int;
using FReturn = decltype(EXIT_SUCCESS);
using FVoid = void;

static const decltype("") NullStr = "";
static const decltype('\0') NullChr = '\0';
static const decltype(true) True = true;
static const decltype(false) Fasle = false;
static const decltype(nullptr) NullPtr = nullptr;
static const decltype(EXIT_SUCCESS) Success = EXIT_SUCCESS;
static const decltype(EXIT_FAILURE) Failure = EXIT_FAILURE;
