#pragma once

#include <Types>
#include <Model>
#include <Sequence>

namespace LVQ
{
	struct FParameters
	{
		FReal Alpha;
	};

	class CLVQ1 : public TModel<8, 3, FParameters>
	{
	public:

		struct FState
		{
			TSequence<FFeature> Prototypes;
		};

		FState *State;

		CLVQ1(
				FVoid
			);

		~CLVQ1(
				FVoid
			);

		virtual FVoid Train(
				TIterator<FSample> Samples,
				FParameters Parameters
			) override;

		virtual FVoid Use(
				TIterator<FFeature> Features,
				TData<FLabel> &Labels,
				FParameters Parameters
			) override;

		virtual FVoid Validate(
				TIterator<FSample> Samples,
				FPerformence &Performance,
				FParameters Parameters
			) override;

		virtual FVoid Optimize(
				TIterator<FSample> Samples,
				FParameters Parameters
			) override;

		virtual FVoid Optimize(
				FParameters Parameters
			) override;

	private:

		FVoid _Use(
				const FFeature,
				FLabel &
			);

		FVoid _Train(
				const FLabel &, 
				const FLabel &, 
				FReal
			);

		FVoid _Validate(
				const FLabel &,
				const FLabel &,
				FPerformence &
			);
	};
}