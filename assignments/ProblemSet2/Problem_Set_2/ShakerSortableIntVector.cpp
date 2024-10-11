// Problem Set 2, 2024

#include "ShakerSortableIntVector.h"

ShakerSortableIntVector::ShakerSortableIntVector(const int aArrayOfIntegers[], size_t aNumberOfElements) :
	// calls super class constructor
	SortableIntVector(aArrayOfIntegers, aNumberOfElements)
{ }

void ShakerSortableIntVector::sort(Comparable aOrderFunction)
{
	size_t lStart = 0;
	size_t lEnd = size() - 1;

	// sorts in DECREASING order without a "sorted" flag
	while (lStart < lEnd)
	{
		// forward loop from left to right
		// bubbles the smallest value to the end of the array
		for (size_t i = lStart; i < lEnd; i++)	
		{
			// compares and swaps if the former element is smaller
			if (!aOrderFunction((*this)[i + 1], (*this)[i]))
			{
				swap(i, i + 1);
			}
		}

		// moves the end point back by one
		lEnd--;

		// backward loop from right to left
		// bubbles the largest value to the start of the array
		for (size_t i = lEnd; i > lStart; i--)	
		{
			// compares and swaps if the latter element is bigger
			if (!aOrderFunction((*this)[i], (*this)[i - 1]))
			{
				swap(i - 1, i);
			}
		}

		// moves the start point ahead by one
		lStart++;
	}
}