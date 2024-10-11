//#include <iostream>
#include "IntArrayIterator.h"

using namespace std;

IntArrayIterator::IntArrayIterator(const int aArray[], const int aLength, int aStart) :
	fArrayElements(aArray), fLength(aLength), fIndex(aStart)
{ }

const int& IntArrayIterator::operator*() const
{
	return fArrayElements[fIndex];
}

IntArrayIterator& IntArrayIterator::operator++()
{
	fIndex++;
	return *this;
}

IntArrayIterator IntArrayIterator::operator++(int)
{
	IntArrayIterator temp = *this;
	++(*this);	// reuse implementation
	return temp;
}

bool IntArrayIterator::operator==(const IntArrayIterator& aOther) const
{
	return (fIndex == aOther.fIndex)
		&& (fArrayElements == aOther.fArrayElements);
}

bool IntArrayIterator::operator!=(const IntArrayIterator& aOther) const
{
	return !(*this == aOther);
}

IntArrayIterator IntArrayIterator::begin() const
{
	return IntArrayIterator(fArrayElements, fLength);
}

IntArrayIterator IntArrayIterator::end() const
{
	return IntArrayIterator(fArrayElements, fLength, fLength);
}