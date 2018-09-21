#pragma once
#include <Types>
#include <Point>

struct FWindow
{
    TPoint2D<FReal> Position, Dimensions, Scale;
    TColor<FReal> Background;
    FBool FullScreen, Borderless;
    FString Name, Title;

    static FWindow Default(
            FVoid
        )
    {
        FWindow Window = {0};
        Window.Position = {300, 300};
        Window.Dimensions = {1280, 720};
        Window.Scale = {1, 1};
        Window.Background = {1, 1, 1, 1};
        Window.Name = "DefaultWindow";
        Window.Title = "Nameless";
        return Window;
    }
};

struct FSemantic
{
    FString Name;

    FBool _VertexData;
    FSize _SizeOf, _Rate;
};

struct FStyle
{
    FSize SizeData, SizeResult;
    FString Path;
    FPointer Parameters, Data, Result;
    
    FSize _SizeOfParameters, _SizeOfData, _SizeOfResult;
    FSemantic _ParameterSemantic, _DataSemantic, _ResultSemantic;

    static FStyle Default(
            FVoid
        )
    {
        FStyle Style = {0};
        return Style;
    }
};

class MDriver
{
public:
    FSize Make(
            FWindow &,
            FSize *
        );
    
    FSize Make(
            FStyle &,
            FSize,
            FSize Layer = 0
        );

    FVoid Frame(
            FSize,
            FBool Clear = True
        );

    FVoid Release(
            FSize
        );
    
    FReturn Wait(
            FVoid
        );
    
    ~MDriver(
            FVoid
        );

    static MDriver * Instance(
            FVoid
        );
    
private:
    static FPointer _State;

    MDriver(
            FVoid
        );
};