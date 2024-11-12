
// COS30008, Tutorial 11, 2022

#pragma once

#include <stdexcept>
#include <algorithm>

using namespace std;

template<typename T>
class BTree
{
private:
    T fKey;                                         // T() for empty BTree
    BTree<T>* fLeft;
    BTree<T>* fRight;

    // sentinel constructor
    BTree() :
		fKey(T()),
		fLeft(&NIL),
		fRight(&NIL)
    { }

    // tree manipulator auxiliaries
    void attach(BTree<T>** aNode, const BTree<T>& aBTree)
    {
        if (empty())
        {
			throw domain_error("BTree::attach(): empty tree");
        }

		if (*aNode != &NIL)
		{
			throw domain_error("BTree::attach(): non-NIL target");
		}

		*aNode = const_cast<BTree<T> *>(& aBTree);
	}

    const BTree<T>& detach(BTree<T>** aNode)
    {
        if (empty())
        {
            throw domain_error("BTree::detach(): empty tree");
        }

		if (*aNode == &NIL)
		{
			throw domain_error("BTree::detach(): empty target");
		}

		const BTree<T>& result = **aNode;
		*aNode = &NIL;

		return result;
	}

public:
    // Empty BTree
    static BTree<T> NIL;

    // BTree leaf
    BTree(const T& aKey) :
		fKey(aKey),
		fLeft(&NIL),
		fRight(&NIL)
	{ }

    // destructor
    virtual ~BTree()
	{
		if (fLeft != &NIL)
		{
			delete fLeft;
		}

		if (fRight != &NIL)
		{
			delete fRight;
		}
	}

    // clone a tree
    virtual BTree* clone() const
	{
        return new BTree(*this);
	}

    // copy constructor
    BTree(const BTree& aOtherBTree) :
		fKey(aOtherBTree.fKey),
		fLeft(&NIL),
		fRight(&NIL)
    {
        *this = aOtherBTree;
    }

    // copy assignment operator
    BTree& operator=(const BTree& aOtherBTree)
    {
        // protect against accidental suicide
        if (this != &aOtherBTree)
        {
            if (aOtherBTree.empty())
            {
                throw domain_error("BTree::operator=(): copying NIL");
            }

            this->~BTree();
            fKey = aOtherBTree.fKey;

            if (aOtherBTree.fLeft != &NIL)
            {
                fLeft = aOtherBTree.fLeft->clone();
            }

            if (aOtherBTree.fRight != &NIL)
            {
                fRight = aOtherBTree.fRight->clone();
            }
        }

		return *this;
    }

    // BTree leaf
    BTree(T&& aKey) :
        fKey(move(aKey)),
        fLeft(&NIL),
        fRight(&NIL)
    { }

    // move constructor
    BTree(BTree&& aOtherBTree) :
        fLeft(&NIL),
        fRight(&NIL)
    {
        *this = move(aOtherBTree);
    }

    // move assignment operator
    BTree& operator=(BTree&& aOtherBTree)
    {
        if (this != &aOtherBTree)
        {
            if (aOtherBTree.empty())
            {
                throw domain_error("BTree::operator=(): moving NIL");
            }

            this->~BTree();
            fKey = move(aOtherBTree.fKey);

            if (aOtherBTree.fLeft != &NIL)
            {
                attachLeft(aOtherBTree.detach(&aOtherBTree.fLeft));
            }

            if (aOtherBTree.fRight != &NIL)
            {
                attachRight(aOtherBTree.detach(&aOtherBTree.fRight));
            }
        }

        return *this;
    }

    // is tree empty
    bool empty() const
    {
		return this == &NIL;
    }

    // get key (node value)
    const T& operator*() const
    {
		return fKey;
    }

    const BTree& left() const
    {
		return *fLeft;
    }

    const BTree& right() const
    {
        return *fRight;
    }

    // tree manipulators
    void attachLeft(const BTree<T>& aBTree)
    {
		attach(&fLeft, aBTree);
    }

    void attachRight(const BTree<T>& aBTree)
    {
		attach(&fRight, aBTree);
    }

    const BTree& detachLeft()
    {
        return detach(&fLeft);
    }

    const BTree& detachRight()
    {
		return detach(&fRight);
    }
};

template<class T>
BTree<T> BTree<T>::NIL;
