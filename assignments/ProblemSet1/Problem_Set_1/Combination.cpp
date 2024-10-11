// COS30008, Problem Set 1/3, 2024

#include "Combination.h"

Combination::Combination(size_t aN, size_t aK) :
	fN(aN), fK(aK)
{ }

size_t Combination::getN() const
{
	return fN;
}

size_t Combination::getK() const
{
	return fK;
}

unsigned long long Combination::operator()() const
{
	if (fK > fN)
	{
		return 0;
	}

	unsigned long long result = 1;

	size_t lK = fK;

	if (fK > fN / 2)
	{
		// this will reduce the number of iterations by choosing the smaller k
		lK = fN - fK; 
	}

	for (size_t i = 1; i <= lK; i++)
	{
		result *= fN - i + 1;
		result /= i;
	}

	return result;
}