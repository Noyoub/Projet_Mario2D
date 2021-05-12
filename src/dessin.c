/*!
*  \file       dessin.c
*  \brief      S'occupe des fonctions graphiques du jeu
*  \version    1.7
*  \author     Lucas BOUILLON, Arthur SCHERRER, Lucas BEAUFRETON
*  \date 
 */

#include "prototypes.h"


//Variables pour le HUD
SDL_Texture *HUD_vie, *HUD_pieces, *HUD_temps, *HUD_record; 

extern int record;
int timer, timer_reset = 0;


void chargeJeu(int pauseMenu)
{
    // Affiche le fond (background) aux coordonnées (0,0)
    dessineImage(getBackground(), 0, 0);
    
    /* Affiche la map de tiles : couche 2 (couche du fond) */
    dessineMap(2);
    
    /* Affiche la map de tiles : couche 1 (couche active : sol, etc.)*/
    dessineMap(1);
    
    /* Affiche le joueur */
    dessineJoueur();

    /* Affiche les monstres */
    for (int i = 0; i < recupNombreMonstres(); i++)
    {
    dessineMonstre(recupMonstre(i));
    }

    //On affiche le HUD par-dessus tout le reste
    dessineHUD();

    //On affiche le menu Pause, si on est en Pause
    if (pauseMenu)
        dessineMenuPause();
    
    //Affiche l'écran
    SDL_RenderPresent(recupRendu());
    
    //Délai pour laisser respirer le processeur
    SDL_Delay(1);
    
}





SDL_Texture *chargeImage(char *nom)
{
    
    /* Charge les images avec SDL Image dans une SDL_Surface */
    
    SDL_Surface *loadedImage = NULL;
    SDL_Texture *texture = NULL;
    loadedImage = IMG_Load(nom);
    
    if (loadedImage != NULL)
    {
    //Conversion de l'image en texture
    texture = SDL_CreateTextureFromSurface(recupRendu(), loadedImage);
    
    //On se débarrasse du pointeur vers une surface
    SDL_FreeSurface(loadedImage);
    loadedImage = NULL;
    }
    else
    printf("L'image n'a pas pu être chargée! SDL_Error : %s\n", SDL_GetError());
    
    return texture;
    
}
    
  
void dessineImage(SDL_Texture *image, int x, int y)
{
    
    SDL_Rect dest;
    
    /* Règle le rectangle à dessiner selon la taille de l'image source */
    dest.x = x;
    dest.y = y;
    
    /* Dessine l'image entière sur l'écran aux coordonnées x et y */
    SDL_QueryTexture(image, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(recupRendu(), image, NULL, &dest);
 
}
 


void delay(unsigned int frameLimit)
{
    // Gestion des 60 fps (images/seconde)
    unsigned int ticks = SDL_GetTicks();
 
    if (frameLimit < ticks)
    {
        return;
    }
 
    if (frameLimit > ticks + 16)
    {
        SDL_Delay(16);
    }
 
    else
    {
        SDL_Delay(frameLimit - ticks);
    }
}


void dessineTile(SDL_Texture *image, int destx, int desty, int srcx, int srcy)
{
    /* Rectangle de destination à dessiner */
    SDL_Rect dest;
    
    dest.x = destx;
    dest.y = desty;
    dest.w = TAILLE_TILE;
    dest.h = TAILLE_TILE;
    
    /* Rectangle source */
    SDL_Rect src;
    
    src.x = srcx;
    src.y = srcy;
    src.w = TAILLE_TILE;
    src.h = TAILLE_TILE;
    
    /* Dessine la tile choisie sur l'écran aux coordonnées x et y */
    SDL_RenderCopy(recupRendu(), image, &src, &dest);
}



void initHUD(void)
{
    /* On charge les images du HUD */
    HUD_vie = chargeImage("../images/life.png");
    HUD_pieces = chargeImage("../images/piece.png");
    HUD_temps = chargeImage("../images/timer.png");
    HUD_record = chargeImage("../images/record.png");

}
 


void nettoyageHUD(void)
{
    if (HUD_pieces != NULL)
    {
        SDL_DestroyTexture(HUD_pieces);
    }
    
    if (HUD_vie != NULL)
    {
        SDL_DestroyTexture(HUD_vie);
    }

    if (HUD_temps != NULL)
    {
        SDL_DestroyTexture(HUD_temps);
    }

    if (HUD_record != NULL)
    {
        SDL_DestroyTexture(HUD_temps);
    }
}


void dessineHUD(void)
{
    //On crée une variable qui contiendra notre texte
    char text[200];
    
    int i;

    timer = SDL_GetTicks() / 1000; //On lance le timer depuis le lancement de la SDL
    timer -= timer_reset; //On retire le temps dans les menus pour avoir uniquement le temps en partie de jeu
    

    /* Affiche le nombre de vies en haut à droite */
    dessineImage(HUD_vie, LARGEUR_FENETRE - 125, 18);
    
    //Pour afficher le nombre de vies, on formate notre string pour qu'il prenne la valeur de la variable
    sprintf_s(text, sizeof(text), "x %d", recupNombreDeVies());
    
    
    //Puis on utilise notre fonction créée précédemment pour écrire en noir (0, 0, 0, 255)
    //et en blanc (255, 255, 255, 255) afin de surligner le texte et de le rendre plus
    //visible
    afficheTexte(text, LARGEUR_FENETRE - 80, 20, 0, 0, 0, 255);
    afficheTexte(text, LARGEUR_FENETRE - 82, 20, 255, 255, 255, 255);
    
    /* Affiche le nombre de pièces en haut à gauche */
    dessineImage(HUD_pieces, 20, 15);
    
    sprintf_s(text, sizeof(text), "%d", recupNombreDePieces());

    afficheTexte(text, 60, 20, 0, 0, 0, 255);
    afficheTexte(text, 60, 18, 255, 255, 255, 255);


    /* Affiche le temps en haut au centre */
    dessineImage(HUD_temps, 280, 20);

    sprintf_s(text, sizeof(text), "%d", timer);
    
    afficheTexte(text, 322, 25, 0, 0, 0, 255);
    afficheTexte(text, 320, 23, 255, 255, 255, 255);

    /* Affiche le temps record en haut au centre */
    dessineImage(HUD_record, 440, 20);

    sprintf_s(text, sizeof(text), "%d", record);
    afficheTexte(text, 482, 25, 0, 0, 0, 255);
    afficheTexte(text, 480, 23, 255, 255, 255, 255);
 
}

