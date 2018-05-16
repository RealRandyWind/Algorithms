#include <Types>
#include <LVQModel>

FReturn main(FVoid)
{
	LVQ::CModel Model;

	Model.Optimize({0.4f});

	return Success;
}