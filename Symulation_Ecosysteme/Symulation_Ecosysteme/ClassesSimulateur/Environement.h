/**
 * Project Untitled
 */

#ifndef _ENVIRONEMENT_H
#define _ENVIRONEMENT_H

// Librairies standard
#include <list>

// Librairie Qt
#include <qgraphicsitem.h>

// Header files du simulateur
#include "Plante.h"
#include "Herbivore.h"
#include "Carnivore.h"
#include "Charogne.h"
#include "Meute.h"
#include "Grid.h"

// Déclaration enticipée

class Environnement {
public: 

	// Constructeur
	Environnement()=default;
	// Destructeur
	~Environnement();
    
// Fonctions membres pour ajouter des éléments au listes
	void addPlante(Plante *plante);
	void addHerbivore(Herbivore *herbivore);
	void addHerbivorePack(Meute *meuteHerbivores);
	void addCarnivore(Carnivore *carnivore);
	void addCarnivorePack(Meute *meuteCarnivores);
	void addCharognards(Carnivore *charognard);
	void addCharogardsPack(Meute *meuteCharognards);
	void addCharogne(Charogne* charogne);
	void addVivant(Vivant* vivant);
    
// Accesseur des listes d'éléments
	std::list<Plante*>& getPlantes();
	std::list<Meute*>& getMeutesHerbivores();
	std::list<Herbivore*>& getHerbivores();
	std::list<Meute*>& getMeutesCarnivores();
	std::list<Carnivore*>& getCarnivores();
	std::list<Meute*>& getMeutesCharognards();
	std::list<Carnivore*>& getCharognards();
	std::list<Charogne*>& getCharognes();

// Accesseurs d'éléments de la grille
	Terrain* getTerrain(int x, int y);

/*Fonction mis dans slots par Fred afin de pouvoir le connecter à un signal*/
public slots:
// Fonction commendant 
	std::list<Vivant*>& simulation();

private: 
    std::list<Plante*> m_plantes;
    std::list<Meute*> m_meutesHerbivores;
    std::list<Herbivore*> m_herbivores;
    std::list<Meute*> m_meutesCarnivores;
    std::list<Carnivore*> m_carnivores;
    std::list<Meute*> m_meutesCharognards;
    std::list<Carnivore*> m_charognards;
    std::list<Charogne*> m_charognes;
	std::list<Vivant*> m_vivnats;
    Grid m_grille;
};

#endif //_ENVIRONEMENT_H