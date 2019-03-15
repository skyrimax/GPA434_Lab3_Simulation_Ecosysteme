/**
 * Project Untitled
 */


#include "Vivant.h"

int Vivant::getHp() const
{
	return m_hp;
}

int Vivant::gatHpMax() const
{
	return m_hpMax;
}

int Vivant::getEnergy() const
{
	return m_age;
}

int Vivant::getEnergyMax() const
{
	return m_ageMax;
}

int Vivant::getAge() const
{
	return m_age;
}

int Vivant::getAgeMax() const
{
	return m_ageMax;
}

std::string Vivant::getEspece() const
{
	return m_espece;
}

Coordonne Vivant::getCoordonne() const
{
	return m_coordonne;
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
