// COS30008, Tutorial 4, 2022

#pragma once

#include <iostream>
#include <string>

using namespace std;

class ResistorBase
{
private:
	// normalize base value and unit (object remains unchanged)
	// example: the value of a register 56000.0 Ohm becomes 56.0 kOhm
	void normalize(double& aNormalizedValue, string& aUnit) const;

	// flatten base value and unit
	// example: the value of a register 56.0 kOhm becomes 56000.0 Ohm
	void flatten(const double& aRawValue, const string& aRawUnit);

	// base value of a resistor component
	double fBaseValue;

protected:
	// auxiliary methods (=0 - pure virtual members)
	virtual bool mustScale(double aValue) const = 0;
	virtual const double getMultiplier() const = 0;

	virtual const string getMajorUnit() const = 0;
	virtual const string getMinorUnits() const = 0;

	// setter for base value (used in flatten)
	void setBaseValue(double aBaseValue);

public:
	// constructor with a default value
	ResistorBase(double aBaseValue = 0.0);

	// retquired virtual destructor (implementation)
	virtual ~ResistorBase() {}

	// returns base value
	double getBaseValue() const;

	// returns (frequency-dependent) passive resistance value
	virtual double getReactance(double aFrequency = 0.0) const = 0;

	// returns (frequency-dependent) voltage drop
	double getPotentialAt(double aCurrent, double aFrequency = 0.0) const;

	// returns (frequency-dependent) current flowing through a resistor
	double getCurrentAt(double aVoltage, double aFrequency = 0.0) const;

	// resistor I/O
	friend istream& operator>>(istream& aIStream, ResistorBase& aObject);
	friend ostream& operator<<(ostream& aOStream, const ResistorBase& aObject);
};

