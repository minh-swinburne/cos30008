// COS30008, Tutorial 6, 2024

#include "FibonacciSequenceIterator.h"

FibonacciSequenceIterator::FibonacciSequenceIterator(const FibonacciSequence& aSequenceObject, uint64_t aStart) :
	fSequenceObject(aSequenceObject), fIndex(aStart)
{ }

FibonacciSequenceIterator::FibonacciSequenceIterator(uint64_t aLimit, uint64_t aStart) :
	FibonacciSequenceIterator(FibonacciSequence(aLimit), aStart)
{ }

const uint64_t& FibonacciSequenceIterator::operator*() const
{
	return fSequenceObject.current();
}

FibonacciSequenceIterator& FibonacciSequenceIterator::operator++()
{
	fSequenceObject.advance();
	fIndex++;
	return *this;
}

FibonacciSequenceIterator FibonacciSequenceIterator::operator++(int)
{
	FibonacciSequenceIterator temp = *this;
	++(*this);
	return temp;
}

bool FibonacciSequenceIterator::operator==(const FibonacciSequenceIterator& aOther) const
{
	return (fSequenceObject.getLimit() == aOther.fSequenceObject.getLimit())
		&& (fIndex == aOther.fIndex);
}

bool FibonacciSequenceIterator::operator!=(const FibonacciSequenceIterator& aOther) const
{
	return !(*this == aOther);
}

FibonacciSequenceIterator FibonacciSequenceIterator::begin() const
{
	return fSequenceObject.begin();
}

FibonacciSequenceIterator FibonacciSequenceIterator::end() const
{
	return fSequenceObject.end();
}