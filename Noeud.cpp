/*
 * Noeud.cpp
 *
 *  Created on: 2016-12-07
 *      Author: etudiant
 */

#include "Noeud.h"

Noeud::Noeud(const int & dist, const unsigned int & sommet) : distance(dist), m_sommet(sommet),
	  enfantGauche(NULL), voisin(NULL), maitre(NULL){
}

Noeud * Noeud::getVoisin(){
	return voisin;
}

int Noeud::getDistance(){
	return distance;
}

Noeud * Noeud::getEnfantGauche(){
	return enfantGauche;
}

unsigned int Noeud::getSommet(){
	return m_sommet;
}
