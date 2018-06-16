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
		FDuration RunningTime;
		FSize ComplexOperations, SimpleOperations, N;
	};

	inline FSize FeatureSize(
			FVoid
		)
	{
		return SizeFeature;
	}

	inline FSize LabelSize(
			FVoid
		)
	{
		return SizeLabel;
	}

	TIterator<FSample> Pair(
			TIterator<FFeature>,
			TIterator<FLabel>
		)
	{
		TIterator<FSample> It;

		It.Data = NullPtr;
		It._Size = 0;

		return It;
	}

	FVoid Save(
			FString Path,
			FBool IsBinary = True
		)
	{
		FFStream File;
		File.OpenWrite(Path, IsBinary);
		File << *this;
		File.Close();
	}

	FVoid Load(
			FString Path,
			FBool IsBinary = True
		)
	{
		FFStream File;
		File.OpenRead(Path, IsBinary);
		File >> *this;
		File.Close();
	}

	FVoid Initialize(
			const FParameters Parameters
		)
	{
		_Initialize(Parameters);
	}

	FVoid Train(
			TIterator<FSample> Samples,
			const FParameters Parameters
		)
	{
		FLabel Label;

		for (const auto &Sample : Samples)
		{
			_Use(Sample.Feature, Label, Parameters);
			_Train(Label, Sample.Label, Parameters);
		}
	}

	FVoid Use(
			TIterator<FFeature> Features,
			TData<FLabel> &Labels,
			const FParameters Parameters
		)
	{
		FSize N = 0;
		Labels.Reserve(Features.Size());
		for (const auto &Feature : Features)
		{
			_Use(Feature, Labels[N], Parameters);
			++N;
		}
		Labels._Size = N;
	}

	FVoid Validate(
			TIterator<FSample> Samples,
			FPerformence &Performance,
			const FParameters Parameters
		)
	{
		FLabel Label;
		for (const auto &Sample : Samples)
		{
			++Performance.N;
			_Use(Sample.Feature, Label, Parameters);
			_Validate(Label, Sample.Label, Performance, Parameters);
		}
	}

	FVoid Optimize(
			TIterator<FSample> Samples,
			const FParameters Parameters
		)
	{
		for (const auto &Sample : Samples)
		{
			_Optimize(Sample, Parameters);
		}
	}

	FVoid Optimize(
			const FParameters Parameters
		)
	{
		_Optimize(Parameters);
	}

protected:
	virtual FVoid _Initialize(
				const FParameters &Parameters
			) = 0;

	virtual FVoid _Use(
			const FFeature &,
			FLabel &,
			const FParameters &
		) = 0;

	virtual FVoid _Train(
			const FLabel &, 
			const FLabel &, 
			const FParameters &
		) = 0;

	virtual FVoid _Validate(
			const FLabel &,
			const FLabel &,
			FPerformence &,
			const FParameters &
		) = 0;

	virtual FVoid _Optimize(
			const FSample &,
			const FParameters &
		) = 0;

	virtual FVoid _Optimize(
			const FParameters &
		) = 0;
};
