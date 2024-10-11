// COS30008, Tutorial 7, 2024
// Created: 2024-10-11
// Last modified: 2024-10-11
// Description: 12-bit input file stream class.

#pragma once
#include <fstream>

using byte = unsigned char;

class ifstream12
{
private:
	std::ifstream fIStream;

	byte* fBuffer;              // input buffer
	size_t fBufferSize;         // input buffer size

	size_t fByteIndex;          // current byte index
	int fBitIndex;              // current bit index (can be negative)

	// Initializes data members
	void init();
	// Reads a bit from the buffer
	bool readBit();            

public:
	// using C++11's nullptr
	ifstream12(const char* aFileName = nullptr, size_t aBufferSize = 128);
	~ifstream12();

	void open(const char* aFileName);
	void close();

	bool good() const;
	bool isOpen() const;

	explicit operator bool() const;
	// Reads a size_t value from the file
	ifstream12& operator>>(size_t& aValue);
};

