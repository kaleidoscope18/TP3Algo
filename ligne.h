//
// Created by prtos on 29/04/16.
//

#ifndef RTC_LIGNE_H
#define RTC_LIGNE_H

#include <string>
#include <vector>
#include "voyage.h"
#include "station.h"
#include "auxiliaires.h"
#include <exception>
#include <algorithm>

/*!
 * \enum CategorieBus
 * \brief Représente les différentes catégories de bus
 *
 */
enum class CategorieBus {METRO_BUS, LEBUS, EXPRESS, COUCHE_TARD};

class Voyage;


/*!
 * \class Ligne
 * \brief Cette classe représente une ligne d'autobus du réseau de transport contenues dans le fichier routes.txt
 * Par exemple, la "800", la "801" et la "13A" sont toutes des lignes différentes.
 * Veuillez, noter qu’il y peut y avoir plus d'une  entrées dans le fichier routes.txt pour chaque ligne d’autobus.
 * Cela est dû au fait qu'un dossier gtfs puisse cheuvaucher deux saisons (des saisons différentes donnent des ids différents à une même ligne).
 * Ceci qui implique qu’un numéro de ligne est associé à deux identifiants différents, cependant vous ne devez construire qu'un seul
 * objet ligne par ligne d'autobus.
 * \note Sa déclaration nécessite la déclaration partielle des classe Voyage, en raison de référence circulaire avec cette classe.
 */
class Ligne {

private:
    unsigned int m_id;
    std::string m_numero;
    std::string m_description;
    CategorieBus m_categorie;
    std::vector<Voyage*> m_voyages;

public:
    Ligne(const std::vector<std::string>& ligne_gtfs);
    static CategorieBus couleurToCategorie(std::string couleur);
    static std::string categorieToString(CategorieBus c);
	CategorieBus getCategorie() const;
	void setCategorie(CategorieBus categorie);
	std::pair<std::string, std::string> getDestinations() const;
	unsigned int getId() const;
	void setId(unsigned int id);
	const std::string& getNumero() const;
	void setNumero(const std::string& numero);
	const std::vector<Voyage*>& getVoyages() const;
	void setVoyages(const std::vector<Voyage*>& voyages);
	void addVoyage(Voyage* ptr_voyage);
	const std::string& getDescription() const;
	void setDescription(const std::string& description);
	friend std::ostream& operator <<(std::ostream& f, const Ligne& p_ligne);
};


#endif //RTC_LIGNE_H
