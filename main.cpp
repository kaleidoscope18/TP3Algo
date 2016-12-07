#include <iostream>
#include "coordonnees.h"
#include "reseau.h"
#include <vector>
#include "investigation.h"
#include "PairingH.h"

using namespace std;


int main() {
//    GestionnaireInvestigation rtc("RTC/");
////
//    cout << "Temps moyen de dijsktra " << rtc.tester_n_paires_dijsktra(1) << endl << endl;

//    cout << "Temps moyen de bellman " << rtc.tester_n_paires_bellman(10) << endl << endl;

	PairingH h;
	vector<pair<unsigned int, Noeud *>>sommetNoeud;
	cout << "digraph mongraphe{" << endl; //pour imprimer en format DOT (combiner avec parcoursDOT)

	for(unsigned int i = 1; i < 15; ++i){
		sommetNoeud.push_back(pair<unsigned int,Noeud*>(i, h.ajouterNoeud(1000-(2*i),i)));
	}
	h.diminuerDistance(sommetNoeud[5].second,10);
	h.diminuerDistance(sommetNoeud[6].second,5);
	h.diminuerDistance(sommetNoeud[3].second,3);
	h.retirerRacine();
	h.parcoursDOT(h.getRacine());
    cout << "}" << endl; //pour imprimer en format DOT (combiner avec parcoursDOT)


    return 0;
}


