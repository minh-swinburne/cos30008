#include "IntArrayIndexer.h"
#include <stdexcept>

using namespace std;

IntArrayIndexer::IntArrayIndexer(const int aArray[], size_t aSize) : 
	fArray(aArray), 
	fSize(aSize)
{}

IntArrayIndexer::~IntArrayIndexer()
{}

const size_t IntArrayIndexer::size() const
{
	return fSize;
}

const int& IntArrayIndexer::get(const string& aKey, StringMap aFunc) const
{
	return (*this)[aFunc(aKey)];
}

const int& IntArrayIndexer::operator[](const size_t aIndex) const
{
	if (aIndex >= fSize)
	{
		throw out_of_range("Index out of range");
	}
	return fArray[aIndex];
}