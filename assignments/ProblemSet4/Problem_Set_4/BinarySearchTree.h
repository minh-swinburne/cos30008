
// COS30008, Problem Set 4, Problem 2, 2022

#pragma once

#include "BinaryTreeNode.h"

#include <stdexcept>

// Problem 3 requirement
template<typename T>
class BinarySearchTreeIterator;

template<typename T>
class BinarySearchTree
{
private:

    using BNode = BinaryTreeNode<T>;
    using BTreeNode = BNode*;

    BTreeNode fRoot;
    
public:

    BinarySearchTree();

    ~BinarySearchTree();

    bool empty() const;
    size_t height() const;
    
    bool insert( const T& aKey );
    bool remove( const T& aKey );

	// Problem 3 methods
    
    using Iterator = BinarySearchTreeIterator<T>;

    // Allow iterator to access private member variables
    friend class BinarySearchTreeIterator<T>;

    Iterator begin() const;
    Iterator end() const;
};
