#ifndef CORE_EXTENDED_HPP
#define CORE_EXTENDED_HPP

#include "core.hpp"

/* vector_t overloads */
template<typename TypeLhs, TypeRhs>
inline struct vector_t<TypeLhs> & operator+=(struct vector_t<TypeLhs> &lhs, const struct vector_t<TypeRhs> &rhs)
{
	size_t n, N;

	N = min(lhs.N, rhs.N);
	for (n = 0; n < N; ++n)
	{
		lhs.d[n] += static_cast<TypeLhs>(rhs.d[n]);
	}
	return lhs;
};

template<typename TypeLhs, TypeRhs>
inline struct vector_t<TypeLhs> & operator-=(struct vector_t<TypeLhs> &lhs, const struct vector_t<TypeRhs> &rhs)
{
	size_t n, N;

	N = min(lhs.N, rhs.N);
	for (n = 0; n < N; ++n)
	{
		lhs.d[n] -= static_cast<TypeLhs>(rhs.d[n]);
	}
	return lhs;
};

template<typename TypeLhs, TypeRhs>
inline struct vector_t<TypeLhs> & operator*=(struct vector_t<TypeLhs> &lhs, const struct vector_t<TypeRhs> &rhs)
{
	size_t n, N;

	N = min(lhs.N, rhs.N);
	for (n = 0; n < N; ++n)
	{
		lhs.d[n] = lhs.d[n] * static_cast<TypeLhs>(rhs.d[n]);
	}
	return lhs;
};

template<typename TypeLhs, TypeRhs>
inline struct vector_t<TypeLhs> & operator*=(struct vector_t<TypeLhs> &lhs, const TypeRhs &rhs)
{
	size_t n, N;

	N = lhs.N;
	for (n = 0; n < N; ++n)
	{
		lhs.d[n] *= static_cast<TypeLhs>(rhs);
	}
	return lhs;
};


/* array_t overloads */
template<typename TypeLhs, TypeRhs>
inline struct array_t<TypeLhs> & operator+=(struct array_t<TypeLhs> &lhs, const struct array_t<TypeRhs> &rhs)
{
	size_t n, N;

	N = min(lhs.N, rhs.N);
	for (n = 0; n < N; ++n)
	{
		lhs.d[n] += static_cast<TypeLhs>(rhs.d[n]);
	}
	return lhs;
};

template<typename TypeLhs, TypeRhs>
inline struct array_t<TypeLhs> & operator-=(struct array_t<TypeLhs> &lhs, const struct array_t<TypeRhs> &rhs)
{
	size_t n, N;

	N = min(lhs.N, rhs.N);
	for (n = 0; n < N; ++n)
	{
		lhs.d[n] -= static_cast<TypeLhs>(rhs.d[n]);
	}
	return lhs;
};

template<typename TypeLhs, TypeRhs>
inline struct array_t<TypeLhs> & operator*=(struct array_t<TypeLhs> &lhs, const struct array_t<TypeRhs> &rhs)
{
	size_t n, N;

	N = min(lhs.N, rhs.N);
	for (n = 0; n < N; ++n)
	{
		lhs.d[n] = lhs.d[n] * static_cast<TypeLhs>(rhs.d[n]);
	}
	return lhs;
};

template<typename TypeLhs, TypeRhs>
inline struct array_t<TypeLhs> & operator*=(struct array_t<TypeLhs> &lhs, const TypeRhs &rhs)
{
	size_t n, N;

	N = lhs.N;
	for (n = 0; n < N; ++n)
	{
		lhs.d[n] *= static_cast<TypeLhs>(rhs);
	}
	return lhs;
};

#endif