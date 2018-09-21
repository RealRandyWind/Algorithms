#include <Types>
#include <Sequence>
#include <Point>
#include <Data>

using FPoint = TPoint<2, FReal>;
using FTriangle = TPoint<6, FReal>;

enum class EPathOperation
{
	Union,
	Exclusion,
	_Size
};

struct FPath
{
	EPathOperation Operation;
	TSequence<FPoint> Points;
};

struct F2DTree
{
	FPoint Position;
	FTriangle &Triangle;
	struct F2DTree &XDim, &YDim;
};

using FShape = TSequence<FPath>;
using FProcedure = TProcedure<FShape, FMovement, FParameters>;

FReturn main()
{
	FParameters Parameters;
	TData<FMovement> Movements;

	TData<FShape> Shapes("Shapes.Data");
	FProcedure Procedure();
	Procedure.Use(Shapes, &Movements, Parameters);

	return Success;
}