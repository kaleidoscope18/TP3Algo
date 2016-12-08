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
        cout << "Temps moyen de dijkstra modifié avec pairing heap : " << rtc.tester_n_paires_dijkstra_modifie(1000) << endl << endl;
    }



    return 0;
}


