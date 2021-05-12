/*!
*  \file       sons.c
*  \brief      S'occupe de charger les sons et musiques
*  \version    1.7
*  \author     Lucas BOUILLON, Arthur SCHERRER, Lucas BEAUFRETON
*  \date 
 */

#include "prototypes.h"
 
 
 
//Sons Fx
Mix_Chunk *pause_sound, *jump_sound, *coin_sound, *mob_sound, *mort_sound, *gameover_sound;
 
//Musique
Mix_Music *musique;
 
void chargeMusique(char filename[200])
{
 
    /* On libère la chanson précédente s'il y en a une */
    if (musique != NULL)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(musique);
    }
    
    /* On charge la nouvelle chanson */
    musique = Mix_LoadMUS(filename);
    if (musique == NULL)
    {
        fprintf(stderr, "Impossible de lire la musique. \n");
        exit(1);
    }
    
    /* On active la répétition de la musique à l'infini */
    if (Mix_PlayMusic(musique, -1) == -1)
    {
        printf("Mix_PlayMusic: %s\n", Mix_GetError());
    }
 
}
 
 
void libereMusique(void)
{
    /* On libère la musique */
    if (musique != NULL)
        Mix_FreeMusic(musique);
}
 
 
void chargeSon(void)
{
 
    pause_sound = Mix_LoadWAV("../sounds/pause.wav");
    if (pause_sound == NULL)
    {
        fprintf(stderr, "Impossible de lire le son de mob\n");
        exit(1);
    }
    
    jump_sound = Mix_LoadWAV("../sounds/jump.wav");
    if (jump_sound == NULL)
    {
        fprintf(stderr, "Impossible de lire le son de saut du héro \n");
        exit(1);
    }
    
    coin_sound = Mix_LoadWAV("../sounds/coin.wav");
    if (coin_sound == NULL)
    {
        fprintf(stderr, "Impossible de lire le son des pièces \n");
        exit(1);
    }

    mob_sound = Mix_LoadWAV("../sounds/blockbreak.wav");
    if (mob_sound == NULL)
    {
        fprintf(stderr, "Impossible de lire le son de mob \n");
        exit(1);
    }

    mort_sound = Mix_LoadWAV("../sounds/death.wav");
    if(mort_sound == NULL)
    {
        fprintf(stderr, "Impossible de lire le son de mort du héro \n");
        exit(1);

    }

    gameover_sound = Mix_LoadWAV("../sounds/gameover.wav");
    if(mort_sound == NULL)
    {
        fprintf(stderr, "Impossible de lire le son de gameover \n");
        exit(1);

    }

    // On baisse le volume car il est très fort sinon...

    Mix_VolumeChunk(pause_sound, MIX_MAX_VOLUME/4);
    Mix_VolumeChunk(jump_sound, MIX_MAX_VOLUME/4);
    Mix_VolumeChunk(coin_sound, MIX_MAX_VOLUME/4);
    Mix_VolumeChunk(mob_sound, MIX_MAX_VOLUME/4);
    Mix_VolumeChunk(mort_sound, MIX_MAX_VOLUME/4);
    Mix_VolumeChunk(gameover_sound, MIX_MAX_VOLUME/4);

 
}
 
 
void libereSon(void)
{
    // On libère la mémoire liée à chaque musique
 
    Mix_FreeChunk(pause_sound);
    Mix_FreeChunk(jump_sound);
    Mix_FreeChunk(coin_sound);
    Mix_FreeChunk(mob_sound);
    Mix_FreeChunk(mort_sound);
    Mix_FreeChunk(gameover_sound);
    
}
 
 
void joueSon(int type)
{

    // Gestion des états de la partie et/ou du joueur
 
    switch (type)
    {
    
        case PAUSE_GAME:
            Mix_PlayChannel(-1, pause_sound, 0);
            break;
        
        case JUMP:
            Mix_PlayChannel(-1, jump_sound, 0);
            break;
        
        case COIN:
            Mix_PlayChannel(-1, coin_sound, 0);
            break;

        case MORT_HERO:
            Mix_PlayChannel(-1, mort_sound, 0);
            break;
            
        case MORT_MOB:
            Mix_PlayChannel(-1, mob_sound, 0);
            break;
        case GAME_OVER:
            Mix_PlayChannel(-1, gameover_sound, 0);
            break;
    
    }
 
}