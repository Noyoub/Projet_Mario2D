/*!
 *  \file       structs.h
 *  \brief      Implémentation des structures liées aux différentes fonctionnalités du projet
 *  \version    1.7
 *  \author     Lucas BOUILLON, Arthur SCHERRER, Lucas BEAUFRETON
 *  \date 
 */

#ifndef DEF_STRUCTS
#define DEF_STRUCTS
 
#include "constantes.h"
 
/* Structures qui seront utilisées pour gérer le jeu */
 
// Structure pour gérer les entrées clavier
typedef struct Input
{
 
    int gauche, droite, haut, bas, saut, entrer, volume, pause;
 
} Input;


// Structure pour gérer la map à afficher
typedef struct Map
{
 
    SDL_Texture *background;
    SDL_Texture *tileSet;
    
    //Numéro du tileset à utiliser
    int tilesetAffiche;
    
    /* Coordonnées de départ du héros, lorsqu'il commence le niveau */
    int beginx, beginy;
    
    /* Coordonnées de début, lorsqu'on doit dessiner la map */
    int startX, startY;
    
    /* Coordonnées max de fin de la map */
    int maxX, maxY;
    
    /* Tableau à double dimension représentant la map de tiles */
    int tile[MAX_MAP_Y][MAX_MAP_X];
    
    //Deuxième couche de tiles
    int tile2[MAX_MAP_Y][MAX_MAP_X];
    
} Map;


// Structure pour gérer nos sprites
typedef struct Personnage
{
 
    // Points de vie/santé 
    int vie;
    
    // Coordonnées du sprite
    int x, y;
    
    // Largeur, hauteur du sprite
    int h, w;
    
    // Checkpoint pour le héros 
    int checkpointActif;

    // + coordonnées de réapparition
    int respawnX, respawnY;
    
    // Variables utiles pour l'animation :
    // Numéro de la frame (= image) en cours + timer
    int frameNumber, frameTimer, frameMax;

    // état du sprite et direction
    // dans laquelle il se déplace (gauche / droite)
    int etat, direction;
    
    
    // Variables utiles pour la gestion des collisions :
    //Est-il sur le sol, chrono une fois mort
    int surSol, timerMort;

    //Vecteurs de déplacement temporaires avant détection
    //des collisions avec la map
    float dirX, dirY;
    
    //Sauvegarde des coordonnées de départ
    int saveX, saveY;
    
    //Variable pour le saut
    int jump;
 
 
} Personnage;

//Une enum pour la gestion des sons.
enum
{
    PAUSE_GAME,
    JUMP,
    COIN,
    MORT_MOB,
    MORT_HERO,
    GAME_OVER,
    MUSIQUE
};

//Une enum pour la gestion du menu.
enum
{
    START,
    PAUSE,
    GAMEOVER,
    FIN
};

#endif