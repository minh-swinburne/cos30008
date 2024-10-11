#define _USE_MATH_DEFINES     // must be defined before any #include  
#include "Polynomial.h"

#include <cmath>

using namespace std;

Polynomial::Polynomial() {
	fDegree = 0;
	for (size_t i = 0; i <= MAX_DEGREE; i++) {
		fCoeffs[i] = 0.0;
	}
}

istream& operator>>(istream& aIStream, Polynomial& aObject) {
	aIStream >> aObject.fDegree;
	for (int i = aObject.fDegree; i >= 0; i--) {
		aIStream >> aObject.fCoeffs[i];
	}
	return aIStream;
}

ostream& operator<<(ostream& aOStream, const Polynomial& aObject) {
	int i;
	for (i = aObject.fDegree; i >= 0; i--) {
		if (aObject.fCoeffs[i] != 0) {
			aOStream << aObject.fCoeffs[i] << "x^" << i << " + ";
		}
	}
	aOStream << "\b" << "\b" << "\b" << "  ";
	return aOStream;
}

bool Polynomial::operator==(const Polynomial& aRHS) const {
	bool q = true;
	if (fDegree != aRHS.fDegree) {
		q = false;
	}
	else {
		for (int i = fDegree; i >= 0; i--) {
			if (fCoeffs[i] != aRHS.fCoeffs[i]) {
				q = false;
				break;
			}
		}
	}
	return q;
}

Polynomial Polynomial::operator*(const Polynomial& aRHS) const {
	int i, j;
	Polynomial Result;
	Result.fDegree = fDegree + aRHS.fDegree;
	for(i = 0; i <= fDegree; i++)
		for (j = 0; j <= aRHS.fDegree; j++) {
			Result.fCoeffs[i+j] += fCoeffs[i] * aRHS.fCoeffs[j];
		}
	return Result;
}