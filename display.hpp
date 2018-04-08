#ifndef DISPLAY_HPP
#define DISPLAY_HPP

template<typename Type>
struct surface_t
{
	struct cursor_t { Type x, y, z, w; };
	
	struct cursor_t cursor, upper, lower;

	surface_t() {};
	~surface_t() {};
};

template<typename Type>
struct vertex_t
{
	struct vector_t { Type x, y, z, w; };
	struct color_t { Type r, g, b, a; };

	struct vector_t origin, up, left, right;
	struct color_t color;
};

#endif