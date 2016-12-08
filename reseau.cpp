#include "reseau.h"
#include <map>
#include "PairingH.h"

/*!
 * \brief constructeur par défaut d'un réseau. Crée un réseau vide.
 *
 */
Reseau::Reseau(): nbSommets(0), nbArcs(0) {}


/*!
 * \brief Trouver le nombre de sommet dans le graphe en O(1)
 * \return nombre de sommet du graphe
 */
int Reseau::nombreSommets() const
{
    return nbSommets;
}

/*!
 * \brief Trouver le nombre d'arcs dans le graphe en O(1)
 * \return nombre d'arcs du graphe
 */
int Reseau::nombreArcs() const
{
	return nbArcs;
}

/*!
 * \brief Déterminer si le graphe est vide ou pas en O(1)
 * \return True ssi le graphe est vide
 */
bool Reseau::estVide() const
{
    return nbSommets == 0;
}

/*!
 * \brief Permet de déterminer si un sommet existe ou pas
 * \param[in] numero: numéro du sommet à valider
 * \return true ssi le sommet existe
 */
bool Reseau::sommetExiste(unsigned int numero) const
{
    return m_arcs.count(numero) != 0;
}

/*!
 * \brief Permet de déterminer si un arc existe ou pas
 * \param[in] numOrigine: numéro du sommet où l'arc part
 * \param[in] numDest: numéro du sommet où l'arc arrive
 * \exception logic_error si un des deux sommet n'existe pas
 * \return true ssi l'arc existe
 */
bool Reseau::arcExiste(unsigned int numOrigine, unsigned int numDest) const throw (std::logic_error)
{
    if (!(sommetExiste(numOrigine) && sommetExiste(numDest)))
    	throw std::logic_error ("arcExiste: Un des sommets n'existe pas!");
    return m_arcs.find(numOrigine)->second.count(numDest) != 0;
}

/*!
 * \brief Permet d'ajouter un sommet dans le réseau
 * \param[in] p_numero: numéro du sommet à ajouter
 * \exception logic_error si un sommet ayant le même numéro est déjà présent
 * \post le graphe contient un sommet de plus
 */
void Reseau::ajouterSommet(unsigned int p_numero) throw (std::logic_error)
{
    if (sommetExiste(p_numero)) throw std::logic_error("ajouterSommet: Un sommet avec le numero existe!") ;
    m_arcs[p_numero] = liste_arcs();
    nbSommets++;
}

/*!
 * \brief Permet d'ajouter un arc au réseau
 * \param[in] numOrigine: numéro du sommet destiné à émettre l'arc
 * \param[in] numDest: numéro du sommet destiné à recevoir l'arc
 * \param[in] cout: le coût ou poids de l'arc à ajouter
 * \param[in] type: type de l'arc à ajouter
 * \exception logic_error si un des sommets n'existe pas
 * \exception logic_error si l'arc est déjà présent
 * \post le graphe contient un arc de plus entre l'origine et la destination
 */
void Reseau::ajouterArc(unsigned int numOrigine, unsigned int numDest, unsigned int cout, unsigned int type)
throw(std::logic_error)
{
    if ( arcExiste(numOrigine, numDest) ) throw std::logic_error ("ajouterArc: arc déja existant");
    m_arcs[numOrigine].insert({numDest, {cout, type} });
    nbArcs++;
}

/*!
 * \brief Permet d'enlever un sommet dans du réseau, ainsi que tous ces arcs entrants et sortants.
 * \param[in] numero: numéro du sommet à enlever
 * \exception logic_error si aucun sommet ayant le même numéro est déjà présent
 * \post le graphe contient un sommet de moins et peut être plusieurs arcs de moins.
 */
void Reseau::enleverSommet(unsigned int numero) throw (std::logic_error)
{
    if (!sommetExiste(numero)) throw std::logic_error("enleverSommet: le sommet n'existe pas");
    unsigned int origine;

    for(auto kv: m_arcs){
    	origine = kv.first;
        if(arcExiste(origine, numero)){enleverArc(origine, numero);}
    }
    m_arcs.erase(numero);
    nbSommets --;
}

/*!
 * \brief Enlever un arc du réseau
 * \param[in] numOrigine: numéro du sommet supposé émettre l'arc
 * \param[in] numDest: numéro du sommet supposé recevoir l'arc
 * \exception logic_error si un des sommets n'existe pas
 * \exception logic_error si l'arc n'est pas présent dans le graphe
 * \post le graphe contient un arc de moins
 */
void Reseau::enleverArc(unsigned int numOrigine, unsigned int numDest) throw (std::logic_error)
{
    if (!arcExiste(numOrigine, numDest)) throw std::logic_error ("enleverArc: arc non existant");
    m_arcs[numOrigine].erase(numDest);
    nbArcs--;
}

/*!
 * \brief Permet de mettre à jour le coût d'un arc du réseau
 * \param[in] numOrigine: numéro du sommet destiné à émettre l'arc
 * \param[in] numDest: numéro du sommet destiné à recevoir l'arc
 * \param[in] cout: le nouveau coût ou poids de l'arc à mettre à jour
 * \exception logic_error si un des sommets n'existe pas
 * \exception logic_error si l'arc n'est pas déjà présent
 * \post le poids de l'arc a été mis à jour
 */
void Reseau::majCoutArc(unsigned int numOrigine, unsigned int numDest, unsigned int cout) throw (std::logic_error)
{
	if (!arcExiste(numOrigine, numDest)) throw std::logic_error ("majCoutArc: arc non existant");
    m_arcs[numOrigine][numDest].first = cout;
}

/*!
 * \brief Trouver le coût d'un arc du réseau
 * \param[in] numOrigine: numéro du sommet supposé émettre l'arc
 * \param[in] numDest: numéro du sommet supposé recevoir l'arc
 * \exception logic_error si un des sommets n'existe pas
 * \exception logic_error si l'arc n'est pas présent dans le graphe
 * \return le cout de l'arc
 */
int Reseau::getCoutArc(unsigned int numOrigine, unsigned int numDest) const throw (std::logic_error){
	if (!arcExiste(numOrigine, numDest) ) throw std::logic_error ("getCoutArc: arc non existant");
    return m_arcs.find(numOrigine)->second.find(numDest)->second.first;
}

/*!
 * \brief Trouver le type d'un arc du réseau
 * \param[in] numOrigine: numéro du sommet supposé émettre l'arc
 * \param[in] numDest: numéro du sommet supposé recevoir l'arc
 * \exception logic_error si un des sommets n'existe pas
 * \exception logic_error si l'arc n'est pas présent dans le graphe
 * \return le type de l'arc
 */
int Reseau::getTypeArc(unsigned int numOrigine, unsigned int numDest) const throw (std::logic_error){
	if (!arcExiste(numOrigine, numDest) ) throw std::logic_error ("getTypeArc: arc non existant");
    return m_arcs.find(numOrigine)->second.find(numDest)->second.second;
}

/*!
 * \brief Algorithme de Dijkstra en O(n*n)  permettant de trouver le plus court chemin entre deux noeuds du graphe
 * \param[in] numOrigine: le sommet d'où le chemin part
 * \param[in] numDest: le sommet que le chemin est censé atteindre
 * \param[out] chemin:  le vecteur contenant le chemin trouvé s'il y en existe un
 * \exception logic_error si un des sommets n'existe pas
 * \return la longueur du chemin (= numeric_limits<int>::max() si p_destination n'est pas atteignable)
 */
int Reseau::dijkstra(unsigned int numOrigine, unsigned int numDest, std::vector<unsigned int> & chemin) throw (std::logic_error)
{
    if ( !sommetExiste(numOrigine) || !sommetExiste(numDest) ) throw std::logic_error ("dijkstra: Un des sommets n'existe pas!");
    std::unordered_map<unsigned int, int> distances;
    std::unordered_map<unsigned int, int> predecesseurs;
    std::unordered_set<unsigned int> Q;
    unsigned int max_poids = std::numeric_limits<int>::max();
    unsigned int noeud_min;
    int temp;

    for(auto kv: m_arcs){
    	distances[kv.first] = max_poids;
    	predecesseurs[kv.first] = -1;
    	Q.insert(kv.first);
    }

    distances[numOrigine] = 0;
    for(int i = 0; i < nbSommets; i++){
    	noeud_min = *(Q.begin());
    	for(auto noeud: Q){
    		if(distances[noeud] < distances[noeud_min]){
    			noeud_min = noeud;
    		}
    	}
    	Q.erase(noeud_min);
    	if(noeud_min == numDest){
    		break;
    	}

    	for(auto voisin: m_arcs[noeud_min]){
    		if(Q.count(voisin.first) != 0){
    			temp = voisin.second.first + distances[noeud_min];
    			if(temp < distances[voisin.first]) {
    				distances[voisin.first] = temp;
    				predecesseurs[voisin.first] = noeud_min;
    			}
    		}
    	}
    }

    chemin.clear();
    if(predecesseurs[numDest] != -1){
    	std::vector<unsigned int> chemin_inverse;
		int courant = numDest;
		while(courant!=-1){
			chemin_inverse.push_back(courant);
			courant = predecesseurs[courant];
		}
		for(int i=chemin_inverse.size() -1; i >= 0; i--){
			chemin.push_back(chemin_inverse[i]);
		}
    }
    return distances[numDest];
}

/*!
 * \brief Algorithme de Dijkstra en O(nlogn)  permettant de trouver le plus court chemin entre deux noeuds du graphe
 * \param[in] numOrigine: le sommet d'où le chemin part
 * \param[in] numDest: le sommet que le chemin est censé atteindre
 * \param[out] chemin:  le vecteur contenant le chemin trouvé s'il y en existe un
 * \exception logic_error si un des sommets n'existe pas
 * \return la longueur du chemin (= numeric_limits<int>::max() si p_destination n'est pas atteignable)
 */
int Reseau::meilleurPlusCourtChemin(unsigned int numOrigine, unsigned int numDest, std::vector<unsigned int> & chemin) throw (std::logic_error)
{
    if ( !sommetExiste(numOrigine) || !sommetExiste(numDest) ) throw std::logic_error ("dijkstra: Un des sommets n'existe pas!");
//    for(auto kv: m_arcs){
//    	for(auto kw: kv.second){
//    		std::cout << kv.first << "->" << kw.first << " poids : " << kw.second.first << std::endl;
//    	}
//    }
    std::unordered_map<unsigned int, std::pair<Noeud *, unsigned int>> sommetsNodes;
   // <sommet depart, <ptr_noeud associé au sommet dans le heap, predecesseur>>

    PairingH heap;
    // dans le heap chaque Noeud a la distance et le sommet associé au noeud

    //on ajoute la racine en premier (noeud initial)
    sommetsNodes[numOrigine] = std::pair<Noeud *, unsigned int>(heap.ajouterNoeud(1, numOrigine), 0);

    for(auto kv: m_arcs){ //on construit le heap
    	unsigned int le_sommet = (kv.first);
//    	std::cout << "ajout sommet " << le_sommet << std::endl;
    	if(le_sommet != numOrigine){
    		sommetsNodes[le_sommet] = std::pair<Noeud *, unsigned int>(heap.ajouterNoeud(9999, le_sommet), 0);
    	}
//    	std::cout << "racine " << heap.racine->sommet << " distance " << heap.racine->distance << std::endl;
    }

    for(int i = 0; i < nbSommets; ++i){

    	unsigned int u_etoile = heap.racine->m_sommet; //u* est noeud dans Q tel que d(u) est minimal = racine du heap
    	int dist_u_etoile = heap.racine->distance;

    	std::cout << "la racine est : " << u_etoile << " et sa distance est : " << dist_u_etoile << std::endl;

    	heap.retirerRacine();

    	std::cout << heap.nombreNoeuds() << std::endl;

    	for(auto u : m_arcs[u_etoile]){ //on itère sur tous les u adj a u*

			int temp { dist_u_etoile + u.second.first }; // temp = d(u*) + w(u*, u)
    		std::cout << "temp = d(u*) + w(u*, u) <=> " << temp << std::endl;

    		int dist_u = sommetsNodes[u.first].first->distance; //d(u)

    		if(temp < dist_u){
    			Noeud * u_noeud =  sommetsNodes[u.first].first;
    			heap.diminuerDistance(u_noeud, temp); //d(u) = temp
    			sommetsNodes[u.first].second = u_etoile; //p(u) = u*
    			std::cout << "sommet " << u.first << " a passe de " << dist_u << " a " << u_noeud->distance << std::endl;
    			std::cout << "la racine est devenue : " << heap.racine->m_sommet << " avec une distance de " << heap.racine->distance << std::endl;
    		}
    	}
    }

    chemin.clear();
    if(sommetsNodes[numDest].second == 0){
    	std::cout << "le sommet de destination n'est pas atteignable" << std::endl;
    }
    else{
    	std::vector<unsigned int> chemin_inverse;
    	unsigned int courant = numDest;
    	while(courant != numOrigine){
    		chemin_inverse.push_back(courant);
    		courant = sommetsNodes[courant].second;
    	}
    	chemin.push_back(numOrigine);
    	for(auto i : chemin_inverse){
    		chemin.push_back(i);
    	}
    }

    return 0; //sommetsNodes.find(ptr_sommetDest)->second.first->distance;
}


/*!
 * \brief Algorithme de BellmanFord en O(n*m)  permettant de trouver le plus court chemin entre deux noeuds du graphe
 * \param[in] numOrigine: le sommet d'où le chemin part
 * \param[in] numDest: le sommet que le chemin est censé atteindre
 * \param[out] chemin:  le vecteur contenant le chemin trouvé s'il y en existe un
 * \exception logic_error si un des sommets n'existe pas
 * \return la longueur du chemin (= numeric_limits<int>::max() si p_destination n'est pas atteignable)
 */
int Reseau::bellmanFord(unsigned int numOrigine, unsigned int numDest, std::vector<unsigned int> & chemin) throw (std::logic_error)
{
    if ( !sommetExiste(numOrigine) || !sommetExiste(numDest) ) throw std::logic_error ("bellmanFord: Un des sommets n'existe pas!");
    unsigned int noeud_courant;
    int temp;
    std::unordered_map<unsigned int, int> distances;
    std::unordered_map<unsigned int, int> predecesseurs;
    int max_poids = std::numeric_limits<int>::max();
    for(auto kv: m_arcs){
    	distances[kv.first] = max_poids;
    	predecesseurs[kv.first] = -1;
    }
    bool estInstable = true;

    distances[numOrigine] = 0;
    for(int i = 1; (i <  nbSommets) && estInstable ; i++){
    	estInstable = false;
    	for(auto kv: m_arcs){
    		noeud_courant = kv.first;
    		if(distances[noeud_courant] < max_poids){
				for(auto voisin: kv.second){
					temp = voisin.second.first + distances[noeud_courant];
					if(temp < distances[voisin.first] && temp >= 0) {
						distances[voisin.first] = temp;
						predecesseurs[voisin.first] = noeud_courant;
						estInstable = true;
					}
				}
    		}
    	}
    }
    chemin.clear();
    if(predecesseurs[numDest] != -1){
    	std::vector<unsigned int> chemin_inverse;
		int courant = numDest;
		while(courant!=-1){
			chemin_inverse.push_back(courant);
			courant = predecesseurs[courant];
		}
		for(int i=chemin_inverse.size() -1; i >= 0; i--){
			chemin.push_back(chemin_inverse[i]);
		}
    }
    return distances[numDest];
}
