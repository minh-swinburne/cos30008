
// COS30008, List, Problem Set 3, 2022

#pragma once

#include "DoublyLinkedList.h"
#include "DoublyLinkedListIterator.h"

#include <stdexcept>

template<class T> 
class List
{
private:
	// auxiliary definition to simplify node usage
	using Node = DoublyLinkedList<T>;

	Node* fRoot;	// the first element in the list
	size_t fCount;	// number of elements in the list

public:
	// auxiliary definition to simplify iterator usage
    using Iterator = DoublyLinkedListIterator<T>;
    
	List();                              		// default constructor - creates empty list
	List( const List& aOtherList );             // copy constructor
	List( List&& aOtherList );                  // move constructor
	List& operator=( const List& aOtherList );  // assignment operator
	List& operator=( List&& aOtherList );       // move assignment operator
	~List();                                    // destructor - frees all nodes
    
	bool empty() const;	                        // Is list empty?
	size_t size() const;                		// list size

	void push_front( const T& aElement );	    // adds aElement at front (copy)
	void push_front( T&& aElement );            // adds aElement at front (move)
	void push_back( const T& aElement );        // adds aElement at back (copy)
	void push_back( T&& aElement );           	// adds aElement at back (move)
	void remove( const T& aElement );	       	// remove first match from list

	const T& operator[]( size_t aIndex ) const;	// list indexer

	Iterator begin() const;                     // return a forward iterator
	Iterator end() const;                       // return a forward end iterator
	Iterator rbegin() const;                    // return a backwards iterator
	Iterator rend() const;                      // return a backwards end iterator
};
