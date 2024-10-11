// COS30008, Tutorial 4, 2022

#include <string>
#include <stdexcept>
#include "ResistorBase.h"

using namespace std;

void ResistorBase::normalize(double& aNormalizedValue, string& aUnit) const
{
	aNormalizedValue = fBaseValue;
	string lPrefixes = getMinorUnits();

	for (size_t i = 0; i < lPrefixes.size(); i++)
	{
		// stop scaling at maximum unit
		if (mustScale(aNormalizedValue) && (i < lPrefixes.size() - 1))
		{
			aNormalizedValue *= getMultiplier();
		}
		else
		{
			if (i > 0)
			{
				aUnit += lPrefixes[i];
			}
			aUnit += getMajorUnit();
			break;
		}
	}
}

void ResistorBase::flatten(const double& aRawValue, const string& aRawUnit)
{
	string lMajorUnit = getMajorUnit();
	string lMinorUnits = getMinorUnits();

	// error handling
	// test basic features (raw unit too long and not containing major unit)
	if ((aRawUnit.size() > lMajorUnit.size() + 1) || 
		(aRawUnit.find(lMajorUnit) == string::npos))
	{
		throw invalid_argument("Invalid unit specification");
	}

	// test scale features, aRawUnit[0] must be contained in minor units
	if ((aRawUnit.size() == lMajorUnit.size() + 1) &&
		(lMinorUnits.find(aRawUnit[0]) == string::npos))
	{
		throw invalid_argument("Invalid unit specification");
	}

	// adjust base value
	double lMultiplier = 1.0;

	size_t i = lMinorUnits.find(aRawUnit[0]);
	double lRawValue = aRawValue;

	// scale raw value first
	for (; i > 0; i--)
	{
		if (mustScale(lRawValue))
		{
			lRawValue /= getMultiplier();
			cout << "lRawValue: " << lRawValue << endl;
		}
		else
		{
			break;
		}
	}

	// adjust multiplier
	for (; i > 0; i--)
	{
		lMultiplier *= 1.0/getMultiplier();
	}

	setBaseValue(lRawValue * lMultiplier);
}