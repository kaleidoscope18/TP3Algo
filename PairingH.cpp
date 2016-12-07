/*
 * PairingH.cpp
 *
 *  Created on: 2016-12-07
 *      Author: Nadia
 */

#include "PairingH.h"
#include <stdexcept>
#include <vector>

/**
 * Constructeur par défaut
 */
PairingH::PairingH( )
{
	racine = NULL;
}
/*
 * Constructeur de copie
 */
PairingH::PairingH( const PairingH & nouvPH )
{
	racine = NULL;
	*this = nouvPH;
}
/**
 * Insert item x into the priority queue, maintaining heap order.
 * Return a pointer to the node containing the new item.
 */

Node * PairingH::insert( const int & x )
{
	Node *newNode = new Node( x );

	if( racine == NULL )
		racine = newNode;
	else
		fusionner( racine, newNode );
	return newNode;
}

/**
 * Find the smallest item in the priority queue.
 * Return the smallest item, or throw std::logic_error if empty.
 */

const int & PairingH::findMin( ) const
{
	if( isEmpty( ) )
		throw std::logic_error("logic error heap is empty");
	return racine->distance;
}

Node * PairingH::getRacine( ) const{
	return racine;
}

/**
 * Remove the smallest item from the priority queue.
 * Throws std::logic_error if empty.
 */

void PairingH::deleteMin( )
{
	if( isEmpty( ) )
		throw std::logic_error("logic error heap is empty");

	Node *oldracine = racine;

	if( racine->getEnfantGauche() == NULL )
		racine = NULL;
	else
		racine = fusionPassePasse( racine->getEnfantGauche() );

	delete oldracine;
}
/**
 * Test if the priority queue is logically empty.
 * Returns true if empty, false otherwise.
 */
bool PairingH::isEmpty( ) const
{
	return racine == NULL;
}
/**
 * Change the value of the item stored in the pairing heap.
 * Does nothing if newVal is larger than currently stored value.
 * p points to a node returned by insert.
 * newVal is the new value, which must be smaller
 *    than the currently stored value.
 */
void PairingH::diminuerDistance( Node *p, const int & nouvDistance )
{
	if( p->distance < newVal )
		return;    // newVal cannot be bigger
	p->distance = newVal;
	if( p != racine )
	{
		if( p->voisin != NULL )
			p->voisin->maitre = p->maitre;
		if( p->maitre->getEnfantGauche() == p )
			p->maitre->getEnfantGauche() = p->voisin;
		else
			p->maitre->voisin = p->voisin;

		p->voisin = NULL;
		fusionner( racine, p );
	}
}

/**
 * Internal method that is the basic operation to maintain order.
 * Links first and second together to satisfy heap order.
 * first is racine of tree 1, which may not be NULL.
 *    first->voisin MUST be NULL on entry.
 * second is racine of tree 2, which may be NULL.
 * first becomes the result of the tree merge.
 */

void PairingH::fusionner( Node * & A, Node *B ) const
{
	if( B == NULL )
		return;

	if( B->distance < A->distance ) {//B va devenir A et la A devient l'enfant gauche de B
		B->maitre = A->maitre;
		A->maitre = B;
		A->voisin = B->enfantGauche;
		if( A->voisin != NULL )
			A->voisin->maitre = first;
		B->getEnfantGauche() = A;
		A = B;
	}
	else { //B va devenir l'enfant gauche de A
		B->maitre = A;
		A->voisin = B->voisin;
		if( A->voisin != NULL )
			A->voisin->maitre = A;
		B->voisin = A->getEnfantGauche();
		if( B->voisin != NULL )
			B->voisin->maitre = B;
		A->getEnfantGauche() = B;
	}
}

/**
 * Implémentation du two-pass merging/pairing
 * voisinImmediat the racine of the conglomerate;
 *     assumed not NULL.
 */
Node * PairingH::fusionPassePasse(Node * voisinImmediat) const
{
    {
    	if(voisinImmediat == NULL){ //on ne doit pas avoir de racine nulle..
    		return NULL;
    	}
    	//pas de fusionPassePasse si on a pas de voisin
        if(voisinImmediat->voisin == NULL)
            return voisinImmediat;

            // On pourra ensuite mettre les sous-heaps dans le vecteur pour les refusionner plus tard
        static std::vector<Node *> sousMonceaux(5);
        int nombreVoisins = 0;
        for( ; voisinImmediat != NULL; nombreVoisins++) //pour chaque voisin qui existe
        {
            if(nombreVoisins == sousMonceaux.size()) //reallocation du vecteur, optimal pour pas avoir de reallocation a chaque fois
                sousMonceaux.resize(nombreVoisins*2);
            sousMonceaux[nombreVoisins] = voisinImmediat;
            voisinImmediat->maitre->voisin = NULL;  // après avoir stocké le voisin, on brise les liens
            voisinImmediat = voisinImmediat->voisin;
        }
        if(nombreVoisins == sousMonceaux.size()) //reallocation du vecteur
            sousMonceaux.resize(nombreVoisins+1);
        sousMonceaux[nombreVoisins] = NULL;

            // on fait la premiere passe en combinant des paires de sous heap
        int i = 0;
        for( ; i+1 < nombreVoisins; i += 2)
            fusionner(sousMonceaux[i], sousMonceaux[i+1]);

        int j = i - 2;

            // j has the result of last fusionner.
            // If an odd number of trees, get the last one.
        if(j == nombreVoisins - 3)
            fusionner(sousMonceaux[j], sousMonceaux[j + 2]);

            // Now go right to left, merging last tree with
            // next to last. The result becomes the new last.
        for( ; j >= 2; j -= 2)
            fusionner(sousMonceaux[j-2], sousMonceaux[j]);
        return sousMonceaux[0];
    }
}

Node * Node::getVoisin(){
	return voisin;
}

int Node::getDistance(){
	return distance;
}

Node * Node::getEnfantGauche(){
	return enfantGauche;
}

unsigned int Node::getSommet(){
	return m_sommet;
}
