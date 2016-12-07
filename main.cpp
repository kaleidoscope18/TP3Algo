#include <iostream>
#include "coordonnees.h"
#include "reseau.h"
#include <vector>
#include "investigation.h"
#include "PairingH.h"

using namespace std;


//void parcoursProfondeur(Noeud * p_debut)
//{
//	if(p_debut->getEnfantGauche() != nullptr){
//		Noeud * noeudKid = p_debut->getEnfantGauche();
//		std::cout << p_debut->getSommet() << " -> " << noeudKid->getSommet() << " [color=blue]" << std::endl;
//		if(noeudKid->getVoisin() != nullptr){
//			Noeud * noeudKidVoisin = noeudKid->getVoisin();
//			std::cout << noeudKid->getSommet() << " -> " << noeudKidVoisin->getSommet() << " [color=red]"<< std::endl;
//			std::cout << "{rank = same; " << noeudKid->getSommet() << "; "<< noeudKidVoisin->getSommet() << ";}" << std::endl;
//			while(noeudKidVoisin != nullptr){
//				if(noeudKidVoisin->getEnfantGauche() != nullptr){
//					parcoursProfondeur(noeudKidVoisin);
//				}
//				if(noeudKidVoisin->getVoisin() != nullptr){
//					std::cout << noeudKidVoisin->getSommet() << " -> " << noeudKidVoisin->getVoisin()->getSommet() << " [color=red]"<< std::endl;
//				}
//				Noeud * noeudKidVoisin = noeudKidVoisin->getVoisin();
//			}
//		}
//		parcoursProfondeur(noeudKid);
//	}
//}
/*
 * On peut redessiner avec https://stamm-wilbrandt.de/GraphvizFiddle/ (visualisation du heap)
 */
void parcoursDOT(Node * p_debut)
{
	if(p_debut->getEnfantGauche() != NULL){
		Node * noeudKid = p_debut->getEnfantGauche();
		std::cout << p_debut->getElement() << " -> " << noeudKid->getElement() << " [color=blue]" << std::endl;
		std::cout << noeudKid->getElement() << " -> " << p_debut->getElement() << " [color=black]" << std::endl;
		if(noeudKid->getVoisin() != NULL){
			Node * noeudKidVoisin = noeudKid->getVoisin();
			std::cout << noeudKid->getElement() << " -> " << noeudKidVoisin->getElement() << " [color=red]"<< std::endl;
			std::cout << "{rank = same; " << noeudKid->getElement() << "; "<< noeudKidVoisin->getElement() << ";}" << std::endl;
			std::cout << noeudKidVoisin->getElement() << " -> " << p_debut->getElement() << " [color=black]" << std::endl;
			while(noeudKidVoisin != NULL){
				if(noeudKidVoisin->getEnfantGauche() != NULL){
					parcoursDOT(noeudKidVoisin);
				}
				if(noeudKidVoisin->getVoisin() != NULL){
					std::cout << noeudKidVoisin->getElement() << " -> " << noeudKidVoisin->getVoisin()->getElement() << " [color=red]"<< std::endl;
					std::cout << "{rank = same; " << noeudKidVoisin->getElement() << "; "<< noeudKidVoisin->getVoisin()->getElement() << ";}" << std::endl;
					std::cout << noeudKidVoisin->getVoisin()->getElement() << " -> " << p_debut->getElement() << " [color=black]" << std::endl;
				}
				noeudKidVoisin = noeudKidVoisin->getVoisin();
			}
		}
		if(noeudKid->getEnfantGauche() != NULL){
			parcoursDOT(noeudKid);
		}
	}
}

int main() {
//    GestionnaireInvestigation rtc("RTC/");
//
//    cout << "Temps moyen de dijsktra " << rtc.tester_n_paires_dijsktra(1) << endl << endl;

//    cout << "Temps moyen de bellman " << rtc.tester_n_paires_bellman(10) << endl << endl;


	/*
    PairingH h1;
    for(int i = 1; i < 100; ++i)
        h1.insert(i);

    parcoursProfondeur(h1.getRacine());
    */
	cout << "digraph mongraphe{" << endl;
	PairingH h;
	for(int i = 20; i > 0; --i){
		--i;
		h.insert(i);
	}
	h.insert(21);
	h.insert(10);
	h.insert(15);
	h.decreaseKey(h.getRacine()->getEnfantGauche(),5);
	parcoursDOT(h.getRacine());

/*
	PairingH h;
    int numItems = 4000;
    int i = 37;
    int j;

    for( i = 37; i != 0; i = ( i + 37 ) % numItems )
        h.insert( i );

    for( i = 1; i < numItems; i++ )
    {
        int x;
        h.deleteMin( x );
        if( x != i )
            cout << "Oops! " << i << endl;
    }

    vector<Node * > p( numItems );
    for( i = 0, j = numItems / 2; i < numItems; i++, j =(j+71)%numItems )
        p[ j ] = h.insert(j + numItems );
    for( i = 0, j = numItems / 2; i < numItems; i++, j =(j+53)%numItems )
        h.decreaseKey( p[ j ], j );
    i = -1;

    parcoursProfondeur(h.getRacine());
    */


//
//    PairingH h2;
//
//    h2 = h;
//    while( !h2.isEmpty( ) )
//    {
//        int x;
//        h2.deleteMin( x );
//        if( x != ++i )
//            cout << "Oops! " << i << endl;
//    }

    cout << "}" << endl;


    return 0;


/* testing le pairing heap

		cout << "Tests sur le Pairing Heap" << endl;

		vector<int> sommetsId {};
		vector<Noeud *> noeuds{};
		PairingHeap heap {};
		sommetsId.push_back(0);
		int distance = 2;
		heap.ajoutNoeud((sommetsId.back()), distance);
		noeuds.push_back(heap.getRacine());
		for(int i = 0; i < 10; ++i){ // on cree des sommets 1 a 10 avec valeur 10 a 19
			sommetsId.push_back(i);
			distance = 20;
			parcoursProfondeur(heap.getRacine());
			noeuds.push_back(heap.ajoutNoeud(i, distance));
		}
		parcoursProfondeur(heap.getRacine());

		heap.supprimerRacine();
		parcoursProfondeur(heap.getRacine());
		cout << "la nouvelle racine a une distance de : " << heap.getRacine()->getDistance() << endl;

		heap.supprimerRacine();
		parcoursProfondeur(heap.getRacine());
		cout << "la nouvelle racine a une distance de : " << heap.getRacine()->getDistance() << endl;
		cout << noeuds[2]->getDistance() << endl;
		heap.diminuerDistanceNoeud(noeuds[2], 10);
		parcoursProfondeur(heap.getRacine());
		cout << "et donc la racine est" << heap.getRacine()->getDistance() << endl;
		heap.diminuerDistanceNoeud(noeuds[4], 5);
		parcoursProfondeur(heap.getRacine());
		cout << "et donc la racine est" << heap.getRacine()->getDistance() << endl;
*/
}


