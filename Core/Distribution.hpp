#pragma once

template<typename TypeVariable, typename Type>
struct TDistribution;

template<typename TypeVariable, typename Type>
struct TDistribution
{
    TypeVariable Generate(FReal);
    FReal Probability(TypeVariable);
};