/**
 * Project Untitled
 */


#ifndef _PLANTE_H
#define _PLANTE_H

 // Librairies standard
#include <list>
//Librairies de Qt
#include <QGraphicsItem>
// Header files du simulateur
#include "Vivant.h"
#include"constantes.h"

// Déclarations anticipées
class Herbivore;


//Ajout du parent QGraphicItem par Fred
class Plante: public Vivant {
public:
	// Constructeur
	Plante()=default;
	Plante(Environnement* environnement, std::string espece, int hp,
		int energy, int ageAdulte, int ageMax, int x, int y,
		int timeToReproduction);
	// Destructeur
	~Plante()=default;

	// Fonctions membres virtuelles héritées de QGraphicsItem
	virtual QRectF boundingRect() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

	// Fonctions membres virtuelles héritées de Vivant
	virtual void replenishEnergy() override;
	virtual void seekEnergy() override;
	virtual void healing() override;
	virtual void receiveDamages(int nbDamage);
	virtual void reproduction() override;
	virtual void simulation() override;
	virtual void dying() override;
	virtual bool isDead() override;
	virtual bool isDamaged();

	// Fonctions membres propre au plantes
	void pousserFruits();

protected:
	//Ajouté par Fred, la forme de la plante
	QRectF mshape;
	//Ajouté par Fred, couleur des plantes
	static const QColor sPlantesBackgoundColor;

private: 
    int m_fruits;
	int m_timer;
	int m_timeToReproduction;
    std::list<Herbivore*> m_isEatenBy;
    bool m_isBeingEaten;
};

#endif //_PLANTE_H