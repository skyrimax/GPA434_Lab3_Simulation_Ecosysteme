/**
 * Project Untitled
 */


#ifndef _MEUTE_H
#define _MEUTE_H

#include "vivant.h"
#include "Animal.h"
#include "orientation.h"
#include "Herbivore.h"
#include  <list>

 // Déclaration enticipée
class Animal;
class Environnement;

class Meute {
public:

	std::list<Animal*>& getMembres();
	std::list<Animal*>& simulation();
	void addMembre(Animal* membre);
	Animal* getAlpha();
	void setAlpha();


private:
	std::list<Animal*> m_membres;
	bool attacked;
	bool faim;
	Animal* m_alpha;
	Environnement* m_environnement;
};

#endif //_MEUTE_H