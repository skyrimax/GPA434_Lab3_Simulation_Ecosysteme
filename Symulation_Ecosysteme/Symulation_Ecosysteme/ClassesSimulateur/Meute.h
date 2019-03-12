/**
 * Project Untitled
 */


#ifndef _MEUTE_H
#define _MEUTE_H

#include "QGraphicsItemGroup.h"


class Meute: public QGraphicsItemGroup {
private: 
    list<Animal*> membres;
    bool attacked;
    bool faim;
};

#endif //_MEUTE_H