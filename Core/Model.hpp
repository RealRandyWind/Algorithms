#pragma once

#include <Types>
#include <Point>
#include <Iterator>
#include <Data>

template<FSize SizeFeature, FSize SizeLabel, typename TypeParameters>
struct TModel;

template<FSize SizeFeature, FSize SizeLabel, typename TypeParameters>
struct TModel
{
	using FParameters = TypeParameters;
	using FFeature = TPoint<SizeFeature, FReal>;
	using FLabel = TPoint<SizeLabel, FReal>;
	
	struct FSample
	{
		FFeature Feature;
		FLabel Label;
	};

	struct FPerformence
	{
		FLabel ErrorMean, ErrorSD, ErrorSkew;
		FReal Error, ErrorTypeII, ErrorTypeI, ErrorGeneralization;
		FTime RunningTime;
		FSize ComplexOperations, SimpleOperations, N;
	};

	inline FSize FeatureSize(
			FVoid
		)
	{
		return SizeFeature;
	};

	inline FSize LabelSize(
			FVoid
		)
	{
		return SizeLabel;
	};

	TIterator<FSample> Pair(
			TIterator<FFeature>,
			TIterator<FLabel>
		)
	{
		TIterator<FSample> It;
		
		return It;
	};

	virtual FVoid Train(
			TIterator<FSample>,
			FParameters
		) = 0;

	virtual FVoid Use(
			TIterator<FFeature>,
			TData<FLabel> &,
			FParameters
		) = 0;

	virtual FVoid Validate(
			TIterator<FSample>,
			FPerformence &,
			FParameters
		) = 0;

	virtual FVoid Optimize(
			TIterator<FSample>,
			FParameters
		) = 0;
	
	virtual FVoid Optimize(
			FParameters
		) = 0;
};
