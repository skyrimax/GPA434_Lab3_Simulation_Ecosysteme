/**
 * Project Untitled
 */


#ifndef _MEUTE_H
#define _MEUTE_H

#include <QGraphicsItemGroup>


class Meute: public QGraphicsItemGroup {
public:

	std::list<Animal*> getMembres();

	void addMembre(Animal* membre);

	std::list<Animal*>& simulation();

private: 
    std::list<Animal*> m_membres;
    bool attacked;
    bool faim;
};

#endif //_MEUTE_H