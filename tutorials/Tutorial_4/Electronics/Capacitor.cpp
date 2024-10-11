// COS30008, Tutorial 4, 2022

#define _USE_MATH_DEFINES

#include "Capacitor.h"

Capacitor::Capacitor(double aBaseValue) :
	ResistorBase(aBaseValue)
{ }

bool Capacitor::mustScale(double aValue) const
{
	return aValue < 1.0;
}

const double Capacitor::getMultiplier() const
{
	return 1000.0;
}

const string Capacitor::getMajorUnit() const
{
	return "F";
}

const string Capacitor::getMinorUnits() const
{
	return "Fmunp";
}

double Capacitor::getReactance(double aFrequency) const
{
	return 1.0 / (2.0 * M_PI * aFrequency * getBaseValue());
}