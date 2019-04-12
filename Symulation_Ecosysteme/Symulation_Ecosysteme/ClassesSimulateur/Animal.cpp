/**
 * Project Untitled
 */
#include "stdafx.h"

#include "Animal.h"
#include "Environement.h"

/**
 * Animal implementation
 */


Animal::Animal(Environnement * environnement, std::string espece, int hp, int energy, int ageAdulte, int ageMax, double x, double y,
	double vitesse, double sprint, Sex sex,
	int nbProgenituresMin, int nbProgenituresMax,
	Animal* mere, Meute* meute,
	int timerMort, int tempsGestation, int tempsReproduction,
	std::list<std::string> cible)
	: Vivant(environnement, espece, hp, energy, ageAdulte, ageMax, x, y),
	m_vitesse(vitesse), m_sprint(sprint), m_sex(sex), m_isSprinting(false),
	m_aEnfant(false), m_nbProgenituresMin(nbProgenituresMin),
	m_nbProgenituresMax(nbProgenituresMax), m_closestPredateur(nullptr),
	m_mate(nullptr), m_mere(mere), m_meute(meute),
	m_timerMort(timerMort), m_tempsGestation(tempsGestation),
	m_tempsReproduction(tempsReproduction), m_cible(cible)
{
}

Meute * Animal::getMeute()
{
	return m_meute;
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
	for (auto const enfant : m_enfant) {
		enfant->resetTarget();
	}

	m_dead = true;
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

bool Animal::isHungry()
{
	return false;
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
void Animal::sprint(Animal* cible) {
	m_isSprinting = true;

	this->trackTarget();

	this->deplacer(m_sprint, cible);
}

/**
 * @return void
 */
void Animal::walk(Animal* cible) {

	m_isSprinting = false;

	this->trackTarget();

	this->deplacer(m_vitesse, cible);
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

void Animal::trackMother()
{
}

void Animal::devenirAdulte()
{
}

void Animal::deplacer(double vitesse)
{
	Coordonne pointDepart(m_coordonne);
	Coordonne nextCoordonne(m_coordonne);
	Coordonne pointCroisement(-1, -1);

	/*
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
	*/

	double distance = vitesse;

	do {
		nextCoordonne = pointDepart;

		nextCoordonne.moveX(m_orientation.getUnitX()*distance);
		nextCoordonne.moveY(m_orientation.getUnitY()*distance);

		pointCroisement = croisementEntre2Lignes(pointDepart, nextCoordonne);

		if (pointCroisement.getX() != -1 && pointCroisement.getY() != -1) {
			distance -= distanceEntre2Points(pointDepart, pointCroisement);

			if (pointCroisement.getX() == 0 || pointCroisement.getX() == LARGEUR_GRILLE) {
				if (m_isSprinting) {
					m_orientation.setVX(0);
				}
				else {
					m_orientation.setVX(-m_orientation.getVX());
				}
			}
			else
			{
				if (m_isSprinting) {
					m_orientation.setVY(0);
				}
				else {
					m_orientation.setVY(-m_orientation.getVY());
				}
			}

			pointDepart = pointCroisement;
		}
	} while (pointCroisement.getX() != -1 && pointCroisement.getY() != -1);

	m_coordonne = nextCoordonne;

	setPos(m_coordonne.getX(), m_coordonne.getY());
}

void Animal::deplacer(double vitesse, Animal* cible) {
	
	if (distanceEntre2Points(m_coordonne, cible->m_coordonne) <= vitesse) {
		m_coordonne.setX(cible->m_coordonne.getX());
		m_coordonne.setY(cible->m_coordonne.getY());
	}
	else
	{
		deplacer(vitesse);
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

void Animal::trackAlpha()
{
	m_isSprinting = false;

	if (this != m_meute->getAlpha()){
		
		m_orientation.setVX(m_meute->getAlpha()->getCoordonne().getX() + (rand() % 20 - 10) - m_coordonne.getX());
		m_orientation.setVY(m_meute->getAlpha()->getCoordonne().getY() + (rand() % 20 - 10) - m_coordonne.getY());

		deplacer(m_vitesse);
	}
}

void Animal::sprintAlpha() {
	m_isSprinting = true;
	if (this != m_meute->getAlpha()) {
		this->trackAlpha();

		this->deplacer(m_sprint);

	}
}

Animal::Sex Animal::getSex()
{
	return m_sex;
}

Animal * Animal::getclosestPredateur()
{
	return m_closestPredateur;
}

Orientation Animal::getOrientation()
{
	return m_orientation;
}

/*Plante * Animal::getPlante()
{
	return m_plante;
}*/

bool Animal::getaEnfant()
{
	return m_aEnfant;
}

int Animal::gettimerReproduction()
{
	return m_timerReproduction;
}

Animal * Animal::getMate()
{
	return m_mate;
}

bool Animal::getenceinte()
{
	return m_enceinte;
}

int Animal::gettimerGestation()
{
	return m_timerGestation;
}

int Animal::gettimerMort()
{
	return m_timerMort;
}

void Animal::settimerReproduction(int timer)
{
	m_timerReproduction = timer;
}

void Animal::settimerGestation(int timer)
{
	m_timerGestation = timer;
}

void Animal::settimerMort(int timer)
{
	m_timerMort = timer;
}

/*Orientation Animal::setOrientation()
{
	return m_orientation;
}*/
