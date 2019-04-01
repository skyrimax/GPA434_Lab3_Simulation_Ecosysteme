/**
 * Project Untitled
 */


#ifndef _MEUTE_H
#define _MEUTE_H

#include <QGraphicsItemGroup>


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