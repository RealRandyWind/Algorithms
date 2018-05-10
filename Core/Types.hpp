#ifndef TYPES_HPP
#define TYPES_HPP

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
using FReturn = int;

using NullPtr = decltype(nullptr); 
using NullStr = decltype("");
using NullChr = decltype('\0');
using True = decltype(true);
using False = decltype(false);

static const FReturn Success = EXIT_SUCCESS;
static const FReturn Failure = EXIT_FAILURE;

#endif