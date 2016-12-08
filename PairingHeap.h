#ifndef PAIRING_HEAP_H_
#define PAIRING_HEAP_H_

#include <iostream>       // For NULL

// Pairing heap class
//
// CONSTRUCTION: with no parameters
//
// ******************PUBLIC OPERATIONS*********************
// PairNode & insert( x ) --> Insert x
// deleteMin( minItem )   --> Remove (and optionally return) smallest item
// Comparable findMin( )  --> Return smallest item
// bool isEmpty( )        --> Return true if empty; else false
// bool isFull( )         --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void decreaseKey( PairNode p, newVal )
//                        --> Decrease value in node p
// ******************ERRORS********************************
// Throws Underflow as warranted


  // Node and forward declaration because g++ does
  // not understand nested classes.
class PairingHeap;

class PairNode
{
public:
	unsigned int   element;
	unsigned int m_sommet;
	PairNode    *leftChild;
	PairNode    *nextSibling;
	PairNode    *prev;

	PairNode( const unsigned int & theElement, const unsigned int & sommet ) : element( theElement ), m_sommet( sommet ),
	  leftChild( NULL ), nextSibling( NULL ), prev( NULL ) { }
	const unsigned int & getSommet() const;
	friend class PairingHeap;
};

class PairingHeap
{
  public:
	PairingHeap( );
	PairingHeap( const PairingHeap & rhs );
	~PairingHeap( );

	bool isEmpty( ) const;
	bool isFull( ) const;
	const unsigned int & findMin( ) const;

	PairNode *insert( const unsigned int & x, const unsigned int & sommet );
	void deleteMin( );
	void deleteMin( unsigned int & minItem );
	void makeEmpty( );
	void decreaseKey( PairNode *p, const unsigned int & newVal );
	PairNode * findRoot() const;
//	const PairingHeap & operator=( const PairingHeap & rhs );

  private:
	PairNode *root;

	void reclaimMemory( PairNode *t ) const;
	void compareAndLink( PairNode * & first, PairNode *second ) const;
	PairNode * combineSiblings( PairNode *firstSibling ) const;
//	PairNode * clone( PairNode * t ) const;
};

#endif
