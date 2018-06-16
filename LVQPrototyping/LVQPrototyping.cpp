#include <Types>
#include <LVQModel>
#include <Data>
#include <Byte>
#include <Sequence>

using namespace LVQ;  

FReturn main(
		FVoid
	)
{
	CLVQ1 LVQ1;

	CLVQ1::FPerformence Performance = {0};
	CLVQ1::FParameters Parameters = {0.2f, True};
	
	TData<CLVQ1::FFeature> Features(L"LVQ.Features.Bin");
	TData<CLVQ1::FLabel> Targets(L"LVQ.Targets.Bin"), Labels;
	auto Samples = LVQ1.Pair(Features, Targets);

	LVQ1.Initialize(Parameters);
	LVQ1.Train(Samples, Parameters);
	LVQ1.Validate(Samples, Performance, Parameters);
	LVQ1.Use(Features, Labels, Parameters);
	LVQ1.Optimize(Parameters);

	Labels.Save(L"LVQ.Labels.Bin");
	return Success;
}