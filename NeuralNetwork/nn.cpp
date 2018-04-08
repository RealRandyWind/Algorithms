#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <core>


typedef struct parameters_t { real_t alpha, beta, epsilon, lamda; } parameters_t;
typedef struct feature_t { size_t N; real_t *d; } feature_t;
typedef struct samples_t { size_t N; feature_t *input, *target; real_t alpha; } samples_t;

typedef struct neuron_t { size_t N; real_t *weights; } neuron_t;
typedef struct layer_t { size_t N; neuron_t *neurons; real_t bias; } layer_t;

struct network_t
{
	size_t N; layer_t *layers;
};

typedef point_t<1, uint16_t> pixel_t;
typedef point_t<1, real_t> value_t;

int main()
{
	data_t<pixel_t> data("test.tif");
	parameters_t parameters("test.parameters");
	samples_t tsamples("ttest.samples");
	samples_t vsamples("vtest.samples");
	network_t network("test.network");

	network.train(tsamples, parameters);
	network.validate(vsamples, parameters);
	network.optimize(parameters);
	cout << network.use(data, parameters);

	return EXIT_SUCCESS;
}