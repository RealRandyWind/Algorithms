#pragma once

#include <Types>
#include <Point>
#include <Iterator>
#include <Data>

template<FSize SizeFeature, FSize SizeLabel>
struct TModel;

template<FSize SizeFeature, FSize SizeLabel>
struct TModel
{
	using FFeature = TPoint<SizeFeature, FReal>;
	using FLabel = TPoint<SizeLabel, FReal>;
	
	struct FSample
	{
		FFeature Feature;
		FLabel Label;
	};

	struct FPerformence
	{
		FLabel ErrorMin, ErrorMax, ErrorMean, ErrorSD, ErrorSkew;
		FSize ComplexOperations, SimpleOperations, MemoryReads, MemoryWrites;
		FSize N, NThreads;
		FDuration RunningTime;
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
			FVoid
		)
	{
		_Initialize();
	}

	FVoid Train(
			TIterator<FSample> Samples
		)
	{
		FLabel Label;

		for (const auto &Sample : Samples)
		{
			_Use(Sample.Feature, Label);
			_Train(Label, Sample.Label);
		}
	}

	FVoid Use(
			TIterator<FFeature> Features,
			TData<FLabel> &Labels
		)
	{
		FSize N = 0;
		Labels.Reserve(Features.Size());
		for (const auto &Feature : Features)
		{
			_Use(Feature, Labels[N]);
			++N;
		}
		Labels._Size = N;
	}

	FVoid Validate(
			TIterator<FSample> Samples,
			FPerformence &Performance
		)
	{
		FLabel Label;
		/*
		FTime Time;
		*/

		for (const auto &Sample : Samples)
		{
			/*
			Time = FTime::Now();
			*/
			_Use(Sample.Feature, Label);
			/*
			Performance.RunningTime += FTime::Now() - Time;
			*/
		}
	}

	FVoid Optimize(
			TIterator<FSample> Samples
		)
	{
		for (const auto &Sample : Samples)
		{
			_Optimize(Sample);
		}
	}

	FVoid Optimize(
			FVoid
		)
	{
		_Optimize();
	}

protected:
	virtual FVoid _Initialize(
				FVoid
			) = 0;

	virtual FVoid _Use(
			const FFeature &,
			FLabel &
		) = 0;

	virtual FVoid _Train(
			const FLabel &,
			const FLabel &
		) = 0;

	virtual FVoid _Optimize(
			const FSample &
		) = 0;

	virtual FVoid _Optimize(
			FVoid
		) = 0;
};
