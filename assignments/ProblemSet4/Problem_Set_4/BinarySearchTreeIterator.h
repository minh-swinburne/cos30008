
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
    
    void pushLeft( BTreeNode aNode );
    
public:
    
    using Iterator = BinarySearchTreeIterator<T>;
    
    BinarySearchTreeIterator( const BSTree& aBSTree );

    const T& operator*() const;
    Iterator& operator++();
    Iterator operator++(int);
    bool operator==( const Iterator& aOtherIter ) const;
    bool operator!=( const Iterator& aOtherIter ) const;
    
    Iterator begin() const;
    Iterator end() const;
};
