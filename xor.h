#ifndef _ESTRING_H
#define _ESTRING_H

#pragma once
#include "stdafx.h"

template<size_t N, size_t I>
struct XORImpl
{
	static char* XOR(char(&data)[N], char k)
	{
		data[I] ^= k;
		return XORImpl<N, I - 1>::XOR(data, k);
	}
};

template<size_t N>
struct XORImpl<N, 0>
{
	static char* XOR(char(&data)[N], char k)
	{
		data[0] ^= k;
		return data;
	}
};

template<size_t N> char* XOR(char(&data)[N], char k)
{
	return XORImpl<N, N - 2>::XOR(data, k);
}

template<size_t N> std::string XORRuntime(char(&data)[N], char k)
{
	char* res = new char[N];
	for (size_t i = 0; i < N - 1; ++i)
		res[i] = data[i] ^ k;
	res[N - 1] = 0;

	std::string ret(res);
	delete[] res;

	return ret;
}

#endif