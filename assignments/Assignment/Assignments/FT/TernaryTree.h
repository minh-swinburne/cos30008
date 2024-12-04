
// COS30008, Final Exam

#pragma once

#include <stdexcept>
#include <algorithm>

template<typename T>
class TernaryTreePrefixIterator;

template<typename T>
class TernaryTree
{
public:
    
    using TTree = TernaryTree<T>;
    using TSubTree = TTree*;

private:
    
    T fKey;
    TSubTree fSubTrees[3];

    // private default constructor used for declaration of NIL
    TernaryTree() :
        fKey(T())
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            fSubTrees[i] = &NIL;
        }
    }

public:

    using Iterator = TernaryTreePrefixIterator<T>;
        
    static TTree NIL;           // sentinel

    // getters for subtrees
    const TTree& getLeft() const { return *fSubTrees[0]; }
    const TTree& getMiddle() const { return *fSubTrees[1]; }
    const TTree& getRight() const { return *fSubTrees[2]; }

    // add a subtree
    void addLeft( const TTree& aTTree ) { addSubTree( 0, aTTree ); }
    void addMiddle( const TTree& aTTree ) { addSubTree( 1, aTTree ); }
    void addRight( const TTree& aTTree ) { addSubTree( 2, aTTree ); }
            
    // remove a subtree, may through a domain error
    const TTree& removeLeft() { return removeSubTree( 0 ); }
    const TTree& removeMiddle() { return removeSubTree( 1 ); }
    const TTree& removeRight() { return removeSubTree( 2 ); }

/////////////////////////////////////////////////////////////////////////
// Problem 1: TernaryTree Basic Infrastructure

private:

    // remove a subtree, may throw a domain error [22]
    const TTree& removeSubTree( size_t aSubtreeIndex );
    
    // add a subtree; must avoid memory leaks; may throw domain error [18]
    void addSubTree( size_t aSubtreeIndex, const TTree& aTTree );
    
public:
    
    // TernaryTree l-value constructor [10]
	TernaryTree( const T& aKey );
    
    // destructor (free sub-trees, must not free empty trees) [14]
	~TernaryTree();
    
    // return key value, may throw domain_error if empty [2]
	const T& operator*() const;

    // returns true if this ternary tree is empty [4]
	bool empty() const;

    // returns true if this ternary tree is a leaf [10]
	bool leaf() const;

    // return height of ternary tree, may throw domain_error if empty [48]
    size_t height() const;
    
/////////////////////////////////////////////////////////////////////////
// Problem 2: TernaryTree Copy Semantics
    
    // copy constructor, must not copy empty ternary tree
	TernaryTree( const TTree& aOtherTTree );

    // copy assignment operator, must not copy empty ternary tree
    // may throw a domain error on attempts to copy NIL
	TTree& operator=( const TTree& aOtherTTree );
    
    // clone ternary tree, must not copy empty trees
	TSubTree clone() const;

/////////////////////////////////////////////////////////////////////////
// Problem 3: TernaryTree Move Semantics

    // TTree r-value constructor
	TernaryTree( T&& aKey );

    // move constructor, must not copy empty ternary tree
	TernaryTree( TTree&& aOtherTTree );

    // move assignment operator, must not copy empty ternary tree
	TTree& operator=( TTree&& aOtherTTree );
    
/////////////////////////////////////////////////////////////////////////
// Problem 4: TernaryTree Prefix Iterator

    // return ternary tree prefix iterator positioned at start
	Iterator begin() const;

    // return ternary prefix iterator positioned at end
	Iterator end() const;
};

template<typename T>
TernaryTree<T> TernaryTree<T>::NIL;
