#include <Types>
#include <Driver>
#include <Point>

struct FTriangle : public FStyle
{
    FTriangle(
            FVoid
        )
    {
        Path = "Triangle.hlsl";
        Data = _Make(sizeof(TPoint4D<FReal>) * 6);
        SizeData = 6;

        auto Vertex = (TPoint4D<FReal> *) Data;
        Vertex[0].Point = {0, .5f, 0, 1};
        Vertex[1].Point = {1, 0, 0, 1};
        Vertex[2].Point = {.45f , -.5f, 0, 1};
        Vertex[3].Point = {0, 1, 0, 1};
        Vertex[4].Point = {-.45f , -.5f, 0, 1};
        Vertex[5].Point = {0, 0, 1, 1};

        _DataSemantic = { "VERTEX", True, sizeof(TPoint4D<FReal>), 0 };
        _SizeOfData = sizeof(TPoint4D<FReal>);
    }

    ~FTriangle(
            FVoid
        )
    {
        _Remove(Data);
    }
};

FReturn main(
		FVoid
	)
{
    FStyle Triangle = FTriangle();

    auto Window = FWindow::Default();
    auto Driver = MDriver::Instance();
    auto WindowID = Driver->Make(Window,Null);
    auto StyleID = Driver->Make(Triangle, WindowID);
    Driver->Frame(WindowID);
    return Driver->Wait();
}