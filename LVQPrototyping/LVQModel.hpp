#pragma once

#include <Types>
#include <Model>

namespace LVQ
{
	struct FParameters
	{
		FReal Alpha;
	};

	class CModel : public TModel<8, 3, FParameters>
	{
	public:
		CModel(
				FVoid
			);

		~CModel(
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
	};
}