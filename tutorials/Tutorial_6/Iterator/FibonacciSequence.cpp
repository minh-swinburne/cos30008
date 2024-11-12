// COS30008, Tutorial 6, 2024

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
	return FibonacciSequenceIterator(*this, lLimit);
}