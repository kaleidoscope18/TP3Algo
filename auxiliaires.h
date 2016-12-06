//
// Created by prtos on 13/06/16.
//

#ifndef RTC_AUXILIAIRES_H
#define RTC_AUXILIAIRES_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "time.h"
#include <unordered_set>
#include <algorithm>

/*!
 * \brief Cette fonction permet de séparer une chaine de caractère en un vecteur de chaines de caractère séparés par un délimiteur
 * Par exemple "toto,tata,tutu" séparé par une virgule donnerait un vecteur contenant "toto", "tata", "tutu"
 * \param[in] s: la chaine de caractère à séparer
 * \param[in] delim: le caractère délimitant
 * \return le vecteur de contenant le résultat
 */
std::vector<std::string> split(const std::string &s, char delim);

/*!
 * \brief Permet de lire un fichier au format gtfs
 * \param[in] nomFichier: chemin d'acces au fichier qui est suposé contennir plusieurs lignes et plusieurs colonnes
 * \param[out] resultats: vecteur 2D destiné à contenir le fichier, l'élement [i][j] représente la ième ligne et la jème colonne du fichier
 * \param[in] delimiteur: le caractère délimiteur des colonnes dans ce fichier.
 * \param[in] rm_entete:  un booléen qui spécifie s'il faut supprimer ou pas la première ligne du fichier.
 * \pre Le fichier existe
 * \exception logic_error s'il y a un problème lors de l'ouverture du fichier.
 */
void lireFichier(std::string nomFichier, std::vector<std::vector<std::string>>& resultats, char delimiteur, bool rm_entete);


/*!
 * \brief Trouver les éléments en communs dans deux vecteurs
 * \param[in] v1: Le premier vecteur
 * \param[in] v2: le deuxième vecteur
 * \param[out] res: vecteur destiné à contenir l'intersection des deux vecteurs.
 */
template<typename T>
void intersection(const std::vector<T>& v1, const std::vector<T>& v2, std::vector<T>& res){
	res.clear();
	std::unordered_set<T> inter;
	for(const T & x: v1){
		inter.insert(x);
	}
	for(const T & y: v2){
		if(inter.count(y) == 1){
			res.push_back(y);
		}
	}
};


/*!
 * \class Date
 * \brief Cette classe représente une date.
 */
class Date {
public:
	Date();
	Date(unsigned int an, unsigned int mois, unsigned int jour);
	bool operator== (const Date & other) const;
	bool operator< (const Date & other) const;
	bool operator> (const Date & other) const;
	friend std::ostream & operator<<(std::ostream & flux, const Date & p_date);

	int getTimeCode() const{
		return m_code;
	}

	unsigned int getAn() const {
		return m_an;
	}

	void setAn(unsigned int p_an) {
		this->m_an = p_an;
		encode(m_an, m_mois, m_jour);
	}

	unsigned int getJour() const {
		return m_jour;
	}

	void setJour(unsigned int p_jour) {
		this->m_jour = p_jour;
		encode(m_an, m_mois, m_jour);
	}

	unsigned int getMois() const {
		return m_mois;
	}

	void setMois(unsigned int p_mois) {
		this->m_mois = p_mois;
		encode(m_an, m_mois, m_jour);
	}

private:
	int m_code; // nombre de jours depuis 1970-01-01 pour la date en parametre
	unsigned int m_an;
	unsigned int m_mois;
	unsigned int m_jour;

	void encode(unsigned int an, unsigned int mois, unsigned int jour);

};


/*!
 * \class Heure
 * \brief Cette classe représente l'heure d'une journée.
 * Cependant pour les besoins du travail pratique nous permettont qu'elle puisse encoder un nombre d'heures supérieurs à 24
 */
class Heure {
public:
	Heure();
	Heure(unsigned int heure, unsigned int min, unsigned int sec);
	Heure add_secondes(unsigned int secs) const;
	bool operator== (const Heure & other) const;
	bool operator< (const Heure & other) const;
	bool operator> (const Heure & other) const;
	bool operator<= (const Heure & other) const;
	bool operator>= (const Heure & other) const;
	int operator- (const Heure & other) const;
	friend std::ostream & operator<<(std::ostream & flux, const Heure & p_heure);

	unsigned int getHeure() const {
		return m_heure;
	}

	void setHeure(unsigned int p_heure) {
		this->m_heure = p_heure;
		encode(m_heure, m_min, m_sec);
	}

	unsigned int getMin() const {
		return m_min;
	}

	void setMin(unsigned int p_min) {
		this->m_min = p_min;
		encode(m_heure, m_min, m_sec);
	}

	unsigned int getSec() const {
		return m_sec;
	}

	void setSec(unsigned int p_sec) {
		this->m_sec = p_sec;
		encode(m_heure, m_min, m_sec);
	}

private:
	unsigned int m_code;
	unsigned int m_heure;
	unsigned int m_min;
	unsigned int m_sec;

	void encode(unsigned int heure, unsigned int min, unsigned int sec);
};


namespace std {

  /*!
   * \brief La définition de cette structure de hash est nécessaire si l'on veut utiliser une date comme une clé dans un unordered_map ou un unordered_set
   */
  template <>
  struct hash<Date>
  {
    std::size_t operator()(const Date& d) const
    {
      using std::size_t;
      using std::hash;

      // Compute hash values
      return (hash<int>()(d.getTimeCode()) << 1);
    }
  };

}
#endif //RTC_AUXILIAIRES_H
