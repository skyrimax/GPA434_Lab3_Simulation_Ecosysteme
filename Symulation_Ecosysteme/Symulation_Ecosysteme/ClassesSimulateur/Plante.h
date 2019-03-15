/**
 * Project Untitled
 */


#ifndef _PLANTE_H
#define _PLANTE_H

 // Librairies standard
#include <list>

// Header files du simulateur
#include "Vivant.h"
#include"constantes.h"

// Déclarations anticipées
class Herbivore;

class Plante: public Vivant {
	// Cosntructeur
	Plante();
	// Destructeur
	~Plante()=default;

	// Fonctions membres virtuelles héritées de Vivant
	virtual void replenishEnergy() override;
	virtual void seekEnergy() override;
	virtual void reproduction() override;
	virtual void simulation() override;
	virtual void dying() override;
	virtual bool isDead() override;

private: 
    int fruits;
    std::list<Herbivore*> isEatenBy;
    bool isBeingEaten;
};

#endif //_PLANTE_H