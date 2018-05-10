using FPoint = TPoint<2, FReal>;
using FTriangle = TPoint<9, FReal>;

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

struct FParameters
{
	FReal ProbeRadius;
	FPoint ProbeStart;
};

struct F2DTree
{
	FPoint Position;
	FTriangle &Triangle;
	struct F2DTree &XDim, &YDim;
};

using FMovement = TSequence<FPoint>;
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