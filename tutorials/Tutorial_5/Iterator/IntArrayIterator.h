#pragma once

class IntArrayIterator
{
private:
	const int* fArrayElements;
	const int fLength;
	int fIndex;

public:
	IntArrayIterator(const int aArray[], const int aLength, int aStart = 0);

	const int& operator*() const;
	IntArrayIterator& operator++();		// prefix
	IntArrayIterator operator++(int);	// postfix (extra unused int parameter)
	bool operator==(const IntArrayIterator& aOther) const;
	bool operator!=(const IntArrayIterator& aOther) const;

	IntArrayIterator begin() const;
	IntArrayIterator end() const;
};

