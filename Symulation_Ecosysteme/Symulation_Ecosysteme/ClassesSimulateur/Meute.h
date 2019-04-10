/**
 * Project Untitled
 */


#ifndef _MEUTE_H
#define _MEUTE_H

#include <QGraphicsItemGroup>

//Ajouté par Fred:
class Animal; //Averti le programme qu'il y aura une class Animal

class Meute: public QGraphicsItemGroup {
public:

	void simulation();
	void addMembre(Animal* membre);

private: 
    std::list<Animal*> membres;
    bool attacked;
    bool faim;
};

#endif //_MEUTE_H