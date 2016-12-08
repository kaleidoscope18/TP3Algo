/*
 * PairingHeap.cpp
 *
 *  Created on: 2016-12-08
 *  Author : Nadia
 *    Source #1 : https://github.com/saadtaame/pairing-heap/blob/master/pairing_heap.cc
 *    Source #2 : https://users.cs.fiu.edu/~weiss/ (Mark Allen Weiss)
 */
#ifndef PAIRING_HEAP_H_
#define PAIRING_HEAP_H_

#include <iostream>
#include "Noeud.h"


class PairingH
{
  public:
	PairingH();

	bool estVide() const;
	const unsigned int & trouverDistanceMin() const;

	Noeud * ajouterNoeud(const unsigned int & dist, const unsigned int & sommet);
	void supprimerRacine();
	void diminuerDistance(Noeud *p, const unsigned int & newVal);
	Noeud * getRacine() const;

	void parcoursDOT(Noeud * p_debut) const;

  private:
	Noeud * racine;
	void fusionner(Noeud * & A, Noeud * B) const;
	Noeud * fusionPassePasse(Noeud * noeud) const;
};

#endif
