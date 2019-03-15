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
class Plante;
class Herbivore;
class Carnivore;
class Meute;
class Charogne;
class Grid;

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
    
// Accesseur des listes d'éléments
	std::list<Plante*> getPlantes() const;
	std::list<Meute*> getMeutesHerbivores() const;
	std::list<Herbivore*> getHerbivores() const;
	std::list<Meute*> getMeutesCarnivores() const;
	std::list<Carnivore*> getCarnivores() const;
	std::list<Meute*> getMeutesCharognards() const;
	std::list<Carnivore*> getCharognards() const;
	std::list<Charogne*> getCharognes() const;

// Fonction commendant 
	QGraphicsItemGroup simulation();
    
	QGraphicsItemGroup retourAnimaux();
private: 
    std::list<Plante*> m_plantes;
    std::list<Meute*> m_meutesHerbivores;
    std::list<Herbivore*> m_herbivores;
    std::list<Meute*> m_meutesCarnivores;
    std::list<Carnivore*> m_carnivores;
    std::list<Meute*> m_meutesCharognards;
    std::list<Carnivore*> m_charognards;
    std::list<Charogne*> m_charognes;
    Grid m_grille;
};

#endif //_ENVIRONEMENT_H