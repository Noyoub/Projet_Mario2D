/*!
*  \file       input.c
*  \brief      S'occupe de gérer les évènements des touches du clavier
*  \version    1.7
*  \author     Lucas BOUILLON, Arthur SCHERRER, Lucas BEAUFRETON
*  \date 
 */

#include "prototypes.h"
 

void gestionTouches(Input *touche)
{
    //On gère le clavier 
    recupTouche(touche);
}
 

void recupTouche(Input *touche)
{
    SDL_Event event;
 
    //On gère les appuis sur les touches et les enregistre

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
 
            case SDL_QUIT:
                exit(0);
            break;
            //à l'appuie sur la touche
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        touche->pause = 1;
                        break;
 
                    case SDLK_m:
                        touche->volume = 1;
                    break;
 
                    case SDLK_SPACE:
                        touche->saut = 1;
                    break;
 
                    case SDLK_LEFT:
                        touche->gauche = 1;
                    break;
 
                    case SDLK_RIGHT:
                        touche->droite = 1;
                    break;
 
                    case SDLK_DOWN:
                        touche->bas = 1;
                    break;
 
                    case SDLK_UP:
                        touche->haut = 1;
                    break;
 
                    case SDLK_RETURN:
                        touche->entrer = 1;
                    break;
 
 
                    default:
                    break;
                }
            break;
            //au relachement de la touche
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        touche->pause = 0;
                    break;
                    
                    case SDLK_m:
                        touche->volume = 0;
                    break;
 
                    case SDLK_SPACE:
                        touche->saut = 0;
                    break;
 
                    case SDLK_LEFT:
                        touche->gauche = 0;
                    break;
 
                    case SDLK_RIGHT:
                        touche->droite = 0;
                    break;
 
                    case SDLK_DOWN:
                        touche->bas = 0;
                    break;
 
                    case SDLK_UP:
                        touche->haut = 0;
                    break;
 
                    case SDLK_RETURN:
                        touche->entrer = 0;
                    break;
 
                    default:
                    break;
                }
            break;
 
        }
 
    }
}
