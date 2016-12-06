//
// Created by prtos on 29/05/16.
//

#ifndef RTC_GESTIONNAIRE_H
#define RTC_GESTIONNAIRE_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include "station.h"
#include "voyage.h"
#include "reseau.h"
#include "auxiliaires.h"
#include "coordonnees.h"
#include <algorithm>
#include <math.h>
#include "sys/time.h"
#include <iostream>

const double vitesse_de_marche = 5.0; /*! vitesse moyenne de marche d'un humain selon wikipedia */

const double distance_max_transfert = 0.2; // Cette distance est relativement courte et prend juste 2.5 min à parcourir.

enum class MoyenDeplacement {BUS=0, PIEDS};


/*!
 * \class Gestionnaire
 * \brief classe intégrante les données avec les autres classes pour rendre concret le
 */
class GestionnaireInvestigation  {

public:

	GestionnaireInvestigation(std::string chemin_dossier);
	bool station_existe(int station_id);
	std::vector< unsigned int > plus_court_chemin_dijsktra(unsigned int num_station_depart, unsigned int num_station_dest);
	std::vector< unsigned int > plus_court_chemin_bellman(unsigned int num_station_depart, unsigned int num_station_dest);
	double tester_n_paires_dijsktra(unsigned int nb_paires, unsigned int seed=42);
	double tester_n_paires_bellman(unsigned int nb_paires, unsigned int seed=42);

private:
	std::unordered_map<std::string, Ligne> lignes;
	std::unordered_map<unsigned int, Station> stations;
	std::unordered_map<std::string, Voyage> voyages;
	Reseau m_reseau;

	void initialiser_reseau(double dist_transfert=distance_max_transfert);
	void ajouter_aretes_empruntees_par_bus();
	void ajouter_aretes_transfert(double dist_transfert);


};

#endif //RTC_GESTIONNAIRE_H
