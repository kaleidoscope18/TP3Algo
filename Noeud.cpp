/*
 * Noeud.cpp
 *
 *  Created on: 2016-12-05
 *      Author: Nadia
 */

#include "Noeud.h"


/*
 * Chaque noeud a un sommet qui lui est associé dans le réseau
 */
Noeud::Noeud(const int & dist, const unsigned int & sommet) :
		m_distance(dist), m_enfantGauche(nullptr), m_voisin(nullptr), m_sommet(sommet), m_maitre(nullptr) {
}

Noeud::~Noeud() {
}

int Noeud::getDistance() const {
	return m_distance;
}

void Noeud::setDistance(int distance) {
	m_distance = distance;
}

Noeud * Noeud::getEnfantGauche() const {
	return m_enfantGauche;
}

void Noeud::setEnfantGauche(Noeud * enfantGauche) {
	m_enfantGauche = enfantGauche;
}

Noeud * Noeud::getMaitre() const {
	return m_maitre;
}

void Noeud::setMaitre(Noeud * maitre) {
	m_maitre = maitre;
}

const unsigned int & Noeud::getSommet() const {
	return m_sommet;
}

void Noeud::setSommet(const unsigned int sommet) {
	m_sommet = sommet;
}

Noeud * Noeud::getVoisin() const {
	return m_voisin;
}

void Noeud::setVoisin(Noeud * voisin) {
	m_voisin = voisin;
}
