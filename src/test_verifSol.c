#include "prototypes.h"

extern Personnage monstre[MONSTRES_MAX];
extern int nombreMonstres;

int testVerifSol(Personnage monstre)
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
            printf("C'est traversable\n");

        else
            printf("C'est solide\n");
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
            printf("C'est traversable\n");
        else
            printf("C'est solide\n");
    }
}

