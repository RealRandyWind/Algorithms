#pragma once

#include <Types>
#include <Iterator>
#include <Data>

template<typename TypeInput, typename TypeResult, typename TypeParameters>
struct TProcedure
{
	virtual FVoid Use(TIterator<TypeInput>, TData<TypeResult> &, TypeParameters) = 0;
};
