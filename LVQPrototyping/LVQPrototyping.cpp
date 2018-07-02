#include <Types>
#include <LVQ1>
#include <Data>

using namespace LVQ;

using FLVQ1 = TLVQ1<8,3>;

FReturn main(
		FVoid
	)
{
	FLVQ1 LVQ1;
	
	FLVQ1::FPerformence Performance = {0};
	
	TData<FLVQ1::FFeature> Features(L"LVQ.Features.F8.Bin");
	TData<FLVQ1::FLabel> Targets(L"LVQ.Targets.L3.Bin"), Labels;
	
	auto Samples = LVQ1.Pair(Features, Targets);

	LVQ1.Parameters = {0.2f, 1, 3, True};
	LVQ1.Initialize();
	LVQ1.Train(Samples);
	LVQ1.Validate(Samples, Performance);
	LVQ1.Use(Features, Labels);
	LVQ1.Optimize();

	Labels.Save(L"LVQ.Labels.L3.Bin");
	return Success;
}