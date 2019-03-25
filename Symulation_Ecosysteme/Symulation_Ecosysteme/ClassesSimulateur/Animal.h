/**
 * Project Untitled
 */


#ifndef _ANIMAL_H
#define _ANIMAL_H

#define _USE_MATH_DEFINES

 // Librairies standard
#include <list>
#include <cmath>

#include "Vivant.h"
#include "Orientation.h"
#include "Charogne.h"


class Animal: public Vivant {
public: 

	enum class Sex { Male = 0, Female = 1 };
	// Constructeur
	Animal() = default;
	Animal(Environnement* environnement, std::string espece, int hp,
		int energy, int ageAdulte, int ageMax, int x, int y,
		double vitesse, double sprint, Sex sex,
		int nbProgenituresMin, int nbProgenituresMax,
		int timerMort, int timerGestation, int timerReproduction,
		std::list<std::string> cible);
	// Destructeur
	~Animal() = default;

	// Fonctions membres virtuelles héritées de Vivant
	virtual void seekEnergy() override;
	virtual void healing() override;
	virtual void receiveDamages(int nbDamage) override;
	virtual void reproduction() override;
	virtual void dying() override;
	virtual bool isDead() override;
	virtual bool isDamaged() override;
    
	// Fonctions membres communes à tous les animaux
	void devenirCharogne();
	bool isSprinting();
	void sprint();
	void walk();
	void flee();
	void wander();

	// Fonction membres spécifique à chaque type d'animaux
	virtual void chooseTarget() = 0;
	virtual void trackTarget() = 0;

protected: 

	// Fonction membre pour déplacer l'animal
	void deplacer(double vitesse);
	void closestPredateur();

    double m_vitesse;
    double m_sprint;
    bool m_isSprinting;
    Sex m_sex;
    bool m_aEnfant;
	int m_nbProgenituresMin;
	int m_nbProgenituresMax;
    std::list<Animal*> m_predateurs;
	Animal* m_closestPredateur;
    Orientation m_orientation;
    int m_timerMort;
	int m_timerGestation;
	int m_timerReproduction;
	std::list<std::string> m_cible;
};

#endif //_ANIMAL_H