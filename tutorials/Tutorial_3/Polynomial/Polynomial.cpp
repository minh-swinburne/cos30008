#include <iostream>
#include "Polynomial.h"

using namespace std;


Polynomial::Polynomial()
{
	fDegree = 0;
	//for (size_t i = 0; i <= MAX_DEGREE; i++)
	//{
	//	fCoeffs[i] = 0.0;
	//}
	fill(fCoeffs, fCoeffs + MAX_DEGREE + 1, 0.0);
}


istream& operator>>(istream& aIStream, Polynomial& aObject)
{
	size_t aDegree;

	aIStream >> aDegree;
	aObject.fDegree = aDegree;

	for (long int i = aDegree; i >= 0; i--)
	{
		aIStream >> aObject.fCoeffs[i];
	}

	return aIStream;
}


ostream& operator<<(ostream& aOStream, const Polynomial& aObject)
{
	for (long int i = aObject.fDegree; i >=0 ; i--)
	{
		double lCoeff = aObject.fCoeffs[i];

		if (lCoeff == 0)
		{
			continue;
		}
		if (i != aObject.fDegree)
		{
			if (lCoeff >= 0)
			{
				aOStream << " + ";
		
			}
			else
			{
				aOStream << " - ";
				lCoeff = -lCoeff;
			}
		}
		aOStream << lCoeff << "x^" << i;
	}

	return aOStream;
}


Polynomial Polynomial::operator*(const Polynomial& aRHS) const
{
	Polynomial lResult;

	lResult.fDegree = fDegree + aRHS.fDegree;

	for (size_t i = 0; i <= fDegree; i++)
	{
		for (size_t j = 0; j <= aRHS.fDegree; j++)
		{
			lResult.fCoeffs[i + j] += fCoeffs[i] * aRHS.fCoeffs[j];
		}
	}

	return lResult;
}


bool Polynomial::operator==(const Polynomial& aRHS) const
{
	if (fDegree != aRHS.fDegree)
	{
		return false;
	}

	for (size_t i = 0; i <= fDegree; i++)
	{
		if (fCoeffs[i] != aRHS.fCoeffs[i])
		{
			return false;
		}
	}

	return true;
}