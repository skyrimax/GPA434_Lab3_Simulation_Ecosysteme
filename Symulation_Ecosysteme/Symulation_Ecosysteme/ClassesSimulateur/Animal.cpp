/**
 * Project Untitled
 */
#include "stdafx.h"

#include "Animal.h"
#include "Environement.h"

/**
 * Animal implementation
 */


Animal::Animal(Environnement * environnement, std::string espece, int hp, int energy, int ageAdulte, int ageMax, int x, int y,
	double vitesse, double sprint, Sex sex,
	int nbProgenituresMin, int nbProgenituresMax,
	int timerMort, int tempsGestation, int tempsReproduction,
	std::list<std::string> cible)
	: Vivant(environnement, espece, hp, energy, ageAdulte, ageMax, x, y),
	m_vitesse(vitesse), m_sprint(sprint), m_sex(sex), m_isSprinting(false),
	m_aEnfant(false), m_nbProgenituresMin(nbProgenituresMin),
	m_nbProgenituresMax(nbProgenituresMax), m_closestPredateur(nullptr),
	m_mate(nullptr), m_timerMort(timerMort), m_tempsGestation(tempsGestation),
	m_tempsReproduction(tempsReproduction), m_cible(cible)
{
}

void Animal::healing()
{
	if (m_hpMax - m_hp >= RATE_GUERISON)
	{
		if (m_energy > COUT_GUERISON*RATE_GUERISON) {
			m_energy -= COUT_GUERISON * RATE_GUERISON;
			m_hp += RATE_GUERISON;
		}
	}
	else {
		if (m_energy > (m_hpMax - m_hp)*COUT_GUERISON) {
			m_energy -= (m_hpMax - m_hp)*COUT_GUERISON;
			m_hp = m_hpMax;
		}
	}
}

void Animal::receiveDamages(int nbDamage)
{
	m_hp -= nbDamage;
	if (m_hp < 0)
		m_hp = 0;
}

void Animal::reproduction()
{
	if (m_sex == Sex::Female) {
		m_aEnfant = true;

		m_enceinte = true;
		m_timerGestation = m_tempsGestation;
	}
	else
	{
		m_aEnfant = true;

		m_timerReproduction = m_tempsReproduction;
	}
}

void Animal::dying()
{
	// Il ne se passe rien de particulier à la mort d'un animal.
}

bool Animal::isDead()
{
	return m_hp==0;
}

bool Animal::isDamaged()
{
	return m_hp<m_hpMax;
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

	this->trackTarget();

	this->deplacer(m_sprint);
}

/**
 * @return void
 */
void Animal::walk() {

	m_isSprinting = false;

	this->trackTarget();

	this->deplacer(m_vitesse);
}

/**
 * @return void
 */
void Animal::flee() {

	m_isSprinting = true;

	closestPredateur();

	m_orientation.setVX(m_coordonne.getX() - m_closestPredateur->m_coordonne.getX());
	m_orientation.setVY(m_coordonne.getY() - m_closestPredateur->m_coordonne.getY());

	this->deplacer(m_sprint);
}

/**
 * @return void
 */
void Animal::wander() {

	double angle;

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(-DEVIATION_MAX, DEVIATION_MAX);

	m_isSprinting = false;

	angle = m_orientation.getDirection();
	angle += dist(mt);

	m_coordonne.setX(sin(angle*M_PI / 360));
	m_coordonne.setY(sin(angle*M_PI / 360));

	this->deplacer(m_vitesse);
}

void Animal::deplacer(double vitesse) {

	Coordonne nextCoordonne(m_coordonne);
	Coordonne pointCroisement(-1, -1);

	double distance;

	nextCoordonne.moveX(m_vitesse*m_orientation.getUnitX());
	nextCoordonne.moveY(m_vitesse*m_orientation.getUnitY());

	// Computer si points de croisement
	//pointCroisement=

	if (pointCroisement.getX() == 0 || pointCroisement.getX() == LARGEUR_GRILLE) {
		distance = distanceEntre2Points(pointCroisement, nextCoordonne);

		m_orientation.setVX(-m_orientation.getVX());

		pointCroisement.moveX(m_orientation.getUnitX()*distance);

		m_coordonne.setX(pointCroisement.getX());
		m_coordonne.setY(nextCoordonne.getY());
	}

	else if (pointCroisement.getY() == 0 || pointCroisement.getY() == LARGEUR_GRILLE) {
		distance = distanceEntre2Points(pointCroisement, nextCoordonne);

		m_orientation.setVY(-m_orientation.getVY());

		pointCroisement.moveY(m_orientation.getUnitY()*distance);

		m_coordonne.setY(pointCroisement.getY());
		m_coordonne.setX(nextCoordonne.getX());
	}
	else {
		m_coordonne.setX(nextCoordonne.getX());
		m_coordonne.setY(nextCoordonne.getY());
	}
}

void Animal::closestPredateur() {
	double distance = DBL_MAX;
	Animal *closest = nullptr;

	for (auto const predator : m_predateurs) {
		if (distanceEntre2Points(m_coordonne, predator->m_coordonne) < distance) {
			distance = distanceEntre2Points(m_coordonne, predator->m_coordonne);
			closest = predator;
		}
	}

	m_closestPredateur = closest;
}
