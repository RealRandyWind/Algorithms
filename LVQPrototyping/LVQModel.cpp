#include <Types>
#include <LVQModel>

using namespace LVQ;

/* Public Fuctions */

CLVQ1::CLVQ1(
		FVoid
	)
{
	return;
};

CLVQ1::~CLVQ1(
		FVoid
	)
{
	return;
};

FVoid CLVQ1::Train(
		TIterator<FSample> Samples,
		FParameters Parameters
	)
{
	FLabel Label;

	LogStream << "Training... ";
	for (const auto &Sample : Samples)
	{
		_Use(Sample.Feature, Label);
		_Train(Label, Sample.Label, Parameters.Alpha);
	}
	LogStream << "Done\n";
};

FVoid CLVQ1::Use(
		TIterator<FFeature> Features,
		TData<FLabel> &Labels,
		FParameters Parameters)
{
	FSize N = 0;
	LogStream << "Using... ";
	Labels.Reserve(Features.Size());
	for (const auto &Feature : Features)
	{
		_Use(Feature, Labels[N]);
		++N;
	}
	LogStream << "Done\n";
};

FVoid CLVQ1::Validate(
		TIterator<FSample> Samples,
		FPerformence &Performance,
		FParameters Parameters
	)
{
	FLabel Label;
	LogStream << "Validating... ";
	for (const auto &Sample : Samples)
	{
		_Use(Sample.Feature, Label);
		_Validate(Label, Sample.Label, Performance);
	}
	LogStream << "Done\n";
};

FVoid CLVQ1::Optimize(
		TIterator<FSample> Samples,
		FParameters Parameters
	)
{
	LogStream << "Optimizing Guided... ";
	/* TODO */
	LogStream << "Done\n";
};

FVoid CLVQ1::Optimize(
		FParameters Parameters
	)
{
	LogStream << "Optimizing... ";
	/* TODO */
	LogStream << "Done\n";
};

/* Private Functions */

FVoid CLVQ1::_Use(
		const FFeature Feature,
		FLabel & Label
	)
{

}

FVoid CLVQ1::_Train(
		const FLabel & Label, 
		const FLabel & Target, 
		FReal Rate
	)
{

}

FVoid CLVQ1::_Validate(
		const FLabel & Label,
		const FLabel & Target,
		FPerformence & Performance
	)
{

}
