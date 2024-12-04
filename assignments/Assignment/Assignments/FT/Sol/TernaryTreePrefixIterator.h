
// COS30008, Final Exam

#pragma once

#include "TernaryTree.h"

#include <stack>

template<typename T>
class TernaryTreePrefixIterator
{
private:
    using TTree = TernaryTree<T>;
    using TTreeNode = TTree*;
    using TTreeStack = std::stack<const TTree*>;
    
    const TTree* fTTree;             // ternary tree
    TTreeStack fStack;               // traversal stack

public:

    using Iterator = TernaryTreePrefixIterator<T>;
           
    Iterator operator++(int)
    {
        Iterator old = *this;

        ++(*this);
               
        return old;
    }
           
    bool operator!=( const Iterator& aOtherIter ) const
    {
        return !(*this == aOtherIter);
    }

/////////////////////////////////////////////////////////////////////////
// Problem 4: TernaryTree Prefix Iterator

private:

	// push subtree of aNode
	void push_subtrees( const TTree* aNode )
    {
        if ( !aNode->getRight().empty() )                   // 5
        {
            fStack.push( &aNode->getRight() );              // 5
        }

        if ( !aNode->getMiddle().empty() )                  // 5
        {
            fStack.push( &aNode->getMiddle() );             // 5
        }

        if ( !aNode->getLeft().empty() )                    // 5
        {
            fStack.push( &aNode->getLeft() );               // 5(30)
        }
    }
    
 public:

	// iterator constructor
	TernaryTreePrefixIterator( const TTree* aTTree ) :
        fTTree(aTTree)                                      // 4
    {
        if ( !fTTree->empty() )                             // 4
        {
            fStack.push( fTTree );                          // 4(12)
        }
    }

	// iterator dereference
	const T& operator*() const
    {
        return **fStack.top();                              // (8)
    }

    // prefix increment
	Iterator& operator++()
    {
        const TTree* lTop = fStack.top();                   // 4

        fStack.pop();                                       // 2
        
        push_subtrees( lTop );                              // 4
        
        return *this;                                       // 2(12)
    }

	// iterator equivalence
	bool operator==( const Iterator& aOtherIter ) const
    {
        return
            fTTree == aOtherIter.fTTree &&                  // 6
            fStack.size() == aOtherIter.fStack.size();      // 6(12)
    }

	// auxiliaries
	Iterator begin() const
    {
        return TernaryTreePrefixIterator( fTTree );         // (4)
    }

    Iterator end() const
    {
        Iterator Result = *this;                            // 4
        
        Result.fStack = TTreeStack();                       // 4
        
        return Result;                                      // 2(10)
    }
};
