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
public:
	int distance;
	unsigned int m_sommet;
	Noeud *enfantGauche;
	Noeud *voisin;
	Noeud *maitre;

	Noeud(const int & dist, const unsigned int & sommet);

	Noeud * getVoisin();
	int getDistance();
	Noeud * getEnfantGauche();
	unsigned int getSommet();

	friend class PairingH;
};

#endif /* NOEUD_H_ */
