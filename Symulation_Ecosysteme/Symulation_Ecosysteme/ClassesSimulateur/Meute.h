/**
 * Project Untitled
 */


#ifndef _MEUTE_H
#define _MEUTE_H

#include <QGraphicsItemGroup>
#include "vivant.h"
#include "Animal.h"
#include "orientation.h"
#include "Herbivore.h"
#include  <list>

 // Déclaration enticipée
class Animal;

class Meute : public QGraphicsItemGroup {
public:

	void simulation();
	void addMembre(Animal* membre);
	Animal* getAlpha();
	void setAlpha();

private:
	std::list<Animal*> m_membres;
	bool attacked;
	bool faim;
	Animal* m_alpha;
	
};

#endif //_MEUTE_H