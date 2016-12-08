#include <iostream>
#include "coordonnees.h"
#include "reseau.h"
#include <vector>
#include "investigation.h"
#include "PairingH.h"

using namespace std;

int main() {
    GestionnaireInvestigation rtc("RTC/");
    cout << "Temps moyen de dijsktra " << rtc.tester_n_paires_dijsktra(1) << endl << endl;
//    cout << "Temps moyen de bellman " << rtc.tester_n_paires_bellman(10) << endl << endl;

//	h.retirerRacine();
//	h.parcoursDOT(h.getRacine());
//    cout << "}" << endl; //pour imprimer en format DOT (combiner avec parcoursDOT)


    return 0;
}


