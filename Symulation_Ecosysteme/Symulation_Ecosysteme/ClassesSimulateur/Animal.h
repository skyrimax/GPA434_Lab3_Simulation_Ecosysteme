/**
 * Project Untitled
 */


#ifndef _ANIMAL_H
#define _ANIMAL_H

 // Librairies standard
#include <list>

#include "Vivant.h"
#include "Sex.h"
#include "Velocite.h"
#include "Charogne.h"


class Animal: public Vivant {
public: 
	// Constructeur
	Animal() = default;
	Animal(Environnement* environnement, std::string espece, int hp,
		int energy, int ageAdulte, int ageMax, int x, int y,
		double vitesse, double sprint, Sex sex,
		int timerMort, int timerGestation, int timerReproduction,
		std::string cible);
	// Destructeur
	~Animal() = default;
    
	// Fonctions membres communes � tous les animaux
	void devenirCharogne();
	bool isSprinting();
	void sprint();
	void walk();
	void flee();
	void wander();

	// Fonction membres sp�cifique � chaque type d'animaux
	virtual void chooseTarget() = 0;
	virtual void trackTarget() = 0;

private: 
    double m_vitesse;
    double m_sprint;
    bool m_isSprinting;
    Sex m_sex;
    bool m_aEnfant;
    std::list<Animal*> m_predateurs;
    Orientation m_velocite;
    int m_timerMort;
	int m_timerGestation;
	int m_timerReproduction;
	std::string cible;
};

#endif //_ANIMAL_H