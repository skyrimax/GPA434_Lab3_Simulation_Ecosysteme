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
#include "constantes.h"


class Animal: public Vivant {
public: 

	enum class Sex { Male = 0, Female = 1 };
	// Constructeur
	Animal() = default;
	Animal(Environnement* environnement, std::string espece, int hp,
		int energy, int ageAdulte, int ageMax, double x, double y,
		double vitesse, double sprint, Sex sex,
		int nbProgenituresMin, int nbProgenituresMax,
		Animal* mere, Meute* meute,
		int timerMort, int tempsGestation, int tempsReproduction,
		std::list<std::string> cible);
	// Destructeur
	~Animal() = default;

	// Fonctions membres virtuelles héritées de Vivant
	virtual void healing() override;
	virtual void receiveDamages(int nbDamage) override;
	virtual void reproduction() override;
	virtual void dying() override;
	virtual bool isDead() override;
	virtual bool isDamaged() override;
    
	// Fonctions membres communes à tous les animaux
	void devenirCharogne();
	bool isHungry();
	bool isSprinting();
	void sprint();
	void walk();
	void flee();
	void wander();
	void trackMother();
	void devenirAdulte();
	void trackAlpha();
	void sprintAlpha();

	//Accesseurs
	Sex getSex();
	Animal* getclosestPredateur();
	Orientation getOrientation();
	Plante* getPlante();
	bool getaEnfant();
	int gettimerReproduction();
	Animal* getMate();
	bool getenceinte();
	int gettimerGestation();
	int gettimerMort();

	//Mutateurs
	void settimerReproduction(int timer);
	void settimerGestation(int timer);
	void settimerMort(int timer);
	Orientation setOrientation(Orientation orientation);

	// Fonction membres spécifique à chaque type d'animaux
	virtual void chooseTarget() = 0;
	virtual void chooseTarget(Vivant* target) = 0;
	virtual void resetTarget() = 0;
	virtual void trackTarget() = 0;
	virtual void chooseMate() = 0;
	virtual void trackMate() = 0;
	virtual void accoucher()=0;

protected: 

	// Fonction membre pour déplacer l'animal
	void deplacer(double vitesse);
	void closestPredateur();

	// Attributs
    double m_vitesse;
    double m_sprint;
    bool m_isSprinting;
    Sex m_sex;
    bool m_aEnfant;
	bool m_enceinte;
	int m_nbProgenituresMin;
	int m_nbProgenituresMax;
    std::list<Animal*> m_predateurs;
	Animal* m_closestPredateur;
	Animal* m_mate;
	Animal* m_mere;
	Meute* m_meute;
	std::list<Animal*> m_enfant;
    Orientation m_orientation;
    int m_timerMort;
	int m_timerGestation;
	int m_tempsGestation;
	int m_timerReproduction;
	int m_tempsReproduction;
	std::list<std::string> m_cible;
	
};

#endif //_ANIMAL_H