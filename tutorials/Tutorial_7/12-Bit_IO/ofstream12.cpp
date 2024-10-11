// COS30008, Tutorial 7, 2024

#include "ofstream12.h"

ofstream12::ofstream12(const char* aFileName, size_t aBufferSize) :
	fBufferSize(aBufferSize)
{
	fBuffer = new byte[fBufferSize];

	init();

	if (aFileName != nullptr)
	{
		open(aFileName);
	}
}

ofstream12::~ofstream12()
{
	flush();
	close();

	delete[] fBuffer;
}

void ofstream12::init()
{
	for (size_t i = 0; i < fBufferSize; i++)
	{
		fBuffer[i] = 0;
	}

	fByteIndex = 0;
	// start at the most significant bit
	// which will be the first bit written
	// to the file (little-endian)
	fBitIndex = 7;
}

void ofstream12::completeWriteBit()
{
	if (--fBitIndex < 0)
	{
		// move to the start of the next byte
		fByteIndex++;
		fBitIndex = 7;

		// flush the buffer if it is full
		if (fByteIndex == fBufferSize)
		{
			flush();
		}
	}
}

void ofstream12::writeBit0()
{
	completeWriteBit();
}

void ofstream12::writeBit1()
{
	// set the bit at the current position
	fBuffer[fByteIndex] |= 1 << fBitIndex;
	completeWriteBit();
}

void ofstream12::open(const char* aFileName)
{
	fOStream.open(aFileName, std::ios_base::binary);
}

void ofstream12::close()
{
	fOStream.close();
}

bool ofstream12::good() const
{
	return fOStream.good();
}

bool ofstream12::isOpen() const
{
	return fOStream.is_open();
}

void ofstream12::flush()
{
	// write the current buffer content to the file
	fOStream.write((const char*)fBuffer, fByteIndex);
	// reset the buffer
	init();
}

ofstream12& ofstream12::operator<<(size_t aValue)
{
	// write 12 bits in little-endian order
	for (int i = 0; i < 12; i++)
	{
		if (aValue & 0x1)
		{
			writeBit1();
		}
		else
		{
			writeBit0();
		}
		aValue >>= 1;	// shift right by 1 bit
	}

	return (*this);
}