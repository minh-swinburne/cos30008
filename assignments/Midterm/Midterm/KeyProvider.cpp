
// COS30008, Midterm, Problem 1, 2024

#include "KeyProvider.h"

// Include library for isalpha() and toupper()
#include <cctype>

KeyProvider::KeyProvider(const std::string& aKeyword) :
	// Member initializers
	fKeyword(nullptr),
	fSize(0),
	fIndex(0)
{
	initialize(aKeyword);
}

KeyProvider::~KeyProvider()
{
	// Release resources
	delete[] fKeyword;
}

void KeyProvider::initialize(const std::string& aKeyword)
{
	// Delete existing keyword
	if (fKeyword != nullptr)
	{
		delete[] fKeyword;
	}

	// Initialize or reset keyword
	fSize = aKeyword.length();
	fKeyword = new char[fSize];
	fIndex = 0;

	for (size_t i = 0; i < fSize; i++)
	{
		// Use operator<< to push new keyword character
		*this << aKeyword[i];
	}
}

char KeyProvider::operator*() const
{
	// Return current keyword character
	return fKeyword[fIndex];
}

KeyProvider& KeyProvider::operator<<(char aKeyCharacter)
{
	// Push new keyword character if aKeyCharacter is a letter
	if (isalpha(aKeyCharacter))
	{
		// Replace current keyword character
		fKeyword[fIndex] = toupper(aKeyCharacter);
		// Advance to next keyword character (circular)
		fIndex = (fIndex + 1) % fSize;
	}

	return *this;
}