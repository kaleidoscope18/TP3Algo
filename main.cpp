#include <iostream>
#include "coordonnees.h"
#include "reseau.h"
#include <vector>
#include "investigation.h"

using namespace std;

int main() {
    GestionnaireInvestigation rtc("RTC/");
    for(int i = 0; i < 1; i++){
//        cout << "Temps moyen de dijsktra" << rtc.tester_n_paires_dijsktra(1000) << endl << endl;
//        cout << "Temps moyen de bellman " << rtc.tester_n_paires_bellman(1000) << endl << endl;
        cout << "Temps moyen de dijkstra modifié avec pairing heap : " << rtc.tester_n_paires_dijkstra_modifie(100) << endl << endl;
    }
//    cout << "Fin du test avec 1000 paires, 20 fois pour les trois algorithmes";

//	h.parcoursDOT(h.getRacine());
//    cout << "}" << endl; //pour imprimer en format DOT (combiner avec parcoursDOT)


    return 0;
}


