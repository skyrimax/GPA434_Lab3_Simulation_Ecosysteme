/**
 * Project Untitled
 */


#ifndef _ANIMAL_H
#define _ANIMAL_H

#include "Vivant.h"


class Animal: public Vivant {
public: 
    
void devenirCharogne();
    
bool isSprinting();
    
void sprint();
    
void walk();
    
void flee();
    
void wander();
    
virtual virtual void chooseTarget() = 0;
    
virtual virtual void trackTarget() = 0;
    class Class1 {
    };
private: 
    double vitesse;
    double sprint;
    bool isSprinting;
    Sex sex;
    bool aEnfant;
    list<Animal*> predateurs;
    Velocite velocite;
    int timerMort;
};

#endif //_ANIMAL_H