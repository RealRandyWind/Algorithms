#include "Library.hpp"

ILibrary* CLibrary::Instance = nullptr;

CLibrary::CLibrary()
{
}

CLibrary::~CLibrary()
{
}

ILibrary* CLibrary::GetInstance()
{
	if (!Instance) { Instance = new CLibrary();  }
	return Instance;
}

float CLibrary::MyFunction(float Argument)
{
	return Argument + 3.0;
}

ILibrary* GetAPI()
{
	return CLibrary::GetInstance();
}