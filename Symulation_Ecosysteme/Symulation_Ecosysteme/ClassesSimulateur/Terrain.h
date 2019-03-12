/**
 * Project Untitled
 */


#ifndef _TERRAIN_H
#define _TERRAIN_H

class Terrain {
public: 
    
	enum class TypeTerrain { Eau = 0, Terre = 1, Gazon = 2, Frontiere = 3 };

void reprendreRessources();
void perdreRessources(int nbRessources);

private: 
    int Resource;
    TypeTerrain type;
};

#endif //_TERRAIN_H