/**
 * Project Untitled
 */


#ifndef _PLANTE_H
#define _PLANTE_H

 // Librairies standard
#include <list>

#include "Vivant.h"
#include "Herbivore.h"


class Plante: public Vivant {



private: 
    int fruits;
    std::list<Herbivore*> isEatenBy;
    bool isBeingEaten;
};

#endif //_PLANTE_H