#include <core>
#include <tiff>

typedef struct prototype_t { real_t rho; vector_t<real_t> mu, v; } prototype_t;

int main()
{
	tiff_t tiff("test.tif");
	print(tiff);
	return EXIT_SUCCESS;
}