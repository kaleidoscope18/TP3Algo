/*
 * Noeud.h
 *
 *  Created on: 2016-12-05
 *      Author: Nadia
 */

#ifndef NOEUD_H_
#define NOEUD_H_


#include <iostream>

class Noeud{ //modifier la classe pour que les attributs deviennent privÃ©s
	public:
		Noeud (const int & dist, int * ptr_sommet);
		bool operator>(Noeud * noeud);
		bool operator<(Noeud * noeud);
		virtual ~Noeud();
		int getDistance() const;
		void setDistance(int distance);
		Noeud * getEnfantGauche() const;
		void setEnfantGauche(Noeud * enfantGauche);
		Noeud * getMaitre() const;
		void setMaitre(Noeud* maitre);
		int * getSommet() const;
		void setSommet(int* sommet);
		Noeud * getVoisin() const;
		void setVoisin(Noeud* voisin);
	private:
		int m_distance; //key est la valeur comparable qui est la distance
		Noeud * m_enfantGauche;
		Noeud * m_voisin; //voisin de droite plus precisement
		int * m_sommet;
		Noeud * m_maitre;
};

#endif /* NOEUD_H_ */
