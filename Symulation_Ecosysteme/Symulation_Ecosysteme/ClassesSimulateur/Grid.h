/**
 * Project Untitled
 */


#ifndef _GRID_H
#define _GRID_H

// Header files du simulateur
#include "Terrain.h"
#include "constantes.h"
#include "Plante.h"

// Déclarations anticipées
class Environnement;

class Grid {
public: 
    
	// Constructeur de Grid utilisant le Bruit de Perlin
	// pour une génération procédurale pseudo-aléatoire du terrain
	Grid(Environnement* environnement);
	// Destructeur de Grid
	~Grid();
    
	void updateTerrain();

	Terrain* getTerrain(int x, int y);
private: 
	Terrain *m_grid[LARGEUR_GRILLE][HAUTEUR_GRILLE];
	Environnement *m_environnementProprietaire;

};

#endif //_GRID_H