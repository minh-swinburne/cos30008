// COS30008, Tutorial 4, 2022

#include "PassiveResistor.h"

using namespace std;

PassiveResistor::PassiveResistor(double aBaseValue) :
	ResistorBase(aBaseValue)
{ }

bool PassiveResistor::mustScale(double aValue) const
{
	return aValue >= 1000.0;
}

const double PassiveResistor::getMultiplier() const
{
	return 1.0 / 1000.0;
}

const string PassiveResistor::getMajorUnit() const
{
	return "Ohm";
}

const string PassiveResistor::getMinorUnits() const
{
	return "OkM";
}

double PassiveResistor::getReactance(double aFrequency) const
{
	return getBaseValue();
}