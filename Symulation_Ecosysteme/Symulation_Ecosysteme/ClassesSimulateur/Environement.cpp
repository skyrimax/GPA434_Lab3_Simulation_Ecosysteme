/**
 * Project Untitled
 */

#include "stdafx.h"

#include "Environement.h"

/**
 * Environement implementation
 */


Environnement::Environnement()
{
	m_grille = new Grid(this);
}

Environnement::~Environnement()
{
	for (auto & p : m_plantes) {
		delete p;

		m_vivants.remove(p);

		p = nullptr;
	}

	for (auto & mh : m_meutesHerbivores) {
		delete mh;

		mh = nullptr;
	}

	for (auto & h : m_herbivores) {
		delete h;

		m_vivants.remove(h);

		h = nullptr;
	}

	for (auto & mc : m_meutesCarnivores) {
		delete mc;

		mc = nullptr;
	}

	for (auto & c : m_carnivores) {
		delete c;

		m_vivants.remove(c);

		c = nullptr;
	}

	for (auto & mc : m_meutesCharognards) {
		delete mc;

		mc = nullptr;
	}

	for (auto & c : m_charognards) {
		delete c;

		m_vivants.remove(c);

		c = nullptr;
	}

	for (auto & c : m_charognes) {
		delete c;

		m_vivants.remove(c);

		c=nullptr;
	}

	for (auto & v : m_vivants) {
		delete v;

		v = nullptr;
	}
}

/**
 * @param Herbivore *herbivore
 * @return void
 */
void Environnement::addHerbivore(Herbivore *herbivore) {
	m_herbivores.push_back(herbivore);

	m_vivants.push_back(herbivore);
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

	m_vivants.push_back(carnivore);
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

	m_vivants.push_back(charognard);
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
	 m_charognes.push_back(charogne);

	 m_vivants.push_back(charogne);
 }

 void Environnement::addVivant(Vivant * vivant)
 {
	 m_vivants.push_back(vivant);
 }

/**
 * @param Plante *plante
 * @return void
 */
void Environnement::addPlante(Plante *plante) {
	m_plantes.push_back(plante);

	m_vivants.push_back(plante);
}

/**
 * @return list<Plante*>
 */
std::list<Plante*>& Environnement::getPlantes() {
    return m_plantes;
}

/**
 * @return list<Meute*>
 */
std::list<Meute*>& Environnement::getMeutesHerbivores() {
    return m_meutesHerbivores;
}

/**
 * @return list<Herbivore*>
 */
std::list<Herbivore*>& Environnement::getHerbivores() {
	return m_herbivores;
}

/**
 * @return list<Meute*>
 */
std::list<Meute*>& Environnement::getMeutesCarnivores() {
    return m_meutesCarnivores;
}

/**
 * @return list<Carnivore*>
 */
std::list<Carnivore*>& Environnement::getCarnivores() {
    return m_carnivores;
}

/**
 * @return list<Meute*>
 */
std::list<Meute*>& Environnement::getMeutesCharognards() {
    return m_meutesCharognards;
}

/**
 * @return list<Carnivore*>
 */
std::list<Carnivore*>& Environnement::getCharognards() {
    return m_charognards;
}

/**
* @return list<Charogne*>
*/
std::list<Charogne*>& Environnement::getCharognes() {
	return m_charognes;
}

Terrain * Environnement::getTerrain(int x, int y)
{
	return m_grille->getTerrain(x, y);
}

Grid * Environnement::getGrille()
{
	return m_grille;
}

/**
 * @return void
 */
std::list<Vivant*>& Environnement::simulation() {
	std::list<Vivant*> toDie;
	std::list<Animal*> meuteToDie;
	std::list<Meute*> emptyMeute;

	// Cycle de simulation des plantes
	for (auto const & plante : m_plantes)
	{
		plante->simulation();

		if (plante->isDead()) {
			toDie.push_back(plante);
		}
	}

	// Cycle de simulation des meutes d'herbivores
	for (auto const & meuteHerbivores : m_meutesHerbivores)
	{
		meuteToDie=meuteHerbivores->simulation();

		for (auto const & membre : meuteToDie) {
			toDie.push_back(membre);
		}

		if (meuteHerbivores->getMembres().empty()) {
			emptyMeute.push_back(meuteHerbivores);
		}
	}
	
	// Cycle de simulation des herbivore pas en meute
	for (auto const & herbivore : m_herbivores)
	{
		herbivore->simulation();

		if (herbivore->isDead()) {
			toDie.push_back(herbivore);
		}
	}

	// Cycle de simulation des meutes de carnivores
	for (auto const & meuteCarnivores : m_meutesCarnivores)
	{
		meuteToDie=meuteCarnivores->simulation();

		for (auto const & membre : meuteToDie) {
			toDie.push_back(membre);
		}

		if (meuteCarnivores->getMembres().empty()) {	//Modifi� par Fred, meuteCarnivores->getMembres().empty est devnu meuteCarnivores->getMembres().empty()
			emptyMeute.push_back(meuteCarnivores);
		}
	}
	
	// Cycle de simulation des carnivores pas en meute
	for (auto const & carnivore : m_carnivores)
	{
		carnivore->simulation();

		if (carnivore->isDead()) {
			toDie.push_back(carnivore);
		}
	}

	// Cycle de simulation des meutes de charognards
	for (auto const & meuteCharognards : m_meutesCharognards)
	{
		meuteToDie=meuteCharognards->simulation();

		for (auto const & membre : meuteToDie) {
			toDie.push_back(membre);
		}

		if (meuteCharognards->getMembres().empty()) {
			emptyMeute.push_back(meuteCharognards);
		}
	}

	// Cycle de simulation des charognards pas en meute
	for (auto const & charognard : m_charognards)
	{
		charognard->simulation();

		if (charognard->isDead()) {
			toDie.push_back(charognard);
		}
	}
	
	for (auto const & mort : toDie) {
		m_vivants.remove(mort);

		if (typeid(*mort) == typeid(Herbivore) || typeid(*mort) == typeid(Carnivore)) {
			Animal* animalMort = static_cast<Animal*>(mort);

			if (animalMort->getMeute() != nullptr) {
				animalMort->getMeute()->getMembres().remove(animalMort);
			}
			else if (typeid(*mort) == typeid(Herbivore)) {
				Herbivore* herbivoreMort = static_cast<Herbivore*>(mort);

				m_herbivores.remove(herbivoreMort);
			}
			else if (typeid(*mort) == typeid(Carnivore)) {
				Carnivore* carnivoreMort = static_cast<Carnivore*>(mort);

				if (carnivoreMort->isCharognard()) {
					m_charognards.remove(carnivoreMort);
				}
				else {
					m_carnivores.remove(carnivoreMort);
				}
			}
		}
		else if (typeid(*mort) == typeid(Plante)) {
			Plante* planteMorte = static_cast<Plante*>(mort);

			m_plantes.remove(planteMorte);
		}
		else if (typeid(*mort) == typeid(Charogne)) {
			Charogne* charogneMorte = static_cast<Charogne*>(mort);

			m_charognes.remove(charogneMorte);
		}

		delete mort;
	}

	for (auto const & meute : emptyMeute) {
		if (std::find(m_meutesHerbivores.begin(), m_meutesHerbivores.end(), meute) != m_meutesHerbivores.end()) {
			m_meutesHerbivores.remove(meute);
		}
		else if (std::find(m_meutesCarnivores.begin(), m_meutesCarnivores.end(), meute) != m_meutesCarnivores.end()) {
			m_meutesCarnivores.remove(meute);
		}
		else if (std::find(m_meutesCharognards.begin(), m_meutesCharognards.end(), meute) != m_meutesCharognards.end()) { //Modifi� par Fred, (std::find(m_meutesCharognards.begin(), m_meutesCharognards.end(), meute) != m_meutesCharognards.end est devenu (std::find(m_meutesCharognards.begin(), m_meutesCharognards.end(), meute) != m_meutesCharognards.end()
			m_meutesCharognards.remove(meute);
		}
	}

	return m_vivants;
}