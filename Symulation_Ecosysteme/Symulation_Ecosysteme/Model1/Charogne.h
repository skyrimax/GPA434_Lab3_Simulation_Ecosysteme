/**
 * Project Untitled
 */


#ifndef _CHAROGNE_H
#define _CHAROGNE_H

#include "Vivant.h"


class Charogne: public Vivant {
public: 
    
void pourrir();
    
int getTime();
private: 
    int time;
};

#endif //_CHAROGNE_H