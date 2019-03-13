/**
 * Project Untitled
 */


#ifndef _VIVANT_H
#define _VIVANT_H

 // Librairies standard
#include <list>

#include <qgraphicsitem>


class Vivant: public QGraphicsItem {
public: 
    
virtual vitual void getEnergie() = 0;
    
virtual virtual void seekEnergie() = 0;
    
virtual virutal void reproduction() = 0;
    
virtual virtual void simulation() = 0;
    
virtual virtual void mourrir() = 0;
    
virtual virtual bool estMort() = 0;
private: 
    std::string espece;
    int hp;
    int hpMax;
    int energy;
    int energyMax;
    int age;
    int ageMax;
    Coordonne coordonne;
    Environnement* environnement;
};

#endif //_VIVANT_H