#include <Types>
#include <LVQModel>
#include <Math>

using namespace LVQ;

/* Protected Functions */

FVoid CLVQ1::_Initialize(
		FVoid
	)
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

FVoid CLVQ1::_Use(
		const FFeature &Feature,
		FLabel &Label
	)
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

FVoid CLVQ1::_Train(
		const FLabel &Label,
		const FLabel &Target
	)
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

/*
FVoid CLVQ1::_Validate(
		const FLabel &Label,
		const FLabel &Target,
		FPerformence &Performance,
		const FParameters &Parameters
	)
{
	const FLabel Mean = Target - Label;
	const FLabel SD = Mean * Mean;
	const FLabel Skew = Mean * SD;
	const FReal One = 1;
	const FSize N = Performance.N;
	const FReal OneByN = One / N;

	Performance.ErrorMin = Min(Performance.ErrorMin, Mean);
	Performance.ErrorMax = Max(Performance.ErrorMax, Mean);
	Performance.ErrorMean = OneByN * ((N - One) * Performance.ErrorMean + Mean);
	Performance.ErrorSD = OneByN * ((N - One) * Performance.ErrorSD + SD);
	Performance.ErrorSkew = OneByN * ((N - One) * Performance.ErrorSkew + Skew);
	++Performance.N;
}
*/

FVoid CLVQ1::_Optimize(
		const FSample &Sample
	)
{

}

FVoid CLVQ1::_Optimize(
		FVoid
	)
{

}