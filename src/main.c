/*!
 *  \file       main.c
 *  \brief      Programme principal qui charge le jeu et qui va gérer les différents évènements
 *  \version    1.7
 *  \author     Lucas BOUILLON, Arthur SCHERRER, Lucas BEAUFRETON
 *  \date 
 */

/*!
 *  \mainpage Projet MARIO2D : Projet pour les étudiants de L2 informatique visant à coder un jeu avec des algorithmes pertinents, et éventuellement une interface graphique. \n
 *  Le groupe "MARIO2D" a décidé de faire une sorte de remake de Super Mario Bros, mais de transformer le jeu en Mario Parkour. \n
 *  Le but est d'implémenter un jeu avec interface graphique, ou l'on fait évoluer un personnage dans un univers rempli de défis à relever. \n
 *  L'utilisateur devra parcourir les trois niveau en un temps record tout en mourrant le moins possible et en récupérant un maximum de pièces.
 */

#include "prototypes.h"
 
//gcc src/main.c src/menu.c src/sons.c src/polices.c src/dessin.c src/init.c src/input.c src/map.c src/joueur.c src/monstre.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf

/* Déclaration des variables / structures utilisées par le jeu */
Input touche;
extern int record;
extern int timer, timer_reset;
 
int main(int argc, char *argv[])
{
    //Gestion des fps
    unsigned int frameLimit = SDL_GetTicks() + 16;
    int go;
 
    // Initialisation de la SDL
    init("Mario2D");

    // Chargement des ressources (graphismes, sons)
    chargementJeu();

    /* On initialise le joueur */
    initJoueur(1);
 
    // Appelle la fonction nettoyageAll à la fin du programme
    atexit(nettoyageAll);

    FILE* fichier = NULL;
    char chaine[4] = ""; // Chaîne vide de taille 4
 
    fichier = fopen("../record.txt", "r");
 
    if (fichier != NULL)
    {
        fgets(chaine, 4, fichier); // On lit maximum 4 caractères du fichier, on stocke le tout dans "chaine"
        fclose(fichier);
    }

    else{
        printf("Impossible d'ouvrir le fichier.\n");
        exit(1);
    }

    record = atoi(chaine);
 
    go = 1;
 
    // Boucle infinie, principale, du jeu
    while (go == 1)
    {
        //Gestion des touches clavier
        gestionTouches(&touche);
        //Si on n'est pas dans un menu
        if (recupStatutMenu() == 0)
        {
            /* On met à jour le jeu */
            majJoueur(&touche);
            majMonstre();
        }

        else
        {

            if (recupTypeMenu() == START)
            {
                majMenuPrincipal(&touche);
                timer_reset = SDL_GetTicks() / 1000;
            }

            else if (recupTypeMenu() == FIN)
            {
                majMenuFin(&touche);
            }
            
            else if (recupTypeMenu() == PAUSE)
            {
                majMenuPause(&touche);
            }

            else if (recupTypeMenu() == GAMEOVER)
            {
                majMenuGameover(&touche);
            }
            
        }
        
        
        //Si on n'est pas dans un menu, on affiche le jeu
        if (recupStatutMenu() == 0){
            chargeJeu(0);
        }
        
        else
        {
            if (recupTypeMenu() == START)
            {
                dessineMenuPrincipal();
                SDL_RenderPresent(recupRendu());
                SDL_Delay(1);
            }

            else if (recupTypeMenu() == FIN)
            {
                dessineMenuFin();
                SDL_RenderPresent(recupRendu());
                SDL_Delay(1);
            }
        
            else if (recupTypeMenu() == PAUSE)
                chargeJeu(1);
            
            else if (recupTypeMenu() == GAMEOVER)
            {
                dessineMenuGameover();
                SDL_RenderPresent(recupRendu());
                SDL_Delay(1);
            }

        }
 
        // Gestion des 60 fps (1000ms/60 = 16.6 -> 16
        delay(frameLimit);
        frameLimit = SDL_GetTicks() + 16;
    }
 
    // On quitte
    exit(0);
 
}
