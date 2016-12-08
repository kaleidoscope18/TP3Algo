/*
 * Noeud.h
 *
 *  Created on: 2016-12-08
 *  Author : Nadia
 *    Source #1 : https://github.com/saadtaame/pairing-heap/blob/master/pairing_heap.cc
 *    Source #2 : https://users.cs.fiu.edu/~weiss/ (Mark Allen Weiss)
 */

#ifndef NOEUD_H_
#define NOEUD_H_

class Noeud
{
public:
	unsigned int distance;
	unsigned int m_sommet;
	Noeud * enfantGauche;
	Noeud * voisin;
	Noeud * maitre;

	Noeud( const unsigned int & dist, const unsigned int & sommet );

	const unsigned int & getSommet() const;
};

#endif /* NOEUD_H_ */
