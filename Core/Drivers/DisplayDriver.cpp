#include <DisplayDriver>
#include <Functions>

#ifndef _ASSERT_ERROR
#define _ASSERT_ERROR(Code, Message) if(FAILED(Code)) { OutStream << "\nDriver Error" << "(" << std::hex << Code << ") : " << Message << "\n   at " << __FUNCSIG__ << "\n   in " << __FILE__ << "(" << (FSize)__LINE__ << ")\n"; exit(Failure); }
#endif

using namespace Drivers;

MDisplayDriver *MDisplayDriver::_Instance = NullPtr;

MDisplayDriver::MDisplayDriver(
        FVoid
    )
{
    _WindowID = 0;
}

MDisplayDriver::~MDisplayDriver(
        FVoid
    )
{
    FSize Index, End;
    
    End = Display::_MaxLayersPerWindow;
    for (Index = 0; Index < End; ++Index)
    {
        auto &Window = _Windows[Index];
        Release(Window);
    }
}

LRESULT CALLBACK MDisplayDriver::_WindowProcedure(
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

FVoid MDisplayDriver::Make(
        Display::FStyle Style,
        Display::FWindow &Window,
        FSize Layer,
        FBool ClearStyle
    )
{
    LPCWSTR Path;
    Display::FShader *Shader;
    D3D11_BUFFER_DESC DataDescriptor, ParameterDescriptor, ResultDescriptors;
    D3D11_MAPPED_SUBRESOURCE MapData, MapParameters, MapResult;
    HRESULT Error;

    if (Layer >= Display::_MaxLayersPerWindow)
    {
        return;
    }

    auto &_Style = Window._Layers[Layer];
    if (_Style._Binded)
    {
        Release(_Style);
    }

    if(Style._SizeOfParameters)
    {
        ZeroMemory(&ParameterDescriptor, sizeof(D3D11_BUFFER_DESC));

        ParameterDescriptor.Usage = D3D11_USAGE_DYNAMIC;
        ParameterDescriptor.ByteWidth = Style._SizeOfParameters;
        ParameterDescriptor.BindFlags = D3D11_BIND_CONSTANT_BUFFER; 
        ParameterDescriptor.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; 
        ParameterDescriptor.MiscFlags = 0;

        Error = Window._Device->CreateBuffer(&ParameterDescriptor, NullPtr, &Style._Parameters);
        _ASSERT_ERROR(Error, "Create Parameter Buffer");
        Error = Window._Context->Map(Style._Parameters, Null, D3D11_MAP_WRITE_DISCARD, Null, &MapParameters);
        _ASSERT_ERROR(Error, "Map Parameter Buffer");
        MapParameters.pData = _Copy(MapParameters.pData, Style.Parameters, ParameterDescriptor.ByteWidth);
    }

    if(Style._SizeOfData && Style.SizeData)
    {
        ZeroMemory(&DataDescriptor, sizeof(D3D11_BUFFER_DESC));

        DataDescriptor.Usage = D3D11_USAGE_DYNAMIC;
        DataDescriptor.ByteWidth = Style.SizeData * Style._SizeOfData;
        DataDescriptor.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        DataDescriptor.MiscFlags = 0;
        DataDescriptor.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

        Error = Window._Device->CreateBuffer(&DataDescriptor, Null, &Style._Data);
        _ASSERT_ERROR(Error, "Create Data Buffer");
        Error = Window._Context->Map(Style._Data, Null, D3D11_MAP_WRITE_DISCARD, Null, &MapData);
        _ASSERT_ERROR(Error, "Map Data Buffer");
        MapData.pData = _Copy(MapData.pData, Style.Data, DataDescriptor.ByteWidth);
        Window._Context->Unmap(Style._Data, Null);
    }

    if(Style._SizeOfResult && Style.SizeResult)
    {
        ZeroMemory(&ResultDescriptors, sizeof(D3D11_BUFFER_DESC));

        ResultDescriptors.Usage = D3D11_USAGE_DYNAMIC;
        ResultDescriptors.ByteWidth = Style.SizeResult * Style._SizeOfResult;
        ResultDescriptors.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        ResultDescriptors.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
        ResultDescriptors.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        
        Error = Window._Device->CreateBuffer(&ResultDescriptors, NullPtr, &Style._Result);
        _ASSERT_ERROR(Error, "Create Result Buffer");
        Error = Window._Context->Map(Style._Result, Null, D3D11_MAP_WRITE_DISCARD, Null, &MapData);
        _ASSERT_ERROR(Error, "Map Result Buffer");
    }
   
    Path = LPCWSTR(Style.Path.c_str());
    Shader = &Style.Pipeline[(FSize)Display::EShader::PreCompute];
    if(Shader->Use && !Shader->_Binded)
    {
        D3DCompileFromFile(Path, Null, Null, "PreComputeShader", "cs_5_0", Null, 
                Null, &Shader->_Blob, Null);
        Error = Window._Device->CreateComputeShader(Shader->_Blob->GetBufferPointer(),
                Shader->_Blob->GetBufferSize(), Null, &Shader->_PreCompute);
        _ASSERT_ERROR(Error, " Create PreCompute Shader");
        Window._Context->CSSetShader(Shader->_PreCompute, Null, Null);
        Shader->_Binded = True;
    }

    Shader = &Style.Pipeline[(FSize)Display::EShader::Vertex];
    if(Shader->Use && !Shader->_Binded)
    {
        D3DCompileFromFile(Path, Null, Null, "VertexShader", "vs_5_0", Null, 
                Null, &Shader->_Blob, Null);
        Error = Window._Device->CreateVertexShader(Shader->_Blob->GetBufferPointer(),
                Shader->_Blob->GetBufferSize(), Null, &Shader->_Vertex);
        _ASSERT_ERROR(Error, " Create Vertex Shader");
        Window._Context->VSSetShader(Shader->_Vertex, Null, Null);
        Shader->_Binded = True;
        D3D11_INPUT_ELEMENT_DESC ied[] =
        {
            {"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0},
        };
        Error = Window._Device->CreateInputLayout(ied, 2, Shader->_Blob->GetBufferPointer(), 
                Shader->_Blob->GetBufferSize(), &Style._DataLayout);
        _ASSERT_ERROR(Error, " Create Vertex Layout");
        Window._Context->IASetInputLayout(Style._DataLayout);
        UINT Offset = 0;
        UINT Stride = Style._SizeOfData;
        Window._Context->IASetVertexBuffers(0, 1, &Style._Data, &Stride, &Offset);
        Window._Context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    }

    Shader = &Style.Pipeline[(FSize)Display::EShader::Tesselation];
    if(Shader->Use && !Shader->_Binded)
    {
        D3DCompileFromFile(Path, Null, Null, "TesselationShader", "hs_5_0", Null, 
                Null, &Shader->_Blob, Null);
        Error = Window._Device->CreateHullShader(Shader->_Blob->GetBufferPointer(),
                Shader->_Blob->GetBufferSize(), Null, &Shader->_Tessalation);
        _ASSERT_ERROR(Error, " Create Tesselation Shader");
        Window._Context->HSSetShader(Shader->_Tessalation, Null, Null);
        Shader->_Binded = True;
    }

    Shader = &Style.Pipeline[(FSize)Display::EShader::Evaluation];
    if(Shader->Use && !Shader->_Binded)
    {
        D3DCompileFromFile(Path, Null, Null, "EvalutionShader", "ds_5_0", Null, 
                Null, &Shader->_Blob, Null);
        Error = Window._Device->CreateDomainShader(Shader->_Blob->GetBufferPointer(),
                Shader->_Blob->GetBufferSize(), Null, &Shader->_Evaluation);
        _ASSERT_ERROR(Error, " Create Evalution Shader");
        Window._Context->DSSetShader(Shader->_Evaluation, Null, Null);
        Shader->_Binded = True;
    }

    Shader = &Style.Pipeline[(FSize)Display::EShader::Geometry];
    if(Shader->Use && !Shader->_Binded)
    {
        D3DCompileFromFile(Path, Null, Null, "GeomentryShader", "gs_5_0", Null, 
                Null, &Shader->_Blob, Null);
        Error = Window._Device->CreateGeometryShader(Shader->_Blob->GetBufferPointer(),
                Shader->_Blob->GetBufferSize(), Null, &Shader->_Geometry);
        _ASSERT_ERROR(Error, " Create Geomentry Shader");
        Window._Context->GSSetShader(Shader->_Geometry, Null, Null);
        Shader->_Binded = True;
    }

    Shader = &Style.Pipeline[(FSize)Display::EShader::Fragment];
    if(Shader->Use && !Shader->_Binded)
    {
        D3DCompileFromFile(Path, Null, Null, "FragmentShader", "ps_5_0", Null, 
                Null, &Shader->_Blob, Null);
        Error = Window._Device->CreatePixelShader(Shader->_Blob->GetBufferPointer(),
                Shader->_Blob->GetBufferSize(), Null, &Shader->_Fragment);
        _ASSERT_ERROR(Error, " Create Fragment Shader");
        Window._Context->PSSetShader(Shader->_Fragment, Null, 0);
        Shader->_Binded = True;
    }

    Shader = &Style.Pipeline[(FSize)Display::EShader::PostCompute];
    if(Shader->Use && !Shader->_Binded)
    {
        D3DCompileFromFile(Path, Null, Null, "PostComputeShader", "cs_5_0", Null, 
                Null, &Shader->_Blob, Null);
        Error = Window._Device->CreateComputeShader(Shader->_Blob->GetBufferPointer(),
                Shader->_Blob->GetBufferSize(), Null, &Shader->_PostCompute);
        _ASSERT_ERROR(Error, " Create PostCompute Shader");
        Window._Context->CSSetShader(Shader->_PostCompute, Null, 0);
        Shader->_Binded = True;
    }

    Style._Binded = True;
    Window._Layers[Layer] = _Style;
}

FVoid MDisplayDriver::Make(
        Display::FWindow &Window,
        Display::FWindow *Parent
    )
{
    DXGI_SWAP_CHAIN_DESC Descriptor;
    D3D11_VIEWPORT ViewPort;
    ID3D11Texture2D *Texture;
    WNDCLASSEX WindowClass;
    HWND _Parent;
    HRESULT Error;

    _Parent = Parent ? Parent->_Self : Null;

    ZeroMemory(&WindowClass, sizeof(WNDCLASSEX));
    Window._Handler = GetModuleHandle(Null);
    
    WindowClass.cbSize = sizeof(WNDCLASSEX);
    WindowClass.style = CS_HREDRAW | CS_VREDRAW;
    WindowClass.lpfnWndProc = _WindowProcedure;
    WindowClass.hInstance = Window._Handler;
    WindowClass.hCursor = LoadCursor(NullPtr, IDC_ARROW);
    WindowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
    WindowClass.lpszClassName = Window.Name.c_str();

    RegisterClassEx(&WindowClass);
    Window._Self = CreateWindowEx(Null, Window.Name.c_str(), Window.Title.c_str(), WS_OVERLAPPEDWINDOW,
            Window.Position.X, Window.Position.Y, Window.Dimensions.X, Window.Dimensions.Y,
            _Parent, Null, Window._Handler, Null);
    Window._Binded = True;

    ZeroMemory(&Descriptor, sizeof(DXGI_SWAP_CHAIN_DESC));

    Descriptor.BufferCount = Window.BufferCount;
    Descriptor.BufferDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
    Descriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;   
    Descriptor.OutputWindow = Window._Self;
    Descriptor.SampleDesc.Count = Window.Sampling;
    Descriptor.Windowed = !Window.FullScreen;
    Descriptor.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    Error = D3D11CreateDeviceAndSwapChain(Null, D3D_DRIVER_TYPE_HARDWARE,
            Null, Null, Null, Null, D3D11_SDK_VERSION, 
            &Descriptor, &Window._Swap, &Window._Device, Null, &Window._Context);
    _ASSERT_ERROR(Error, "Create Swap Chain");

    Error = Window._Swap->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *) &Texture);
    _ASSERT_ERROR(Error, "Create Swap Buffer");
    Error = Window._Device->CreateRenderTargetView(Texture, Null, &Window._Target);
    _ASSERT_ERROR(Error, "Create Renter Target");
    Texture->Release();
    Window._Context->OMSetRenderTargets(1, &Window._Target, Null);

    ZeroMemory(&ViewPort, sizeof(D3D11_VIEWPORT));

    ViewPort.Height = Window.Dimensions.Y;
    ViewPort.Width = Window.Dimensions.X;
    ViewPort.MaxDepth = Window.View.MaxDepth;
    ViewPort.MinDepth = Window.View.MinDepth;
    ViewPort.TopLeftX = 0;
    ViewPort.TopLeftY = 0;
    
    Window._Context->RSSetViewports(1, &ViewPort);

    ShowWindow(Window._Self, Window.Visible);
}

FVoid MDisplayDriver::Release(
        Display::FWindow &Window
    )
{
    FSize Index, End;

    Window._Binded = False;

    if (Window._Swap)
    {
        Window._Swap->SetFullscreenState(False, Null);
        Window._Swap->Release();
        Window._Swap = Null;
    }

    if (Window._Device)
    {
        Window._Device->Release();
        Window._Device = Null;
    }

    if (Window._Context)
    {
        Window._Context->Release();
        Window._Context = Null;
    }

    if (Window._Target)
    {
        Window._Target->Release();
        Window._Target = Null;
    }

    End = Display::_MaxLayersPerWindow;
    for (Index = 0; Index < End; ++Index)
    {
        auto &Style = Window._Layers[Index];
        if (Style._Binded)
        {
            Release(Style);
        }
    }

    DestroyWindow(Window._Self);

    OutStream << "Window Destroyed\n";
}

FVoid MDisplayDriver::Release(
        Display::FStyle &Style
    )
{
    FSize Index, End;

    Style._Binded = False;

    if (Style._ParametersLayout)
    {
        Style._ParametersLayout->Release();
        Style._ParametersLayout = Null;
    }

    if (Style._DataLayout)
    {
        Style._DataLayout->Release();
        Style._DataLayout = Null;
    }

    if (Style._ResultLayout)
    {
        Style._ResultLayout->Release();
        Style._ResultLayout = Null;
    }

    if (Style._Data)
    {
        Style._Data->Release();
        Style._Data = Null;
    }

    if (Style._Parameters)
    {
        Style._Parameters->Release();
        Style._Parameters = Null;
    }

    if (Style._Result)
    {
        Style._Result->Release();
        Style._Result = Null;
    }

    if (Style.ClearParameters && Style.Parameters)
    {
        Remove(Style.Parameters);
    }
    Style.Parameters = Null;

    if (Style.ClearData && Style.Data)
    {
        Remove(Style.Data);
    }
    Style.Data = Null;

    if (Style.ClearResult && Style.Result)
    {
        Remove(Style.Result);
    }
    Style.Result = Null;

    End = (FSize) Display::EShader::_Size;
    for (Index = 0; Index < End; ++Index)
    {
        auto &Shader = Style.Pipeline[Index];
        if (!Shader._Binded)
        {
            continue;
        }

        if (Shader._Unknown)
        {
            Shader._Unknown->Release();
            Shader._Unknown = Null;
            Shader._Blob->Release();
            Shader._Blob = Null;
        }
    }
}

MDisplayDriver *MDisplayDriver::Instance(
        FVoid
    )
{
    if (!_Instance)
    {
        _Instance = new MDisplayDriver();
    }
    return _Instance;
}

FVoid MDisplayDriver::Frame(
        const Display::FWindow &Window,
        FBool Clear
    )
{
    if(Clear)
    {
         Window._Context->ClearRenderTargetView(Window._Target, Window.Background.Point.Data);
    }
    Window._Context->Draw(3, 0);
    auto Error = Window._Swap->Present(0,0);
    _ASSERT_ERROR(Error, "Swap Buffer");
}

FReturn MDisplayDriver::Wait(
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