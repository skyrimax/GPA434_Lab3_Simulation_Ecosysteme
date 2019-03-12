/**
 * Project Untitled
 */


#ifndef _ENVIRONEMENT_H
#define _ENVIRONEMENT_H

class Environnement {
public: 
    
/**
 * @param Herbivore *herbivore
 */
void addHerbivore(void Herbivore *herbivore);
    
/**
 * @param Meute *meuteHerbivores
 */
void addHerbivorePack(void Meute *meuteHerbivores);
    
/**
 * @param Carnivore *carnivore
 */
void addCarnivore(void Carnivore *carnivore);
    
/**
 * @param Meute *meuteCarnivores
 */
void addCarnivorePack(void Meute *meuteCarnivores);
    
/**
 * @param Carnivore *charognard
 */
void addCharognards(void Carnivore *charognard);
    
/**
 * @param Meute *meuteCharognards
 */
void addCharogardsPack(void Meute *meuteCharognards);
    
/**
 * @param Plante *plante
 */
void addPlante(void Plante *plante);
    
list<Plante*> getPlantes();
    
list<Meute*> getMeutesHerbivores();
    
list<Herbivores*> getHerbivores();
    
list<Meutes*> getMeutesCarnivores();
    
list<Carnivores*> getCarnivores();
    
list<Meute*> getMeutesCharognards();
    
list<Carnivore*> getCharognards();
    
void simulation();
    
QGraphicsItemGroup retourAnimaux();
private: 
    list<Plante*> plantes;
    list<Meute*> meutesHerbivores;
    list<Herbivore*> herbivores;
    list<Meute*> meutesCarnivores;
    list<Carnivore*> carnivores;
    list<Meute*> meutesCharognards;
    list<Charognards*> charognards;
    list<Charogne*> charognes;
    Grid grille;
};

#endif //_ENVIRONEMENT_H