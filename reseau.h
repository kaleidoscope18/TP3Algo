//
// Created by prtos on 29/04/16.
//

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <new>
#include <limits>
#include <algorithm>
#include "station.h"

#ifndef Reseau__H
#define Reseau__H

#define INFINI 999999
#define DEFAULT_TYPE 0

/*!
 *
 */
typedef std::unordered_map<unsigned int, std::pair<unsigned int, unsigned int> > liste_arcs;
//liste_arcs est <sommet destination <poids, type>> ??


/*!
 * \class Reseau
 * \brief Classe réprésentant un graphe orienté valué. Les sommets du graphe sont tous identifiés par des nombres entiers positifs distincts.
 * Les entre les sommets arcs sont tous identifiés par poids positif ou nul, et un type qui est aussi un entier positif.
 *
 */
class Reseau
{
public:

	Reseau();

	void ajouterSommet(unsigned int numero) throw (std::logic_error);
	void enleverSommet(unsigned int numero) throw (std::logic_error);
	void ajouterArc(unsigned int numOrigine, unsigned int numDest, unsigned int cout, unsigned int type=DEFAULT_TYPE)
				throw (std::logic_error);
	void enleverArc(unsigned int numOrigine, unsigned int numDest) throw (std::logic_error);
	void majCoutArc(unsigned int numOrigine, unsigned int numDest, unsigned int cout) throw (std::logic_error);

	int nombreSommets() const;
	int nombreArcs() const;
	bool estVide() const;

	bool sommetExiste(unsigned int numero) const;
	bool arcExiste(unsigned int numOrigine, unsigned int numDest) const throw (std::logic_error);
	int getCoutArc(unsigned int numOrigine, unsigned int numDestination) const throw (std::logic_error);
	int getTypeArc(unsigned int numOrigine, unsigned int numDestination) const throw (std::logic_error);

	int dijkstra(unsigned int numOrigine, unsigned int numDest, std::vector<unsigned int> & chemin)
				throw (std::logic_error);
	int meilleurPlusCourtChemin(unsigned int numOrigine, unsigned int numDest, std::vector<unsigned int> & chemin)
				throw (std::logic_error);
	int bellmanFord(unsigned int numOrigine, unsigned int numDest, std::vector<unsigned int> & chemin)
				throw (std::logic_error);

private:
	/**< Le nombre de sommets dans le Reseau */
	int nbSommets;

	/**< Le nombre d'arcs dans le Reseau */
	int nbArcs;

    /** Ce vector agira comme une table de hachage contenant les arcs d'un sommet avec son numero associé */
	std::unordered_map<unsigned int, liste_arcs > m_arcs;

};

#endif
