#pragma once

#include <Types>
#include <Model>
#include <Sequence>

namespace LVQ
{
	class CLVQ1 : public TModel<8, 3>
	{
	public:
		struct FParameters
		{
			FReal LearningRate;
			FSize KNearest, NPrototypes;
			FBool UseClassIndexAsLabel;
		};

		struct FPrototype
		{
			FSize Class;
			FFeature Feature;
			FLabel Label;
		};
		
		struct FNeighbour
		{
			FReal Distance2;
			FFeature Direction;
			FPrototype *Prototype;
		};

		struct FState
		{
			TSequence<FPrototype> Prototypes;
			TSequence<FNeighbour> Neighbours;
		};
		
		FParameters Parameters;
		FState State;

	protected:
		virtual FVoid _Initialize(
				FVoid
			) override;

		virtual FVoid _Use(
				const FFeature &,
				FLabel &
			) override;

		virtual FVoid _Train(
				const FLabel &,
				const FLabel &
			) override;

		virtual FVoid _Optimize(
				const FSample &
			) override;

		virtual FVoid _Optimize(
				FVoid
			) override;
	};
}