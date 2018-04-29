#ifndef CORE_HPP
#define CORE_HPP

#include <stdlib.h>
#include <cstdint>
#include <iostream>

#define SBOOLEAN(a) ((a) ? "true" : "false")

#define STRING_INIT_SIZE 8;
#define BITS_BYTE 8

#define nullptr nullptr
#define nullstr ""
#define nullchr '\0'
#define null 0

#define undefined -1
#define success EXIT_SUCCESS
#define failure EXIT_FAILURE
#define true true
#define false false
#define one 1
#define zero 0
#define two 2
#define half 0.5

typedef uint16_t enum_t;
typedef uint8_t raw_t;
typedef void* pointer_t;
typedef double real_t;
typedef size_t size_t;
typedef bool boolean_t;
typedef size_t natural_t;
typedef int integer_t;

typedef struct vector_t<size_t> indices_t;

template<typename Type>
inline Type max(const Type &lhs, const Type &rhs)
{
	return (lhs < rhs ? rhs : lhs);
};

template<typename Type>
inline Type min(const Type &lhs, const Type &rhs)
{
	return (lhs < rhs ? lhs : rhs);
};

template<typename Type>
inline Type swap(Type &lhs, Type &rhs)
{
	Type tmp;

	tmp = lhs;
	lhs = rhs;
	rhs = tmp;
	return lhs;
};

template<typename Type>
inline Type * mk(size_t N)
{
	Type *rhs;

	rhs = (Type *) malloc(N * sizeof(Type));
	if(!rhs) { exit(EXIT_FAILURE); }
	return rhs;
};

template<typename Type>
inline Type * rs(Type *rhs, size_t N)
{

	rhs = (Type *) realloc(rhs, N * sizeof(Type));
	if(!rhs) { exit(EXIT_FAILURE); }
	return rhs;
};

template<typename Type>
inline Type * rm(Type *d)
{
	free(d); return nullptr;
};

/* 
implement eindianess template argument byte_e FlipRead/FlipWrite/Flip 

enum class byte_e : enum_t
{
	noflip = 0,
	flipread = 1,
	flipwrite = 2,
	flip = flipread | flipwrite,
	_SizeEnum
};

template<size_t NBytes, byte_e EFlip = byte_e::noflip>
*/

template<size_t NBytes>
struct byte_t
{
	raw_t d[NBytes];

	inline size_t N()
	{
		return NBytes;
	};

	inline friend std::istream & operator>>(std::istream &is, byte_t<NBytes> &bytes)
	{
		size_t n;
		
		for (n = 0; n < NBytes; ++n) { is >> bytes.d[n]; }
		return is;
	};

	inline friend std::ostream & operator<<(std::ostream &os, const byte_t<NBytes> &bytes)
	{
		size_t n;

		for (n = 0; n < NBytes; ++n) { os << bytes.d[n]; }
		return os;
	};

	template<typename TypeLhs>
	inline operator TypeLhs() const
	{
		
		TypeLhs lhs;
		raw_t* plhs;
		size_t n, N;

		plhs = (raw_t *) &lhs;
		N = min(NBytes, sizeof(TypeLhs));
		for(n = 0; n < N; ++n) { plhs[n] = d[n]; }
		return *plhs;
	};
};

template<typename TypeSym>
struct string_t
{
	size_t _N, N; TypeSym *d;

	/* null constructor */
	string_t()
	{
		_N = N = 0;
		d = nullptr;
	};

	/* copy constructor */
	string_t(const string_t &rhs)
	{
		size_t n;

		_N = rhs._N; N = rhs.N;
		d = mk<TypeSym>(_N);
		for(n = 0; n < N; ++n) { d[n] = rhs.d[n]; };
	};
	
	/* move constructor */
	string_t(string_t &&rhs)
	{
		_N = rhs._N; N = rhs.N;
		d = rhs.d;
		rhs._N = rhs.N = 0;
		rhs.d = nullptr;
	};

	/* init constructor */
	string_t(const TypeSym *rhs) : string_t()
	{
		if(!rhs || !*rhs) { return; }

		_N = STRING_INIT_SIZE
		d = mk<TypeSym>(_N);

		for(N = 0; d[N] = rhs[N]; ++N)
		{
			if(N <= _N) { d = rs(d, _N += STRING_INIT_SIZE); }
		}

		d[N] = TypeSym();
	};

	~string_t()
	{ 
		d = rm(d);
	};

	inline friend std::istream & operator>>(std::istream &is, string_t &str)
	{
		size_t n;
		
		for (n = 0; n < str.N; ++n) { is >> str.d[n]; }
		return is;
	};

	inline friend std::ostream & operator<<(std::ostream &os, const string_t &str)
	{
		size_t n;

		for (n = 0; n < str.N; ++n) { os << str.d[n]; }
		return os;
	};
};

template<size_t NSize, typename Type>
struct point_t
{
	Type d[NSize];

	inline size_t N()
	{
		return NSize;
	};


	template<size_t NSizeLhs, typename TypeLhs>
	inline operator struct point_t<NSizeLhs, TypeLhs>() const
	{
		
		struct point_t<NSizeLhs, TypeLhs> lhs;
		size_t n, N;

		N = min(NSizeLhs, NSize);
		for(n = 0; n < N; ++n)
		{
			lhs.d[n] = static_cast<TypeLhs>(d[n]);
		}	
		return lhs;
	};
};

template<typename Type>
struct vector_t
{
	size_t N, _N; Type *d;

#ifdef CORE_EXTENDED_HPP
	inline TypeLhs & max()
	{
		Type tmp;
		size_t n;

		tmp = (N >= 1 ? d[0] : Type());
		for (n = 1; n < N; ++n)
		{
			tmp = max(tmp,d[n]);
		}
		return static_cast<TypeLhs>(tmp);
	};

	inline TypeLhs & min()
	{
		Type tmp;
		size_t n;

		tmp = (N >= 1 ? d[0] : Type());
		for (n = 1; n < N; ++n)
		{
			tmp = min(tmp,d[n]);
		}
		return static_cast<TypeLhs>(tmp);
	};

	inline TypeLhs & sum()
	{
		Type tmp;
		size_t n;

		tmp = Type();
		for (n = 0; n < N; ++n)
		{
			tmp += d[n];
		}
		return static_cast<TypeLhs>(tmp);
	};

	inline TypeLhs & prod()
	{
		Type tmp;
		size_t n;

		tmp = Type();
		++tmp;
		for (n = 0; n < N; ++n)
		{
			tmp *= d[n];
		}
		return static_cast<TypeLhs>(tmp);
	};

	inline struct vector_t<Type> & T()
	{
		size_t n, K;

		K = N - 1;
		for (n = 0; n < N / 2; ++n)
		{
			swap(d[n], d[K-n]);
		}
		return *this;
	};

	template<TypeLhs>
	inline TypeLhs & L()
	{
		Type tmp;
		size_t n;

		Type tmp = Type();
		for (n = 0; n < N; ++n)
		{
			tmp += d[n] * d[n];
		}
		return static_cast<TypeLhs>(tmp);
	};

	inline Type* begin()
	{
		return &d[0];
	};

	inline const Type* begin() const
	{
		return &d[0];
	};

	inline Type* end()
	{
		return &d[N];
	};

	inline const Type* end() const
	{
		return &d[N];
	};
#endif

	template<typename TypeLhs>
	inline operator struct vector_t<TypeLhs>() const
	{
		
		struct vector_t<TypeLhs> lhs;
		size_t m, M;

		M = min(lhs.N, N);
		for(m = 0; m < M; ++m)
		{
			lhs.d[m] = static_cast<TypeLhs>(d[m]);
		}
		return lhs;
	};
};

template<typename Type>
struct array_t
{
	size_t D, N, _N, _D, *dim; Type *d;

#ifdef CORE_EXTENDED_HPP
	inline TypeLhs & max()
	{
		Type tmp;
		size_t n;

		tmp = (N >= 1 ? d[0] : Type());
		for (n = 1; n < N; ++n)
		{
			tmp = max(tmp,d[n]);
		}
		return static_cast<TypeLhs>(tmp);
	};

	inline TypeLhs & min()
	{
		Type tmp;
		size_t n;

		tmp = (N >= 1 ? d[0] : Type());
		for (n = 1; n < N; ++n)
		{
			tmp = min(tmp,d[n]);
		}
		return static_cast<TypeLhs>(tmp);
	};

	inline TypeLhs & sum()
	{
		Type tmp;
		size_t n;

		tmp = Type();
		for (n = 0; n < N; ++n)
		{
			tmp += d[n];
		}
		return static_cast<TypeLhs>(tmp);
	};

	inline TypeLhs & prod()
	{
		Type tmp;
		size_t n;

		tmp = Type();
		++tmp;
		for (n = 0; n < N; ++n)
		{
			tmp *= d[n];
		}
		return static_cast<TypeLhs>(tmp);
	};

	template<TypeLhs>
	inline TypeLhs & L()
	{
		Type tmp;
		size_t n;

		Type tmp = Type();
		for (n = 0; n < N; ++n)
		{
			tmp += d[n] * d[n];
		}
		return static_cast<TypeLhs>(tmp);
	};

	inline Type * begin()
	{
		return &d[0];
	};

	inline const Type * begin() const
	{
		return &d[0];
	};

	inline Type * end()
	{
		return &d[N];
	};

	inline const Type * end() const
	{
		return &d[N];
	};
#endif
	
	template<typename TypeLhs>
	inline operator struct array_t<TypeLhs>() const
	{
		
		struct array_t<TypeLhs> lhs;
		size_t m, M;

		M = min(lhs.N, N);
		for(m = 0; m < M; ++m)
		{
			lhs.d[m] = static_cast<TypeLhs>(d[m]);
		}	
		return lhs;
	};
};


/* byte_t overloads */

template<typename TypeLhs, size_t NBytes>
inline boolean_t operator==(const TypeLhs &lhs, const byte_t<NBytes> &rhs)
{
	size_t n, N;
	const raw_t* plhs;

	plhs = (raw_t *) &lhs;
	N = min(NBytes, sizeof(TypeLhs));
	for(n = 0; n < N; ++n) { if(rhs.d[n] != plhs[n]) { return false; } }

	return true;
};

template<size_t NBytes, typename TypeRhs>
inline boolean_t operator==(const byte_t<NBytes> &lhs, const TypeRhs &rhs)
{
	return (rhs == lhs);
};

template<size_t NBytes, typename TypeLhs>
inline boolean_t operator!=(const TypeLhs &lhs, const byte_t<NBytes> &rhs)
{
	size_t n, N;
	const raw_t* plhs;

	plhs = (raw_t *) &lhs;
	N = min(NBytes, sizeof(TypeLhs));
	for(n = 0; n < N; ++n) { if(rhs.d[n] == plhs[n]) { return false; } }

	return true;
};

template<size_t NBytes, typename TypeRhs>
inline boolean_t operator!=(const byte_t<NBytes> &lhs, const TypeRhs &rhs)
{
	return (rhs != lhs);
};

template<size_t NBytes>
inline boolean_t operator!(const byte_t<NBytes> &rhs)
{
	size_t n;

	for(n = 0; n < NBytes; ++n) { if(rhs.d[n]) { return false; } }
	return true;
};

#endif