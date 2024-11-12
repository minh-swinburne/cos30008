
// COS30008, Tutorial 10, 2024

#pragma once

#include "DoublyLinkedList.h"
#include "DoublyLinkedListIterator.h"

#include <stdexcept>

template<class T>
class SortedList
{
private:
	// auxiliary definition to simplify node usage
	using Node = DoublyLinkedList<T>;

	Node* fRoot;    // the first element in the list
	size_t fCount;  // number of elements in the list

public:
	// auxiliary definition to simplify iterator usage
	using Iterator = DoublyLinkedListIterator<T>;

	// default constructor - creates an empty list
	SortedList() : fRoot(nullptr), fCount(0) {}

	// copy constructor
	SortedList(const SortedList& aOther) : 
		fRoot(nullptr), 
		fCount(0)
	{
		*this = aOther;
	}

	// move constructor
	SortedList(SortedList&& aOther) : 
		fRoot(aOther.fRoot), 
		fCount(aOther.fCount)
	{
		aOther.fRoot = nullptr;
		aOther.fCount = 0;
	}

	// destructor - frees all nodes
	~SortedList()
	{
		while (fRoot != nullptr)
		{
			// more than one element
			if (fRoot != &fRoot->getPrevious())
			{
				// select last
				Node* lTemp = const_cast<Node*>(&fRoot->getPrevious());

				// remove from list
				lTemp->isolate(); 
				delete lTemp; // free
			}
			else
			{
				delete fRoot; // free last
				break; // stop loop
			}
		}
	}

	// assignment operator
	SortedList& operator=(const SortedList& aOtherList)
	{
		if (this != &aOtherList)
		{
			this->~SortedList(); // destroy current list
			fCount = 0; // reset count

			for (const T& lItem : aOtherList)
			{
				insert(lItem);
			}
		}

		return *this;
	}

	// move assignment operator
	SortedList& operator=(SortedList&& aOtherList)
	{
		if (this != &aOtherList)
		{
			this->~SortedList(); // destroy current list

			fRoot = aOtherList.fRoot; // move root
			fCount = aOtherList.fCount; // move count

			aOtherList.fRoot = nullptr; // reset root
			aOtherList.fCount = 0; // reset count
		}

		return *this;
	}

	// Is the list empty?
	bool isEmpty() const
	{
		return fCount == 0;
	}

	// number of elements in the list
	size_t size() const
	{
		return fCount;
	}

	// add aElement at a proper position
	void insert(const T& aElement)
	{
		// create new node
		Node* lNewNode = new Node(aElement);
		// start searching at root node
		Node* lNode = fRoot;

		// Are there still nodes available?
		while (lNode != nullptr)
		{
			// Have we found the node?
			if (**lNode > aElement) 
			{
				// Is this the root node?
				if (lNode == fRoot)
				{
					// set new root
					fRoot = lNewNode;
				}
				break; // stop the search
			}

			// go to next node
			lNode = const_cast<Node*>(&lNode->getNext());

			// Have we reached the end of the list?
			if (lNode == fRoot)
			{
				break; // stop search
			}
		}

		if (lNode == nullptr)
		{
			fRoot = lNewNode; // set root
		}
		else
		{
			// insert in front of current node
			// if current node is root
			// then the new node is at the end
			lNode->push_front(*lNewNode);
		}

		// increment count
		fCount++;
	}

	// add aElement at a proper position
	void insert(T&& aElement)
	{
		// create new node
		Node* lNewNode = new Node(std::move(aElement));
		// start searching at root node
		Node* lNode = fRoot;

		// Are there still nodes available?
		while (lNode != nullptr)
		{
			// Have we found the node?
			if (**lNode > **lNewNode)
			{
				// Is this the root node?
				if (lNode == fRoot)
				{
					// set new root
					fRoot = lNewNode;
				}
				break; // stop the search
			}

			// go to next node
			lNode = const_cast<Node*>(&lNode->getNext());

			// Have we reached the end of the list?
			if (lNode == fRoot)
			{
				break; // stop search
			}
		}

		if (lNode == nullptr)
		{
			fRoot = lNewNode; // set root
		}
		else
		{
			// insert in front of current node
			// if current node is root
			// then the new node is at the end
			lNode->push_front(*lNewNode);
		}

		// increment count
		fCount++;
	}

	// remove first match from list
	void remove(const T& aElement)
	{
		Node* lNode = fRoot; // start at first

		// Are there still nodes available?
		while (lNode != nullptr)
		{
			// Have we found the node?
			if (**lNode == aElement)
			{
				break; // stop the search
			}

			// Have we reached the end of the list?
			if (lNode != &fRoot->getPrevious())
			{
				// go to next
				lNode = const_cast<Node*>(&lNode->getNext());
			}
			else
			{
				lNode = nullptr; // stop search
			}
		}

		// At this point we have either reached the end or found the node.
		if (lNode != nullptr) // We have found the node.
		{
			if (fCount != 1) // not the only element
			{
				if (lNode == fRoot)
				{
					fRoot = const_cast<Node*>(&fRoot->getNext()); // make next root
				}
			}
			else
			{
				fRoot = nullptr; // list becomes empty
			}

			lNode->isolate(); // isolate node
			delete lNode; // release node's memory
			fCount--; // decrement count
		}
	}

	// list indexer
	const T& operator[](size_t aIndex) const
	{
		if (aIndex >= fCount)
		{
			throw std::out_of_range("SortedList<>::operator[]: index out of range");
		}

		Node* lNode = fRoot;

		for (size_t i = 0; i < aIndex; i++)
		{
			lNode = const_cast<Node*>(&lNode->getNext());
		}

		return **lNode;
	}

	// return a forward iterator
	Iterator begin() const
	{
		return Iterator(fRoot);
	}

	// return a forward end iterator
	Iterator end() const
	{
		return Iterator(fRoot).end();
	}

	// return a backward iterator
	Iterator rbegin() const
	{
		return Iterator(fRoot).rbegin();
	}

	// return a backward end iterator
	Iterator rend() const
	{
		return Iterator(fRoot).rend();
	}
};