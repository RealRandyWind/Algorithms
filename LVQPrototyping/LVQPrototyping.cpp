#include <Types>
#include <LVQModel>
#include <Data>

using namespace LVQ;

FReturn main(
		FVoid
	)
{
	CLVQ1 LVQ1;

	CLVQ1::FPerformence Performance = {0};
	
	TData<CLVQ1::FFeature> Features(L"LVQ.Features.Bin");
	TData<CLVQ1::FLabel> Targets(L"LVQ.Targets.Bin"), Labels;
	auto Samples = LVQ1.Pair(Features, Targets);

	LVQ1.Parameters = {0.2f, 1, 3, True};
	LVQ1.Initialize();
	LVQ1.Train(Samples);
	LVQ1.Validate(Samples, Performance);
	LVQ1.Use(Features, Labels);
	LVQ1.Optimize();

	Labels.Save(L"LVQ.Labels.Bin");
	return Success;
}