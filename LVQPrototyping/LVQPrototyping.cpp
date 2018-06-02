#include <Types>
#include <LVQModel>

using namespace LVQ;

FReturn main(
		FVoid
	)
{
	CLVQ1 LVQ1;

	LVQ1.Optimize({0.2f});
	return Success;
}