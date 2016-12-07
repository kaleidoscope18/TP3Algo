/*
 * PairingH.cpp
 *
 *  Created on: 2016-12-07
 *      Author: Nadia
 */

#include <stdexcept>
#include <vector>
#include "PairingH.h"

/**
 * Constructeur par défaut
 */
PairingH::PairingH()
{
	racine = NULL;
}
/*
 * Constructeur de copie
 */
PairingH::PairingH(const PairingH & nouvPH)
{
	racine = NULL;
	*this = nouvPH;
}
/**
 * ajouter un noeud dans le heap tout en conservant les propriétés du heap
 * Return un pointeur vers l'objet Noeud créé
 */

Noeud * PairingH::ajouterNoeud(const int & dist, const unsigned int & sommet)
{
	Noeud *newNoeud = new Noeud(dist, sommet);

	if( racine == NULL )
		racine = newNoeud; //si on n'avait pas de racine, rien de plus a faire
	else
		fusionner(racine, newNoeud); //sinon, on doit s'assurer que le noeud se place au bon endroit et que le heap
									// respecte les règles du heap-min
	return newNoeud;
}
/**
 * retourne la racine du monceau (qui a la distance minimale)
 */
Noeud * PairingH::getRacine() const{
	return racine;
}
/**
 * Retire la racine (item ayant la distance minimale) du monceau
 * Le heap ne doit pas etre vide
 */

void PairingH::retirerRacine()
{
	if( estVide() )
		throw std::logic_error("logic error heap is empty");

	Noeud * oldracine = racine;

	if(racine->getEnfantGauche() == NULL) //si on retire le dernier noeud existant dans le monceau la racine devient nulle
		racine = NULL;
	else
		racine = fusionPassePasse(racine->getEnfantGauche()); //on doit refaire le heap pour s'assurer
															 // de respecter les règles du monceau (min-heap)
	delete oldracine;
}
/**
 * retourne vrai si le monceau est vide (racine == NULL)
 * retourne faux s'il y a une racine
 */
bool PairingH::estVide() const
{
	return racine == NULL;
}
/*
 * Implementation du decrease-key
 * La nouvelle valeur doit etre inférieure à la valeur deja existante pour ce noeud
 * Sinon il ne se passera rien
 */
void PairingH::diminuerDistance(Noeud *p, const int & nouvDistance)
{
	if(p->distance < nouvDistance)
		return;    // on doit diminuer et non augmenter la distance
	p->distance = nouvDistance; //on diminue la valeur
	if( p != racine ) { //si c'est la racine, on n'a pas d'opération supplémentaire à faire
		if(p->voisin != NULL)
			p->voisin->maitre = p->maitre;
		if(p->maitre->getEnfantGauche() == p)
			p->maitre->getEnfantGauche() = p->voisin;
		else
			p->maitre->voisin = p->voisin;

		p->voisin = NULL;
		fusionner(racine, p);
	}
}

/**
 * fusion de deux noeuds
 * doit respecter les regles du min-heap (racine doit etre la valeur minimale)
 * le noeud A ne peut pas etre NULL et ne doit pas avoir de voisin
 * le noeud A est donc normalement la racine du premier monceau
 * le noeud B est donc la racine du deuxieme monceau
 * le noeud A est la racine du nouvel arbre
 */

void PairingH::fusionner(Noeud * & A, Noeud *B) const
{
	if(B == NULL)
		return;

	if( B->distance < A->distance ) {//A devient l'enfant gauche de B
		B->maitre = A->maitre; //A devrait normalement pas avoir de maitre (NULL)
		A->maitre = B;
		A->voisin = B->enfantGauche;
		if(A->voisin != NULL)
			A->voisin->maitre = A;
		B->getEnfantGauche() = A;
		A = B; //B est devenu la racine, donc A prend la place de l'enfant gauche de B
	}
	else { //B va devenir l'enfant gauche de A
		B->maitre = A;
		A->voisin = B->voisin;
		if(A->voisin != NULL)
			A->voisin->maitre = A;
		B->voisin = A->getEnfantGauche();
		if(B->voisin != NULL)
			B->voisin->maitre = B;
		A->getEnfantGauche() = B; //A reste la racine ici
	}
}

/**
 * Implémentation du two-pass merging/pairing
 */
Noeud * PairingH::fusionPassePasse(Noeud * voisinImmediat) const
{
    {
    	if(voisinImmediat == NULL){ //on ne doit pas avoir de racine nulle..
    		return NULL;
    	}
    	//pas de fusionPassePasse si on a pas de voisin
        if(voisinImmediat->voisin == NULL)
            return voisinImmediat;

            // On pourra ensuite mettre les sous-heaps dans le vecteur pour les refusionner plus tard
        static std::vector<Noeud *> sousMonceaux(5);
        int nombreVoisins = 0;
        for( ; voisinImmediat != NULL; nombreVoisins++) //pour chaque voisin qui existe
        {
            if(nombreVoisins == sousMonceaux.size()) //reallocation du vecteur, optimal pour pas avoir de reallocation a chaque fois
                sousMonceaux.resize(nombreVoisins*2);
            sousMonceaux[nombreVoisins] = voisinImmediat;
            voisinImmediat->maitre->voisin = NULL;  // après avoir stocké le voisin, on brise les liens
            voisinImmediat = voisinImmediat->voisin;
        }
        if(nombreVoisins == sousMonceaux.size()) //reallocation du vecteur
            sousMonceaux.resize(nombreVoisins+1);
        sousMonceaux[nombreVoisins] = NULL;

            // on fait la premiere passe en combinant des paires de sous heap, de gauche a droite
        int i = 0;
        for( ; i+1 < nombreVoisins; i += 2)
            fusionner(sousMonceaux[i], sousMonceaux[i+1]);

        int j = i - 2;

        if(j == nombreVoisins - 3)
            fusionner(sousMonceaux[j], sousMonceaux[j + 2]);

            // on fait la seconde passe cette fois-ci en passant de droite a gauche
        for( ; j >= 2; j -= 2)
            fusionner(sousMonceaux[j-2], sousMonceaux[j]);
        return sousMonceaux[0];
    }
}
