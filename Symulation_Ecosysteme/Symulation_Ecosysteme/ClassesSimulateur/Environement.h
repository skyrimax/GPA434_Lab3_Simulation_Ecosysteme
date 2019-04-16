/**
 * Project Untitled
 */

#ifndef _ENVIRONEMENT_H
#define _ENVIRONEMENT_H

// Librairies standard
#include <list>

// Librairie Qt
#include <qgraphicsitem.h>
#include <qgraphicsscene.h>

// Header files du simulateur
#include "Plante.h"
#include "Herbivore.h"
#include "Carnivore.h"
#include "Charogne.h"
#include "Meute.h"
#include "Grid.h"


class Environnement: public QGraphicsScene {
public: 

	// Constructeur
	Environnement();
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
	std::list<Vivant*>& getVivants(); //Ajouté par Fred, avoir accès à la liste depuis la MainWindow

	// Accesseurs d'éléments de la grille
	Terrain* getTerrain(int x, int y);

	// Accesseur de la grille
	Grid* getGrille();

	// Fonction commendant la simulation du monde
	void simulation();

private: 
    std::list<Plante*> m_plantes;
    std::list<Meute*> m_meutesHerbivores;
    std::list<Herbivore*> m_herbivores;
    std::list<Meute*> m_meutesCarnivores;
    std::list<Carnivore*> m_carnivores;
    std::list<Meute*> m_meutesCharognards;
    std::list<Carnivore*> m_charognards;
    std::list<Charogne*> m_charognes;
	std::list<Vivant*> m_vivants;
    Grid* m_grille;
};

#endif //_ENVIRONEMENT_H