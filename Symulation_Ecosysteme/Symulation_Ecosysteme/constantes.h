#pragma once

// Constantes relatant à la taille de la grille
#define HAUTEUR_GRILLE 500
#define LARGEUR_GRILLE 500

// Constantes relatant au ressource d'une parcelle de terrain
#define RESSOURCES_EAU 100
#define RESSOURCES_TERRE 0
#define RESSOURCES_GAZON 1000
#define RATE_GAZON 100
#define RESSOURCES_FRONTIERE 0

// Constantes relantant à la génération du terrain
#define THRESHOLD_EAU 0.1
#define THRESHOLD_TERRE 0.3
#define THRESHOLD_GAZON 0.5
#define THRESHOLD_PLANTE 0.85

// Constraintes relatant à la fonction de bruit pour la génération du terrain
#define OCTAVES 6
#define PERSISTENCE 0.2

// Constantes relatant aux plantes
#define ENERGY_REGEN_PLANTE 10
#define ENERGY_MAX_PLANTE 2000
#define ODDS_GAZON 2
#define ODDS_TERRE 1024
#define RESSOURCES_MIN_PLANTE 100
#define COUT_GUERISON 10
#define RATE_GUERISON 1
#define HP_TO_RESSOURCE_RATE 10