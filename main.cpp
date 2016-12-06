#include <iostream>
#include "coordonnees.h"
#include "reseau.h"
#include <vector>
#include "investigation.h"
#include "PairingHeap.h"

using namespace std;



int main() {
    GestionnaireInvestigation rtc("RTC/");

    cout << "Temps moyen de dijsktra " << rtc.tester_n_paires_dijsktra(1) << endl << endl;

    //cout << "Temps moyen de bellman " << rtc.tester_n_paires_bellman(10) << endl << endl;

	/*
	 * testing le pairing heap
	 */

//		cout << "Tests sur le Pairing Heap" << endl;
//
//		vector<int> sommetsId {};
//		vector<Noeud *> noeuds{};
//		PairingHeap heap {};
//
//		for(int i = 0; i < 10; ++i){ // on cree des sommets 1 a 10 avec valeur 10 a 19
//			sommetsId.push_back(i+1);
//			int distance = 20-i;
//			heap.ajoutNoeud((sommetsId.back()), distance);
//			noeuds.push_back(heap.getRacine());
//			cout << (heap.getRacine())->getDistance() << " = " << distance << endl;
//		}
//
//		heap.supprimerRacine();
//
//		cout << "la nouvelle racine a une distance de : " << heap.getRacine()->getDistance() << endl;
//
//		heap.supprimerRacine();
//
//		cout << "la nouvelle racine a une distance de : " << heap.getRacine()->getDistance() << endl;
//		cout << noeuds[2]->getDistance() << endl;
//		heap.diminuerDistanceNoeud(noeuds[2], 10);
//		cout << "et donc la racine est" << heap.getRacine()->getDistance() << endl;
//		heap.diminuerDistanceNoeud(noeuds[4], 5);
//		cout << "et donc la racine est" << heap.getRacine()->getDistance() << endl;

    return 0;
}
