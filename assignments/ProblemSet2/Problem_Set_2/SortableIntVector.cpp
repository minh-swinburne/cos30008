// Problem Set 2, 2024

#include "SortableIntVector.h"

SortableIntVector::SortableIntVector(const int aArrayOfIntegers[], size_t aNumberOfElements) :
	// calls super class constructor
	IntVector(aArrayOfIntegers, aNumberOfElements)	
{ }

void SortableIntVector::sort(Comparable aOrderFunction)
{
	// only calls the getter once
	size_t lSize = size();

	// sorts in INCREASING order
	for (size_t i = 0; i < lSize - 1; i++)	// outer loop
	{
		for (size_t j = 0; j < lSize - 1 - i; j++)	// inner loop
		{
			// compares adjacent elements and swaps if the former has bigger value
			// doesn't swap if the elements are equal
			if (!aOrderFunction((*this)[j], (*this)[j + 1]))
			{
				swap(j, j + 1);
			}
		}
	}
}