using FPoint2D = TPoint2D<FReal>;

enum class EPathOperation
{
	Union,
	Exclusion,
	_Size
};

struct FTriangle2D
{
	FPoint2D P1, P2, P3;
};

struct FPath
{
	EPathOperation Operation;
	TSequence<FPoint2D> Points;
};

struct FParameters
{
	FReal ProbeRadius;
	FPoint2D ProbeStart;
};

struct F2DTree
{
	FPoint2D Position;
	FTriangle2D &Triangle;
	struct F2DTree &XDim, &YDim;
};

using FMovement = TSequence<FPoint2D>;
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