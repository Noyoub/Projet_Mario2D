/*!
 *  \file       map.c
 *  \brief      Ce fichier implémente toutes les fonctions nécessaires à la génération de la map. C'est-à-dire modéliser la map dans une matrice, récupérer ces coordonées aisni que gérer les collisions entre les textures de la map et le sprite du personnage.
 *  \version    1.7
 *  \author     Lucas BOUILLON, Arthur SCHERRER, Lucas BEAUFRETON
 *  \date 
 */

#include "prototypes.h"
 
 
Map map;
int record, record_battu = 0;
extern int timer;
extern SDL_bool volume;
FILE* fich = NULL;


void initMaps(int niveau)
{
    // Charge l'image du fond (background)
    if(niveau == 1){
        map.background = chargeImage("../images/background.png");
    }
    else if(niveau == 2){
        map.background = chargeImage("../images/background2.png");
    }
    else{
        map.background = chargeImage("../images/background3.png"); 
    }

    //On charge la musique
    if(niveau == 1){
        if(volume == SDL_TRUE)
            chargeMusique("../sounds/overworld.wav");
    }
    else if(niveau == 2){
        if(volume == SDL_TRUE)
            chargeMusique("../sounds/underwater.wav");
    }
    else{
        if(volume == SDL_TRUE)
            chargeMusique("../sounds/underground.wav");
    }
}

 
SDL_Texture *getBackground(void)
{
    return map.background;
}
 
 
void nettoyageMaps(void)
{
    // Libère la texture du background
    if (map.background != NULL)
    {
        SDL_DestroyTexture(map.background);
        map.background = NULL;
    }
    
    // Libère les textures des tilesets
    if (map.tileSet != NULL)
    {
        SDL_DestroyTexture(map.tileSet);
        map.tileSet = NULL;
    }
 
}


int recupValeurTile(int y, int x)
{
    return map.tile[y][x];
} 
 
void chargeMap(char *nom)
{
    int x, y;
    FILE *fp;
    int err;
    
    //Ouvre le fichier en lecture (renvoie une erreur s'il n'existe pas)
    if ((err = fopen_s(&fp, nom, "rb")) != 0)
    {
        printf("Le fichier map n'a pas pu etre ouvert.\n");
        exit(1);
    }
    
    /* Lit les données du fichier dans la map */
    
    /* Lit les coordonnées de début du joueur */
    fscanf_s(fp, "%d", &map.beginx);
    fscanf_s(fp, "%d", &map.beginy);
    
    /* On lit le numéro du tileset */
    fscanf_s(fp, "%d", &map.tilesetAffiche);
    
    map.maxX = map.maxY = 0;
    
    
    for (y = 0; y < MAX_MAP_Y; y++)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            /* On lit le numéro de la tile et on le copie dans notre tableau */
            fscanf_s(fp, "%d", &map.tile[y][x]);
        
            /* Permet de déterminer la taille de la map */
            if (map.tile[y][x] > 0)
            {
                if (x > map.maxX)
                {
                    map.maxX = x;
                }
            
                if (y > map.maxY)
                {
                    map.maxY = y;
                }
            }
        }
    }
    
    //Deuxième couche de tiles
    for (y = 0; y < MAX_MAP_Y; y++)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            /* On lit le numéro de la tile et on le copie dans notre tableau */
            fscanf_s(fp, "%d", &map.tile2[y][x]);
        }
    }

    // maxX et maxY sont les coordonnées de fin de la map.
    map.maxX = (map.maxX + 1) * TAILLE_TILE;
    map.maxY = (map.maxY + 1) * TAILLE_TILE;
    
    
    /* on ferme le fichier */
    fclose(fp);
 
}





void dessineMap(int couche)
{
    int x, y, mapX, x1, x2, mapY, y1, y2, xsource, ysource, a;
    
    //On initialise mapX à la 1ère colonne qu'on doit blitter.
 
    mapX = map.startX / TAILLE_TILE;
    
    // Coordonnées de départ pour l'affichage de la map 
    x1 = (map.startX % TAILLE_TILE) * -1;
    
    //Calcul des coordonnées de la fin de la map 
    x2 = x1 + LARGEUR_FENETRE + (x1 == 0 ? 0 : TAILLE_TILE);
    
    
    /* On fait pareil pour calculer y */
    mapY = map.startY / TAILLE_TILE;
    y1 = (map.startY % TAILLE_TILE) * -1;
    y2 = y1 + HAUTEUR_FENETRE + (y1 == 0 ? 0 : TAILLE_TILE);
    
    
    
    /* Dessine la carte en commençant par startX et startY */
    
    // On dessine ligne par ligne 
    if (couche == 1)
    {
        for (y = y1; y < y2; y += TAILLE_TILE)
        {
            //A chaque début de ligne, on réinitialise mapX qui contient la colonne
    
            mapX = map.startX / TAILLE_TILE;
            
            /* A chaque colonne de tile, on dessine la bonne tile en allant
            de x = 0 à x = 640 */
            for (x = x1; x < x2; x += TAILLE_TILE)
            {
                //Si la tile à dessiner n'est pas une tile vide
                if (map.tile[mapY][mapX] != 0)
                {
                    /*On teste si c'est une tile monstre */
                    if (map.tile[mapY][mapX] == TILE_MONSTRE)
                    {
                        //On initialise un monstre en envoyant les coordonnées de la tile
                        initNouveauMonstre(mapX * TAILLE_TILE, mapY * TAILLE_TILE);
                        
                        //Et on efface cette tile de notre tableau pour éviter un spawn de monstres
                        //infini !
                        map.tile[mapY][mapX] = 0;
                    }
                }
 
    
                /* Suivant le numéro la tile, on découpe le tileset (a = le numéro
                de la tile) */
                a = map.tile[mapY][mapX];
                
                /* Calcul pour obtenir son y (pour un tileset de 10 tiles
                par ligne, d'où le 10 */
                ysource = a / 10 * TAILLE_TILE;
                /* Et son x */
                xsource = a % 10 * TAILLE_TILE;
                
                //on dessine la tile sur notre rendu
                dessineTile(map.tileSet, x, y, xsource, ysource);

                mapX++;
            }
    
            mapY++;
        }
    }
    
    else if (couche == 2)
    {
        //Deuxième couche de tiles ;)
        for (y = y1; y < y2; y += TAILLE_TILE)
        {
            mapX = map.startX / TAILLE_TILE;
    
            for (x = x1; x < x2; x += TAILLE_TILE)
            {
                //Si la tile à dessiner n'est pas une tile vide
                if (map.tile2[mapY][mapX] != 0)
                {
                    /*On teste si c'est une tile monstre */
                    if (map.tile2[mapY][mapX] == TILE_MONSTRE)
                    {
                        //On initialise un monstre en envoyant les coordonnées de la tile
                        initNouveauMonstre(mapX * TAILLE_TILE, mapY * TAILLE_TILE);
                        
                        //Et on efface cette tile de notre tableau pour éviter un spawn de monstres
                        //infini !
                        map.tile2[mapY][mapX] = 0;
                    }
                }
                /* Suivant le numéro de la tile, on découpe le tileset (a = le numéro
                de la tile */
                a = map.tile2[mapY][mapX];
                
                /* Calcul pour obtenir son y (pour un tileset de 10 tiles
                par ligne, d'où le 10 */
                ysource = a / 10 * TAILLE_TILE;
                /* Et son x */
                xsource = a % 10 * TAILLE_TILE;

                dessineTile(map.tileSet, x, y, xsource, ysource);

                mapX++;
            }
    
            mapY++;
        }
    }
}



 
void chargeNiveau(int niveau)
{
    
    char file[200];
    
    /* Charge la map depuis le fichier */
    sprintf_s(file, sizeof(file), "../map/map%d.txt", recupNiveau());
    chargeMap(file);
    
    //Charge le tileset
    if (map.tileSet != NULL)
    {
        SDL_DestroyTexture(map.tileSet);
    }

    initMaps(recupNiveau());
    
    sprintf_s(file, sizeof(file), "../images/tileset%d.png", map.tilesetAffiche);
    map.tileSet = chargeImage(file);
 
}






int recupPersoStartX(void)
{
    return map.startX;
}



 
void initDepartMapX(int valeur)
{
    map.startX = valeur;
}




int recupPersoStartY(void)
{
    return map.startY;
}




void initDepartMapY(int valeur)
{
    map.startY = valeur;
}



 
int recupFinMapX(void)
{
    return map.maxX;
}




int recupFinMapY(void)
{
    return map.maxY;
}



 
int recupDebutMapX(void)
{
    return map.beginx;
}




int recupDebutMapY(void)
{
    return map.beginy;
}


SDL_Texture *recupTileset(void)
{
    return map.tileSet;
}



void mapCollision(Personnage *entite)
{
 
    int i, x1, x2, y1, y2;
    
    //Le héros apparait dans les aires et tombe automatiquement 
    entite->surSol = 0;
    

    // Ici, le but est de tester chaque mouvement horizontal du héros

    if (entite->h > TAILLE_TILE)
        i = TAILLE_TILE;
    else
        i = entite->h;
    
    
    //On lance alors une boucle for infinie car on l'interrompra en fonction des résultats de nos calculs
    for (;;)
    {
        //On va calculer ici les coins de notre sprite à gauche et à droite pour gérer le contact avec une autre texture
        x1 = (entite->x + entite->dirX) / TAILLE_TILE;
        x2 = (entite->x + entite->dirX + entite->w - 1) / TAILLE_TILE;
        
        //Même chose avec y
        y1 = (entite->y) / TAILLE_TILE;
        y2 = (entite->y + i - 1) / TAILLE_TILE;
        
        //On va tester les mouvements initiés dans majJoueur()
        if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
            //Si on a un mouvement à droite
            if (entite->dirX > 0)
            {

                //Test des tiles Power-up
                if (map.tile[y1][x2] >= TILE_POWER_UP_DEBUT && map.tile[y1][x2] <= TILE_POWER_UP_FIN)
                {
                    recupItem(map.tile[y1][x2] - TILE_POWER_UP_DEBUT + 1);
                    
                    //On remplace la tile power-up par une tile transparente
                    map.tile[y1][x2] = 0;
                }


                else if (map.tile[y2][x2] >= TILE_POWER_UP_DEBUT && map.tile[y2][x2] <= TILE_POWER_UP_FIN)
                {
                    recupItem(map.tile[y2][x2] - TILE_POWER_UP_DEBUT + 1);
                    
                    //On remplace la tile power-up par une tile transparente
                    map.tile[y2][x2] = 0;
                }

                //Test de la tile checkpoint
                if (map.tile[y1][x2] == TILE_CHECKPOINT)
                {
                    //On active le booléen checkpoint
                    entite->checkpointActif = 1;
                    
                    //On enregistre les coordonnées
                    entite->respawnX = x2 * TAILLE_TILE;
                    entite->respawnY = (y1 * TAILLE_TILE) - entite->h;
                    
                    //On change la tile
                    map.tile[y1][x2] += 1;
                }

                    else if (map.tile[y2][x2] == TILE_CHECKPOINT)
                {
                    //On active le booléen checkpoint
                    entite->checkpointActif = 1;
                    
                    //On enregistre les coordonnées
                    entite->respawnX = x2 * TAILLE_TILE;
                    entite->respawnY = (y2 * TAILLE_TILE) - entite->h;
                    
                    //On change la tile
                    map.tile[y2][x2] += 1;
                }
 

                //On vérifie si les tiles recouvertes sont solides
                if (map.tile[y1][x2] > SEUIL_TILES_TRAVERSABLES_HAUT || map.tile[y2][x2] > SEUIL_TILES_TRAVERSABLES_HAUT)
                {
                    // Si c'est le cas, on place le joueur très proche de la tile 
        
                    entite->x = x2 * TAILLE_TILE;
                    entite->x -= entite->w + 1;
                    entite->dirX = 0;
                
                }
            }
            
            //Même chose à gauche
            else if (entite->dirX < 0)
            {


                //Test des tiles Power-up : pièces
                if (map.tile[y1][x1] >= TILE_POWER_UP_DEBUT
                && map.tile[y1][x1] <= TILE_POWER_UP_FIN)
                {
                    //On appelle la fonction recupItem()
                    recupItem(map.tile[y1][x1] - TILE_POWER_UP_DEBUT + 1);
                    
                    //On remplace la tile power-up par une tile transparente
                    map.tile[y1][x1] = 0;
                }

                else if (map.tile[y2][x1] >= TILE_POWER_UP_DEBUT
                && map.tile[y2][x1] <= TILE_POWER_UP_FIN)
                {
                    //On appelle la fonction recupItem()
                    recupItem(map.tile[y2][x1] - TILE_POWER_UP_DEBUT + 1);
                    
                    //On remplace la tile power-up par une tile transparente
                    map.tile[y2][x1] = 0;
                }

                //Test de la tile checkpoint
                if (map.tile[y1][x1] == TILE_CHECKPOINT)
                {
                    //On active le booléen checkpoint
                    entite->checkpointActif = 1;
                    
                    //On enregistre les coordonnées
                    entite->respawnX = x1 * TAILLE_TILE;
                    entite->respawnY = (y1 * TAILLE_TILE) - entite->h;
                    
                    //On change la tile
                    map.tile[y1][x1] += 1;
                }
                else if (map.tile[y2][x1] == TILE_CHECKPOINT)
                {
                    //On active le booléen checkpoint
                    entite->checkpointActif = 1;
                    
                    //On enregistre les coordonnées
                    entite->respawnX = x1 * TAILLE_TILE;
                    entite->respawnY = (y2 * TAILLE_TILE) - entite->h;
                    
                    //On change la tile
                    map.tile[y2][x1] += 1;
                }

                if (map.tile[y1][x1] > SEUIL_TILES_TRAVERSABLES_HAUT || map.tile[y2][x1] > SEUIL_TILES_TRAVERSABLES_HAUT)
                {
                    entite->x = (x1 + 1) * TAILLE_TILE;
                    entite->dirX = 0;
                }
            }
        }
        
        //On sort de la boucle si on a testé toutes les tiles le long de la hauteur du sprite
        if (i == entite->h)
        {
            break;
        }
        
        //Sinon, on teste les tiles supérieures en se limitant à la heuteur du sprite
        i += TAILLE_TILE;
        
        if (i > entite->h)
        {
            i = entite->h;
        }
    }
    
    
    //Même chose avec le mouvement vertical du héros

    if (entite->w > TAILLE_TILE)
        i = TAILLE_TILE;
    else
        i = entite->w;
    
    
    for (;;)
    {
        x1 = (entite->x) / TAILLE_TILE;
        x2 = (entite->x + i) / TAILLE_TILE;
        
        y1 = (entite->y + entite->dirY) / TAILLE_TILE;
        y2 = (entite->y + entite->dirY + entite->h) / TAILLE_TILE;
        
        if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
            if (entite->dirY > 0)
            {
                /* Déplacement en bas */


                //Test des tiles Power-up
                if (map.tile[y2][x1] >= TILE_POWER_UP_DEBUT
                && map.tile[y2][x1] <= TILE_POWER_UP_FIN)
                {
                    recupItem(map.tile[y2][x1] - TILE_POWER_UP_DEBUT + 1);
                    
                    //On remplace la tile power-up par une tile transparente
                    map.tile[y2][x1] = 0;
                }
                else if (map.tile[y2][x2] >= TILE_POWER_UP_DEBUT
                && map.tile[y2][x2] <= TILE_POWER_UP_FIN)
                {
                    recupItem(map.tile[y2][x2] - TILE_POWER_UP_DEBUT + 1);
                    
                    //On remplace la tile power-up par une tile transparente
                    map.tile[y2][x2] = 0;
                }
                
                //Test de la tile checkpoint
                if (map.tile[y2][x1] == TILE_CHECKPOINT)
                {
                    //On active le booléen checkpoint
                    entite->checkpointActif = 1;
                    
                    //On enregistre les coordonnées
                    entite->respawnX = (x1 * TAILLE_TILE);
                    entite->respawnY = (y2 * TAILLE_TILE) - entite->h;
                    
                    //On change la tile
                    map.tile[y2][x1] += 1;
                }

                else if (map.tile[y2][x2] == TILE_CHECKPOINT)
                {
                    //On active le booléen checkpoint
                    entite->checkpointActif = 1;
                    
                    //On enregistre les coordonnées
                    entite->respawnX = x2 * TAILLE_TILE;
                    entite->respawnY = (y2 * TAILLE_TILE) - entite->h;
                    
                    //On change la tile
                    map.tile[y2][x2] += 1;
                }
 
                
                /* Gestion des pics */
                if ((map.tile[y2][x1] == TILE_PIKES) || (map.tile[y2][x2] == TILE_PIKES))
                {
                
                    //On tue le joueur intantanément
                    tuerJoueur();
                    
                }

                /* Gestion de la lave */
                if ((map.tile[y2][x1] == TILE_LAVE) || (map.tile[y2][x2] == TILE_LAVE))
                {
                    
                    //On tue le joueur intantanément
                    tuerJoueur();
                    
                }



        
                //Gestion des plateformes traversables 
                if (map.tile[y2][x1] > SEUIL_TILES_TRAVERSABLES || map.tile[y2][x2] > SEUIL_TILES_TRAVERSABLES)
                {
                    //Si la tile est une plateforme ou une tile solide, on y colle le joueur et on le déclare sur le sol 
                    entite->y = y2 * TAILLE_TILE;
                    entite->y -= entite->h;
                    entite->dirY = 0;
                    entite->surSol = 1;
                }
                
            }
        
            else if (entite->dirY < 0)
            {
            
                /* Déplacement vers le haut */

                //Test des tiles Power-up
                if (map.tile[y1][x1] >= TILE_POWER_UP_DEBUT && map.tile[y1][x1] <= TILE_POWER_UP_FIN)
                {
                    recupItem(map.tile[y1][x1] - TILE_POWER_UP_DEBUT + 1);
                    
                    //On remplace la tile power-up par une tile transparente
                    map.tile[y1][x1] = 0;
                }
                if (map.tile[y1][x2] >= TILE_POWER_UP_DEBUT && map.tile[y1][x2] <= TILE_POWER_UP_FIN)
                {
                    recupItem(map.tile[y1][x2] - TILE_POWER_UP_DEBUT + 1);
                    
                    //On remplace la tile power-up par une tile transparente
                    map.tile[y1][x2] = 0;
                }

                //Test de la tile checkpoint
                if (map.tile[y1][x1] == TILE_CHECKPOINT)
                {
                    //On active le booléen checkpoint
                    entite->checkpointActif = 1;
                    
                    //On enregistre les coordonnées
                    entite->respawnX = x1 * TAILLE_TILE;
                    entite->respawnY = (y1 * TAILLE_TILE) - entite->h;
                    
                    //On change la tile
                    map.tile[y1][x1] += 1;
                }
                else if (map.tile[y1][x2] == TILE_CHECKPOINT)
                {
                    //On active le booléen checkpoint
                    entite->checkpointActif = 1;
                    
                    //On enregistre les coordonnées
                    entite->respawnX = x2 * TAILLE_TILE;
                    entite->respawnY = (y1 * TAILLE_TILE) - entite->h;
                    
                    //On change la tile
                    map.tile[y1][x2] += 1;
                }


                if (map.tile[y1][x1] > SEUIL_TILES_TRAVERSABLES_HAUT || map.tile[y1][x2] > SEUIL_TILES_TRAVERSABLES_HAUT)
                {
                    entite->y = (y1 + 1) * TAILLE_TILE;
                    entite->dirY = 0;
                }
            
            }
        }
            
        //On teste la largeur du sprite (même technique que pour la hauteur du sprite)
        if (i == entite->w)
        {
            break;
        }
        
        i += TAILLE_TILE;
        
        if (i > entite->w)
        {
            i = entite->w;
        }
    }
    
    /* Maintenant, on applique les vecteurs de mouvement si le sprite n'est pas bloqué */
    entite->x += entite->dirX;
    entite->y += entite->dirY;
    
    //Et on empèche le dépassement de l'écran.
    if (entite->x < 0)
    {
        entite->x = 0;
    }
    

    else if (entite->x + entite->w >= map.maxX)
    {
        //Si on touche le bord droit de l'écran, on passe au suivant
        changeNiveau(recupNiveau() + 1);

        //Si on dépasse le niveau max, on annule et on limite le déplacement du joueur
        if (recupNiveau() > NIVEAU_MAX)
        {
            changeNiveau(1);
            entite->x = map.maxX - entite->w - 1;

            // Gestion du record
            if(timer < record)
            {
                record = timer;
                record_battu = 1;

                fich = fopen("../record.txt", "w+");
            
                if (fich != NULL)
                {
                    // On l'écrit dans un fichier afin de le garder et de pouvoir le mettre à jour
                    fprintf(fich, "%d", record);
                    fclose(fich);
                }

            }

            Mix_PauseMusic();

            //Dans ce cas on affiche le menu de fin 
            initTypeMenu(1, FIN);

            if(volume == SDL_TRUE)
                chargeMusique("../sounds/castleend.wav");
        }

        //Sinon, on passe au niveau sup, on charge la nouvelle map et on réinitialise le joueur
        else
        {
            //On désactive le checkpoint
            entite->checkpointActif = 0;
            
            chargeNiveau(recupNiveau());
            initJoueur(1);
        }
    }
    
    //S'il sort de l'écran par le bas (chute dans un trou), on lance le timer qui va gérer sa mort et sa réapparition
    if (entite->y > map.maxY)
    {
        entite->timerMort = 60;
    }
}

void collision_map_monstre(Personnage *entite)
{
 
    int i, x1, x2, y1, y2;
    
    entite->surSol = 0;
    
    if (entite->h > TAILLE_TILE)
        i = TAILLE_TILE;

    else
        i = entite->h;
    
    for (;;)
    {
        x1 = (entite->x + entite->dirX) / TAILLE_TILE;
        x2 = (entite->x + entite->dirX + entite->w - 1) / TAILLE_TILE;
        
        y1 = (entite->y) / TAILLE_TILE;
        y2 = (entite->y + i - 1) / TAILLE_TILE;
        
        if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
            //Si on a un mouvement à droite
            if (entite->dirX > 0)
            {
                //On vérifie si les tiles recouvertes sont solides
                if (map.tile[y1][x2] > SEUIL_TILES_TRAVERSABLES_HAUT || map.tile[y2][x2] > SEUIL_TILES_TRAVERSABLES_HAUT)
                {
                    entite->x = x2 * TAILLE_TILE;
                    entite->x -= entite->w + 1;
                    entite->dirX = 0;
                
                }
            
            }
            
            //Même chose à gauche
            else if (entite->dirX < 0)
            {
        
                if (map.tile[y1][x1] > SEUIL_TILES_TRAVERSABLES_HAUT || map.tile[y2][x1] > SEUIL_TILES_TRAVERSABLES_HAUT)
                {
                entite->x = (x1 + 1) * TAILLE_TILE;
                entite->dirX = 0;
                }
        
            }
    
        }
    
        //On sort de la boucle si on a testé toutes les tiles le long de la hauteur du sprite.
        if (i == entite->h)
        {
            break;
        }
        
        //Sinon, on teste les tiles supérieures en se limitant à la heuteur du sprite.
        i += TAILLE_TILE;
        
        if (i > entite->h)
        {
            i = entite->h;
        }
    }
    
    //On recommence la même chose avec le mouvement vertical (axe des Y)
    if (entite->w > TAILLE_TILE)
        i = TAILLE_TILE;
    else
        i = entite->w;
    
    
    for (;;)
    {
        x1 = (entite->x) / TAILLE_TILE;
        x2 = (entite->x + i) / TAILLE_TILE;
        
        y1 = (entite->y + entite->dirY) / TAILLE_TILE;
        y2 = (entite->y + entite->dirY + entite->h) / TAILLE_TILE;
        
        if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
            if (entite->dirY > 0)
            {
            
                /* Déplacement en bas */
                
                if (map.tile[y2][x1] > SEUIL_TILES_TRAVERSABLES || map.tile[y2][x2] > SEUIL_TILES_TRAVERSABLES)
                {
                    entite->y = y2 * TAILLE_TILE;
                    entite->y -= entite->h;
                    entite->dirY = 0;
                    entite->surSol = 1;
                }
            
            }
        
            else if (entite->dirY < 0)
            {
            
                /* Déplacement vers le haut */
                
                if (map.tile[y1][x1] > SEUIL_TILES_TRAVERSABLES_HAUT || map.tile[y1][x2] > SEUIL_TILES_TRAVERSABLES_HAUT)
                {
                    entite->y = (y1 + 1) * TAILLE_TILE;
                    entite->dirY = 0;
                }
        
            }
        }
        
        //On teste la largeur du sprite (même technique que pour la hauteur précédemment)
        if (i == entite->w)
        {
            break;
        }
        
        i += TAILLE_TILE;
        
        if (i > entite->w)
        {
            i = entite->w;
        }
    }
    
    /* Maintenant, on applique les vecteurs de mouvement si le sprite n'est pas bloqué */
    entite->x += entite->dirX;
    entite->y += entite->dirY;
    
    //Et on contraint son déplacement aux limites de l'écran, comme avant.
    if (entite->x < 0)
    {
        entite->x = 0;
    }
    
    else if (entite->x + entite->w >= map.maxX)
    {
        entite->x = map.maxX - entite->w - 1;
    }
    
    //Maintenant, s'il sort de l'écran par le bas, on lance le timer qui gère sa mort et sa réapparition 
    if (entite->y > map.maxY)
    {
        entite->timerMort = 60;
    }
}

