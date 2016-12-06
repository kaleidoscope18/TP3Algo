//
// Created by prtos on 29/05/16.
//

#include "investigation.h"


//détermine le temps d'exécution (en microseconde) entre tv2 et tv2
long tempsExecution(const timeval& tv1, const timeval& tv2) {
	const long unMillion = 1000000;
	long dt_usec = tv2.tv_usec - tv1.tv_usec;
	long dt_sec = tv2.tv_sec - tv1.tv_sec;
	long dtms = unMillion * dt_sec + dt_usec;
	return dtms;
}



/*!
 * \brief Constructeur de la classe Gestionnaire. C'est ici que vous devez lire et charger les fichiers gtfs utile au tp.
 * \param chemin_dossier: chemin d'accès vers le dossier gtfs. Dans le cadre du tp, vous deviez vous intéressé aux fichiers
 * routes.txt, trips.txt, stop_times.txt, stops.txt, calendar_dates.txt
 *
 */
GestionnaireInvestigation::GestionnaireInvestigation(std::string chemin_dossier){
	std::unordered_map<unsigned int, Ligne*> lignes_par_id;
	std::unordered_multimap<std::string, Voyage*> voyages_par_service_id;
	std::unordered_multimap<std::string, Arret> map_arrets;
	std::vector<std::vector<std::string> > temp;
	unsigned int id;

	clock_t begin = clock();
	lireFichier(chemin_dossier+"/routes.txt", temp, ',', true);
	for(const std::vector<std::string>& ligne_gtfs: temp)
	{
		//On utilise ici une passe pour que tous les ids d'une même ligne de bus refère à un même objet Ligne
		if(lignes.count(ligne_gtfs[2]) == 0)
		{
			lignes.insert(std::make_pair(ligne_gtfs[2], Ligne(ligne_gtfs)));
			lignes_par_id.insert({(lignes.find(ligne_gtfs[2])->second).getId(), &(lignes.find(ligne_gtfs[2])->second)});
		}
		else
		{
			id = std::atoi(ligne_gtfs[0].c_str());
			lignes_par_id.insert({id, &(lignes.find(ligne_gtfs[2])->second)});
		}
	}

	temp.clear();
	lireFichier(chemin_dossier+"/stops.txt", temp, ',', true);
	for(const std::vector<std::string>& ligne_gtfs: temp)
	{
		id = std::atoi(ligne_gtfs[0].c_str());
		stations.insert(std::make_pair(id, Station(ligne_gtfs)));
	}

	temp.clear();
	lireFichier(chemin_dossier+"/trips.txt", temp, ',', true);
	for(const std::vector<std::string>& ligne_gtfs: temp)
	{
		id = std::atoi(ligne_gtfs[0].c_str());
		std::pair<std::unordered_map<std::string, Voyage>::iterator, bool> res =
				voyages.insert(std::make_pair(ligne_gtfs[2], Voyage(ligne_gtfs, lignes_par_id.find(id)->second)));
		voyages_par_service_id.insert({ligne_gtfs[1], &(res.first->second)});
		lignes_par_id.find(id)->second->addVoyage(&(res.first->second));
	}

	temp.clear();
	lireFichier(chemin_dossier+"/stop_times.txt", temp, ',', true);
	for(const std::vector<std::string>& ligne_gtfs: temp)
	{
		map_arrets.insert({ligne_gtfs[0], Arret(ligne_gtfs)});
		unsigned int sid = std::atoi(ligne_gtfs[3].c_str());
		auto it = voyages.find(ligne_gtfs[0]);
		auto it2 = stations.find(sid);
		(it2->second).addVoyage(&(it->second));
	}
	for(auto kv: voyages){
		auto arrets_trouvees = map_arrets.equal_range(kv.first);
		std::vector<Arret> arrets_voyages;
		for(auto it= arrets_trouvees.first; it != arrets_trouvees.second; it++){
			arrets_voyages.push_back(it->second);
		}
		if(arrets_voyages.size()  == 0) throw std::logic_error("error here");
		voyages.find(kv.first)->second.setArrets(arrets_voyages);
	}

	temp.clear();

	clock_t end = clock();
	std::cout << "Chargement des données terminé en " << double(end - begin) / CLOCKS_PER_SEC << " secondes" << std::endl;

	begin = clock();
	std::cout << "Initialisation du réseau ...." << std::endl;
	initialiser_reseau();
	end = clock();
	std::cout << "Chargement des données terminé en " << double(end - begin) / CLOCKS_PER_SEC << " secondes" << std::endl << std::endl;

}

/*!
 * \brief Permet de vérifier si un numéro de station est pris en charge ou pas
 * \param station_id: l'identifiant de la station d'intéret
 * \return True ssi la station est prise en charge
 */
bool GestionnaireInvestigation::station_existe(int station_id){
	return (stations.find(station_id) != stations.end());
}


/*!
 * \brief Trouver le plus court chemin en autobus pour aller deux stations A et B
 * Pour ce faire, il faut initialiser le réseau, puis faire appel à ses routines de plus courts chemin
 * \param num_station_depart: numéro de la station de départ
 * \param num_station_dest: numéro de la station de départ
 * \return Un vecteur contenant les stations du chemin trouvé, le vecteur est vide si aucun chemin n'est disponible
 */
std::vector<unsigned int> GestionnaireInvestigation::plus_court_chemin_dijsktra(unsigned int num_station_depart, unsigned int num_station_dest)
{
	timeval tv1, tv2;

	if (gettimeofday(&tv1, 0) != 0)
			throw std::logic_error("gettimeofday() a échoué");

	std::vector<unsigned int> chemin;
	m_reseau.dijkstra(num_station_depart, num_station_dest, chemin);

	if (gettimeofday(&tv2, 0) != 0)
			throw std::logic_error("gettimeofday() a échoué");

	std::cout << "la fonction s'est terminé en " << tempsExecution(tv1, tv2) << "microsecondes" << std::endl;
	return chemin;}

/*!
 * \brief Trouver le plus court chemin en autobus pour aller deux stations A et B
 * Pour ce faire, il faut initialiser le réseau, puis faire appel à ses routines de plus courts chemin
 * Cette méthode affiche le temps d'exécution de votre algorithme pour la paire A, B
 * \param num_station_depart: numéro de la station de départ
 * \param num_station_dest: numéro de la station de départ
 * \return Un vecteur contenant les stations du chemin trouvé, le vecteur est vide si aucun chemin n'est disponible
 */
std::vector<unsigned int> GestionnaireInvestigation::plus_court_chemin_bellman(unsigned int num_station_depart, unsigned int num_station_dest)
{
	timeval tv1, tv2;

	if (gettimeofday(&tv1, 0) != 0)
			throw std::logic_error("gettimeofday() a échoué");

	std::vector<unsigned int> chemin;
	m_reseau.bellmanFord(num_station_depart, num_station_dest, chemin);

	if (gettimeofday(&tv2, 0) != 0)
			throw std::logic_error("gettimeofday() a échoué");

	std::cout << "la fonction s'est terminé en " << tempsExecution(tv1, tv2) << " microsecondes" << std::endl;
	return chemin;
}

/*!
 * Mesurer le temps d'exécution moyen de l'algorithme dijsktra sur toutes les paires de stations du réseau de la RTC
 * return un réel représentant le temps moyen de l'algorithme en microsecondes
 */
double GestionnaireInvestigation::tester_n_paires_dijsktra(unsigned int nb_paires, unsigned int seed){
	/* initialize random seed: */
	srand (seed);
	double total = 0;
	unsigned int i =0;

	std::vector<unsigned int > v;

	for(auto st1: stations){
		v.push_back(st1.first);
	}

	while(i < nb_paires){
		timeval tv1, tv2;
		int k = rand() % v.size();
		int j = rand() % v.size();


		if (gettimeofday(&tv1, 0) != 0)
				throw std::logic_error("gettimeofday() a échoué");

		std::vector<unsigned int> chemin;
		plus_court_chemin_dijsktra(v[j], v[k]);
		//m_reseau.dijkstra(v[j], v[k], chemin);

		//Je cherche le nombre de chemin et le nombre d'arcs du réseau
		std::cout << "Le réseau possède : " << m_reseau.nombreSommets() << " sommets   et "<< m_reseau.nombreArcs() << " arcs" << std::endl << std::endl;

		if (gettimeofday(&tv2, 0) != 0)
				throw std::logic_error("gettimeofday() a échoué");
		total = total + tempsExecution(tv1, tv2);
		i++;
	}
	return total/(1.0*nb_paires);
}


/*!
 * Mesurer le temps d'exécution moyen de l'algorithme bellmanFord sur toutes les paires de stations du réseau de la RTC
 * return un réel représentant le temps moyen de l'algorithme en microsecondes
 */
double GestionnaireInvestigation::tester_n_paires_bellman(unsigned int nb_paires, unsigned int seed){
	/* initialize random seed: */
	srand (seed);
	double total = 0;
	unsigned int i =0;

	std::vector<unsigned int > v;

	for(auto st1: stations){
		v.push_back(st1.first);
	}


	while(i < nb_paires){
		timeval tv1, tv2;
		int k = rand() % v.size();
		int j = rand() % v.size();


		if (gettimeofday(&tv1, 0) != 0)
				throw std::logic_error("gettimeofday() a échoué");

		std::vector<unsigned int> chemin;
		plus_court_chemin_bellman(v[j], v[k]);
		//m_reseau.bellmanFord(v[j], v[k], chemin);

		//Je cherche le nombre de chemin et le nombre d'arcs du réseau
		std::cout << "Le réseau possède : " << m_reseau.nombreSommets() << " sommets   et "<< m_reseau.nombreArcs() << " arcs" << std::endl << std::endl;

		if (gettimeofday(&tv2, 0) != 0)
				throw std::logic_error("gettimeofday() a échoué");
		total = total + tempsExecution(tv1, tv2);
		//std::cout << i << ": " << tempsExecution(tv1, tv2) << std::endl;
		i++;
	}
	return total/(1.0*nb_paires);
}

/*!
 * \brief inialiser ou réinitialiser l'attribut m_reseau en fonction des paramètres.
 * On ajoute des arêtes à tous les endroits empruntées par les bus dans le réseau.
 * Aussi, on ajoute des arêtes entre les stations qui sont à une distance l'une de l'autre inférieure à dist_transfert
 * \param dist_transfert: distance maximale de marche pour un transfert de bus
 */
void GestionnaireInvestigation::initialiser_reseau(double dist_transfert)
{
	for(auto st: stations){
		m_reseau.ajouterSommet(st.first);
	}
	ajouter_aretes_empruntees_par_bus();
	ajouter_aretes_transfert(dist_transfert);
}

/*!
 * \brief Ajouter dans un réseau, où toutes les stations existent déjà, les arêtes entre deux stations ssi où au moins
 * un bus les relient sans arrets intermédiaires.
 *
 */
void GestionnaireInvestigation::ajouter_aretes_empruntees_par_bus()
{
	for(auto kv: voyages)
	{
		std::vector<Arret> seq = kv.second.getArrets();
		for(unsigned int i=0; i< seq.size()-1; i++)
		{
			int d = seq[i+1].getHeureDepart() - seq[i].getHeureArrivee();
			if(!m_reseau.arcExiste(seq[i].getStationId(), seq[i+1].getStationId()))
			{
				m_reseau.ajouterArc(seq[i].getStationId(), seq[i+1].getStationId(), d, (unsigned int)MoyenDeplacement::BUS);
			}
		}
	}
}

/*!
 * \brief ajouter des arêtes entre les stations qui sont à une distance l'une de l'autre inférieure à dist_transfert.
 * Les arêtes ajoutées doivent être de type MoyenDeplacement::PIEDS
 * \param dist_transfert: distance maximale de marche pour un transfert de bus
 */
void GestionnaireInvestigation::ajouter_aretes_transfert(double dist_transfert)
{
	unsigned int st_dep, st_dest, t;
	unsigned int i, j;
	double distance;
	std::vector<unsigned int> list_stations;
	for(auto st: stations){
		list_stations.push_back(st.first);
	}

	// Ajout des arêtes de transfert
	for(i= 0; i < list_stations.size(); i++)
	{
		st_dep = list_stations[i];

		for(j= i+1; j < list_stations.size(); j++)
		{
			st_dest = list_stations[j];
			distance = (stations.find(st_dep)->second).distance(stations.find(st_dest)->second);
			if (distance <= dist_transfert)
			{
				if(!m_reseau.arcExiste(st_dep, st_dest) && !m_reseau.arcExiste(st_dest, st_dep))
				{
					t = (unsigned int)round((distance/vitesse_de_marche)*3600);
					m_reseau.ajouterArc(st_dep, st_dest, t, (unsigned int)MoyenDeplacement::PIEDS);
					m_reseau.ajouterArc(st_dest, st_dep, t, (unsigned int)MoyenDeplacement::PIEDS);
				}
			}
		}
	}
}

