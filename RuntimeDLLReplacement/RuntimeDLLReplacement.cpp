#include <windows.h> 
#include <stdio.h> 
#include <Types>
#include "Library.hpp"

FReturn RuntimeLoadAPI(HINSTANCE &HAPI, ILibrary** PtrAPI)
{
	ILibrary::FunctionGetAPI PtrGetAPI;
	HINSTANCE _HAPI;

	if(!PtrAPI)
	{
		return Failure;
	}

	_HAPI = LoadLibrary("Library.dll");
	if(!_HAPI)
	{
		return Failure;
	}

	PtrGetAPI = (ILibrary::FunctionGetAPI) GetProcAddress(_HAPI, TEXT("GetAPI"));
	if(!PtrGetAPI)
	{
		FreeLibrary(_HAPI);
		return Failure;
	}

	*PtrAPI = PtrGetAPI();
	
	if(!HAPI)
	{
		FreeLibrary(HAPI);
	}
	HAPI = _HAPI;
	
	return Success;
}

FReturn main()
{
	HINSTANCE HAPI;
	ILibrary* API;

	if(RuntimeLoadAPI(HAPI,&API) != Success)
	{
		printf("FaildToLoadAPI\n");
		return Failure;
	}

	while(True)
	{
		printf("%f\n", API->MyFunction(1.0f));
		Sleep(3000);
		RuntimeLoadAPI(HAPI,&API);
	}

	FreeLibrary(HAPI);
	return Success;
}