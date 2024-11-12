
// COS30008, Midterm, Problem 3, 2024

#include "iVigenereStream.h"

using namespace std;

iVigenereStream::iVigenereStream(Cipher aCipher, const string& aKeyword, const char* aFileName) : 
	fCipher(aCipher), 
	fCipherProvider(aKeyword)
{
	open(aFileName);
}

iVigenereStream::~iVigenereStream()
{
	// Close the file stream
	close();
}

void iVigenereStream::open(const char* aFileName)
{
	// Open file in binary mode
	fIStream.open(aFileName, ios_base::binary);
}

void iVigenereStream::close()
{
	fIStream.close();
}

void iVigenereStream::reset()
{
	// Reset the cipher provider
	fCipherProvider.reset();
	// Reset the file stream
	seekstart();
}

bool iVigenereStream::good() const
{
	return fIStream.good();
}

bool iVigenereStream::is_open() const
{
	return fIStream.is_open();
}

bool iVigenereStream::eof() const
{
	return fIStream.eof();
}

iVigenereStream& iVigenereStream::operator>>(char& aCharacter)
{
	if (fIStream.good())
	{
		// Read a character using get() method of ifstream
		// so as not to skip whitespace characters
		fIStream.get(aCharacter);

		if (fIStream.good())
		{
			// Call the cipher function to encode/decode the character
			aCharacter = fCipher(fCipherProvider, aCharacter);
		}
	}

	return *this;
}