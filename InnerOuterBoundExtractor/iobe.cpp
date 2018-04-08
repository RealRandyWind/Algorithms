#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double real_t;
typedef size_t size_t;

typedef struct point_t { real_t x, y, z, w; } point_t;
typedef struct parms_t { real_t alpha, radius; } parms_t;
typedef struct data_t { size_t N; point_t *d; } data_t;
typedef struct bounds_t { data_t inner, outer; real_t error; } bounds_t;

int scanpoint(point_t *ptrpoint )
{
	point_t point;

	if(!ptrpoint) { exit(EXIT_FAILURE); }

	if(!scanf("%f %f %f %f", 
		&point.x, &point.y, &point.z, 
		&point.w)) { return 0; }
	
	(*ptrpoint) = point;
	return 1;
}

int scanparms(parms_t *ptrparms)
{
	parms_t parms;

	if(!ptrparms) { exit(EXIT_FAILURE); }

	if(!scanf("%f %f", 
		&parms.alpha, &parms.radius)) { return 0; }

	(*ptrparms) = parms;
	return 1;
}

int scandata(data_t *ptrdata)
{
	size_t n;
	data_t data;

	if(!ptrdata) { exit(EXIT_FAILURE); }

	if(!scanf("%d", &data.N)) { return 0; }
	data.d = (point_t *) malloc(N * sizeof(point_t));
	for (n = 0; n < data.N; ++n)
	{
		if(!scanpoint(&data.d[n])) { free(data.d); return 0; }
	}

	(*ptrdata) = data;
	return 1;
}

void printpoint(const point_t point)
{
	printf("%f %f %f %f", point.x, point.y, point.z, point.w);
}

void printresult(const bounds_t result)
{
	size_t n;

	printf("%d\n", result.inner.N);
	if(result.inner.N) { printpoint(result.inner.d[0]) }
	for (n = 1; n < result.inner.N; ++n) { printf("\n"); printpoint(result.inner.d[n]); }

	if(result.outer.N) { printpoint(result.outer.d[0]) }
	for (n = 1; n < result.outer.N; ++n) { printf("\n"); printpoint(result.outer.d[n]); }
}

void iobe(const data_t data, const parms_t parms, bounds_t* ptrresult)
{
	bounds_t result;

	if(!ptrresult) { exit(EXIT_FAILURE); }

	/* kd tree can reduce the NN seach space, construction of a kd wel be n*log(n-1) */

	/* TODO implment methods */

	(*ptrresult) = result;
}

int main()
{
	parms_t parms;
	data_t data;
	bounds_t result;

	if(!scanparms(&parms) || !scandata(&data)) { exit(EXIT_FAILURE); }
	iobe(data, parms, &result);
	printresult(result);

	return EXIT_SUCCESS;
}