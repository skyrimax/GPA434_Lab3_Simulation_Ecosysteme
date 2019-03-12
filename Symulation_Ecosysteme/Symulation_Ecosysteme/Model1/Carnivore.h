/**
 * Project Untitled
 */


#ifndef _CARNIVORE_H
#define _CARNIVORE_H

#include "Animal.h"


class Carnivore: public Animal {
private: 
    Animal* proie;
    bool isCharognard;
};

#endif //_CARNIVORE_H