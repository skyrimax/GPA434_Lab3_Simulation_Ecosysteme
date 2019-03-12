/**
 * Project Untitled
 */


#ifndef _GRID_H
#define _GRID_H

// Header files du simulateur
#include "Terrain.h"
#include "constantes.h"

class Grid {
public: 
    
	Grid();

	void genererTerrain();
    
	void updateTerrain();
private: 
	Terrain *grid[LARGEUR_GRILLE][HAUTEUR_GRILLE];
};

#endif //_GRID_H