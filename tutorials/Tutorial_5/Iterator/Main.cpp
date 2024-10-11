#include <iostream>
#include "IntArrayIterator.h"

using namespace std;

int main()
{
	int a[] = { 1, 2, 3, 4, 5 };
	int sum = 0;

	for (IntArrayIterator iter(a, 5); iter != iter.end(); iter++)
	{
		sum += *iter;
	}

	cout << "For loop: Iterated sum of [1,2,3,4,5] is " << sum << endl;

	sum = 0;

	for (const auto& i : IntArrayIterator(a, 5))
	{
		sum += i;
	}

	cout << "For-each loop: Iterated sum of [1,2,3,4,5] is " << sum << endl;

	// using for-each

	for (int i : a)
	{
		cout << hex << &i << ", " << sizeof(i) << ": " << i << endl;
	}
	cout << endl;

	for (const int& i : a)
	{
		cout << hex << &i << ", " << sizeof(i) << ": " << i << endl;
	}
	cout << endl;

	for (auto i : a)
	{
		cout << hex << &i << ", " << sizeof(i) << ": " << i << endl;
	}
	cout << endl;

	for (const auto& i : a)
	{
		cout << hex << &i << ", " << sizeof(i) << ": " << i << endl;
	}

	return 0;
}