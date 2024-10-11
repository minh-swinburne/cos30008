// COS30008, Tutorial 4, 2022

#define _USE_MATH_DEFINES

#include "Inductor.h"

Inductor::Inductor(double aBaseValue) :
	ResistorBase(aBaseValue)
{ }

bool Inductor::mustScale(double aValue) const
{
	return aValue < 1.0;
}

const double Inductor::getMultiplier() const
{
	return 1000.0;
}

const std::string Inductor::getMajorUnit() const
{
	return "H";
}

const std::string Inductor::getMinorUnits() const
{
	return "Hmunp";
}

double Inductor::getReactance(double aFrequency) const
{
	return 2.0 * M_PI * aFrequency * getBaseValue();
}