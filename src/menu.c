/*!
*  \file       menu.c
*  \brief      S'occupe des fonctions relatives à l'affichage et à la mise à jour des menus
*  \version    1.7
*  \author     Lucas BOUILLON, Arthur SCHERRER, Lucas BEAUFRETON
*  \date 
 */

#include "prototypes.h"

 
int onMenu, menuType, choix, hero = 1;
extern int timer, record, record_battu, timer_reset;
extern int totalPieces, totalMorts;


// Délcarations des différentes textures

SDL_Texture *fond_menu_principal;
SDL_Texture *fond_menu_fin;
SDL_Texture *img_gameover;
SDL_Texture *fleches;
SDL_Texture *volume_on;
SDL_Texture *volume_off;
SDL_Texture *mario;
SDL_Texture *luigi;
SDL_Texture *yoshi;
SDL_Texture *dk;
SDL_Texture *wario;
SDL_Texture *waluigi;
SDL_Texture *totalPiece;
SDL_Texture *totalMort;

SDL_bool volume = SDL_TRUE;

 
int recupStatutMenu(void)
{
    return onMenu;
}
 
int recupTypeMenu(void)
{
    return menuType;
}
 
void initTypeMenu(int valeur, int type)
{
    onMenu = valeur;
    menuType = type;
}
 
void initMenus(void)
{
    fond_menu_principal = chargeImage("../images/title.png");
    fond_menu_fin = chargeImage("../images/fin.png");
    img_gameover = chargeImage("../images/img_gameover.png");
    fleches = chargeImage("../images/fleches.png");
    volume_on = chargeImage("../images/volume.png");
    volume_off = chargeImage("../images/mute.png");
    mario = chargeImage("../images/choix_mario.png");
    luigi = chargeImage("../images/choix_luigi.png");
    yoshi = chargeImage("../images/choix_yoshi.png");
    dk = chargeImage("../images/choix_dk.png");
    wario = chargeImage("../images/choix_wario.png");
    waluigi = chargeImage("../images/choix_waluigi.png");
    totalPiece = chargeImage("../images/piece.png");
    totalMort = chargeImage("../images/mort.png");
}
 
void libereMenus(void)
{
    // Libère la texture du menu principal
    if (fond_menu_principal != NULL)
    {
        SDL_DestroyTexture(fond_menu_principal);
        fond_menu_principal = NULL;
    }

    // Libère la texture du menu de fin
    if (fond_menu_fin != NULL)
    {
        SDL_DestroyTexture(fond_menu_fin);
        fond_menu_fin = NULL;
    }

    // Libère la texture de l'image de fin
    if (img_gameover != NULL)
    {
        SDL_DestroyTexture(img_gameover);
        img_gameover = NULL;
    }

    // Libère la texture des fleches de selection  
    if (fleches != NULL)
    {
        SDL_DestroyTexture(fleches);
        fleches = NULL;
    }

    //Libère la texture des bouttons de volume
    if (volume_on != NULL)
    {
        SDL_DestroyTexture(volume_on);
        volume_on = NULL;
    }

    //Libère la gestion du volume
    if (volume_off != NULL)
    {
        SDL_DestroyTexture(volume_off);
        volume_off = NULL;
    }

    // Libère la texture des héros
    if (mario != NULL)
    {
        SDL_DestroyTexture(mario);
        mario = NULL;
    }

    if (luigi != NULL)
    {
        SDL_DestroyTexture(luigi);
        luigi = NULL;
    }

    if (yoshi != NULL)
    {
        SDL_DestroyTexture(yoshi);
        yoshi = NULL;
    }

    if (dk != NULL)
    {
        SDL_DestroyTexture(dk);
        dk = NULL;
    }

    if (wario != NULL)
    {
        SDL_DestroyTexture(wario);
        wario = NULL;
    }

    if (waluigi != NULL)
    {
        SDL_DestroyTexture(waluigi);
        waluigi = NULL;
    }

    if (totalPiece != NULL)
    {
        SDL_DestroyTexture(totalPiece);
        totalPiece = NULL;
    }

    if (totalMort != NULL)
    {
        SDL_DestroyTexture(totalMort);
        totalMort = NULL;
    }
}
 
 
void majMenuPrincipal(Input *touche)
{
    //Si on appuie sur M
    if(touche->volume == 1)
    {
        //Si volume sur ON
        if(volume == SDL_TRUE)
        {
            volume = SDL_FALSE; //On passe le volume sur off
            Mix_PauseMusic(); //On coupe le son
        }

        //Si volume sur OFF
        else if(volume == SDL_FALSE)
        {
            volume = SDL_TRUE; //On passe le volume sur on
            Mix_ResumeMusic(); //On relance la musique
        }
        touche->volume = 0;
    }

    //Si on appuie sur HAUT
    if (touche->haut == 1)
    {
        //Si choix = O (il est sur start), on le met à 1 
        if (choix == 0)
            choix++;

        //Si choix = 2 (il est sur heros), on le met à 0 
        else if(choix == 2)
            choix-=2;
        
        touche->haut = 0;
    }
 
    //Si on appuie sur BAS
    if (touche->bas == 1)
    {
        //Si choix = 1 (il est sur quit), on le met à 0 (start)
        if (choix == 1)
            choix--;

        //Si choix = 0 (il est sur start), on le met à 2 (heros)
        else if (choix == 0)
            choix+=2;
        
        touche->bas = 0;
    }

    //Choix du héro
    if (touche->droite == 1 && choix == 2)
    {

        if (hero >= 6)
            hero = 1;

        else
            hero++;
        
        touche->droite = 0;
    }
 
    if (touche->gauche == 1 && choix == 2)
    {

        if (hero <= 1)
            hero = 6;

        else
            hero--;
        
        touche->gauche = 0;
    }
 

    //Si on appuie sur Enter et qu'on est sur Start, on charge le premier niveau et on quitte l'état menu
    if (touche->entrer)
    {
        if (choix == 0)
        {
            resetCheckpoint();
            initSpriteJoueur(hero);
            initJoueur(1);
            changeNiveau(1);
            chargeNiveau(recupNiveau());
            
            /* On réinitialise les variables du jeu */
            initNombreDeVies(3);
            initNombreDePieces(0);
            onMenu = 0;
        }
        
        //Sinon on quitte le jeu
        else if (choix == 1)
        {
            exit(0);
        }
        
        touche->entrer = 0;
        touche->saut = 0;
    }
 
}

void majMenuFin(Input *touche)
{
    //Si on appuie sur ECHAP
    if(touche->pause == 1)
    {
        initTypeMenu(1, START);

        if(volume == SDL_TRUE)
            chargeMusique("../sounds/overworld.wav");

        record_battu = 0;
        totalPieces = 0;
        totalMorts = 0;
    }
}

void majMenuGameover(Input *touche)
{
    //On attend 3,7 secondes
    Mix_PauseMusic();
    SDL_Delay(3700);
    initTypeMenu(1, START);

    if(volume == SDL_TRUE)
        chargeMusique("../sounds/overworld.wav");
}
 
 
void majMenuPause(Input *touche)
{

    //Si on appuie sur BAS
    if (touche->bas == 1)
    {
        //Si choix = O (il est sur start), on le met à 1 (quit)
        if (choix == 0)
            choix++;
            
            touche->bas = 0;
    }
    
    //Si on appuie sur HAUT
    if (touche->haut == 1)
    {
        //Si choix = 1 (il est sur Quit), on le met à 0 (Start)
        if (choix == 1)
            choix--;
        
        touche->haut = 0;
    }
 
    //Si on appuie sur Enter et qu'on est sur Start, on recharge le jeu et on quitte l'état menu
    if (touche->entrer)
    {
        if (choix == 0)
        {
            //Si on appuie sur Enter on quitte l'état menu
            onMenu = 0;
            if(volume == SDL_TRUE)
                Mix_ResumeMusic();
        }
        
        //Sinon, on quitte la partie
        else if (choix == 1)
        {
            choix = 0;
            totalMorts = 0;
            totalPieces = 0;
            if(volume == SDL_TRUE)
                chargeMusique("../sounds/overworld.wav");

            menuType = START;
        }
        
        touche->entrer = 0;
        touche->saut = 0;
    }
 
}

void dessineMenuPrincipal(void)
{
 
    //On crée une variable qui contiendra notre texte
    char text[200];
    
    //On affiche l'écran-titre
    dessineImage(fond_menu_principal, 0, 0);
    
    //Si l'option n'est pas en surbrillance, on l'affiche normalement
    if (choix != 0)
    {
        sprintf_s(text, sizeof(text), "START GAME");

        //Ombrage en noir
        afficheTexte(text, 290, 252, 0, 0, 0, 255);
        afficheTexte(text, 288, 250, 255, 255, 255, 255);
    }

    if (choix != 1)
    {
        sprintf_s(text, sizeof(text), "QUIT");

        //Ombrage en noir
        afficheTexte(text, 105, 60, 0, 0, 0, 255);
        afficheTexte(text, 102, 62, 255, 255, 255, 255);
    }

    //On dessine les icones des héros
    if (choix != 2)
    {
        if(hero == 1)
            dessineImage(mario, 340, 322);

        else if(hero == 2)
            dessineImage(luigi, 340, 322);

        else if(hero == 3) 
            dessineImage(yoshi, 340, 322);

        else if(hero == 4)
            dessineImage(dk, 340, 322);

        else if(hero == 5)
            dessineImage(wario, 340, 322);

        else if(hero == 6)
            dessineImage(waluigi, 340, 322);
    }
    
    //Si l'option est en surbrillance, on change la couleur
    if (choix == 0)
    {
        sprintf_s(text, sizeof(text), "START GAME");

        //Ombrage en noir
        afficheTexte(text, 290, 252, 0, 0, 0, 255);
        afficheTexte(text, 288, 250, 255, 255, 0, 255);
    }
    
    else if (choix == 1)
    {
        sprintf_s(text, sizeof(text), "QUIT");

        //Ombrage en noir
        afficheTexte(text, 105, 60, 0, 0, 0, 255);
        afficheTexte(text, 102, 62, 255, 255, 0, 255);
    }

    //On dessine les icones des héros et les flèches de selection
    else if (choix == 2)
    {
        if(hero == 1)
            dessineImage(mario, 340, 322);

        else if(hero == 2)
            dessineImage(luigi, 340, 322);
        else if(hero == 3) 
            dessineImage(yoshi, 340, 322);

        else if(hero == 4)
            dessineImage(dk, 340, 322);

        else if(hero == 5)
            dessineImage(wario, 340, 322);

        else if(hero == 6)
            dessineImage(waluigi, 340, 322);


        dessineImage(fleches, 315, 360);
    }

    //On dessine les boutons de volume
    if(volume == SDL_FALSE)
        dessineImage(volume_off, 750, 20);

    else    
        dessineImage(volume_on, 750, 20);
 
}

void dessineMenuFin(void)
{
 
    //On créé une variable qui contiendra notre texte
    char text[200];
    
    //On affiche le fond d'écran
    dessineImage(fond_menu_fin, 0, 0);

    //On affiche l'image pour le total de pièces
    dessineImage(totalPiece, 300, 210);

    //On affiche l'image pour le total de morts
    dessineImage(totalMort, 430, 210);

    //On écrit le message de fin
    sprintf_s(text, sizeof(text), "** FIN ! **");
    afficheTexte(text, 330, 78, 255, 255, 255, 255);

    //On écrit le temps du joueur
    if(record_battu == 0){
        sprintf_s(text, sizeof(text), "Ton temps         %d", timer);
        afficheTexte(text, 250, 128, 255, 255, 255, 255);
    }

    //On écrit le temps record
    if(record_battu == 0)
        sprintf_s(text, sizeof(text), "Le record          %d", record);

    else
        sprintf_s(text, sizeof(text), "Nouveau record  %d", record);

    afficheTexte(text, 250, 168, 255, 255, 255, 255);

    //On écrit échap en haut à gauche
    sprintf_s(text, sizeof(text), "echap");
    afficheTexte(text, 18, 18, 255, 255, 255, 255);

    //On écrit le nombre total de pièces récupérées
    sprintf_s(text, sizeof(text), "%d", totalPieces);
    afficheTexte(text, 350, 215, 255, 255, 255, 255);

    //On écrit le nombre total de morts
    sprintf_s(text, sizeof(text), "%d", totalMorts);
    afficheTexte(text, 480, 215, 255, 255, 255, 255);

}

void dessineMenuGameover(void)
{
 
    //On crée une variable qui contiendra notre texte
    char text[200];
    
    //On affiche l'écran-titre
    dessineImage(img_gameover, 0, 0);
    
    //On écrit le message de gameover
    sprintf_s(text, sizeof(text), "** GAMEOVER **");
    afficheTexte(text, 267, 230, 0, 0, 0, 255);
    afficheTexte(text, 265, 228, 255, 255, 255, 255);

}
 
 
 
void dessineMenuPause(void)
{
    char text[200];
    
    //On écrit PAUSE
    sprintf_s(text, sizeof(text), "** PAUSE **");
    afficheTexte(text, 282, 200, 0, 0, 0, 255);
    afficheTexte(text, 280, 198, 255, 255, 255, 255);
    
    
    //Si l'option n'est pas en surbrillance, on l'affiche normalement
    if (choix != 0)
    {
        sprintf_s(text, sizeof(text), "Continue");

        //Ombrage en noir
        afficheTexte(text, 306, 252, 0, 0, 0, 255);
        afficheTexte(text, 304, 250, 255, 255, 255, 255);
    }
    if (choix != 1)
    {
        sprintf_s(text, sizeof(text), "Exit");

        //Ombrage en noir
        afficheTexte(text, 346, 292, 0, 0, 0, 255);
        afficheTexte(text, 344, 290, 255, 255, 255, 255);
    }
    
    
    //Si l'option est en surbrillance, on change la couleur
    if (choix == 0)
    {
        sprintf_s(text, sizeof(text), "Continue");

        //Ombrage en noir
        afficheTexte(text, 306, 252, 0, 0, 0, 255);
        afficheTexte(text, 304, 250, 255, 255, 0, 255);
    }

    else if (choix == 1)
    {
        sprintf_s(text, sizeof(text), "Exit");
        
        //Ombrage en noir
        afficheTexte(text, 346, 292, 0, 0, 0, 255);
        afficheTexte(text, 344, 290, 255, 255, 0, 255);
    }
 
}