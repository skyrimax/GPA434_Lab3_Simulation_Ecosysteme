/**
 * Project Untitled
 */
#include "stdafx.h"

#include "Orientation.h"

/**
 * Orientation implementation
 */


/**
 * @return double
 */
double Orientation::getVX() {
    return m_vX;
}

/**
 * @return double
 */
double Orientation::getVY() {
    return m_vY;
}

double Orientation::getUnitX() {
	return m_unitX;
}

double Orientation::getUnitY() {
	return m_unitY;
}

/**
 * @return void
 */
void Orientation::setVX(double vX) {
	m_vX = vX;

	this->unitV();
}

/**
 * @return void
 */
void Orientation::setVY(double vY) {
	m_vY = vY;

	this->unitV();
}

/**
 * @return void
 */
void Orientation::moveVX(double deltaVX) {
	m_vX += deltaVX;

	this->unitV();
}

/**
 * @return void
 */
void Orientation::moveVY(double deltaVY) {
	m_vY += deltaVY;
}

void Orientation::unitV() {
	m_unitX = m_vX / DistanceEntre2Points(Coordonne(m_vX, m_unitY), Coordonne());

	m_unitY = m_vY / DistanceEntre2Points(Coordonne(m_vX, m_unitY), Coordonne());

	m_direction = VitesseVersAngle(m_unitX, m_unitY);
}
