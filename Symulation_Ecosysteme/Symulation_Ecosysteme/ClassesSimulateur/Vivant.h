/**
 * Project Untitled
 */


#ifndef _VIVANT_H
#define _VIVANT_H

 // Librairies standard
#include <list>

// Librairies de Qt
#include <qgraphicsitem>

// Header files du simulateur
#include "Coordonne.h"

// Déclaration anticipée
class Environnement;

class Vivant: public QGraphicsItem {
public: 

	// Constructeur
	Vivant() = default;
	Vivant(Environnement* environnement, std::string espece, int hp,
		int energy, int ageAdulte, int ageMax, int x, int y);
	// Destructeur
	~Vivant()=default;

// Accesseurs
	int getHp() const;
	int gatHpMax() const;
	int getEnergy() const;
	int getEnergyMax() const;
	int getAge() const;
	int getAgeAdulte() const;
	int getAgeMax() const;
	std::string getEspece() const;
	Coordonne getCoordonne() const;

// Mutateurs
	void setHp(int hp);
	void setHpMax(int maxHp);
	void setEnergy(int energy);
	void setEnergyMax(int energyMax);
	void setAge(int age);
	void setAgeAdulte(int ageAdulte);
	void setAgeMax(int ageMax);
	void setEspece(std::string & espece);
	void setCoordonne(Coordonne & coordonne);
    
// Fonctions membres purement virtuelles
	virtual void replenishEnergy() = 0;
	virtual void seekEnergy() = 0;
	virtual void healing() = 0;
	virtual void receiveDamages(int nbDamage) = 0;
	virtual void reproduction() = 0;
	virtual void simulation() = 0;
	virtual void dying() = 0;
	virtual bool isDead() = 0;
	virtual bool isDamaged() = 0;

protected: 
    std::string m_espece;
    int m_hp;
    int m_hpMax;
    int m_energy;
    int m_energyMax;
    int m_age;
	int m_ageAdulte;
    int m_ageMax;
    Coordonne m_coordonne;
    Environnement* m_environnement;
};

#endif //_VIVANT_H