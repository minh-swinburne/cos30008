
// COS30008, Doubly-linked Nodes, Tutorial 9, 2022

#pragma once

template<typename T>
class DoublyLinkedList
{
private:
    T fPayload;
    DoublyLinkedList* fNext;
    DoublyLinkedList* fPrevious;
    
public:
    // l-value constructor and r-value constructor
    explicit DoublyLinkedList( const T& aPayload ) :
        fPayload(aPayload),
        fNext(this),
        fPrevious(this)
    { }

    explicit DoublyLinkedList( T&& aPayload ) :
		fPayload(std::move(aPayload)),
		fNext(this),
		fPrevious(this)
	{ }

    // link functions
    DoublyLinkedList& push_front(DoublyLinkedList& aNode)
    {
        aNode.fNext = this;
        aNode.fPrevious = fPrevious;

        fPrevious->fNext = &aNode;
        fPrevious = &aNode;

        return aNode;
    }

    DoublyLinkedList& push_back(DoublyLinkedList& aNode)
    {
        aNode.fPrevious = this;
        aNode.fNext = fNext;

        fNext->fPrevious = &aNode;
        fNext = &aNode;

        return aNode;
    }

    // unlink list node
    void isolate()
    {
        fPrevious->fNext = fNext;
        fNext->fPrevious = fPrevious;
        fPrevious = this;
        fNext = this;
    }
    
    // exchance payload positions of list nodes
    void swap(DoublyLinkedList& aNode)
    {
		T temp = fPayload;
		fPayload = aNode.fPayload;
		aNode.fPayload = temp;
    }
    
    // getters
    const T& operator*() const
    {
		return fPayload;
    }

    const T& getPayload() const
    {
		return fPayload;
    }

    const DoublyLinkedList& getNext() const
    {
        return *fNext;
    }

    const DoublyLinkedList& getPrevious() const
    {
        return *fPrevious;
    }
};
