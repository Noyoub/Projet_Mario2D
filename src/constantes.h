/*!
*  \file       constantes.h
*  \brief      Implémentation de toutes les constantes nécessaires au projet
*  \version    1.7
*  \author     Lucas BOUILLON, Arthur SCHERRER, Lucas BEAUFRETON
*  \date 
 */


#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL2/SDL.h>
 

/* On inclut les librairies supplémentaires */
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

// Taille de la fenêtre : 800x480 pixels 
#define LARGEUR_FENETRE 800
#define HAUTEUR_FENETRE 480

/* Taille maxi de la map : 150 x 150 tiles */
#define MAX_MAP_X 150
#define MAX_MAP_Y 150

/* Taille d'une tile (32 x 32 pixels) */
#define TAILLE_TILE 32

/* Animation mouvement personnages */
#define TEMPS_ENTRE_2_FRAMES_JOUEUR 4

/* Taille du sprite de notre personnage */
#define LARGEUR_JOUEUR 32
#define HAUTEUR_JOUEUR 40

//Nombre max de monstres à l'écran
#define MONSTRES_MAX 50

//Dimensions du monstre
#define LARGEUR_MONSTRE 20
#define HAUTEUR_MONSTRE 22

//Vitesse de déplacement en pixels du sprite
#define VITESSE_JOUEUR 4
 
//Valeurs attribuées aux états du personnage
#define IMMOBILE 0
#define MARCHE 1
#define SAUT 2
#define MORT 3
 
//Valeurs des directions du personnage
#define RIGHT 1
#define LEFT 2

//Constante pour les limites de la caméra avant scrolling
#define LIMITE_X 400
#define LIMITE_Y 220
#define LIMITE_W 100
#define LIMITE_H 80
 
//Constantes définissant la gravité et la vitesse max de chute
#define VITESSE_GRAVITE 0.6
#define VITESSE_CHUTE 15
#define HAUTEUR_SAUT 11

// Constante définissant le seuil entre les tiles traversables
#define SEUIL_TILES_TRAVERSABLES_HAUT 48
 
//Plateformes solides en haut et traversables sur les autres côtés (de SEUIL_TILES_TRAVERSABLES à SEUIL_TILES_TRAVERSABLES_HAUT)
#define SEUIL_TILES_TRAVERSABLES 30

//Tiles Power-ups (pièce)
#define TILE_POWER_UP_DEBUT 9
#define TILE_POWER_UP_FIN 9
 
//Autres Tiles spéciales
#define TILE_CHECKPOINT 11
#define TILE_PIKES 10
#define TILE_LAVE 7
#define TILE_MONSTRE 2


//Nombre maximum de levels
#define NIVEAU_MAX 3

#endif