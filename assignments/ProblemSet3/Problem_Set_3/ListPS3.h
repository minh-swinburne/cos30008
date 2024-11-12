
// COS30008, List, Problem Set 3, 2024

#pragma once

#include "DoublyLinkedList.h"
#include "DoublyLinkedListIterator.h"

#include <stdexcept>

template<typename T>
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

	~List()                                                             // destructor - frees all nodes
    {
        while ( fRoot != nullptr )
        {
            if ( fRoot != &fRoot->getPrevious() )                       // more than one element
            {
                Node* lTemp = const_cast<Node*>(&fRoot->getPrevious()); // select last
                
                lTemp->isolate();                                       // remove from list
                delete lTemp;                                           // free
            }
            else
            {
                delete fRoot;                                           // free last
                break;                                                  // stop loop
            }
        }
    }

    void remove( const T& aElement )	                                // remove first match from list
    {
        Node* lNode = fRoot;                                            // start at first
        
        while ( lNode != nullptr )                                      // Are there still nodes available?
        {
            if ( **lNode == aElement )                                  // Have we found the node?
            {
                break;                                                  // stop the search
            }

            if ( lNode != &fRoot->getPrevious() )                       // not reached last
            {
                lNode = const_cast<Node*>(&lNode->getNext());           // go to next
            }
            else
            {
                lNode = nullptr;                                        // stop search
            }
        }
        
        // At this point we have either reached the end or found the node.
        if ( lNode != nullptr )                                         // We have found the node.
        {
            if ( fCount != 1 )                                          // not the last element
            {
                if ( lNode == fRoot )
                {
                    fRoot = const_cast<Node*>(&fRoot->getNext());       // make next root
                }
            }
            else
            {
                fRoot = nullptr;                                        // list becomes empty
            }
            
            lNode->isolate();                                           // isolate node
            delete lNode;                                               // release node's memory
            fCount--;                                                   // decrement count
        }
    }

	//////////////////////////////////////////////////////////////////
    //// PS3
    //////////////////////////////////////////////////////////////////
    
	// P1

    // default constructor
    List() :
        fRoot(nullptr),
        fCount(0)
    { }

    // Is list empty?
    bool empty() const
    {
		return fRoot == nullptr;
    }

    // list size
    size_t size() const
    {
        return fCount;
    }

    // adds aElement at front
    void push_front(const T& aElement)
    {
        // allocates a new list node on the heap
        Node* lNode = new Node(aElement);

        // If the list is not currently empty
        // puts the new node in front of the existing root node
        if (!empty())
        {
            fRoot->push_front(*lNode);
        }

        // sets new root node
        fRoot = lNode;
        // increments count
        fCount++;
    }

    // return a forward iterator
    Iterator begin() const
    {
        // Default iterator is at begin position
        return Iterator(fRoot);
    }

    // return a forward end iterator
    Iterator end() const
    {
        return Iterator(fRoot).end();
    }

    // return a backwards iterator
    Iterator rbegin() const
    {
        return Iterator(fRoot).rbegin();
    }

    // return a backwards end iterator
    Iterator rend() const
    {
        return Iterator(fRoot).rend();
    }

	// P2
	
    // adds aElement at back
    // push_back is similar to push_front in node order themselves,
    // except push_back keeps the old root node (if exists) of the List object
    void push_back(const T& aElement)
    {
        // gets the root node address
        Node* lRoot = fRoot;   
        // pushes the new node to the start of the list
        push_front(aElement);

        // If there exists a root node previously
        // re-assigns the root node
        if (lRoot != nullptr)
        {
            fRoot = lRoot;
        }
    }

	// P3

    // list indexer
    const T& operator[](size_t aIndex) const
    {
        // throws exception if index is out of bounds
        if (aIndex >= fCount)
        {
            throw std::out_of_range("Index out of bounds.");
        }

        // starts searching from the root node
        // works with address so that 
        // neither the returned value go out of scope (if use Node)
        // nor the node get changed when iterating through the list (if use Node&)
        const Node* lNode = fRoot;

        for ( ; aIndex > 0; aIndex--)
        {
            // gets the address of the next node
            lNode = &(lNode->getNext());
        }

        // returns the payload of the desired node
        return **lNode;
    }

	// P4
	
    // copy constructor
    List(const List& aOtherList) :
        fRoot(nullptr),
        fCount(0)
    {
        *this = aOtherList;
    }

    // assignment operator
    List& operator=(const List& aOtherList)
    {
        // protection against accidental suicide
        if (&aOtherList != this)
        {
            // releases all old resources
            this->~List();
            // resets count
            fCount = 0;

            // appends each element of the other list to this list (deep copy)
            for (const T& element : aOtherList)
            {
                push_back(element);
            }
        }

        return *this;
    }
    
	// P5

    // move constructor
    List(List&& aOtherList) noexcept :
        fRoot(nullptr),
        fCount(0)
    {
        *this = std::move(aOtherList);
    }

    // move assignment operator
    List& operator=(List&& aOtherList) noexcept
    {
        // protection against accidental suicide
        if (&aOtherList != this)
        {
            // releases all old resources
            this->~List();

            // sets object members to the other list's members
            // No need to use std::move() for primitive types and pointers
            fRoot = aOtherList.fRoot;
            fCount = aOtherList.fCount;

            // empties the old list by resetting its members
            aOtherList.fRoot = nullptr;
            aOtherList.fCount = 0;
        }

        return *this;
    }

    // move push_front
    void push_front(T&& aElement)
    {
        // calls Node's constructor for r-value
        Node* lNode = new Node(std::move(aElement));

        // The rest looks like the reference-based overload
        if (!empty())
        {
            fRoot->push_front(*lNode);
        }

        fRoot = lNode;
        fCount++;
    }

    // move push_back
    void push_back(T&& aElement)
    {
        Node* lRoot = fRoot;
        // calls the overload for r-value
        push_front(std::move(aElement));

        if (lRoot != nullptr)
        {
            fRoot = lRoot;
        }
    }
};

