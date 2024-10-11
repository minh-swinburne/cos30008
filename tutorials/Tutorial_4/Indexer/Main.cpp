#include <iostream>
#include <string>
#include <stdexcept>

#include "IntArrayIndexer.h"

using namespace std;

int main()
{
	int lArray[] = { 1, 2, 3, 4, 5 };
	int lSize = sizeof(lArray) / sizeof(lArray[0]);
	IntArrayIndexer lIndexer(lArray, lSize);

	//string lKeys[] = { "0", "1", "2", "3", "4" };
	string lBinaryKeys[] = { "000", "001", "010", "011", "100" };
	int lSum = 0;

	// lambda function to convert a binary string to an integer
	auto lMapBinary = [] (const string& aNumber) -> size_t
		{
			size_t lIndex = 0;
			for (size_t i = 0; i < aNumber.size(); i++)
			{
				lIndex = (lIndex << 1) + (aNumber[i] - '0');
			}
			return lIndex;
		};

	for (size_t i = 0; i < lIndexer.size(); i++)
	{
		//cout << "Indexed value of key [\"" << lKeys[i] << "\"] = " 
		//	   << lIndexer[lKeys[i]] << " (expect " << lIndexer[i] << ")" << endl;
		lSum += lIndexer.get( lBinaryKeys[i], lMapBinary );
	}

	cout << "Indexed sum of [1, 2, 3, 4, 5] = " << lSum << endl;

	return 0;
}