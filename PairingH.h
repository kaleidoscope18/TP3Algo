/*
 * PairingH.h
 *
 *  Created on: 2016-12-07
 *      Author: etudiant
 */

#ifndef PAIRINGH_H_
#define PAIRINGH_H_

#include <iostream>
#include "Noeud.h"

class PairingH
{
  public:
	PairingH();
	PairingH(const PairingH & nouvPH);

	bool estVide() const;
	Noeud * getRacine() const;
	Noeud *ajouterNoeud(const int & dist, const unsigned int & sommet);
	void retirerRacine();
	void diminuerDistance(Noeud *p, const int & nouvDistance);
	int nombreNoeuds() const;
	void parcoursDOT(Noeud * p_debut) const;
	Noeud * racine;

  private:
	static int nbNoeuds;
	void fusionner(Noeud * & first, Noeud *second) const;
	Noeud * fusionPassePasse(Noeud *firstSibling) const;
};


#endif /* PAIRINGH_H_ */
