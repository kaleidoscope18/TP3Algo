/*
 * Noeud.cpp
 *
 *  Created on: 2016-12-08
 *  Author : Nadia
 *    Source #1 : https://github.com/saadtaame/pairing-heap/blob/master/pairing_heap.cc
 *    Source #2 : https://users.cs.fiu.edu/~weiss/ (Mark Allen Weiss)
 */

#include "Noeud.h"

Noeud::Noeud(const unsigned int & dist, const unsigned int & sommet) :
		distance(dist), m_sommet(sommet), enfantGauche(nullptr), voisin(
				nullptr), maitre(nullptr) {
}

const unsigned int & Noeud::getSommet() const {
	return m_sommet;
}
