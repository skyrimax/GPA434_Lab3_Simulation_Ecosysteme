/**
 * Project Untitled
 */

#include "stdafx.h"

#include "Environement.h"

/**
 * Environement implementation
 */


Environnement::~Environnement()
{
	for (auto p : m_plantes) {
		delete p;
		p = nullptr;
	}

	for (auto mh : m_meutesHerbivores) {
		delete mh;
		mh = nullptr;
	}

	for (auto h : m_herbivores) {
		delete h;
		h = nullptr;
	}

	for (auto mc : m_meutesCarnivores) {
		delete mc;
		mc = nullptr;
	}

	for (auto c : m_carnivores) {
		delete c;
		c = nullptr;
	}

	for (auto mc : m_meutesCharognards) {
		delete mc;
		mc = nullptr;
	}

	for (auto c : m_charognards) {
		delete c;
		c = nullptr;
	}
}

/**
 * @param Herbivore *herbivore
 * @return void
 */
void Environnement::addHerbivore(Herbivore *herbivore) {
	m_herbivores.push_back(herbivore);
}

/**
 * @param Meute *meuteHerbivores
 * @return void
 */
void Environnement::addHerbivorePack(Meute *meuteHerbivores) {
	m_meutesHerbivores.push_back(meuteHerbivores);
}

/**
 * @param Carnivore *carnivore
 * @return void
 */
void Environnement::addCarnivore(Carnivore *carnivore) {
	m_carnivores.push_back(carnivore);
}

/**
 * @param Meute *meuteCarnivores
 * @return void
 */
void Environnement::addCarnivorePack(Meute *meuteCarnivores) {
	m_meutesCarnivores.push_back(meuteCarnivores);
}

/**
 * @param Carnivore *charognard
 * @return void
 */
void Environnement::addCharognards(Carnivore *charognard) {
	m_charognards.push_back(charognard);
}

/**
 * @param Meute *meuteCharognards
 * @return void
 */
void Environnement::addCharogardsPack(Meute *meuteCharognards) {
	m_meutesCharognards.push_back(meuteCharognards);
}

 void Environnement::addCharogne(Charogne * charogne)
 {
 }

/**
 * @param Plante *plante
 * @return void
 */
void Environnement::addPlante(Plante *plante) {
	m_plantes.push_back(plante);
}

/**
 * @return list<Plante*>
 */
std::list<Plante*>& Environnement::getPlantes() const {
    return m_plantes;
}

/**
 * @return list<Meute*>
 */
std::list<Meute*>& Environnement::getMeutesHerbivores() const{
    return m_meutesHerbivores;
}

/**
 * @return list<Herbivore*>
 */
std::list<Herbivore*>& Environnement::getHerbivores() const{
    return m_herbivores;
}

/**
 * @return list<Meute*>
 */
std::list<Meute*>& Environnement::getMeutesCarnivores() const{
    return m_meutesCarnivores;
}

/**
 * @return list<Carnivore*>
 */
std::list<Carnivore*>& Environnement::getCarnivores() const{
    return m_carnivores;
}

/**
 * @return list<Meute*>
 */
std::list<Meute*>& Environnement::getMeutesCharognards() const{
    return m_meutesCharognards;
}

/**
 * @return list<Carnivore*>
 */
std::list<Carnivore*>& Environnement::getCharognards() const{
    return m_charognards;
}

/**
* @return list<Charogne*>
*/
std::list<Charogne*>& Environnement::getCharognes() const {
	return m_charognes;
}

/**
 * @return void
 */
QGraphicsItemGroup Environnement::simulation() {
    
	// Cycle de simulation des plantes
	for (auto const & plante : m_plantes)
	{
		plante->simulation();
	}

	// Cycle de simulation des meutes d'herbivores
	for (auto const & meuteHerbivores : m_meutesHerbivores)
	{
		meuteHerbivores->simulation();
	}

	// Cycle de simulation des herbivore pas en meute
	for (auto const & herbivore : m_herbivores)
	{
		herbivore->simulation();
	}

	// Cycle de simulation des meutes de carnivores
	for (auto const & meuteCarnivores : m_meutesCarnivores)
	{
		meuteCarnivores->simulation();
	}
	
	// Cycle de simulation des carnivores pas en meute
	for (auto const & carnivore : m_carnivores)
	{
		carnivore->simulation();
	}

	// Cycle de simulation des meutes de charognards
	for (auto const & meuteCharognards : m_meutesCharognards)
	{
		meuteCharognards->simulation();
	}

	// Cycle de simulation des charognards pas en meute
	for (auto const & charognard : m_charognards)
	{
		charognard->simulation();
	}
	
	return this->retourAnimaux();
}

/**
 * @return QGraphicsItemGroup
 */
QGraphicsItemGroup Environnement::retourAnimaux() {
    return QGraphicsItemGroup();
}