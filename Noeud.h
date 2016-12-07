/*
 * Noeud.h
 *
 *  Created on: 2016-12-07
 *      Author: etudiant
 */

#ifndef NOEUD_H_
#define NOEUD_H_
#include <stdexcept>
#include <iostream>
class Noeud
{
private:
	int distance;
	unsigned int m_sommet;
	Noeud *enfantGauche;
	Noeud *voisin;
	Noeud *maitre;

public:
	Noeud(const int & dist, const unsigned int & sommet) : distance(distance), m_sommet(sommet),
	  enfantGauche(NULL), voisin(NULL), maitre(NULL) { }

	Noeud * getVoisin();
	int getDistance();
	Noeud * getEnfantGauche();
	unsigned int getSommet();

	friend class PairingH;
};

#endif /* NOEUD_H_ */
