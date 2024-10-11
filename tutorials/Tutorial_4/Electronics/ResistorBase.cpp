// COS30008, Tutorial 4, 2022

#include "ResistorBase.h"

using namespace std;

ResistorBase::ResistorBase(double aBaseValue) :
	fBaseValue(aBaseValue)
{ }

double ResistorBase::getBaseValue() const
{
	return fBaseValue;
}

void ResistorBase::setBaseValue(double aBaseValue)
{
	fBaseValue = aBaseValue;
}

double ResistorBase::getPotentialAt(double aCurrent, double aFrequency) const
{
	// V = I * R
	return aCurrent * getReactance(aFrequency);
}

double ResistorBase::getCurrentAt(double aVoltage, double aFrequency) const
{
	// I = V / R
	return aVoltage / getReactance(aFrequency);
}

// I/O operators
istream& operator>>(istream& aIStream, ResistorBase& aObject)
{
	double lRawValue;
	string lRawUnit;

	aIStream >> lRawValue >> lRawUnit;
	aObject.flatten(lRawValue, lRawUnit);

	return aIStream;
}

ostream& operator<<(ostream& aOStream, const ResistorBase& aObject)
{
	double lNormalizedValue;
	string lNormalizedUnit;

	aObject.normalize(lNormalizedValue, lNormalizedUnit);
	aOStream << lNormalizedValue << " " << lNormalizedUnit;

	return aOStream;
}