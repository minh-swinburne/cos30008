
// COS30008, Problem Set 4, Problem 3, 2022

#pragma once

#include "BinarySearchTree.h"

#include <stack>

template<typename T>
class BinarySearchTreeIterator
{
private:
    
    using BSTree = BinarySearchTree<T>;
    using BNode = BinaryTreeNode<T>;
    using BTreeNode = BNode*;
    using BTNStack = std::stack<BTreeNode>;

    const BSTree& fBSTree;		// binary search tree
    BTNStack fStack;			// DFS traversal stack
    
	// perform a DFS traversal along the left side of the tree
    void pushLeft(BTreeNode aNode)
    {
		while (!aNode->empty())
		{
			fStack.push(aNode);
			aNode = aNode->left;
		}
	}
    
public:
    
    using Iterator = BinarySearchTreeIterator<T>;
    
	// constructor
    BinarySearchTreeIterator( const BSTree& aBSTree ) :
		fBSTree(aBSTree),
		fStack(BTNStack())
	{
		pushLeft(fBSTree.fRoot);
	}

	// dereference operator
    const T& operator*() const
    {
		return fStack.top()->key;
    }

	// prefix increment
    Iterator& operator++()
    {
		BTreeNode lNode = fStack.top();
		fStack.pop();
		pushLeft(lNode->right);
		return *this;
    }

	// postfix increment
    Iterator operator++(int)
    {
		Iterator lTemp = *this;
		++(*this);
		return lTemp;
    }

	// comparison operators
    bool operator==(const Iterator& aOtherIter) const
    {
		return (&fBSTree == &aOtherIter.fBSTree)
            && (fStack == aOtherIter.fStack);
    }

    bool operator!=(const Iterator& aOtherIter) const
    {
		return !(*this == aOtherIter);
    }
    
	// return an iterator with initialized stack
    Iterator begin() const
    {
		return Iterator(fBSTree);
    }

	// return an end iterator with empty stack
    Iterator end() const
    {
        Iterator lIter = *this;
		lIter.fStack = BTNStack();
		return lIter;
    }
};
