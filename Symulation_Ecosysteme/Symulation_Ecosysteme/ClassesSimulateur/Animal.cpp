/**
 * Project Untitled
 */
#include "stdafx.h"

#include "Animal.h"
#include "Environement.h"

/**
 * Animal implementation
 */


Animal::Animal(Environnement * environnement, std::string espece, int hp, int energy, int ageAdulte, int ageMax, int x, int y, double vitesse, double sprint, Sex sex, int timerMort, int timerGestation, int timerReproduction, std::string cible)
{
}

/**
 * @return void
 */
void Animal::devenirCharogne() {
	m_environnement->addCharogne(new Charogne(this));
}

/**
 * @return bool
 */
bool Animal::isSprinting() {
    return m_isSprinting;
}

/**
 * @return void
 */
void Animal::sprint() {
	m_isSprinting = true;
}

/**
 * @return void
 */
void Animal::walk() {
	m_isSprinting = false;
}

/**
 * @return void
 */
void Animal::flee() {
    return;
}

/**
 * @return void
 */
void Animal::wander() {
    return;
}

