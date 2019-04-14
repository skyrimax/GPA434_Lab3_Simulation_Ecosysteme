/**
 * Project Untitled
 */
#include "stdafx.h"

#include "Vivant.h"
#include "Environement.h"

Vivant::Vivant(Environnement * environnement, std::string espece, int hp,
	int energy, int ageAdulte, int ageMax,
	double x, double y)
	:m_environnement(environnement), m_espece(espece), m_hp(hp), m_hpMax(hp),
	m_energy(energy), m_energyMax(energy), m_age(0), m_ageAdulte(ageAdulte), m_ageMax(ageMax),
	m_dead(false), m_toDelete(false), m_coordonne(x, y)
{
	setPos(x, y);
}

int& Vivant::getHp()
{
	return m_hp;
}

int& Vivant::getHpMax()
{
	return m_hpMax;
}

int& Vivant::getEnergy()
{
	return m_age;
}

int& Vivant::getEnergyMax()
{
	return m_ageMax;
}

int& Vivant::getAge()
{
	return m_age;
}

int& Vivant::getAgeAdulte()
{
	return m_ageAdulte;
}

int& Vivant::getAgeMax()
{
	return m_ageMax;
}

bool& Vivant::toDelete()
{
	return m_toDelete;
}

bool & Vivant::getDead()
{
	return m_dead;
}

std::string& Vivant::getEspece()
{
	return m_espece;
}

Coordonne& Vivant::getCoordonne()
{
	return m_coordonne;
}

Environnement * Vivant::getEnvironnement()
{
	return m_environnement;
}

void Vivant::setHp(int hp)
{
	m_hp = hp;
}

void Vivant::setHpMax(int hpMax)
{
	m_hpMax = hpMax;
}

void Vivant::setEnergy(int energy)
{
	m_energy = energy;
}

void Vivant::setEnergyMax(int energyMax)
{
	m_energyMax = energyMax;
}

void Vivant::setAge(int age)
{
	m_age = age;
}

void Vivant::setAgeAdulte(int ageAdulte)
{
	m_ageAdulte = ageAdulte;
}

void Vivant::setAgeMax(int ageMax)
{
	m_ageMax = ageMax;
}

void Vivant::setEspece(std::string & espece)
{
	m_espece = espece;
}

void Vivant::setCoordonne(Coordonne & coordonne)
{
	m_coordonne = coordonne;
}
