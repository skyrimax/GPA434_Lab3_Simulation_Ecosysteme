/**
 * Project Untitled
 */
#include "stdafx.h"

#include "Plante.h"
#include "Herbivore.h"
#include "Terrain.h"
#include "Environement.h"
#include <QPainter>

/**
 * Plante implementation
 */

 //Ajouté par Fred, Plantes RGB : 11-102-35
//const QColor Plante::sPlantesBackgoundColor(11, 102, 35);


/*Constructeur de la classe Plante, il permet de créer une plante 
dans l'écosystème selon son espèce, son niveau de hp (sa vie), son
énergie qu'elle peut fournir au herbivore, son age, ses coordonées et
son temps de reproduction.
Lors de l'appel du constructeur on appel le constructeur de sa classe parent (Vivant)
et on initialise les attributs pour le temps de reproduction, son nombre de fruit initiale
et sa condition booléene qu'elle n'a pas été mangé encore.
Ce constructeur fait la création également d'un rectangle 10 par 10, qui serait visible
dans le QGraphicView aux coordonnées passées dans le constructeur. On définiti la couleur
des plantes à un RGB de 11-102-35 (c'est un ton de vert.)*/
Plante::Plante(Environnement * environnement, std::string espece, int hp, int energy, int ageAdulte, int ageMax, int x, int y,
	int timeToReproduction)
	:Vivant(environnement, espece, hp, energy, ageAdulte, ageMax, x, y),
	m_timeToReproduction(timeToReproduction), m_timer(timeToReproduction), m_fruits(0), m_isBeingEaten(false)
{
	//Ajout par Fred
	//Création d'un rectangle de 10 par 10 positioné à (x,y)
	mshape.setRect(x, y, 10, 10);

	sPlantesBackgoundColor.setRgb(11, 102, 35);//vert
}

/*boundingRect est un fonction purement virtuelle de QGraphicItems,
elle définit le contour rectangulaire de l'iteme.*/
QRectF Plante::boundingRect() const
{
	//Ajouté par Fred,
	return QRectF(this->getCoordonne().getX(), this->getCoordonne().getY(),10,10);
}

/*paint est une fonction purement virtuelle de QGraphicItem,
on utilise painter (un objetb de QPainter) afin de dessiner l'item.
Dans notre cas, on met aucun contour (NoPen), on applique la couleur
comme celle définit dans le constructeur ci-haut et finalement on trace
la forme avec drawRect() selon le pen(contour) et brush(couleur de fond).*/
void Plante::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	//Ajouté par Fred,
	painter->setPen(Qt::NoPen);
	painter->setBrush(sPlantesBackgoundColor);
	painter->drawRect(mshape);
}

/*La fonction redonne de l'énergie aux plantes 
(Photosynthèse et nutriment du sol), jusqu'à ce
que cette énergie atteint le maximum.*/
void Plante::replenishEnergy()
{
	//ENERGY_REGEN_PLANTE est une constante définit dans le fichier constantes.h
	m_energy += ENERGY_REGEN_PLANTE;
	if (m_energy > m_energyMax)
		m_energy = m_energyMax;
}

void Plante::seekEnergy()
{
	// Plants passively receive energy
}

/*Fonction pour la guérison des plantes. Si la vie de la plante 
peut encore augmenter sans dépasser la vie maximale, alors on augmenter
sa vie d'un cycle de guérison et on réduit son énergie en conséquence.
Dans uin autre cas, c'est que sa vie est trops proche de sa vie max,
on met sa vie au maximum et son énergie est réduit.*/
void Plante::healing()
{
	/*RATE_GUERISON est une constante dans le fichier constante.h
	qui définit le nombre de hp regagné à cycle de guérison*/
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

/*Fonction qui envoie les dommages aux plantes, donc 
lorsque les chevreuils mangent les plantes. Si il reste des fruits,
cette quantité va réduire selon le nombre de dommage reçu.
Si le nombre de fruit est à 0, la plante est vide et donc c'est la vie
de la plante qui va diminuer.*/
void Plante::receiveDamages(int nbDamage)
{
	if (m_fruits == 0) {
		m_hp -= nbDamage;
		if (m_hp < 0)
			m_hp = 0;
	}
	else {
		m_fruits -= nbDamage / COUT_FRUIT;
	}
}

void Plante::reproduction()
{
	bool hasReproduced = false;
	int x = m_coordonne.getX();
	int y = m_coordonne.getY();
	int chance;

	Terrain *caseAdjacente;

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, INT_MAX);

	if (m_timer == 0 && m_fruits > 0 && !m_isBeingEaten) {
		do {
			m_fruits--;

			// Sélection d'une case adjacente au hasard
			switch (dist(mt)%4)
			{
			case 0:
				x++;
				break;
			case 1:
				y++;
				break;
			case 2:
				x--;
				break;
			case 3:
				y--;
				break;
			default: // n'arrive jamais;
				break;
			}

			caseAdjacente = m_environnement->getTerrain(x, y);

			if (!caseAdjacente->hasPlante()) {
				// Nombre random pour déterminer si la plante produit un enfant
				chance = dist(mt);

				// Détermination du succès de la reproduction
				if (caseAdjacente->getType() == Terrain::TypeTerrain::Gazon && chance % ODDS_GAZON == 0) {
					if (caseAdjacente->getRessources() > RESSOURCES_MIN_PLANTE) {
						caseAdjacente->perdreRessources(RESSOURCES_MIN_PLANTE);
						caseAdjacente->setHasPlante(true);

						m_environnement->addPlante(new Plante(m_environnement, m_espece, m_hpMax, m_energyMax,
							m_ageAdulte, m_ageMax, x, y, m_timeToReproduction));

						hasReproduced = true;
					}
				}
				else if (caseAdjacente->getType() == Terrain::TypeTerrain::Terre && chance % ODDS_TERRE == 0) {
					caseAdjacente->setType(Terrain::TypeTerrain::Gazon);
					caseAdjacente->reprendreRessources();
					
					caseAdjacente->perdreRessources(RESSOURCES_MIN_PLANTE);
					caseAdjacente->setHasPlante(true);

					m_environnement->addPlante(new Plante(m_environnement, m_espece, m_hpMax, m_energyMax,
						m_ageAdulte, m_ageMax, x, y, m_timeToReproduction));

					hasReproduced = true;
				}
			}


		} while (m_fruits>0 && !hasReproduced);
	}

	m_timer = m_timeToReproduction;
}

/*Fonction de simulation des plantes :
si la plante est encore en vie, celle-ci regagne de l'énergie.
Ensuite si elle ne se fait manger et qu'elle est endomagée, elle va se guérrir
Sinon elle va tenter de se reproduire.*/
void Plante::simulation()
{
	m_timer--;

	if (!this->isDead()) {
		this->replenishEnergy();

		if (!this->m_isBeingEaten && this->isDamaged()) {
			this->healing();
		}
		else {
			this->reproduction();
		}
	}
	else
	{
		this->dying();
	}
}

/*Lorsque la plante meure, la case où elle se trouve va gagner des ressources
selon ses HP et énergie restants*/
void Plante::dying()
{
	m_environnement->getTerrain(m_coordonne.getX(), m_coordonne.getY())->
		gainRessources(m_hp*HP_TO_RESSOURCE_RATE + m_energy * COUT_GUERISON*HP_TO_RESSOURCE_RATE);
}

/*Fonction qui vérifie si la plante est en vie, 3 cas peuvent définir si elle est morte :
	>Sa vie est inférieur ou égale à 0
	>Si elle se fait manger alors qu'elle n'est pas mature encore (Plante pas assez dévellopé pour se guérir)
	>Si l'âge de la plante est rendu supérieur à son âge max, elle a attent son cycle de vie*/
bool Plante::isDead()
{
	return (m_hp <= 0 || (m_age < m_ageAdulte && m_isBeingEaten) || m_age >= m_ageMax);
}

/*Fonction booléenne qui renvoie TRUE si la vie de la plante
est inférieur à sa vie totale, donc qu'elle est endommagée*/
bool Plante::isDamaged()
{
	return m_hp<m_hpMax;
}

/*Si la plante a assez d'énergie pour faire pousser fruit,
il en poussera un.*/
void Plante::pousserFruits()
{
	/*COUT_FRUIT est une constante dans le fichier constante.h 
	qui définit ce que ça coute à une plante en énergie pour faire pousser un fruit*/
	if (m_energy >= COUT_FRUIT) {
		m_energy -= COUT_FRUIT;
			m_fruits++;
	}
}
