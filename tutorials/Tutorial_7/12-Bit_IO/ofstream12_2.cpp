// COS30008, Tutorial 7, 2024

#include "ofstream12.h"

ofstream12::ofstream12(const char* aFileName, size_t aBufferSize)
{
	fBuffer = new byte[aBufferSize];
	fBufferSize = aBufferSize;
	fByteIndex = 0;
	fBitIndex = 7;

	init();

	if (aFileName != nullptr)
	{
		open(aFileName);
	}
}

ofstream12::~ofstream12()
{
	delete[] fBuffer;
}

void ofstream12::init()
{
	for (size_t i = 0; i < fBufferSize; i++)
	{
		fBuffer[i] = 0;
	}
}

void ofstream12::completeWriteBit()
{
	if (fByteIndex < fBufferSize)
	{
		fByteIndex++;
		fBitIndex = 7;
	}
	else
	{
		fOStream.write((char*)fBuffer, fBufferSize);
		init();
		fByteIndex = 1;
		fBitIndex = 7;
	}
}

void ofstream12::writeBit0()
{
	fBuffer[fByteIndex] &= ~(1 << fBitIndex);
	fBitIndex--;

	if (fBitIndex < 0)
	{
		completeWriteBit();
	}
}

void ofstream12::writeBit1()
{
	fBuffer[fByteIndex] |= 1 << fBitIndex;
	fBitIndex--;

	if (fBitIndex < 0)
	{
		completeWriteBit();
	}
}

void ofstream12::open(const char* aFileName)
{
	fOStream.open(aFileName, std::ios::binary);
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
	if (fByteIndex > 0)
	{
		fOStream.write((char*)fBuffer, fByteIndex);
		init();
		fByteIndex = 0;
		fBitIndex = 7;
	}
}

ofstream12& ofstream12::operator<<(size_t aValue)
{
	for (int i = 11; i >= 0; i--)
	{
		if (aValue & (1 << i))
		{
			writeBit1();
		}
		else
		{
			writeBit0();
		}
	}

	return *this;
}