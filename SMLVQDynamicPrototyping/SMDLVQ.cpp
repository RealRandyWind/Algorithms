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

	TIterator<> Partitions = Samples.Partition({0.8, 0.2}, 100);
	
	Model.Train(Partitions[0], Parameters);
	Model.Validate(Partitions[1], &BeforOptimize, Parameters);
	Model.Optimize(Parameters);
	Model.Validate(Partitions[1], &AfterOptimize, Parameters);

	Model.Use(Features.Iterator(), &Labels, Parameters);

	return Success;
}