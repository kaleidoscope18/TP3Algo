#include "PairingHeap.h"
#include <vector>
#include <stdexcept>

using namespace std;

int PairingHeap::nbNoeuds { 0 };

PairingHeap::PairingHeap(){ //constructeur par defaut
	this->m_racine = nullptr;
}

int PairingHeap::nombreNoeuds(){
	return nbNoeuds;
}

bool PairingHeap::estVide(){
	return (this->nombreNoeuds() == 0);
}

Noeud * PairingHeap::getRacine(){
	return this->m_racine;
}

void PairingHeap::setRacine(Noeud * nouvRacine){
	this->m_racine = nouvRacine; //TODO verifier sil a un maitre ?
}

Noeud * PairingHeap::ajoutNoeud(const unsigned int & sommet, const int & distance){ //TODO a verifier

	Noeud * nouvNoeud = new Noeud { distance, sommet };

	Noeud * racineActuelle = this->getRacine();

	if (racineActuelle == nullptr){ //quand on a un heap vide en fait
		this->setRacine(nouvNoeud);
	}
	else{
		fusionner(racineActuelle, nouvNoeud);
	}
	++nbNoeuds;
	return nouvNoeud;
}

/*
 * param A : va etre la racine actuelle si c'est pour un ajout
 */
Noeud * PairingHeap::fusionner(Noeud * A, Noeud * B){
	if(A == nullptr){
		return B;
	}
	else if(B == nullptr){
		return A;
	}
	else if(A->getDistance() < B->getDistance()){ //B va devenir l'enfant gauche de A
		B->setMaitre(A);
		if(A->getEnfantGauche() != nullptr){
			B->setVoisin(A->getEnfantGauche()); //le voisin de B est l'enfant gauche de A
		}
		A->setEnfantGauche(B); //la racine actuelle a un nouvel enfant gauche
		/*Two pointers of the same type compare equal if and only if they are both null, both point to the same function, or both represent the same address (3.9.2)*/
		if(B == this->getRacine()){ //si on comparait une racine & elle n'est plus la plus petite on change de racine
			this->setRacine(A);
		}
		return A;
	} //sinon A >= B
	else{ //B va devenir A et la A devient l'enfant gauche de B
		A->setMaitre(B);
		if(B->getEnfantGauche() != nullptr){
			A->setVoisin(B->getEnfantGauche());
		}
		B->setEnfantGauche(A);
		if(A == this->getRacine()){
			this->setRacine(B); //si on comparait une racine & elle n'est plus la plus petite on change de racine
		}
		return B;
	}
}
/*
 * ici on a fait le choix de supprimer la racine
 */
void PairingHeap::supprimerRacine(){

	if(this->estVide()){
		throw logic_error("Erreur heap vide, peut pas executer extractionRacine");
	}

	if(this->getRacine()->getEnfantGauche() == nullptr){ //pas d'enfant gauche donc on met une racine vide (le heap est desormais vide)
		this->setRacine(nullptr); //pas BON!??!
	}
	else{ //le heap n'est pas vide
		this->setRacine(this->fusionPassePasse(this->getRacine()->getEnfantGauche()));
	}
	//TODO trouver une facon de liberer la memoire occupée par le Noeud retiré
	--nbNoeuds; //on decremente le nombre de noeuds dans le heap
}
/*
 * implementation de two-pass merge / pairing version recurrente
 * param noeud : est l'enfant gauche de la racine qui vient d'etre extraite
 */
Noeud * PairingHeap::fusionPassePasse(Noeud * noeud) {
	if(noeud == nullptr){ //pas d'autres arbres a merge avec lui, il etait le seul descendant de son maitre ou il etait vide
		return noeud; //Y
	}
	else if(noeud->getVoisin() == nullptr){ //X
		return noeud;
	}
	else{
		Noeud *A, *B, *nouvNoeud; //on construit les pointeurs de noeuds (a 0)
		A = noeud; //A ne peut pas etre un nullptr car on a verifie plus haut Y

		B = A->getVoisin(); //B ne peut pas etre un nullptr car on a verifie plus haut X

		nouvNoeud = B->getVoisin(); //peut etre un nullptr

		A->setVoisin(nullptr); //on demanche le schema, pu de maitre, pu de voisin
		B->setVoisin(nullptr);
		A->setMaitre(nullptr);
		B->setMaitre(nullptr);

		return fusionner(fusionner(A,B), fusionPassePasse(nouvNoeud));
	}
	return 0; //suppose d'etre inatteignable
}

void PairingHeap::diminuerDistanceNoeud(Noeud * noeud, const int & nouvDist){
	//il faut que le noeud fasse partie du Heap ! cela fonctionne si le noeud disparait si retiré du heap
	if(nouvDist >= noeud->getDistance()){
		return; //on doit diminuer la distance seulement
	}
	//on doit faire des modifications au monceau pour respecter ses propriÃ©tÃ©s
	// la racine doit etre la valeur minimale et les racines de chaque
	// sous-arbre doivent l'etre aussi
	if(noeud == this->getRacine()){
		this->getRacine()->setDistance(nouvDist); //si c'est la racine et qu'on baisse sa distance c OK
	}
	else{ //si c'est un autre noeud et qu'on baisse sa distance
		noeud->setDistance(nouvDist);
		noeud->getMaitre()->setEnfantGauche(noeud->getVoisin()); //on shift lenfant gauche du maitre
		noeud->setMaitre(nullptr);
		noeud->setVoisin(nullptr);
		this->fusionner(this->getRacine(), noeud);
	}

}
