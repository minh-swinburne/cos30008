#pragma once

#include <functional>
#include <string>

using namespace std;
using StringMap = function<size_t(const string&)>;

class IntArrayIndexer
{
private:
	const int* fArray;
	size_t fSize;

public:
	IntArrayIndexer(const int aArray[], size_t aSize);
	~IntArrayIndexer();

	const size_t size() const;
	const int& operator[](const size_t aIndex) const;

	const int& get(const string& aKey, 
					StringMap aFunc = [](const string& aNumber) 
					{
						size_t lIndex = 0;
						for (size_t i = 0; i < aNumber.size(); i++)
						{
							lIndex += lIndex * 10 + (aNumber[i] - '0');
						}
						return lIndex;
					}) const;
};

