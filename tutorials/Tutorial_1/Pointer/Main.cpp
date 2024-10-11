#include <iostream>

using namespace std;

// Function prototypes
static void changeValue(int aOld, int aNew);
static void changeRef(int& aOld, int aNew);
static void changePointer(int* aOld, int aNew);
static void printValues(int* aOld, int* aNew);

int main()
{
	cout << "Initial Values: " << endl;
	int old1 = 3;
	int new1 = 5;
	printValues(&old1, &new1);

	cout << "Change Value: " << endl;
	changeValue(old1, new1);

	cout << "Change Reference: " << endl;
	int old2 = 3;
	int new2 = 5;
	changeRef(old2, new2);

	cout << "Change Pointer: " << endl;
	int old3 = 3;
	int new3 = 5;
	changePointer(&old3, new3);
	int *ptr, **ptr2, **ptr3;
	ptr = &old3;
	ptr2 = &ptr;
	*ptr2 = ptr;
	ptr3 = &ptr;
	cout << ptr << " - " << &ptr << endl << ptr2 << " - " << *ptr2 << endl << ptr3;
}

static void changeValue(int aOld, int aNew)
{
	aOld = aNew;
	printValues(&aOld, &aNew);
}

static void changeRef(int& aOld, int aNew)
{
	aOld = aNew;
	printValues(&aOld, &aNew);
}

static void changePointer(int* aOld, int aNew)
{
	aOld = &aNew;
	// cout << &(*aOld);
	printValues(aOld, &aNew);
}

static void printValues(int* aOld, int* aNew)
{
	cout << "Old Value: " << *aOld << " - Address: " << aOld << endl
		<< "New Value: " << *aNew << " - Address: " << aNew << endl << endl;
}