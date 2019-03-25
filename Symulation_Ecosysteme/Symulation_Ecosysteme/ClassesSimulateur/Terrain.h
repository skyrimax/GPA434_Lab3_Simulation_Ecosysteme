/**
 * Project Untitled
 */


#ifndef _TERRAIN_H
#define _TERRAIN_H

 // Header files du simulateur
//#include "Grid.h"
#include "constantes.h"

// Déclaration anticipée
class Grid;

class Terrain {
public: 
    
	enum class TypeTerrain { Eau = 0, Terre = 1, Gazon = 2, Frontiere = 3 };

	// Constructeur
	Terrain(Grid* grilleProprietaire, int x, int y, TypeTerrain type);
	// Destructeur par défault, on a pas à détruire la grille
	Terrain() = default;

	// Fontions membres
	void reprendreRessources();
	void gainRessources(int nbRessources);
	void perdreRessources(int nbRessources);
	void update();
	bool hasPlante();

	// Mutateurs
	void setType(TypeTerrain type);
	void setHasPlante(bool hasPlante);

	// Accesseurs
	TypeTerrain getType();
	int getRessources();

private: 
    int m_resource;
    TypeTerrain m_type;
	Grid *m_grilleProprietaire;
	int m_x;
	int m_y;
	bool m_hasPlante;
};

#endif //_TERRAIN_H