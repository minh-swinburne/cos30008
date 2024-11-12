
// COS30008, Doubly-linked Nodes, Tutorial 9, 2022

#pragma once

#include "DoublyLinkedList.h"

template<typename T>
class DoublyLinkedListIterator
{
private:
	enum class States { BEFORE, DATA , AFTER };					// iterator states

	using Node = DoublyLinkedList<T>;

	const Node* fRoot;											// doubly-linked list

    States fState;												// iterator state
    const Node* fCurrent;										// iterator position
    
public:    
	using Iterator = DoublyLinkedListIterator<T>;

	// constructor
	DoublyLinkedListIterator(const Node* aRoot) :
		fRoot(aRoot),
		fState(States::DATA),
		fCurrent(aRoot)
	{ }

	// dereference 
	const T& operator*() const
	{
		return fCurrent->getPayload();
	}

	// prefix increment
	Iterator& operator++()
	{
		if (fState == States::BEFORE)
		{
			fState = States::DATA;
			fCurrent = fRoot;
		}
		else if (fState == States::DATA)
		{
			fCurrent = &(fCurrent->getNext());

			// if we are at the root node (again),
			// we have reached the end of the list
			if (fCurrent == fRoot)
			{
				fState = States::AFTER;
			}
		}
		return *this;
	}

	// postfix increment
	Iterator operator++(int)
	{
		Iterator old = *this;
		++(*this);
		return old;
	}

	// prefix decrement
	Iterator& operator--()
	{
		const Node* lLast = &(fRoot->getPrevious());

		if (fState == States::AFTER)
		{
			fState = States::DATA;
			fCurrent = lLast;
		}
		else if (fState == States::DATA)
		{
			fCurrent = &(fCurrent->getPrevious());

			if (fCurrent == lLast)
			{
				fState = States::BEFORE;
			}
		}

		return *this;
	}

	// postfix decrement
	Iterator operator--(int)
	{
		Iterator old = *this;
		--(*this);
		return old;
	}

	// equivalence
	bool operator==(const Iterator& aOtherIter) const
	{
		return (
				(fState == aOtherIter.fState) 
				|| (fRoot == nullptr)
			)
			&& (fRoot == aOtherIter.fRoot)
			&& (fCurrent == aOtherIter.fCurrent);
	}

	// not equal
	bool operator!=(const Iterator& aOtherIter) const
	{
		return !(*this == aOtherIter);
	}

	// first element forward
	Iterator begin() const
	{
		Iterator iter = *this;
		iter.fCurrent = fRoot;
		iter.fState = States::DATA;
		return iter;
	}

	// after last element forward
	Iterator end() const
	{
		Iterator iter = begin();
		iter.fState = States::AFTER;
		return iter;
	}

	// first element backwards
	Iterator rbegin() const
	{
		Iterator iter = *this;
		iter.fState = States::DATA;
		if (fRoot != nullptr)
		{
			iter.fCurrent = &(fRoot->getPrevious());
		}
		return iter;
	}

	// before first element backwards
	Iterator rend() const
	{
		Iterator iter = rbegin();
		iter.fState = States::BEFORE;
		return iter;
	}
};
