// COS30008, Tutorial 10, 2024

#include "SimpleString.h"

#include <string>

using namespace std;

SimpleString::SimpleString()
{
	fCharacters = new char[1];
	*fCharacters = '\0';
}

SimpleString::~SimpleString()
{
	delete fCharacters;
}

SimpleString& SimpleString::operator+(const char aCharacter)
{
	char* lTemp = new char[strlen(fCharacters) + 2];
	size_t i = 0;

	for ( ; i < strlen(fCharacters); i++)
	{
		lTemp[i] = fCharacters[i];
	}

	lTemp[i++] = aCharacter;
	lTemp[i] = '\0';

	delete fCharacters;
	fCharacters = lTemp;
	return *this;
}

const char* SimpleString::operator*() const
{
	return fCharacters;
}

SimpleString::SimpleString(const SimpleString& aOtherString)
{
	int lLength = strlen(aOtherString.fCharacters) + 1;
	fCharacters = new char[lLength];

	for (size_t i = 0; i < lLength; i++)
	{
		fCharacters[i] = aOtherString.fCharacters[i];
	}
}

SimpleString& SimpleString::operator=(const SimpleString& aOtherString)
{
	// protection against accidental suicide
	if (this != &aOtherString)
	{
		delete fCharacters;

		int lLength = strlen(aOtherString.fCharacters) + 1;
		fCharacters = new char[lLength];

		for (size_t i = 0; i < lLength; i++)
		{
			fCharacters[i] = aOtherString.fCharacters[i];
		}
	}

	return *this;
}

SimpleString::SimpleString(SimpleString&& aOtherString)
{
    fCharacters = aOtherString.fCharacters;
	aOtherString.fCharacters = new char[1] {'\0'};
}

SimpleString& SimpleString::operator=(SimpleString&& aOtherString)
{
	if (this != &aOtherString)
	{
		delete fCharacters;

		fCharacters = aOtherString.fCharacters;
		aOtherString.fCharacters = new char[1] {'\0'};
	}

	return *this;
}

SimpleString* SimpleString::clone()
{
	return new SimpleString(*this);
}