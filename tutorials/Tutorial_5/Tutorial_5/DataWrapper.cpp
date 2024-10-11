#include <fstream>
#include <stdexcept>
//#include <iostream>
#include "DataWrapper.h"

using namespace std;

const char DataMap::getAsChar() const
{
	return static_cast<const char>(fDatum);
}

DataWrapper::DataWrapper()
{
	fSize = 0;
	fData = nullptr;
}

DataWrapper::~DataWrapper()
{
	delete[] fData;
}

bool DataWrapper::load(const string& aFileName)
{
	ifstream lInput(aFileName);

	if (lInput.good())
	{
		lInput >> fSize;

		if (fSize)
		{
			fData = new DataMap[fSize];

			for (size_t i = 0; i < fSize; i++)
			{
				lInput >> fData[i].fIndex >> fData[i].fDatum;
			}

			lInput.close();
			return true;
		}
	}
}

size_t DataWrapper::size() const
{
	return fSize;
}

const DataMap& DataWrapper::operator[](size_t aIndex) const
{
	if (aIndex >= fSize)
		throw out_of_range("Index out of range: Maximum " + to_string(fSize - 1) + ", got " + to_string(aIndex));
	return fData[aIndex];
}

const char DataWrapper::get(size_t aIndex, Callable aSelector)
{
	return aSelector(aIndex);
}

DataWrapper DataWrapper::sorted() const
{
	DataWrapper result;
	result.fSize = fSize;
	result.fData = new DataMap[fSize];

	for (size_t i = 0; i < fSize; i++)
	{
		DataMap lData = fData[i];
		//cout << lData.fIndex << " - " << lData.fDatum << endl;
		result.fData[lData.fIndex] = lData;
	}

	return result;
}