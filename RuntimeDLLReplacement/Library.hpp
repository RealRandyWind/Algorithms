#pragma once

#ifdef LIBRARY_EXPORTS  
#define LIBRARY_API __declspec(dllexport)
#else
#define LIBRARY_API __declspec(dllimport)
#endif

class ILibrary
{
public:
	using FunctionGetAPI = ILibrary* (*)();
	virtual float MyFunction(float Argument) = 0;
};

class LIBRARY_API CLibrary : public ILibrary
{
public:
	~CLibrary();
	static ILibrary* GetInstance();
private:
	CLibrary();
	static ILibrary* Instance;
public:
	virtual float MyFunction(float Argument) override;
};

extern "C" LIBRARY_API ILibrary* __cdecl GetAPI();
