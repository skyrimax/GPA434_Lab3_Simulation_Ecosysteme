/**
 * Project Untitled
 */


#ifndef _ANIMAL_H
#define _ANIMAL_H

 // Librairies standard
#include <list>

#include "Vivant.h"
#include "Sex.h"
#include "Velocite.h"


class Animal: public Vivant {
public: 
    
void devenirCharogne();
    
bool isSprinting();
    
void sprint();
    
void walk();
    
void flee();
    
void wander();
    
virtual void chooseTarget() = 0;
    
virtual void trackTarget() = 0;
    class Class1 {
    };
private: 
    double m_vitesse;
    double m_sprint;
    bool m_isSprinting;
    Sex m_sex;
    bool m_aEnfant;
    std::list<Animal*> m_predateurs;
    Velocite m_velocite;
    int m_timerMort;
};

#endif //_ANIMAL_H