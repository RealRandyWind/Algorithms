#include <Types>
#include <LVQModel>

using namespace LVQ;

CModel::CModel(
		FVoid
	)
{
	return;
};

CModel::~CModel(
		FVoid
	)
{
	return;
};

FVoid CModel::Train(
		TIterator<FSample> Samples,
		FParameters Parameters
	)
{
	std::cout << "Training";
};

FVoid CModel::Use(
		TIterator<FFeature> Features,
		TData<FLabel> &Labels,
		FParameters Parameters
	)
{
	std::cout << "Using";
};

FVoid CModel::Validate(
		TIterator<FSample> Samples,
		FPerformence &Performance,
		FParameters Parameters
	)
{
	std::cout << "Validating";
};

FVoid CModel::Optimize(
		TIterator<FSample> Samples,
		FParameters Parameters
	)
{
	std::cout << "Optimizing Guided";
};

FVoid CModel::Optimize(
		FParameters Parameters
	)
{
	std::cout << "Optimizing";
};