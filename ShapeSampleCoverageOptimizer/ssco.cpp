#include <core>

typedef struct triangle_t { size_t p1, p2, p3; } triangle_t;
typedef struct shape_t { size_t N, _N; triangle_t *d; } shape_t;

typedef struct point_t { real_t x, y; } point_t;
typedef struct path_t { size_t N, _N; enum_t f; point_t *d; } path_t;
typedef struct compound_t { size_t N, _N; path_t *d; } compound_t;
typedef struct probe_t { point_t b; real_t r; } probe_t;

/*
 * allows fast lookup of intersection of points and simple surfaces
 * with kded shape.
 */
typedef struct kdtree_entry_t { size_t t; const point_t o; real_t r; } kdtree_entry_t;
typedef struct kdtree_t { size_t K, D; kdtree_entry_t *d; } kdtree_t;

/*
 *
 */

void triangulate(const compound_t &compound, const probe_t &probe, shape_t &shape)
{

}

void optimalpath(const shape_t &shape, const probe_t &probe, path_t &path)
{

}

/*
 * constaints compound surface is a subset of coverage surface, minimal covrage samples. 
 */
path_t ssco(const compound_t &domain, const probe_t &probe)
{
	size_t n, m, k;
	path_t sequence;
	shape_t shape;

	/* 
	 * triangulate the paths into one shape of only inbounds, simplify
	 * polygonal shape based on the probe radius total shape covarage of 
	 * original on simplyfication, now subdivide scale, and/or merge
	 * polygons to radius of probe to ensure total covrage.
	 */
	triangulate(domain, probe, shape);
	optimalpath(shape, probe, sequence);
}

int main()
{
	compound_t domain("product.domain");
	probe_t probe("machine.probe");

	std::cout << ssco(compound, probe);
}