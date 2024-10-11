// COS30008, Tutorial 6, 2024

#include <iostream>
#include <stdexcept>
#include "FibonacciSequence.h"
#include "FibonacciSequenceIterator.h"

FibonacciSequence::FibonacciSequence(uint64_t aLimit)
{
	fPrevious = 0;
	fCurrent = 1;
	fPosition = 1;
	fLimit = aLimit;
}

const uint64_t& FibonacciSequence::current() const
{
	return fCurrent;
}

void FibonacciSequence::advance()
{
	if (fPosition > fLimit && fLimit != 0)
	{
		throw std::out_of_range("The maximum position has been exceeded.");
	}
	uint64_t lNext = fPrevious + fCurrent;
	fPrevious = fCurrent;
	fCurrent = lNext;
	fPosition++;
}

const uint64_t& FibonacciSequence::getLimit() const
{
	return fLimit;
}

void FibonacciSequence::reset()
{
	fPrevious = 0;
	fCurrent = 1;
	fPosition = 1;
}

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
	/*std::cout << "This: " 
		<< fSequenceObject.current() << " (current) - " 
		<< fSequenceObject.getLimit() << " (limit) - " 
		<< fIndex << " (index)" 
		<< std::endl << "Other: "
		<< aOther.fSequenceObject.current() << " (current) - "
		<< aOther.fSequenceObject.getLimit() << " (limit) - "
		<< aOther.fIndex << " (index)"
		<< std::endl << std::endl;*/
	return (fSequenceObject.getLimit() == aOther.fSequenceObject.getLimit())
		&& (fIndex == aOther.fIndex);
}

bool FibonacciSequenceIterator::operator!=(const FibonacciSequenceIterator& aOther) const
{
	return !(*this == aOther);
}

FibonacciSequenceIterator FibonacciSequence::begin() const
{
	return FibonacciSequenceIterator(*this);
}

FibonacciSequenceIterator FibonacciSequence::end() const
{
	uint64_t lLimit = fLimit + 1;
	if (lLimit == 1)
	{
		lLimit--; // iterator will never reach end
	}
	//std::cout << lLimit << std::endl;
	return FibonacciSequenceIterator(*this, lLimit);
}

FibonacciSequenceIterator FibonacciSequenceIterator::begin() const
{
	return fSequenceObject.begin();
}

FibonacciSequenceIterator FibonacciSequenceIterator::end() const
{
	return fSequenceObject.end();
}