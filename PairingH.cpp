/*
 * PairingH.cpp
 *
 *  Created on: 2016-12-07
 *      Author: Nadia
 */

#include <stdexcept>
#include <vector>
#include "PairingH.h"

int PairingH::nbNoeuds { 0 };

/**
 * Constructeur par défaut
 */
PairingH::PairingH()
{
	racine = nullptr;
}
/*
 * Constructeur de copie
 */
PairingH::PairingH(const PairingH & nouvPH)
{
	racine = nullptr;
	*this = nouvPH;
}
/**
 * Retourne le nombre de noeuds dans le monceau
 */
int PairingH::nombreNoeuds() const
{
	return nbNoeuds;
}
/**
 * ajouter un noeud dans le heap tout en conservant les propriétés du heap
 * Return un pointeur vers l'objet Noeud créé
 */
Noeud * PairingH::ajouterNoeud(const int & dist, const unsigned int & sommet)
{
	Noeud *newNoeud = new Noeud(dist, sommet);

	if( racine == nullptr )
		racine = newNoeud; //si on n'avait pas de racine, rien de plus a faire
	else
		fusionner(racine, newNoeud); //sinon, on doit s'assurer que le noeud se place au bon endroit et que le heap
									// respecte les règles du heap-min
	++nbNoeuds;
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

	if(racine->enfantGauche == nullptr) //si on retire le dernier noeud existant dans le monceau la racine devient nulle
		racine = nullptr;
	else
		racine = fusionPassePasse(racine->enfantGauche); //on doit refaire le heap pour s'assurer
															 // de respecter les règles du monceau (min-heap)
	--nbNoeuds;
	delete oldracine;
}
/**
 * retourne vrai si le monceau est vide (racine == nullptr)
 * retourne faux s'il y a une racine
 */
bool PairingH::estVide() const
{
	return racine == nullptr;
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
		if(p->voisin != nullptr)
			p->voisin->maitre = p->maitre;
		if(p->maitre != nullptr)
		{
			if(p->maitre->enfantGauche == p){
				p->maitre->enfantGauche = p->voisin;
			}
			else{
				p->maitre->voisin = p->voisin;
			}
		}
		p->voisin = nullptr;
		fusionner(racine, p);
	}
}

/**
 * fusion de deux noeuds
 * doit respecter les regles du min-heap (racine doit etre la valeur minimale)
 * le noeud A ne peut pas etre nullptr et ne doit pas avoir de voisin
 * le noeud A est donc normalement la racine du premier monceau
 * le noeud B est donc la racine du deuxieme monceau
 * le noeud A est la racine du nouvel arbre
 */

void PairingH::fusionner(Noeud * & A, Noeud *B) const
{
	if(B == nullptr)
		return;

	if( B->distance < A->distance ) {//A devient l'enfant gauche de B
		B->maitre = A->maitre; //A devrait normalement pas avoir de maitre (nullptr)
		A->maitre = B;
		A->voisin = B->enfantGauche;
		if(A->voisin != nullptr)
			A->voisin->maitre = A;
		B->enfantGauche = A;
		A = B; //B est devenu la racine, donc A prend la place de l'enfant gauche de B
	}
	else { //B va devenir l'enfant gauche de A
		B->maitre = A;
		A->voisin = B->voisin;
		if(A->voisin != nullptr)
			A->voisin->maitre = A;
		B->voisin = A->enfantGauche;
		if(B->voisin != nullptr)
			B->voisin->maitre = B;
		A->enfantGauche = B; //A reste la racine ici
	}
}

/**
 * Implémentation du two-pass merging/pairing
 */
Noeud * PairingH::fusionPassePasse(Noeud * voisinImmediat) const
{
    {
    	if(voisinImmediat == nullptr){ //on ne doit pas avoir de racine nulle..
    		return nullptr;
    	}
    	//pas de fusionPassePasse si on a pas de voisin
        if(voisinImmediat->voisin == nullptr)
            return voisinImmediat;

            // On pourra ensuite mettre les sous-heaps dans le vecteur pour les refusionner plus tard
        static std::vector<Noeud *> sousMonceaux(5);
        int nombreVoisins = 0;
        for( ; voisinImmediat != nullptr; nombreVoisins++) //pour chaque voisin qui existe
        {
            if(nombreVoisins == sousMonceaux.size()) //reallocation du vecteur, optimal pour pas avoir de reallocation a chaque fois
                sousMonceaux.resize(nombreVoisins*2);
            sousMonceaux[nombreVoisins] = voisinImmediat;
            if(voisinImmediat->maitre != nullptr)
            {
            	voisinImmediat->maitre->voisin = nullptr;  // après avoir stocké le voisin, on brise les liens
            }
            voisinImmediat = voisinImmediat->voisin;
        }
        if(nombreVoisins == sousMonceaux.size()) //reallocation du vecteur
            sousMonceaux.resize(nombreVoisins+1);
        sousMonceaux[nombreVoisins] = nullptr;

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
/*
 * On peut redessiner avec https://stamm-wilbrandt.de/GraphvizFiddle/ (visualisation du heap)
 */
void PairingH::parcoursDOT(Noeud * p_debut) const
{
	if(p_debut->enfantGauche != nullptr){
		Noeud * noeudKid = p_debut->enfantGauche;
		std::cout << p_debut->m_sommet << p_debut->distance << " -> " << noeudKid->m_sommet << noeudKid->distance << " [color=blue]" << std::endl;
		std::cout << noeudKid->m_sommet << noeudKid->distance << " -> " << p_debut->m_sommet << p_debut->distance << " [color=black]" << std::endl;
		if(noeudKid->voisin != nullptr){
			Noeud * noeudKidVoisin = noeudKid->voisin;
			std::cout << noeudKid->m_sommet << noeudKid->distance << " -> " << noeudKidVoisin->m_sommet << noeudKidVoisin->distance << " [color=red]"<< std::endl;
			std::cout << "{rank = same; " << noeudKid->m_sommet << noeudKid->distance << "; "<< noeudKidVoisin->m_sommet << noeudKidVoisin->distance << ";}" << std::endl;
			std::cout << noeudKidVoisin->m_sommet << noeudKidVoisin->distance << " -> " << p_debut->m_sommet << p_debut->distance << " [color=black]" << std::endl;
			while(noeudKidVoisin != nullptr){
				if(noeudKidVoisin->enfantGauche != nullptr){
					parcoursDOT(noeudKidVoisin);
				}
				if(noeudKidVoisin->voisin != nullptr){
					std::cout << noeudKidVoisin->m_sommet << noeudKidVoisin->distance << " -> " << noeudKidVoisin->voisin->m_sommet << noeudKidVoisin->voisin->distance << " [color=red]"<< std::endl;
					std::cout << "{rank = same; " << noeudKidVoisin->m_sommet << noeudKidVoisin->distance << "; "<< noeudKidVoisin->voisin->m_sommet << noeudKidVoisin->voisin->distance << ";}" << std::endl;
					std::cout << noeudKidVoisin->voisin->m_sommet << noeudKidVoisin->voisin->distance << " -> " << p_debut->m_sommet << p_debut->distance << " [color=black]" << std::endl;
				}
				noeudKidVoisin = noeudKidVoisin->voisin;
			}
		}
		if(noeudKid->enfantGauche != nullptr){
			parcoursDOT(noeudKid);
		}
	}
}
