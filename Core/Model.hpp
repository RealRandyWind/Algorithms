#pragma once

#include <Types>
#include <Point>
#include <Iterator>
#include <Data>

template<FSize SizeFature, FSize SizeLabel, TypeParameters>
struct TModel
{
	using FFeature = TPoint<SizeFature, FReal>;
	using FLabel = TPoint<SizeLabel, FReal>;
	
	struct FSample
	{
		FFeature Feature;
		FLabel Label;
	};

	struct FPerformence
	{
		FLabel ErrorMean, ErrorSD, ErrorSkew;
		FReal Error, ErrorTypeII, ErrorTypeI;
	};

	FSize FeatureSize()
	{
		return SizeFature;
	};

	FSize LabelSize()
	{
		return SizeLabel;
	};

	virtual FVoid Train(TIterator<FSample>, TypeParameters) = 0;
	virtual FVoid Use(TIterator<FFeature>, TData<FLabel> &, TypeParameters) = 0;
	virtual FVoid Validate(TIterator<FSample>, FPerformence &, TypeParameters) = 0;
	virtual FVoid Optimize(TIterator<FSample>, TypeParameters) = 0;
	virtual FVoid Optimize(TypeParameters) = 0;
};
