/*!
 *  \file       joueur.c
 *  \brief      Ce fichier implémente toutes les fonctions nécessaires à la gestion des évènements liés au personnage.
 *  \version    1.7
 *  \author     Lucas BOUILLON, Arthur SCHERRER, Lucas BEAUFRETON
 *  \date 
 */



#include "prototypes.h"
 
int niveau;
int vies, pieces;
int totalPieces = 0;
int totalMorts = 0;
extern SDL_bool volume;
Personnage joueur;
SDL_Texture *joueurSpriteSheet;
 
 

Personnage *recupJoueur(void)
{
    return &joueur;
}
 
 

int recupJoueurX(void)
{
    return joueur.x;
}
 
 

int recupJoueurY(void)
{
    return joueur.y;
}
 



void initJoueurX(int valeur)
{
    joueur.x = valeur;
}
 
 

void initJoueurY(int valeur)
{
    joueur.y = valeur;
}
 
 

int recupNiveau(void)
{
    return niveau;
}



int recupNombreDeVies(void)
{
    return vies;
}
 


void initNombreDeVies(int valeur)
{
    vies = valeur;
}


int recupNombreDePieces(void)
{
    return pieces;
}
 
void initNombreDePieces(int valeur)
{
    pieces = valeur;
}
 
 

void changeNiveau(int valeur)
{
    niveau = valeur;
}


void initSpriteJoueur(int hero)
{
    if(hero == 1)
        joueurSpriteSheet = chargeImage("../images/mario.png");
    else if(hero == 2)
        joueurSpriteSheet = chargeImage("../images/luigi.png");
    else if(hero == 3)
        joueurSpriteSheet = chargeImage("../images/yoshi.png");
    else if(hero == 4)
        joueurSpriteSheet = chargeImage("../images/dk.png");
    else if(hero == 5)
        joueurSpriteSheet = chargeImage("../images/wario.png");
    else if(hero == 6)
        joueurSpriteSheet = chargeImage("../images/waluigi.png");
}

void resetCheckpoint(void)
{
    joueur.checkpointActif = 0;
} 
 
 

void nettoyageJoueur(void)
{
    if (joueurSpriteSheet != NULL)
    {
    SDL_DestroyTexture(joueurSpriteSheet);
    joueurSpriteSheet = NULL;
    }
}
 
 
void tuerJoueur()
{
    
    //On affiche le héro à l'état mort
    joueur.etat = MORT;
    joueur.frameNumber = 0;
    joueur.frameTimer = TEMPS_ENTRE_2_FRAMES_JOUEUR;
    joueur.frameMax = 1; 

    //On augmente le compteur de morts pour l'écran de fin
    totalMorts += 1;

    //On met le timer à 1 pour tuer le joueur intantanément
    joueur.timerMort = 1;

}
 

void initJoueur(int nouveauNiveau)
{
 
    //PV à 3
    joueur.vie = 3;

    
    //Indique l'état et la direction de notre personnage
    joueur.direction = RIGHT;
    joueur.etat = IMMOBILE;

    //Indique le numéro de la frame où commencer
    joueur.frameNumber = 0;
    
    //Indique la valeur de son chrono ou timer
    joueur.frameTimer = TEMPS_ENTRE_2_FRAMES_JOUEUR;
    
    //Indique son nombre de frames max
    joueur.frameMax = 1;

    /* Coordonnées de démarrage/respawn de notre personnage */
    if (joueur.checkpointActif == 1)
    {
        joueur.x = joueur.respawnX;
        joueur.y = joueur.respawnY;
    }
    else
    {
        joueur.x = recupDebutMapX();
        joueur.y = recupDebutMapY();
    }

    
    //On réinitiliase les coordonnées de la caméra
    //si on change de niveau
    if (nouveauNiveau == 1)
    {
    initDepartMapX(recupDebutMapX());
    initDepartMapY(recupDebutMapY());
    }
    
    /* Hauteur et largeur de notre personnage */
    joueur.w = LARGEUR_JOUEUR;
    joueur.h = HAUTEUR_JOUEUR;
    
    //Variables nécessaires au fonctionnement de la gestion des collisions
    joueur.timerMort = 0;
    joueur.surSol = 0;

    
    //Réinitialise les monstres
    /* Libère le sprite des monstres */
    resetMonstres();
 
}



void dessineJoueur(void)
{
    /* Gestion du timer */
    //Si notre timer (un compte à rebours) arrive à zéro
    if (joueur.frameTimer <= 0)
    {
        //On le réinitialise
        joueur.frameTimer = TEMPS_ENTRE_2_FRAMES_JOUEUR;
        
        //Et on incrémente notre variable qui compte les frames de 1 pour passer à la suivante
        joueur.frameNumber++;
        
        //Mais si on dépasse la frame max, il faut revenir à la première :
        if (joueur.frameNumber >= joueur.frameMax)
            joueur.frameNumber = 0;
    
    }
    //Sinon, on décrémente notre timer
    else
        joueur.frameTimer--;


    /* Rectangle de destination à dessiner */
    SDL_Rect dest;
    
    //On soustrait des coordonnées de notre héros, ceux du début de la map, pour qu'il colle au scrolling
    dest.x = joueur.x - recupPersoStartX();
    dest.y = joueur.y - recupPersoStartY();
    dest.w = joueur.w;
    dest.h = joueur.h;
    
    /* Rectangle source */
    SDL_Rect src;
    
    src.x = joueur.frameNumber * joueur.w;
    src.w = joueur.w;
    src.h = joueur.h;
    
    //On calcule le Y de la bonne frame à dessiner, selon la valeur de l'état du héros 
    src.y = (joueur.etat * joueur.h) ;
    
    
    //Gestion du flip (retournement de l'image en fonction du sprite s'il regarde à droite ou à gauche)
    if (joueur.direction == LEFT)
        SDL_RenderCopyEx(recupRendu(), joueurSpriteSheet, &src, &dest, 0, 0, SDL_FLIP_HORIZONTAL);
    else
        SDL_RenderCopyEx(recupRendu(), joueurSpriteSheet, &src, &dest, 0, 0, SDL_FLIP_NONE);
 
}




void majJoueur(Input *touche)
{
    //On rajoute un timer si l'on meurt
    //Si le timer vaut 0, c'est que tout va bien, sinon, on le décrémente jusqu'à 0
    //on réinitialise à la position de départ du joueur.
    if (joueur.timerMort == 0)
    {
    
        //On réinitialise notre vecteur X 
        joueur.dirX = 0;
        
        // Pour faire tomber le perso avec la gravité
        joueur.dirY += VITESSE_GRAVITE;
        
        //limite pour ne pas que le joueur se mette à tomber trop vite 
        if (joueur.dirY >= VITESSE_CHUTE)
            joueur.dirY = VITESSE_CHUTE;
    
    
        if (touche->gauche == 1)
        {
            joueur.dirX -= VITESSE_JOUEUR;
            //Et on indique qu'il va à gauche (pour le flip)

            joueur.direction = LEFT;
        
            //Si ce n'était pas son état auparavant
            if (joueur.etat != MARCHE && joueur.surSol == 1)
            {
                //On enregistre l'anim de la marche et on l'initialise à 0
                joueur.etat = MARCHE;
                joueur.frameNumber = 0;
                joueur.frameTimer = TEMPS_ENTRE_2_FRAMES_JOUEUR;
                joueur.frameMax = 8;
            }
        }
    
        //Si on détecte un appui sur la touche "fléchée droite"
        else if (touche->droite == 1)
        {
            //On augmente les coordonnées en x du joueur
            joueur.dirX += VITESSE_JOUEUR;
            //Et on indique qu'il va à droite 
            joueur.direction = RIGHT;
            
            //Si ce n'était pas son état auparavant 
            if (joueur.etat != MARCHE && joueur.surSol == 1)
                {
                //On enregistre l'anim de la marche et on l'initialise à 0
                joueur.etat = MARCHE;
                joueur.frameNumber = 0;
                joueur.frameTimer = TEMPS_ENTRE_2_FRAMES_JOUEUR;
                joueur.frameMax = 8;
            }
        }
    
        //Si on n'appuie sur rien et qu'on est sur le sol, on charge l'animation marquant l'inactivité (Immobile)
        else if (touche->droite == 0 && touche->gauche == 0 && joueur.surSol == 1)
        {
            //On teste si le joueur n'était pas déjà inactif, pour ne pas recharger l'animation
            if (joueur.etat != IMMOBILE)
            {
                //On enregistre l'anim de l'inactivité et on l'initialise à 0
                joueur.etat = IMMOBILE;
                joueur.frameNumber = 0;
                joueur.frameTimer = TEMPS_ENTRE_2_FRAMES_JOUEUR;
                joueur.frameMax = 1;
            }
        }
    
    
        //Si on appuie sur la touche saut et qu'on est sur le sol, alors on attribue une valeur négative à Y

        if (touche->saut == 1)
        {
            if (joueur.surSol == 1)
            {
                joueur.dirY = -HAUTEUR_SAUT;
                joueur.surSol = 0;
                joueur.jump = 1;
                if(volume == SDL_TRUE)
                    joueSon(JUMP);
            }
            touche->saut = 0;
        }

        //Si on appuie sur Echap
        if (touche->pause == 1)
        {
            //On met le jeu en pause
            initTypeMenu(1, PAUSE);
            //On joue le son de pause
            if(volume == SDL_TRUE)
                joueSon(PAUSE_GAME);
            Mix_PauseMusic();

            touche->pause = 0;
        }
       
    
        //On gère l'anim du saut
        if (joueur.surSol == 0)
        {
            if (joueur.jump == 1)
            {
                if (joueur.etat != SAUT)
                {
                    joueur.etat = SAUT;
                    joueur.frameNumber = 0;
                    joueur.frameTimer = TEMPS_ENTRE_2_FRAMES_JOUEUR;
                    joueur.frameMax = 1;
                }
            }
        }
        
        //On rajoute notre fonction de détection des collisions pour mettre à jour les coordonnées du joueur
        mapCollision(&joueur);
        
        //On gère le scrolling 
        scrollSurJoueur();
        
    }
    
    //Gestion de la mort quand le héros tombe dans un trou 
    //Si timerMort est différent de 0, c'est qu'il faut réinitialiser le joueur.
    //Si timerMort == 1, on le décrémente encore -> il vaut 0 et on réinitialise
    if (joueur.timerMort > 0)
    {
        joueur.timerMort--;
    
        if (joueur.timerMort == 0)
        {
            Mix_PauseMusic();

            // Si on est mort, on perd une vie
            initNombreDeVies(recupNombreDeVies() - 1);

            initNombreDePieces(0);


            if(volume == SDL_TRUE)
                joueSon(MORT_HERO);

            //On attend 2.8 secondes  
            SDL_Delay(2800);            
 

            //si on a plus de vies
            if (recupNombreDeVies() < 1)
            {
                //Dans ce cas on retourne au menu start
                if(volume == SDL_TRUE)
                    joueSon(GAME_OVER);
                initTypeMenu(1, GAMEOVER);
            }

            // Si on est mort, on réinitialise le niveau
            chargeNiveau(recupNiveau());
            initJoueur(0);

        }
    }
}



void scrollSurJoueur(void)
{
    // on crée une "boîte" imaginaire autour du joueuret quand on dépasse un de ses bords (en haut, en bas, à gauche ou à droite), on scroll.

    int cxperso = joueur.x + joueur.w / 2;
    int cyperso = joueur.y + joueur.h / 2;
    int xlimmin = recupPersoStartX() + LIMITE_X;
    int xlimmax = xlimmin + LIMITE_W;
    int ylimmin = recupPersoStartY() + LIMITE_Y;
    int ylimmax = ylimmin + LIMITE_H;
    
    //Effet de retour en arrière quand on est mort 

    if (cxperso < recupPersoStartX())
    {
        initDepartMapX(recupPersoStartX() - 30);
    }
    
    //Si on dépasse par la gauche, on recule la caméra
    else if (cxperso < xlimmin)
    {
        initDepartMapX(recupPersoStartX() - 4);
    }
    
    //Effet de retour en avant quand on est mort

    if (cxperso > recupPersoStartX() + LARGEUR_FENETRE)
    {
        initDepartMapX(recupPersoStartX() + 30);
    }
    
    //Si on dépasse par la droite, on avance la caméra
    else if (cxperso > xlimmax)
    {
        initDepartMapX(recupPersoStartX() + 4);
    }
    
    //Si on arrive au bout de la map à gauche, on stoppe le scrolling
    if (recupPersoStartX() < 0)
    {
        initDepartMapX(0);
    }
    
    //Si on arrive au bout de la map à droite, on stoppe le scrolling à la valeur Max de la map - la moitié d'un écran (pour ne pas afficher du noir).
    else if (recupPersoStartX() + LARGEUR_FENETRE >= recupFinMapX())
    {
        initDepartMapX(recupFinMapX() - LARGEUR_FENETRE);
    }
    
    //Si on dépasse par le haut, on remonte la caméra
    if (cyperso < ylimmin)
    {
        initDepartMapY(recupPersoStartY() - 4);
    }
    
    //Si on dépasse par le bas, on descend la caméra
    if (cyperso > ylimmax)
    {
        //Sauf si on tombe très vite, auquel cas, on accélère la caméra 
        if (joueur.dirY >= VITESSE_CHUTE - 2)
        {
            initDepartMapY(recupPersoStartY() + VITESSE_CHUTE + 1);
        }
        else
        {
            initDepartMapY(recupPersoStartY() + 4);
        }
    }
    
    //Si on arrive au bout de la map en haut, on stoppe le scrolling
    if (recupPersoStartY() < 0)
    {
        initDepartMapY(0);
    }
    
    //Si on arrive au bout de la map en bas, on stoppe le scrolling à la valeur Max de la map - la moitié d'un écran (pour ne pas afficher du noir).
    else if (recupPersoStartY() + HAUTEUR_FENETRE >= recupFinMapY())
    {
        initDepartMapY(recupFinMapY() - HAUTEUR_FENETRE);
    }
    
}


void recupItem(int itemNumber)
{
    switch (itemNumber)
    {
        //Gestion des pièces
        case 1:
        //On incrémente le compteur de pièces
        initNombreDePieces(recupNombreDePieces() + 1);

        //On incrémente le compteur de pièces total pour l'écran de fin
        totalPieces += 1;
        
        //On joue le son de pièce
        if(volume == SDL_TRUE)
            joueSon(COIN);
        
        //On teste s'il y a 20 pièces et si oui, on remet le compteur à 0 et on rajoute une vie
        if (recupNombreDePieces() >= 20)
        {
            initNombreDePieces(0);
            //On incrémente le nombre de vies (max 99)
            if (recupNombreDeVies() < 99)
                initNombreDeVies(recupNombreDeVies() + 1);
        }
        break;
        
        default:
        break;
    }
 
}