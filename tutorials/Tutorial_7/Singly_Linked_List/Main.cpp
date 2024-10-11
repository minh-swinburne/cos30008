#include <iostream>
#include <string>

using namespace std;

#include "SinglyLinkedListTemplate.h"

int main()
{
	using StringList = SinglyLinkedList<string>;

	string lA = "AAAA";
	string lC = "CCCC";

	StringList One(lA);
	StringList Two("BBBB", &One);
	StringList Three(lC, &Two);
	StringList Four("DDDD");
	StringList Five("EEEE");

	StringList* lTop = &Three;

	for (; lTop != nullptr; lTop = lTop->fNext)
	{
		cout << "Value: " << lTop->fData << endl;
	}

	cout << endl << "Test random access:" << endl;

	size_t lIndex = 0;
	cout << "Value at index " << lIndex << ": " << Three[lIndex]->fData << endl;

	cout << endl << "Test range check:" << endl;

	try
	{
		const StringList* lList = Three[3];

		cerr << "Error, you should not see " << lList->fData << " here!" << endl;
	}
	catch (out_of_range e)
	{
		cerr << "Properly caught error: " << e.what() << endl;
	}
	catch (...)
	{
		cerr << "This message must not be printed!" << endl;
	}

	cout << endl << "Test insert:" << endl;

	One.insert(&Five);
	One.insert(&Four);

	lTop = &Three;

	for (; lTop != nullptr; lTop = lTop->fNext)
	{
		cout << "Value: " << lTop->fData << endl;
	}

	cout << endl << "Test pop:" << endl;

	cout << "Pop value at One: " << One.pop()->fData << endl;

	lTop = &Three;

	for (; lTop != nullptr; lTop = lTop->fNext)
	{
		cout << "Value: " << lTop->fData << endl;
	}
	return 0;
}