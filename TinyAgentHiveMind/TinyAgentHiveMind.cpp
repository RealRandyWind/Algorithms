#include <Types>
#include <Point>

struct FDistraction;

struct FFocus
{
	FSize Encounters;
	FTime Time;
	FAgent &Subject;
};

struct FState
{
	TPoint2D<FReal> Position, Direction, Orientation;
	FReal Speed, Acceleration;
	FFocus Focus;
};

struct FAgent
{
	FSize ID;
	FState &State;
};

FReturn main()
{
	while(True)
	{
		break;
	}
	return Success;
}