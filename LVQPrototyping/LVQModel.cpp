#include <Types>
#include <LVQModel>
#include <Math>

using namespace LVQ;

/* Protected Functions */

FVoid CLVQ1::_Initialize(
		const FParameters &Parameters
	)
{

}

FVoid CLVQ1::_Use(
		const FFeature &Feature,
		FLabel &Label,
		const FParameters &Parameters
	)
{
	FReal Distance;
	FFeature Direction;
	
	for ( const auto &Prototype : Prototypes)
	{
		Direction =  Prototype.Feature - Feature;
		Distance = Norm2(Direction);
		if(Distance > Neighbour.Distance)
		{
			Neighbour.Direction = Direction;
			Neighbour.Distance = Distance;
			Neighbour.Prototype = Prototype;
		}
	}
	Label = Neighbour.Prototype.Label;
}

FVoid CLVQ1::_Train(
		const FLabel &Label, 
		const FLabel &Target,
		const FParameters &Parameters
	)
{
	const FSize Class = Neighbour.Prototype.Class;
	const FReal One = 1; 
	const FReal Delta = Parameters.UseClassIndexAsLabel
		? Parameters.Alpha * (One - Target[Class] - Label[Class])
		: Parameters.Alpha * Norm(One - (Target - Label));	
	
	Neighbour.Prototype.Feature += (Delta * Neighbour.Direction);
}

FVoid CLVQ1::_Validate(
		const FLabel &Label,
		const FLabel &Target,
		FPerformence &Performance,
		const FParameters &Parameters
	)
{
	
}

FVoid CLVQ1::_Optimize(
		const FSample &Sample,
		const FParameters &Parameters
	)
{

}

FVoid CLVQ1::_Optimize(
		const FParameters &Parameters
	)
{

}