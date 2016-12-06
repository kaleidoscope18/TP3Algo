#ifndef PAIRINGHEAP_H_
#define PAIRINGHEAP_H_

#include "Noeud.h"

class PairingHeap{
	public:
		PairingHeap();
		bool estVide();
		Noeud * fusionPassePasse(Noeud * noeud);
		void supprimerRacine();
		Noeud * ajoutNoeud(const unsigned int & sommet, const int & distance);
		Noeud * getRacine();
		int nombreNoeuds();
		void setRacine(Noeud * nouvRacine);
		void diminuerDistanceNoeud(Noeud * noeud, const int & nouvDist);

	private:
		Noeud * m_racine;
		static int nbNoeuds;
		Noeud * fusionner(Noeud * A, Noeud * B);
};


#endif /* PAIRINGHEAP_H_ */
