
// COS30008, Midterm, Problem 2, 2024

#include "Vigenere.h"

#include <cctype>

using namespace std;

Vigenere::Vigenere(const string& aKeyword) :
	// Member initializers
	fKeyword(aKeyword),
	fKeywordProvider(aKeyword)
{
	initializeTable();
}

string Vigenere::getCurrentKeyword()
{
	string lResult;

	// Go through the keyword provider 
	// and copy keyword characters into result string
	for (size_t i = 0; i < fKeyword.length(); i++)
	{
		char lChar = *fKeywordProvider;
		lResult += lChar;
		// Advance to next keyword character 
		// while keeping the keyword provider unchanged
		fKeywordProvider << lChar;
	}

	return lResult;
}

void Vigenere::reset()
{
	fKeywordProvider.initialize(fKeyword);
}

char Vigenere::encode(char aCharacter)
{
	char lResult = aCharacter;

	// Only encode letters
	if (isalpha(aCharacter))
	{
		// Get encoded character from mapping table
		// Please ignore the warning about reading invalid data
		// because we know that fKeywordProvider only contains letters
		lResult = fMappingTable[*fKeywordProvider - 'A'][toupper(aCharacter) - 'A'];
		// Advance to next keyword character
		// and update keyword provider
		fKeywordProvider << aCharacter;

		// Keep the case of the original character
		if (islower(aCharacter))
		{
			lResult = tolower(lResult);
		}
	}

	return lResult;
}

char Vigenere::decode(char aCharacter)
{
	char lResult = aCharacter;

	if (isalpha(aCharacter))
	{
		char lRow = *fKeywordProvider - 'A';

		// Find the column in the mapping table
		for (size_t i = 0; i < CHARACTERS; i++)
		{
			if (fMappingTable[lRow][i] == toupper(aCharacter))
			{
				lResult = 'A' + i;
				break;
			}
		}

		// Advance to next keyword character
		fKeywordProvider << lResult;

		// Keep the case of the original character
		if (islower(aCharacter))
		{
			lResult = tolower(lResult);
		}
	}

	return lResult;
}