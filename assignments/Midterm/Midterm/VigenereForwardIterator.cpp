
// COS30008, Midterm, Problem 4, 2024

#include "VigenereForwardIterator.h"

VigenereForwardIterator::VigenereForwardIterator(iVigenereStream& aIStream) :
	fIStream(aIStream),
	fCurrentChar(0),
	fEOF(false)
{
	// Read first character
	fIStream >> fCurrentChar;
}

char VigenereForwardIterator::operator*() const
{
	return fCurrentChar;
}

VigenereForwardIterator& VigenereForwardIterator::operator++()
{
	// Read next character
	fIStream >> fCurrentChar;

	// Check for EOF
	if (fIStream.eof())
	{
		fEOF = true;
	}

	return *this;
}

VigenereForwardIterator VigenereForwardIterator::operator++(int)
{
	VigenereForwardIterator temp = *this;
	++(*this);
	return temp;
}

bool VigenereForwardIterator::operator==(const VigenereForwardIterator& aOther) const
{
	// Check if both iterators point to the same stream 
	// and have the same EOF status
	return (fIStream == aOther.fIStream)
		&& (fEOF == aOther.fEOF);
}

bool VigenereForwardIterator::operator!=(const VigenereForwardIterator& aOther) const
{
	return !(*this == aOther);
}

VigenereForwardIterator VigenereForwardIterator::begin() const
{
	VigenereForwardIterator temp = *this;
	// Reset the stream
	temp.fIStream.reset();
	return temp;
}

VigenereForwardIterator VigenereForwardIterator::end() const
{
	VigenereForwardIterator temp = *this;
	// Set EOF status to true
	temp.fEOF = true;
	return temp;
}