/*
 * PairingH.h
 *
 *  Created on: 2016-12-07
 *      Author: etudiant
 */

#ifndef PAIRINGH_H_
#define PAIRINGH_H_

#include <iostream>       // For NULL

// Pairing heap class
//
// CONSTRUCTION: with no parameters
//
// ******************PUBLIC OPERATIONS*********************
// Node & insert( x ) --> Insert x
// deleteMin( minItem )   --> Remove (and optionally return) smallest item
// Comparable findMin( )  --> Return smallest item
// bool isEmpty( )        --> Return true if empty; else false
// bool isFull( )         --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void diminuerDistance( Node p, newVal )
//                        --> Decrease value in node p
// ******************ERRORS********************************
// Throws Underflow as warranted


  // Node and forward declaration because g++ does
  // not understand nested classes.
class PairingH;

class Node
{
private:
	int distance;
	unsigned int m_sommet;
	Node *enfantGauche;
	Node *voisin;
	Node *maitre;

public:
	Node(const int & dist, const unsigned int & sommet) : distance(distance), m_sommet(sommet),
	  enfantGauche(NULL), voisin(NULL), maitre(NULL) { }

	Node * getVoisin();
	int getDistance();
	Node * getEnfantGauche();
	unsigned int getSommet();

	friend class PairingH;
};

class PairingH
{
  public:
	PairingH( );
	PairingH( const PairingH & nouvPH );
	~PairingH( );

	bool isEmpty( ) const;
	const int & findMin( ) const;
	Node * getRacine( ) const;
	Node *insert( const int & x );
	void deleteMin( );
	void diminuerDistance(Node *p, const int & nouvDistance);

	const PairingH & operator=( const PairingH & rhs );

  private:
	Node *racine;

	void reclaimMemory( Node *t ) const;
	void fusionner( Node * & first, Node *second ) const;
	Node * fusionPassePasse( Node *firstSibling ) const;
	Node * clone( Node * t ) const;
};


#endif /* PAIRINGH_H_ */
