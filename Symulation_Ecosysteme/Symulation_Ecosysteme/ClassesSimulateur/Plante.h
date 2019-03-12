/**
 * Project Untitled
 */


#ifndef _PLANTE_H
#define _PLANTE_H

#include "Vivant.h"


class Plante: public Vivant {
private: 
    int fruits;
    list<Herbivore*> isEatenBy;
    bool isBeingEaten;
};

#endif //_PLANTE_H