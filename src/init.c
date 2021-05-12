/*!
*  \file       init.c
*  \brief      initialise tous les outils nécessaires aux fonctionnalités du jeu
*  \version    1.7
*  \author     Lucas BOUILLON, Arthur SCHERRER, Lucas BEAUFRETON
*  \date 
 */

#include "prototypes.h"
 
 
SDL_Window *screen;
SDL_Renderer *renderer;
extern int hero;

SDL_Renderer *recupRendu(void)
{
    return renderer;
}



void chargementJeu()
{
    
    //On charge les données pour la map
    initMaps(1);

    //On initialise les menus
    initMenus();    
    
    //On charge le sprite du personnage choisi
    initSpriteJoueur(hero);

    //On charge le sprite du monstre
    chargeSpriteMonstre();

    //On commence au premier niveau
    changeNiveau(1);

    /* On initialise les variables du jeu */
    initNombreDeVies(3);
    initNombreDePieces(0);
    
    /* On charge le HUD */
    initHUD();
 
    /* On charge les sons */
    chargeSon();
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);

    //On commence par le menu start
    initTypeMenu(1, START);
 
}
 
 



void init(char *title)
{
    
    screen = SDL_CreateWindow(title,
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    LARGEUR_FENETRE, HAUTEUR_FENETRE,
    SDL_WINDOW_SHOWN);
 
    //On crée un rendu pour la SDL
    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_PRESENTVSYNC);
 
    // Si on n'y arrive pas, on quitte en enregistrant l'erreur dans stdout.txt
    if (screen == NULL || renderer == NULL)
    {
        printf("Impossible d'initialiser le mode écran à %d x %d: %s\n", LARGEUR_FENETRE,
            HAUTEUR_FENETRE, SDL_GetError());
        exit(1);
    }

    //Création de la surface pour l'icone de la fenêtre
    SDL_Surface* iconSurface = IMG_Load("../images/icone.png");

    SDL_SetWindowIcon(screen, iconSurface);
 
    //Initialisation du chargement des images png avec SDL_Image 2
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image n'a pu être initialisée! SDL_image Error: %s\n", IMG_GetError() );
        exit(1);
    }
 
    //On cache le curseur de la souris
    SDL_ShowCursor(SDL_DISABLE);
 
    //On initialise SDL_TTF qui gérera l'écriture de texte
    if (TTF_Init() < 0)
    {
    printf("Impossible d'initialiser SDL TTF: %s\n", TTF_GetError());
    exit(1);
    }
    
    
    /* Chargement de la police */
    chargePolice("../font/mario.ttf", 25);
    
    
    //On initialise SDL_Mixer qui gérera la musique et les effets sonores
    int flags = MIX_INIT_MP3;
    int initted = Mix_Init(flags);
    if ((initted & flags) != flags)
    {
    printf("Mix_Init: Impossible d'initialiser SDL_Mixer\n");
    printf("Mix_Init: %s\n", Mix_GetError());
    exit(1);
    }


    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
        exit(1);
    }
 
    //Définit le nombre de pistes audio (channels) à mixer
    Mix_AllocateChannels(32);
 
}
 
 
 
 

void nettoyageAll()
{
    //Nettoie les sprites de la map et des menus
    nettoyageMaps();
    libereMenus();
    
    //Libère le sprite du héros 
    nettoyageJoueur();

    /* Libère le sprite des monstres */
    libereMonstre();

    //Libère le HUD
    nettoyageHUD();
    
    /* On libère la musique */
    libereMusique();
    
    //On libère les sons
    libereSon();

    //On quitte SDL_Mixer 2 et on décharge la mémoire
    Mix_CloseAudio();
    Mix_Quit();
    
    //On fait le ménage et on remet les pointeurs à NULL
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(screen);
    screen = NULL;
    
    //On quitte SDL_TTF 2
    TTF_Quit();
    
    //On quitte la SDL
    SDL_Quit();
}