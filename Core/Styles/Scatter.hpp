#pragma once

#include <Types>
#include <Display>
#include <Iterator>
#include <Point>
#include <Functions>

namespace Display
{
    template<FSize Size, typename Type>
    struct TScatter;
    struct FScatterParameters;

    struct FScatterParameters
    {
        FReal Radius;
        TPoint2D<FReal> Origin, Min, Max, Scale;
        TColor<FReal> Color;
        FBool UseDataRange;

        static FScatterParameters Default(
                FVoid
            )
        {
            FScatterParameters Parameters;
            
            Parameters.Radius = 0.01;
            Parameters.Min = {-1, -1};
            Parameters.Max = {1, 1};
            Parameters.Origin = {0, 0};
            Parameters.Scale = {1, 1};
            Parameters.UseDataRange = True;
            Parameters.Color = {0.63f, 0.76f, 0.26f, 1.0f};
            
            return Parameters;
        }
    };

    struct FScatterStub
    {
        TPoint4D<FReal> Position;
        TColor<FReal> Color;
    };

    template<FSize Size, typename Type>
    struct TScatter : public FStyle
    {
        FScatterParameters RawParms;

        TScatter(
                FVoid
            )
        {
            SizeData = 3;
            auto *RawData = Make<FScatterStub>(SizeData);
            RawData[0].Position = {0, 0.5f, 0, 1};
            RawData[1].Position = {0, 0.5f, 0, 1};
            RawData[2].Position = {0, 0.5f, 0, 1};
            RawData[0].Color = {1, 0, 0, 1};
            RawData[1].Color = {0, 1, 0, 1};
            RawData[2].Color = {0, 0, 1, 1};
            Data = RawData;
            ClearData = True;
            
            auto *RawParameters =  Make<FScatterParameters>();
            *RawParameters = FScatterParameters::Default();
            Parameters = RawParameters;
            ClearParameters = True;
            
            Path = "Scatter.hlsl";
            _SizeOfData = sizeof(FScatterStub);
            _SizeOfParameters = 0;
            _SizeOfResult = 0;
            Pipeline[(FSize) EShader::PreCompute] = {0};
            Pipeline[(FSize) EShader::Vertex] = {True, False, False};
            Pipeline[(FSize) EShader::Tesselation] = {0};
            Pipeline[(FSize) EShader::Evaluation] = {0};
            Pipeline[(FSize) EShader::Geometry] = {0};
            Pipeline[(FSize) EShader::Fragment] = {True, False, False};
            Pipeline[(FSize) EShader::PostCompute] = {0};
        }

        ~TScatter(
                FVoid
            )
        {

        }
    };
}