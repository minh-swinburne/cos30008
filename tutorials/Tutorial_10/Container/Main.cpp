
// COS30008, Tutorial 10, 2024

#include <iostream>

using namespace std;

#define P1
#define P2
#define P3

#ifdef P1

#include "Stack.h"

void testStack()
{
	cout << "Stack test:" << endl;
	Stack<int> lStack(10);

	lStack.push(2);
	lStack.push(34);
	lStack.push(68);

	cout << "Number of elements on the stack: " << lStack.size() << endl;
	cout << "Top: " << lStack.top() << endl;
	lStack.pop();
	cout << "Removed the first element." << endl;
	cout << "Top: " << lStack.top() << endl;
	lStack.pop();
	lStack.pop();
	cout << "Number of elements on the stack: " << lStack.size() << endl;

	cout << endl;
}

#endif // P1

#ifdef P2

#include "Queue.h"

void testQueue()
{
	cout << "Queue test:" << endl;
	Queue<int> lQueue;

	lQueue.enqueue(20);
	lQueue.enqueue(3);
	lQueue.enqueue(37);

	cout << "Number of elements in the queue: " << lQueue.size() << endl;

	cout << "Value: " << lQueue.top() << endl; lQueue.dequeue();
	cout << "Value: " << lQueue.top() << endl; lQueue.dequeue();
	cout << "Value: " << lQueue.top() << endl; lQueue.dequeue();

	cout << "Number of elements in the queue: " << lQueue.size() << endl;

	cout << endl;
}

#endif // P2

#ifdef P3

#include "SortedList.h"

void testSortedList()
{
	cout << "SortedList test:" << endl;
	SortedList<int> lSortedList;

	lSortedList.insert(20);	// insert into empty list
	lSortedList.insert(3);	// insert at the start
	lSortedList.insert(37);	// insert at the end
	lSortedList.insert(13);	// insert in the middle

	// test size
	cout << "Number of elements in the sorted list: " << lSortedList.size() << endl;

	//test copy constructor
	SortedList<int> lCopy(lSortedList);

	// test forward iterator
	cout << "A - Top to bottom " << lCopy.size() << " elements:" << endl;

	for (const int& lItem : lCopy)
	{
		cout << "Value: " << lItem << endl;
	}

	// test move constructor
	SortedList<int> lMove(std::move(lCopy));

	// test backward iterator
	cout << "B - Bottom to top " << lMove.size() << " elements:" << endl;

	for (auto lIter = lMove.rbegin(); lIter != lMove.rend(); lIter--)
	{
		cout << "Value: " << *lIter << endl;
	}

	// test indexer
	try
	{
		cout << "Value at index 2: " << lMove[2] << endl;
		cout << "Value at index 3: " << lMove[3] << endl;
		cout << "Value at index 4: ";
		cout << lMove[4] << endl;
		cout << "Error: You should not see this text." << endl;
	}
	catch (out_of_range e)
	{
		cout << endl << "Successfully caught error: " << e.what() << endl;
	}

	// test remove
	lMove.remove(3); // remove the first element

	cout << "Removing 3: ";
	for (const int& lItem : lMove)
	{
		cout << lItem << " ";
	}
	cout << endl;

	lMove.remove(37); // remove the last element

	cout << "Removing 37: ";
	for (const int& lItem : lMove)
	{
		cout << lItem << " ";
	}
	cout << endl;

	lMove.remove(11); // remove non-existing element

	cout << "Removing 11: ";
	for (const int& lItem : lMove)
	{
		cout << lItem << " ";
	}
	cout << endl;

	lMove.remove(20);
	lMove.remove(13); // remove the only element

	cout << "Removing 20 and 13: ";
	for (const int& lItem : lMove)
	{
		cout << lItem << " ";
	}
	cout << endl << endl;
}

#endif // P3

int main()
{
#ifdef P1
	testStack();
#endif // P1
#ifdef P2
	testQueue();
#endif // P2
#ifdef P3
	testSortedList();
#endif // P3

	return 0;
}