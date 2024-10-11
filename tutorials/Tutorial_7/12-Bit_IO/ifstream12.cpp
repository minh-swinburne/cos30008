#include "ifstream12.h"

ifstream12::ifstream12(const char* aFileName, size_t aBufferSize) :
	fBufferSize(aBufferSize)
{
	fBuffer = new byte[fBufferSize];

	if (aFileName != nullptr)
	{
		open(aFileName);
	}

	init();
}

ifstream12::~ifstream12()
{
	close();

	delete[] fBuffer;
}

void ifstream12::init()
{
	// fill buffer
	fIStream.read((char*)fBuffer, fBufferSize); 

	fByteIndex = 0;
	// start at the most significant bit
	// which will be the first bit read
	// from the file (little-endian)
	fBitIndex = 7;	
}

bool ifstream12::readBit()
{
	if (fByteIndex == fBufferSize)
	{
		init();		// reset buffer
	}

	bool lResult = (fBuffer[fByteIndex] >> fBitIndex) & 1;

	if (--fBitIndex < 0)
	{
		fByteIndex++;
		fBitIndex = 7;
	}

	return lResult;
}

void ifstream12::open(const char* aFileName)
{
	fIStream.open(aFileName, std::ios::binary);
}

void ifstream12::close()
{
	fIStream.close();
}

bool ifstream12::good() const
{
	return fIStream.good();
}

bool ifstream12::isOpen() const
{
	return fIStream.is_open();
}

ifstream12::operator bool() const
{
	return !fIStream.fail();
}

ifstream12& ifstream12::operator>>(size_t& aValue)
{
	aValue = 0;

	for (size_t i = 0; i < 12; i++)
	{
		aValue |= (readBit() << i);
	}

	return *this;
}