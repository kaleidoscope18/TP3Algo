/*
 * PairingHeap.h
 *
 *  Created on: 2016-12-08
 *  Author : Nadia
 *    Source #1 : https://github.com/saadtaame/pairing-heap/blob/master/pairing_heap.cc
 *    Source #2 : https://users.cs.fiu.edu/~weiss/ (Mark Allen Weiss)
 */
#include "PairingH.h"

#include <stdexcept>
#include <vector>
/**
 * \brief Constructeur par défaut
 * \post Une instance de la classe PairingH est initialisée
 */
PairingH::PairingH() {
	racine = nullptr;
}
/**
 * \brief ajouter un noeud dans le heap tout en conservant les propriétés du heap en O(1)
 * \param[in] dist la distance entre ce noeud et son prédécesseur
 * \param[in] sommet le numéro de la station
 * \Return Un pointeur vers l'objet Noeud créé
 */
Noeud * PairingH::ajouterNoeud(const unsigned int & x,
		const unsigned int & sommet) {
	Noeud *newNode = new Noeud { x, sommet };

	if (racine == nullptr)
		racine = newNode;
	else
		fusionner(racine, newNode);
	return newNode;
}

/**
 * \brief retourne la distance de la racine du monceau (qui a la distance minimale) en O(1)
 */
const unsigned int & PairingH::trouverDistanceMin() const {
	if (estVide())
		throw std::logic_error("heap vide");
	return racine->distance;
}
/**
 * \brief retourne la racine du monceau (qui a la distance minimale)
 */
Noeud * PairingH::getRacine() const {
	if (estVide())
		throw std::logic_error("heap vide");
	return racine;
}
/**
 * \brief Retire la racine (item ayant la distance minimale) du monceau O(log n)
 * \pre Le heap ne doit pas etre vide
 */
void PairingH::supprimerRacine() {
	if (estVide())
		throw std::logic_error("heap vide");

	Noeud *oldRoot = racine;

	if (racine->enfantGauche == nullptr)
		racine = nullptr;
	else
		racine = fusionPassePasse(racine->enfantGauche);

	delete oldRoot;
}
/**
 * \brief Indiquer si le monceau est vide
 * \return vrai si le monceau est vide (racine == NULL)
 * \return faux s'il y a une racine
 */
bool PairingH::estVide() const {
	return racine == nullptr;
}
/*
 * \brief Implementation du decrease-key en O(log n)
 * La nouvelle valeur doit etre inférieure à la valeur deja existante pour ce noeud
 * Sinon il ne se passera rien
 * \param[in] p un noeud du tas
 * \param[in] nouvDistance une nouvelle distance
 * \return rien si la nouvelle distance est plus grande que l'ancienne
 * \return modifie la distance par référence si la nouvelle est plus petite ou égale que l'ancienne
 */
void PairingH::diminuerDistance(Noeud *p, const unsigned int & newVal) {
	if (p->distance < newVal)
		return;    // newVal cannot be bigger
	p->distance = newVal;
	if (p != racine) {
		if (p->voisin != nullptr)
			p->voisin->maitre = p->maitre;
		if (p->maitre->enfantGauche == p)
			p->maitre->enfantGauche = p->voisin;
		else
			p->maitre->voisin = p->voisin;

		p->voisin = nullptr;
		fusionner(racine, p);
	}
}

/**
 * \brief fusion de deux noeuds en O(1)
 * Operation pour maintenir l'ordre du monceau et respecter les règles de base
 * Le noeud A ne doit pas être un pointeur nullptr
 * \param[in] le noeud A est donc normalement la racine du premier monceau
 * \param[in] le noeud B est donc la racine du deuxieme monceau
 */
void PairingH::fusionner(Noeud * & A, Noeud * B) const {
	if (B == nullptr)
		return;

	if (B->distance < A->distance) {//A devient l'enfant gauche de B
		B->maitre = A->maitre; //A devrait normalement pas avoir de maitre (nullptr)
		A->maitre = B;
		A->voisin = B->enfantGauche;
		if (A->voisin != nullptr)
			A->voisin->maitre = A;
		B->enfantGauche = A;
		A = B; //B est devenu la racine, donc A prend la place de l'enfant gauche de B
	} else { //B va devenir l'enfant gauche de A
		B->maitre = A;
		A->voisin = B->voisin;
		if (A->voisin != nullptr)
			A->voisin->maitre = A;
		B->voisin = A->enfantGauche;
		if (B->voisin != nullptr)
			B->voisin->maitre = B;
		A->enfantGauche = B; //A reste la racine ici
	}
}

/*
 * \brief implementation de two-pass merge / pairing en O(log n)
 * pre ne pas avoir de racine nulle
 * param[in] noeud : est l'enfant gauche de la racine qui vient d'etre extraite
 */
Noeud * PairingH::fusionPassePasse(Noeud * noeud) const {
	if (noeud->voisin == nullptr) //on ne doit pas avoir de racine nulle..
	{
		return noeud;
	}

	// On pourra ensuite mettre les sous-heaps dans le vecteur pour les refusionner plus tard
	static std::vector<Noeud *> sousMonceaux(5);
	int nbVoisins { 0 };
	for (; noeud != nullptr; nbVoisins++) { //pour chaque voisin qui existe
		if (nbVoisins == (int)sousMonceaux.size()) //reallocation du vecteur, optimal pour pas avoir de reallocation a chaque fois
			sousMonceaux.resize(nbVoisins * 2);
		sousMonceaux[nbVoisins] = noeud;
		noeud->maitre->voisin = nullptr;  // après avoir stocké le voisin, on brise les liens
		noeud = noeud->voisin;
	}
	if (nbVoisins == (int)sousMonceaux.size()) //reallocation du vecteur
		sousMonceaux.resize(nbVoisins + 1);
	sousMonceaux[nbVoisins] = nullptr;

	int i { 0 }; // on fait la premiere passe en combinant des paires de sous heap, de gauche a droite
	for (; i + 1 < nbVoisins; i += 2)
	{
		fusionner(sousMonceaux[i], sousMonceaux[i + 1]);
	}

	int j { i - 2 };
	if (j == nbVoisins - 3)
		fusionner(sousMonceaux[j], sousMonceaux[j + 2]);

	// on fait la seconde passe cette fois-ci en passant de droite a gauche
	for (; j >= 2; j -= 2)
		fusionner(sousMonceaux[j - 2], sousMonceaux[j]);
	return sousMonceaux[0];
}
/*
 * \brief Génère le texte dans la console pour avoir un graphe en langage DOT
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
