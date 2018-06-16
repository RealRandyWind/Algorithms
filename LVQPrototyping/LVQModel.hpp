#pragma once

#include <Types>
#include <Model>
#include <Sequence>

namespace LVQ
{
	struct FParameters
	{
		FReal Alpha;
		FBool UseClassIndexAsLabel;
	};

	class CLVQ1 : public TModel<8, 3, FParameters>
	{
	public:
		struct FPrototype
		{
			FSize Class;
			FFeature Feature;
			FLabel Label;
		};
		
		struct FNeighbour
		{
			FReal Distance;
			FFeature Direction;
			FPrototype &Prototype;
		};

		FPrototype NullPrototype = {0};
		TSequence<FPrototype> Prototypes;
		FNeighbour Neighbour = {0, {0}, NullPrototype};

	protected:
		virtual FVoid _Initialize(
				const FParameters &Parameters
			) override;

		virtual FVoid _Use(
				const FFeature &,
				FLabel &,
				const FParameters &
			) override;

		virtual FVoid _Train(
				const FLabel &, 
				const FLabel &, 
				const FParameters &
			) override;

		virtual FVoid _Validate(
				const FLabel &,
				const FLabel &,
				FPerformence &,
				const FParameters &
			) override;

		virtual FVoid _Optimize(
				const FSample &,
				const FParameters &
			) override;

		virtual FVoid _Optimize(
				const FParameters &
			) override;
	};
}