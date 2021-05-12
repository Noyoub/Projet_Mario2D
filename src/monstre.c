/*!
*  \file       monstre.c
*  \brief      S'occupe des fonctions gérant l'affichage et les événements des monstres
*  \version    1.7
*  \author     Lucas BOUILLON, Arthur SCHERRER, Lucas BEAUFRETON
*  \date 
 */
#include "prototypes.h"
 
 
int nombreMonstres;
Personnage monstre[MONSTRES_MAX];
SDL_Texture *MonstreSprite;
extern SDL_bool volume;
 
 
Personnage *recupMonstre(int nombre)
{
    return &monstre[nombre];
}
 
 
int recupNombreMonstres(void)
{
    return nombreMonstres;
}
 
 
void resetMonstres(void)
{
    nombreMonstres = 0;
}
 
 
void chargeSpriteMonstre(void)
{
    MonstreSprite = chargeImage("../images/monster1.png");
}
 
 
void libereMonstre(void)
{
    /* Libère le sprite des monstres */
    if (MonstreSprite != NULL)
    {
        SDL_DestroyTexture(MonstreSprite);
        MonstreSprite = NULL;
    }
}
 
 
 
void initNouveauMonstre(int x, int y)
{
    //Si on n'est pas rendu au max, on rajoute incrémente nombreMonstres : monstre[0] si c'est le 1er, monstre[1], si c'est le 2eme, etc...
    
    if (nombreMonstres < MONSTRES_MAX)
    {
    
        // On indique sa direction 
        monstre[nombreMonstres].direction = LEFT;
        
        // Ses coordonnées de démarrage seront envoyées par la fonction dessineMap() en arguments
        monstre[nombreMonstres].x = x;
        monstre[nombreMonstres].y = y;
        
        // Hauteur et largeur de notre monstre
        monstre[nombreMonstres].w = LARGEUR_MONSTRE;
        monstre[nombreMonstres].h = HAUTEUR_MONSTRE;
        
        // Variables nécessaires au fonctionnement de la gestion des collisions comme pour le héros
        monstre[nombreMonstres].timerMort = 0;
        monstre[nombreMonstres].surSol = 0;
        
        nombreMonstres++;
    
    }
 
}
 
 
 
void majMonstre()
{
    int i;
    
    //On passe en boucle tous les monstres du tableau
    for (i = 0; i < nombreMonstres; i++)
    {
        //Même fonctionnement que pour le joueur
        if (monstre[i].timerMort == 0)
        {
            
            monstre[i].dirX = 0;
            monstre[i].dirY += VITESSE_GRAVITE;
        
            if (monstre[i].dirY >= VITESSE_CHUTE)
                monstre[i].dirY = VITESSE_CHUTE;
            
            //Test de collision dans un mur : si la variable x reste la même, deux tours de boucle durant, le monstre est bloqué et on lui fait faire demi-tour.
            if (monstre[i].x == monstre[i].saveX || verifSol(monstre[i]) == 1)
            {
                if (monstre[i].direction == LEFT)
                {
                    monstre[i].direction = RIGHT;
                }
                else
                {
                    monstre[i].direction = LEFT;
                }
        }

        //test unitaire pour la fonction verifSol() avec le premier monstre du niveau
        //testVerifSol(monstre[0]);
        
        //Déplacement du monstre selon la direction
        if (monstre[i].direction == LEFT)
            monstre[i].dirX -= 1;

        else if(monstre[i].direction == RIGHT)
            monstre[i].dirX += 1;
        
        
        //On sauvegarde les coordonnées du monstre pour gérer le demi-tour avant que mapCollision() ne les modifie.
        monstre[i].saveX = monstre[i].x;
        
        //On détecte les collisions avec la map comme pour le joueur
        collision_map_monstre(&monstre[i]);
        
        //On détecte les collisions avec le joueur

        //Si c'est égal à 1, on tue le joueur
        if (collisionMonstreJoueur(recupJoueur(), &monstre[i]) == 1)
        {
            tuerJoueur();
        }
        
        else if (collisionMonstreJoueur(recupJoueur(), &monstre[i]) == 2)
        {
            //On met le timer à 1 pour tuer le monstre instantanément
            monstre[i].timerMort = 1;

            if(volume == SDL_TRUE)
                joueSon(MORT_MOB);
        }
        
        }
        
        //Si le monstre meurt, on active une tempo
        if (monstre[i].timerMort > 0)
        {
            monstre[i].timerMort--;
            
            /* Et on le remplace simplement par le dernier du tableau puis on
            rétrécit le tableau d'une case */
            if (monstre[i].timerMort == 0)
            {
            
                monstre[i] = monstre[nombreMonstres - 1];
                nombreMonstres--;
            
            }
        }
    }
    
}
 
 
//Fonction de gestion des collisions
int collisionMonstreJoueur(Personnage *joueur, Personnage *monstre)
{
    //On teste pour voir s'il n'y a pas collision, si c'est le cas, on renvoie 0
    if (
        (joueur->x >= monstre->x + monstre->w)
        || (joueur->x + joueur->w <= monstre->x)
        || (joueur->y >= monstre->y + monstre->h)
        || (joueur->y + joueur->h <= monstre->y)
    )
        return 0;
    
    //Sinon, il y a collision. Si le joueur est au-dessus du monstre, on renvoie 2.
    //On devra alors tuer le monstre et on fera rebondir le joueur.
    else if (joueur->y + joueur->h <= monstre->y + 20)
    {
        joueur->dirY = -HAUTEUR_SAUT;
        return 2;
    }
    
    //Sinon, on renvoie 1 et c'est le joueur qui meurt
    else
        return 1;
}
 
 
 
int verifSol(Personnage monstre)
{
    int x, y;
    
    //Fonction qui teste s'il y a du sol sous un monstre
    //Retourne 1 s'il doit tomber, 0 sinon
    
    //On teste la direction, pour savoir si on doit prendre en compte 
    if (monstre.direction == LEFT)
    {
        //On va à gauche : on calcule là où devrait se trouver le monstre après déplacement.
        //S'il sort de la map, on met à jour x et y pour éviter de sortir de notre tableau
        x = (int)(monstre.x + monstre.dirX) / TAILLE_TILE;
        y = (int)(monstre.y + monstre.h - 1) / TAILLE_TILE;
        
        if (y < 0)
            y = 1;
        
        if (y > MAX_MAP_Y)
            y = MAX_MAP_Y;
        
        if (x < 0)
            x = 1;
        
        if (x > MAX_MAP_X)
            x = MAX_MAP_X;
        
        //On teste si la tile sous le monstre est traversable 
        //Si c'est le cas, on renvoie 1, sinon 0.
        if (recupValeurTile(y + 1, x) < SEUIL_TILES_TRAVERSABLES_HAUT - 20)
            return 1;

        else
            return 0;
    }
    else
    {
        //Même chose quand on va à droite
        x = (int)(monstre.x + monstre.w + monstre.dirX) / TAILLE_TILE;
        y = (int)(monstre.y + monstre.h - 1) / TAILLE_TILE;
        
        if (y <= 0)
            y = 1;
        
        if (y >= MAX_MAP_Y)
            y = MAX_MAP_Y - 1;
        
        if (x <= 0)
            x = 1;
        
        if (x >= MAX_MAP_X)
            x = MAX_MAP_X - 1;
        
        if (recupValeurTile(y + 1, x) < SEUIL_TILES_TRAVERSABLES_HAUT - 20)
            return 1;
        else
            return 0;
    }
}
 
 
void dessineMonstre(Personnage *monstre)
{
    
    /* Rectangle de destination à dessiner */
    SDL_Rect dest;
    
    // On soustrait des coordonnées de notre monstre, ceux du début de la map, pour qu'il colle au scrolling :
    dest.x = monstre->x - recupPersoStartX();
    dest.y = monstre->y - recupPersoStartY();
    dest.w = monstre->w;
    dest.h = monstre->h;
    
    
    //Gestion du flip : retournement de l'image selon que le monstre regarde à droite ou à gauche
    if (monstre->direction == LEFT)
        SDL_RenderCopyEx(recupRendu(), MonstreSprite, NULL, &dest, 0, 0, SDL_FLIP_HORIZONTAL);
    else
        SDL_RenderCopyEx(recupRendu(), MonstreSprite, NULL, &dest, 0, 0, SDL_FLIP_NONE);
 
}