#include <Types>
#include <Point>

struct FDistraction;

struct FFocus
{
	FSize Encounters;
	FTime Time;
	FAgent &Subject;
};

template<FSize SizeFocus>
struct FState
{
	TPoint2D<FReal> Position, Direction, Orientation;
	FReal Speed, Acceleration;
	FFocus[SizeFocus] FocusList;
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