/**
 * Project Untitled
 */


#ifndef _HERBIVORE_H
#define _HERBIVORE_H

#include "Animal.h"
#include "Plante.h"

 // Déclaration enticipée
class Plante;

class Herbivore: public Animal {
private: 
    Plante* plante;
};

#endif //_HERBIVORE_H