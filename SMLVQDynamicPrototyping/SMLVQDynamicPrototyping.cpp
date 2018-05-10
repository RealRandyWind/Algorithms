#include <Types>
#include <Model>
#include <Data>

const TSequence<TReal> CrossValidation = {0.7, 0.2, 0.1};

const FSize FeatureCount = 30;
const FSize LabelCount = 30;

struct FParameters
{
	FReal Alpha;
};

using FModel = TModel<FeatureCount, LabelCount, FParameters>;

struct FPrototype
{
	FModel::Feature Mu, Omega;
	FReal W0, W1;
	FSize ID, _K;
};

FReturn main()
{
	FParameters Parameters;
	FModel:FPerformence BeforOptimize, AfterOptimize;
	TData<FModel::FLabel> Labels;
	
	TData<FModel::FSample> Samples("Model.Samples");
	TData<FModel::FFeature> Features("Model.Features");
	FModel Model("Name.Model");

	auto Partitions = Samples.Partition(CrossValidation);
	
	Model.Train(Partitions[0], Parameters);
	Model.Validate(Partitions[1], &BeforOptimize, Parameters);
	Model.Optimize(Partitions[2], Parameters);
	Model.Validate(Partitions[1], &AfterOptimize, Parameters);

	Model.Use(Features, &Labels, Parameters);

	return Success;
}