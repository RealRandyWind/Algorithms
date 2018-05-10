#ifndef PROCEDURE_HPP
#define PROCEDURE_HPP

#include <Types>
#include <Iterator>
#include <Data>

template<typename TypeInput, typename TypeResult, typename TypeParameters>
struct TProcedure
{
	virtual FVoid Use(TIterator<TypInput>, TData<TypeResult> &, TypeParameters) = 0;
};

#endif