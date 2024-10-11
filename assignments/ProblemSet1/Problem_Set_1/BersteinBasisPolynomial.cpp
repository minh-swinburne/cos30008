// COS30008, Problem Set 1/4, 2024

#include "BernsteinBasisPolynomial.h"

#include <cmath>

BernsteinBasisPolynomial::BernsteinBasisPolynomial(unsigned int aV, unsigned int aN) :
	fFactor(aN, aV)
{ }

double BernsteinBasisPolynomial::operator()(double aX) const
{
	size_t lN = fFactor.getN();
	size_t lV = fFactor.getK();

	return fFactor() * pow(aX, lV) * pow(1 - aX, lN - lV);
}