#include <Driver>
#include <Sequence>
#include <Functions>
#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#ifndef _ASSERT_DISPLAY
#define _ASSERT_DISPLAY(Code, Message) if(FAILED(Code)) { OutStream << "\nDriver Error" << "(" << std::hex << Code << ") : " << Message << "\n   at " << __FUNCSIG__ << "\n   in " << __FILE__ << "(" << (FSize)__LINE__ << ")\n"; exit(Failure); }
#endif

struct _MDriver
{
    enum class _EState : FSize
    {
        Window,
        Shader,
        Style,
        _Size
    };

    enum class _EShader : FSize
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

    struct _IUnknown
    {
         _IUnknown(
                FVoid
            ) {};
        
        ~_IUnknown(
                FVoid
            ) {};

        virtual FVoid Release(
                FVoid
            ) {};
    };

    struct _FWindow : _IUnknown
    {
        TColor<FReal> _Color;
        FSize _Sampling, _BufferCount;
        HWND _Self;
        HINSTANCE _Handler;
        LPCSTR _Name;
        IDXGISwapChain *_Swap;
        ID3D11Device *_Device;
        ID3D11DeviceContext *_Context;
        ID3D11RenderTargetView *_Target;
        _FWindow *_Parent;

        _FWindow(
                FVoid
            ) {};
        
        ~_FWindow(
                FVoid
            ) {};

        virtual FVoid Release(
                FVoid
            ) override;
    };

    struct _FShader : _IUnknown
    {
        _EShader _Type;
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

        _FShader(
                FVoid
            ) {};
        
        ~_FShader(
                FVoid
            ) {};

        virtual FVoid Release(
                FVoid
            ) override;
    };

    struct _FStyle : _IUnknown
    {
        FSize _SizeOfParameters, _SizeOfData, _SizeOfResult;
        ID3D11InputLayout *_ParametersLayout, *_DataLayout, *_ResultLayout;
        ID3D11Buffer *_Parameters, *_Data, *_Result;
        FSemantic _ParameterSemantic, _DataSemantic, _ResultSemantic;
        TSequence<FSize> _Shaders;

        _FStyle(
                FVoid
            ) {};
        
        ~_FStyle(
                FVoid
            ) {};

        virtual FVoid Release(
                FVoid
            ) override;
    };

    struct _FState : _IUnknown
    {
        FBool _Free;
        _EState _Type;
        union
        {
            FSize _ID;
            _FWindow _Window;
            _FStyle _Style;
            _FShader _Shader;
            _IUnknown _Unknown;
        };

         _FState(
                FVoid
            ) {};
        
        ~_FState(
                FVoid
            ) {};

        virtual FVoid Release(
                FVoid
            ) override;
    };

    static const FSize MaxStates = 128;
    _FState States[MaxStates];
    FSize NextID, MaxID;
    MDriver *Instance;

    _MDriver(
            FVoid
        );
    
    ~_MDriver(
            FVoid
        );

    _FState & Claim(
            FVoid
        );
    
     _FState & Claim(
            FSize
        );
    
    FVoid Release(
            FSize
        );
    
    static LRESULT CALLBACK _WindowProcedure(
            HWND WindowHandler,
            UINT MessageCode,
            WPARAM WideParameter,
            LPARAM LongParameter
        );
};

_MDriver::_MDriver(
            FVoid
        )
{

}
    
_MDriver::~_MDriver(
        FVoid
    )
{
    FSize Index, End;
    
    End = MaxStates;
    for(Index = 0; Index < End; ++Index)
    {
        States[Index].Release();
    }
}

_MDriver::_FState & _MDriver::Claim(
        FVoid
    )
{
    FSize StateID;

    if(MaxID >= MaxStates)
    {
        exit(Failure);
    }

    if (NextID >= MaxID)
    {
        StateID = MaxID++;
        NextID = MaxID;
        States[StateID]._ID = StateID;
    }
    else
    {
        StateID = NextID;
        Swap(States[NextID]._ID, NextID);
    }
    return States[StateID];
}

_MDriver::_FState & _MDriver::Claim(
        FSize StateID
    )
{
    if(StateID >= MaxID)
    {
        exit(Failure);
    }
    return States[StateID];
}

FVoid _MDriver::Release(
        FSize StateID
    )
{
    if (StateID >= MaxID)
    {
        exit(Failure);
    }

    auto &State = States[StateID];
    if (State._Free)
    {
        return;
    }
    State.Release();
    State._ID = NextID;
    NextID = StateID;
}

LRESULT CALLBACK _MDriver::_WindowProcedure(
        HWND WindowHandler,
        UINT MessageCode,
        WPARAM WideParameter,
        LPARAM LongParameter
    )
{
    switch (MessageCode)
    {
        case WM_DESTROY :
        {
            PostQuitMessage(0);
            return 0;
        } break;
    }

    return DefWindowProc(WindowHandler, MessageCode, WideParameter, LongParameter);
}


FVoid _MDriver::_FWindow::Release(
        FVoid
    )
{
    if (_Swap)
    {
        _Swap->SetFullscreenState(False, Null);
        _Swap->Release();
        _Swap = Null;
    }

    if (_Device)
    {
        _Device->Release();
        _Device = Null;
    }

    if (_Context)
    {
        _Context->Release();
        _Context = Null;
    }

    if (_Target)
    {
        _Target->Release();
        _Target = Null;
    }

    if (_Self)
    {
        DestroyWindow(_Self);
        _Self = Null;
    }

    _Parent = Null;
}

FVoid _MDriver::_FStyle::Release(
        FVoid
    )
{
    if (_ParametersLayout)
    {
        _ParametersLayout->Release();
        _ParametersLayout = Null;
    }

    if (_DataLayout)
    {
        _DataLayout->Release();
        _DataLayout = Null;
    }

    if (_ResultLayout)
    {
        _ResultLayout->Release();
        _ResultLayout = Null;
    }

    if (_Parameters)
    {
        _SizeOfParameters = 0;
        _Parameters->Release();
        _Parameters = Null;
    }

    if (_Data)
    {
        _SizeOfData = 0;
        _Data->Release();
        _Data = Null;
    }

    if (_Result)
    {
        _SizeOfResult = 0;
        _Result->Release();
        _Result = Null;
    }
}

FVoid _MDriver::_FShader::Release(
        FVoid
    )
{
    if (_Blob)
    {
        _Blob->Release();
        _Blob = Null;
    }

    if (_Unknown)
    {
        _Unknown->Release();
        _Unknown = Null;
    }
}

FVoid _MDriver::_FState::Release(
        FVoid
    )
{
    if (!_Free)
    {
        _Unknown.Release();
    }
    _Free = True;
}

FPointer MDriver::_State = NullPtr;

MDriver::MDriver(
            FVoid
        )
{

}

MDriver::~MDriver(
            FVoid
        )
{
    
}

MDriver * MDriver::Instance(
        FVoid
    )
{
    _MDriver *Driver;

    if (!_State)
    {
        Driver = new _MDriver();
        Driver->Instance = new MDriver();
        _State = Driver;
    }
    Driver = (_MDriver *) _State;
    return Driver->Instance;
}

FVoid MDriver::Release(
        FSize StateID
    )
{
    _MDriver *Driver = (_MDriver *) _State;
    Driver->Release(StateID);
}

FReturn MDriver::Wait(
        FVoid
    )
{
    MSG Message;
    
    while(true)
    {
        while(GetMessage(&Message, Null, 0, 0))
        {
            TranslateMessage(&Message);
            DispatchMessage(&Message);
        }

        if(Message.message = WM_QUIT)
        {
            break;
        }
    }
    return Success;
}

FVoid MDriver::Frame(
        FSize WindowID,
        FBool Clear
    )
{
    _MDriver *Driver = (_MDriver *) _State;
    auto &State = Driver->Claim(WindowID);
    if (State._Type != _MDriver::_EState::Window)
    {
        return;
    }
    auto &Window = State._Window;
    if(Clear)
    {
         Window._Context->ClearRenderTargetView(Window._Target, Window._Color.Point.Data);
    }
    auto Error = Window._Swap->Present(0,0);
    _ASSERT_DISPLAY(Error, "Swap Buffer");
}

 FSize MDriver::Make(
        FStyle &Style,
        FSize WindowID,
        FSize Layer
    )
{
    return 0;
}

FSize MDriver::Make(
        FWindow &Window,
        FSize *PtrParentID
    )
{
    DXGI_SWAP_CHAIN_DESC Descriptor;
    D3D11_VIEWPORT ViewPort;
    ID3D11Texture2D *Texture;
    WNDCLASSEX WindowClass;
    HWND _Parent;
    HRESULT Error;

    _MDriver *Driver = (_MDriver *) _State;
    auto &State = Driver->Claim();
    State._Type = _MDriver::_EState::Window;
    auto &_Window = State._Window;

    _Parent = Null;

    ZeroMemory(&WindowClass, sizeof(WNDCLASSEX));
    _Window._Handler = GetModuleHandle(Null);
    
    WindowClass.cbSize = sizeof(WNDCLASSEX);
    WindowClass.style = CS_HREDRAW | CS_VREDRAW;
    WindowClass.lpfnWndProc = _MDriver::_WindowProcedure;
    WindowClass.hInstance = _Window._Handler;
    WindowClass.hCursor = LoadCursor(Null, IDC_ARROW);
    WindowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
    WindowClass.lpszClassName = Window.Name.c_str();

    RegisterClassEx(&WindowClass);
    _Window._Self = CreateWindowEx(Null, Window.Name.c_str(), Window.Title.c_str(), WS_OVERLAPPEDWINDOW,
            Window.Position.X, Window.Position.Y, Window.Dimensions.X, Window.Dimensions.Y,
            _Parent, Null, _Window._Handler, Null);

    ZeroMemory(&Descriptor, sizeof(DXGI_SWAP_CHAIN_DESC));

    Descriptor.BufferCount = 1;
    Descriptor.BufferDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
    Descriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;   
    Descriptor.OutputWindow = _Window._Self;
    Descriptor.SampleDesc.Count = 4;
    Descriptor.Windowed = !Window.FullScreen;
    Descriptor.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    Error = D3D11CreateDeviceAndSwapChain(Null, D3D_DRIVER_TYPE_HARDWARE,
            Null, Null, Null, Null, D3D11_SDK_VERSION, 
            &Descriptor, &_Window._Swap, &_Window._Device, Null, &_Window._Context);
    _ASSERT_DISPLAY(Error, "Create Swap Chain");

    Error = _Window._Swap->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *) &Texture);
    _ASSERT_DISPLAY(Error, "Create Swap Buffer");
    Error = _Window._Device->CreateRenderTargetView(Texture, Null, &_Window._Target);
    _ASSERT_DISPLAY(Error, "Create Renter Target");
    Texture->Release();
    _Window._Context->OMSetRenderTargets(1, &_Window._Target, Null);

    ZeroMemory(&ViewPort, sizeof(D3D11_VIEWPORT));

    ViewPort.Height = Window.Dimensions.Y;
    ViewPort.Width = Window.Dimensions.X;
    ViewPort.MaxDepth = 0;
    ViewPort.MinDepth = 0;
    ViewPort.TopLeftX = 0;
    ViewPort.TopLeftY = 0;
    
    _Window._Context->RSSetViewports(1, &ViewPort);
    _Window._Color = Window.Background;

    ShowWindow(_Window._Self, True);
    return 0;
}