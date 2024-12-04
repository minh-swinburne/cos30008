
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

	// remove a subtree;
    // may throw a domain error on removing NIL
    // may throw an out of range on illegal subtree index
    const TTree& removeSubTree( size_t aSubtreeIndex )
    {
        if ( aSubtreeIndex >= 3 )                                       // 4
        {
            throw std::out_of_range( "Illegal subtree index" );         // 2
        }
        
        // fSubTrees[aSubtreeIndex] == &NIL
        if ( fSubTrees[aSubtreeIndex]->empty() )                        // 4
        {
            throw std::domain_error( "Subtree is NIL" );                // 2
        }
        
        const TTree& Result = *fSubTrees[aSubtreeIndex];                // 4
        
        fSubTrees[aSubtreeIndex] = &NIL;                                // 4
        
        return Result;                                                  // 2(22)
    }
    
    // add a subtree; must avoid memory leaks
    // may throw a domain error on adding to non-NIL subtree
    // may throw an out of range on illegal subtree index
    void addSubTree( size_t aSubtreeIndex, const TTree& aTTree )
    {
        if ( aSubtreeIndex >= 3 )                                       // 4
        {
            throw std::out_of_range( "Illegal subtree index" );         // 2
        }
        
        // fSubTrees[aSubtreeIndex] != &NIL
        if ( !fSubTrees[aSubtreeIndex]->empty() )                       // 4
        {
            throw std::domain_error( "Subtree is not NIL" );            // 2
        }
        
        // const cast required
        fSubTrees[aSubtreeIndex] = const_cast<TSubTree>(&aTTree);       // 6(18)
    }
    
public:
    
    // TernaryTree l-value constructor
	TernaryTree( const T& aKey ) :
        fKey(aKey)                                                      // 2
    {
        for ( size_t i = 0; i < 3; i++ )                                // 5
        {
            fSubTrees[i] = &NIL;                                        // 3(10)
        }
    }

    // destructor (free sub-trees, must not free empty trees)
	~TernaryTree()
    {
        for ( size_t i = 0; i < 3; i++ )                                // 5
        {
            // fSubtree[i] != &NIL
            if ( !fSubTrees[i]->empty() )                               // 5
            {
                delete fSubTrees[i];                                    // 4(14)
            }
        }
    }
    
    // return key value, may throw domain_error if empty
	const T& operator*() const
    {
        if ( empty() )                                                  // 2
        {
            throw std::domain_error( "NIL payload access" );            // 2
        }
        return fKey;                                                    // (6)
    }

    // returns true if this ternary tree is empty
	bool empty() const
    {
        return this == &NIL;                                            // (4)
    }

    // returns true if this ternary tree is a leaf
	bool leaf() const
    {
        return                                                          // 1
            fSubTrees[0] == &NIL &&                                     // 3
            fSubTrees[1] == &NIL &&                                     // 3
            fSubTrees[2] == &NIL;                                       // 3(10)
    }

    // return height of ternary tree, may throw domain_error if empty
    size_t height() const
    {
        if ( empty() )                                                  // 3
        {
            throw std::domain_error( "Operation not supported" );       // 2
        }
        
        // leaf
        if ( leaf() )                                                   // 3
        {
            return 0;                                                   // 2
        }
        
        // need variables
        size_t lLeft = 0;                                               // 2
        size_t lMiddle = 0;                                             // 2
        size_t lRight = 0;                                              // 2
        
        // left
        if ( !fSubTrees[0]->empty() )                                   // 4
        {
            lLeft = fSubTrees[0]->height();                             // 4
        }
        
        // middle
        if ( !fSubTrees[1]->empty() )                                   // 4
        {
            lMiddle = fSubTrees[1]->height();                           // 4
        }
        
        // right
        if ( !fSubTrees[2]->empty() )                                   // 4
        {
            lRight = fSubTrees[2]->height();                            // 4
        }
        
        return std::max( lLeft, std::max( lMiddle, lRight ) ) + 1;      // 8(48)
    }
    
/////////////////////////////////////////////////////////////////////////
// Problem 2: TernaryTree Copy Semantics
    
    // copy constructor, must not copy empty ternary tree
	TernaryTree( const TTree& aOtherTTree ) :
        /* just use default private default constructor */
        TernaryTree()                                                    // 4
    {
        // use assignent operator
        *this = aOtherTTree;                                            // 6(10)
    }

    // copy assignment operator, must not copy empty ternary tree
    // may throw a domain error on attempts to copy NIL
    TTree& operator=( const TTree& aOtherTTree )
    {
        if ( aOtherTTree.empty() )                                      // 4
        {
            throw std::domain_error( "NIL as source not permitted." );  // 2
        }
        
        if ( this != &aOtherTTree )                                     // 4
        {
            // free this
            this->~TernaryTree();                                       // 4
            
            fKey = aOtherTTree.fKey;                                    // 2
            
            // just use clone
            fSubTrees[0] = aOtherTTree.getLeft().clone();               // 6
            fSubTrees[1] = aOtherTTree.getMiddle().clone();             // 6
            fSubTrees[2] = aOtherTTree.getRight().clone();              // 6
        }
        
        return *this;                                                   // 2(36)
    }
    
    // clone ternary tree, must not copy empty trees
	TSubTree clone() const
    {
        if ( empty() )                                                  // 3
        {
            // const cast required (remove const)
            return const_cast<TSubTree>(this);                          // 4
        }
        else
        {
            return new TTree( *this );                                  // 3(10)
        }
    }

/////////////////////////////////////////////////////////////////////////
// Problem 3: TernaryTree Move Semantics

    // TTree r-value constructor
	TernaryTree( T&& aKey ) :
        fKey(std::move(aKey))                                           // 4
    {
        for ( size_t i = 0; i < 3; i++ )                                // 5
        {
            fSubTrees[i] = &NIL;                                        // 3(12)
        }
    }

    // move constructor, must not copy empty ternary tree
	TernaryTree( TTree&& aOtherTTree ) :
        /* just use default private default constructor */
        TernaryTree()                                                    // 4
    {
        // use assignent operator
        *this = std::move(aOtherTTree);                                 // 8(12)
    }

    // move assignment operator
    // may throw a domain error on attempts to copy NIL
    TTree& operator=( TTree&& aOtherTTree )
    {
        if ( aOtherTTree.empty() )                                      // 4
        {
            throw std::domain_error( "NIL as source not permitted." );  // 2
        }
        
        if ( this != &aOtherTTree )                                     // 4
        {
            // free this
            this->~TernaryTree();                                       // 4

            // swap preparation
            fKey = T();                                                 // 2

            for ( size_t i = 0; i < 3; i++ )
            {
                fSubTrees[i] = &NIL;                                    // 6
            }

            std::swap( fKey, aOtherTTree.fKey );                        // 3
            std::swap( fSubTrees[0], aOtherTTree.fSubTrees[0] );        // 3
            std::swap( fSubTrees[1], aOtherTTree.fSubTrees[1] );        // 3
            std::swap( fSubTrees[2], aOtherTTree.fSubTrees[2] );        // 3
        }
        
        return *this;                                                   // 2(36)
    }

/////////////////////////////////////////////////////////////////////////
// Problem 4: TernaryTree Prefix Iterator

    // return ternary tree iterator positioned at start
	Iterator begin() const
    {
        return Iterator( this );                                        // (6)
    }

    // return ternary iterator positioned at end
	Iterator end() const
    {
        return begin().end();                                           // (4)
    }
};

template<typename T>
TernaryTree<T> TernaryTree<T>::NIL;
