#ifndef IMAGE_HPP
#define IMAGE_HPP

template<TypeImage, TypePixel>
struct image_t
{ 
	size_t W, H, N; TypePixel *d; TypeImage _raw;

	
	image_t(string_t s)
	{
		_raw = TypeImage(s);
	}
	
	image_t(W, H) : W(W), H(H)
	{
		N = W * H;
		d = (pixel_t *) malloc(_sz);
		if(!d) { exit(EXIT_FAILURE); }
	};
	
	~image_t()
	{
		if(d) { free(d); }
	};
	
	inline image_t & operator[](const indices_t &ind)
	{
		image_t ret(ind.N, 1);
		for (size_t n = 0; n < ind.N; ++n)
		{ 
			if(ind.d[n] >= N) { exit(EXIT_FAILURE); }
			ret.d[n] = d[ind.d[n]];
		}
		return ret;
	};
	
	inline image_t & operator()(const size_t ind, const size_t r)
	{
		image_t ret(r, r);
		for (size_t n = 0; n < ret.N; ++n)
		{ 
			if(ind.d[n] >= N) { exit(EXIT_FAILURE); }
			ret.d[n] = d[ind.d[n]];
		}
		return ret;
	};
	
};

#endif