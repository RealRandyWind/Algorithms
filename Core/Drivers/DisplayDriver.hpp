#pragma once

#include <Windows.h>
#include <Types>
#include <Sequence>
#include <Point>
#include <d3d11.h>
#include <d3dcompiler.h>

namespace Display
{
	static const FSize _MaxLayersPerWindow = 7;
	static const FSize _MaxWindows = 10;
	
	struct FStyle;
	struct FWindow;
	struct FView;
	struct FShader;

	enum class EShader : FSize
	{
		PreCompute = 0,
		Vertex,
		Tesselation,
		Evaluation,
		Geometry,
		Fragment,
		PostCompute,
		_Size
	};

	struct FShader
	{
		FBool Use, _Binded, CPU;
		ID3DBlob *_Blob;
		union
		{
			ID3D11ComputeShader *_PreCompute;
			ID3D11VertexShader *_Vertex;
			ID3D11HullShader *_Tessalation;
			ID3D11DomainShader *_Evaluation;
			ID3D11GeometryShader *_Geometry;
			ID3D11PixelShader *_Fragment;
			ID3D11ComputeShader *_PostCompute;
			IUnknown *_Unknown;
			FPointer (*_Call)(FPointer, FPointer, FPointer);
		};

		static FShader Default(
				FVoid
			)
		{
			FShader Shader = {0};
			return Shader;
		}
	};

	struct FStyle
	{
		FSize _ID, SizeData, SizeResult, _SizeOfParameters, _SizeOfData, _SizeOfResult, _Reference;
		FString Path;
		FShader Pipeline[(FSize)EShader::_Size];
		FBool ClearParameters, ClearData, ClearResult, _Binded;
		ID3D11InputLayout *_ParametersLayout, *_DataLayout, *_ResultLayout;
		ID3D11Buffer *_Parameters, *_Data, *_Result;
		FPointer Parameters, Data, Result;

		static FStyle Default(
				FVoid
			)
		{
			FStyle Style = {0};
			return Style;
		}
	};

	struct FView
	{
		FReal MaxDepth, MinDepth;
		
		static FView Default(
				FVoid
			)
		{
			FView View = {0};
			return View;
		}
	};

	struct FWindow
	{
		FSize _ID, Sampling, BufferCount, _Reference;
		TPoint2D<FReal> Position, Dimensions, Scale;
		TColor<FReal> Background;
		FBool FullScreen, Borderless, Visible, _Binded;
		FString Name, Title;
		FView View;
		HWND _Self;
		HINSTANCE _Handler;
		IDXGISwapChain *_Swap;
		ID3D11Device *_Device;
		ID3D11DeviceContext *_Context;
		ID3D11RenderTargetView *_Target;
		FWindow *_Parent;
		FStyle _Layers[_MaxLayersPerWindow];

		static FWindow Default(
				FVoid
			)
		{
			FWindow Window = {0};
			Window.Sampling = 4;
			Window.BufferCount = 1;
			Window.Position = {300, 300};
			Window.Dimensions = {1280, 720};
			Window.Visible = True;
			Window.Scale = {1, 1};
			Window.Background = {1, 1, 1, 1};
			Window.Name = "DefaultWindow";
			Window.Title = "Nameless";
			Window.View = FView::Default();
			return Window;
		}
	};
}

namespace Drivers
{
	class MDisplayDriver
	{
	public:
		FVoid Release(
				Display::FWindow &Window
			);
		
		FVoid Release(
				Display::FStyle &Style
			);
		
		FVoid Make(
				Display::FStyle Style,
				Display::FWindow &Window,
				FSize Layer = 0,
				FBool ClearStyle = True
			);

		FVoid Make(
				Display::FWindow &,
				Display::FWindow *Parent = NullPtr
			);

		FVoid Frame(
				const Display::FWindow &,
				FBool Clear = True
			);

		FReturn Wait(
				FVoid
			);

		~MDisplayDriver(
				FVoid
			);

		static MDisplayDriver *Instance(
				FVoid
			);

	private:
		Display::FWindow _Windows[Display::_MaxWindows];
		FSize _WindowID, _StyleID;

		static MDisplayDriver *_Instance;
		
		static LRESULT CALLBACK _WindowProcedure(
				HWND WindowHandler,
				UINT MessageCode,
				WPARAM WideParameter,
				LPARAM LongParameter
			);
		
		MDisplayDriver(
				FVoid
			);
	};
}
