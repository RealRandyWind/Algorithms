#pragma once

#include <Types>
#include <Model>
#include <Sequence>
#include <Math>

namespace LVQ
{
	template<FSize SizeFeature, FSize SizeLabel>
	struct TLVQ1;

	template<FSize SizeFeature, FSize SizeLabel>
	struct TLVQ1 : public TModel<SizeFeature, SizeLabel>
	{
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
			) override
		{
			State.Prototypes.Reserve(Parameters.NPrototypes);
			State.Neighbours.Reserve(Parameters.KNearest);
			
			for (auto &Prototype : State.Prototypes.Buffer())
			{
				Prototype = {0};
			}

			for (auto &Neighbour : State.Neighbours.Buffer())
			{
				Neighbour = {0};
			}
		}

		virtual FVoid _Use(
				const FFeature &Feature,
				FLabel &Label
			) override
		{
			FReal Distance2;
			FFeature Direction;
			const FReal One = 1;
			const FReal OneByKNearest = One / Parameters.KNearest;

			for (auto &Prototype : State.Prototypes)
			{
				Direction =  Prototype.Feature - Feature;
				Distance2 = Norm2(Direction);

				if(Distance2 > State.Neighbours.Active().Distance2)
				{
					State.Neighbours.Swap({Distance2, Direction, &Prototype});
				}
			}

			Label = {0};
			for (const auto &Neighbour : State.Neighbours)
			{
				Label += Neighbour.Prototype->Label;
			}
			Label *= OneByKNearest;
		}

		virtual FVoid _Train(
				const FLabel &Label,
				const FLabel &Target
			) override
		{
			FSize Class;
			FReal Delta;
			const FReal LearningRate = Parameters.LearningRate;
			const FReal One = 1;

			for(auto &Neighbour : State.Neighbours)
			{
				Class = Neighbour.Prototype->Class;
				Delta = Parameters.UseClassIndexAsLabel
					? LearningRate * (One - Target[Class] - Label[Class])
					: LearningRate * Norm(One - (Target - Label));	
				
				Neighbour.Prototype->Feature += (Delta * Neighbour.Direction);
			}
		}

		virtual FVoid _Optimize(
				const FSample &Sample
			) override
		{

		}

		virtual FVoid _Optimize(
				FVoid
			) override
		{

		}
	};
}