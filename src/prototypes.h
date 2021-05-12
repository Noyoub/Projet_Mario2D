/*!
 *  \file       prototypes.h
 *  \brief      Ce fichier contient tous les prototypes des fonctions qui vont être utilisées dans le cadre de ce projet
 *  \version    1.7
 *  \author     Lucas BOUILLON, Arthur SCHERRER, Lucas BEAUFRETON
 *  \date 
 */


#ifndef PROTOTYPES
#define PROTOTYPES

#include "structs.h"
 
/* Catalogue des prototypes des fonctions utilisées. */ 

/*! \brief  Gestion du scrolling de la map, centré sur le héros, et adapté à la vitesse de ce dernier.
 *  
 *  param[in]   int valeur  Valeur x
 * 
 *  \return void
 */
extern void scrollSurJoueur(void);

/*! \brief  Charge une nouvelle map en nettoyant la mémoire qui est occupée à ce moment précis
 *      
 *  param[in]   int niveau  niveau choisi
 *
 *  \return void
 */
extern void chargeNiveau(int niveau);

/*! \brief  Nettoie et libère proprement les textures
 *  
 * 
 *  \return void
 */ 
extern void nettoyageHUD(void);

/*! \brief  Nettoie et libère proprement le background et le tileset
 *      
 * 
 *  \return void
 */ 
extern void nettoyageMaps(void);

/*! \brief  Vide la mémoire liée au sprite proprement
 *  
 * 
 *  \return void
 */
extern void nettoyageJoueur(void);

/*! \brief  La fonction quitte tous les outils proprement en libérant la mémoire 
 *  
 *  \return void
 */ 
extern void nettoyageAll(void);

/*! \brief  Libère la police proprement
 *  
 * 
 *  \return void
 */ 
extern void fermeturePolice(void);

/*! \brief  Fonction qui va gérer les FPS pour laisser respirer le processeur de la machine
 *  
 *  \param[in]  unsigned int frameLimit     
 * 
 *  \return void
 */ 
extern void delay(unsigned int frameLimit);

/*! \brief  Affiche à l'écran les différentes interfaces graphiques du jeu
 *  
 *  \param[in] int pauseMenu  
 *
 *  \return void
 */
extern void chargeJeu(int pauseMenu);

/*! \brief  Dessine les compteurs de vie et de pièces sur le rendu
 *  
 * 
 *  \return void
 */ 
extern void dessineHUD(void);

/*! \brief  Dessine une image en fonction des paramètres passés en paramètres
 *  
 *  \param[in]  SDL_Texture *image      Une image
 *  \param[in]  int x                   Coordonnées en abscisses (coin en haut à gauche de l'image)
 *  \param[in]  int y                   Coordonnées en ordonnée (coin en haut à gauche de l'image)
 * 
 *  \return void
 */ 
extern void dessineImage(SDL_Texture *, int, int);

/*! \brief  Dessine la map sur un rendu en récupérant les coordonnées de la matrice pour une couche donnée
 *      
 *  param[in] int couche Nom de la couche à modéliser
 * 
 *  \return void
 */ 
extern void dessineMap(int couche);

/*! \brief  Dessine le héros aux coordonnées récupérées dans la fonction
 *  
 * 
 *  \return void
 */
extern void dessineJoueur(void);

/*! \brief  Dessine le texte sur le rendu pour des coordonnées et une couleur données
 *  
 * 
 *  \param[in]  char *text              Texte à charger
 *  \param[in]  int x                   Coordonnées en abscisse
 *  \param[in]  int y                   Coordonnées en ordonnée 
 *  \param[in]  int r                   Une des valeurs pour la couleur rouge
 *  \param[in]  int g                   Une des valeurs pour la couleur verte
 *  \param[in]  int b                   Une des valeurs pour la couleur bleu
 *  \param[in]  int a                   Opacité 
 * 
 * 
 *  \return void
 */ 
extern void afficheTexte(char *text, int x, int y, int r, int g, int b, int a);

/*! \brief  charge une image dans un rectangle dont les coordonnées sont passées en paramètres
 *  \param[in]  SDL_Texture *image      l'image à charger
 *  \param[in]  int destx               coordonnées x de la destination
 *  \param[in]  int desty               coordonnées y de la destination
 *  \param[in]  int srcx                coordonnées x de la source
 *  \param[in]  int srcy                coordonnées y de la source
 * 
 *  \return void
 */ 
extern void dessineTile(SDL_Texture *image, int destx, int desty, int srcx, int srcy);

/*! \brief  Appelle la fonction recupTouche() 
 *  
 *  param[in]   Input *touche    Une entrée    
 * 
 *  \return void
 */ 
extern void gestionTouches(Input *touche);

/*! \brief  Récupère la texture background
 *      
 * 
 *  \return SDL_Texture
 */
extern SDL_Texture *getBackground(void);

/*! \brief  Récupère les coordonnées en abscisse du début de la map
 *      
 * 
 *  \return int
 */
extern int recupDebutMapX(void);

/*! \brief  Récupère les coordonnées en ordonnée du début de la map
 *      
 * 
 *  \return int
 */ 
extern int recupDebutMapY(void);

/*! \brief  Fonction qui va gérer les touches du clavier, c'est-à-dire qu'elle va boucler sur chaque évènement qui pourra être traité par le jeu.
 *  
 *  param[in]   Input *touche une entrée  
 *
 *  \return void
 */ 
extern void recupTouche(Input *touche);

/*! \brief Récupère l'entier lié au level
 *  
 * 
 *  \return int
 */
extern int recupNiveau(void);

/*! \brief  Récupère les coordonnées en abscisse de la fin de la map
 *      
 * 
 *  \return int
 */ 
extern int recupFinMapX(void);

/*! \brief  Récupère les coordonnées en ordonnée de la fin de la map
 *      
 * 
 *  \return int
 */ 
extern int recupFinMapY(void);

/*! \brief Récupère le nombre de pièce(s)
 *  
 * 
 *  \return int
 */
extern int recupNombreDePieces(void);

/*! \brief Récupère le nombre de vie(s)
 *  
 * 
 *  \return int
 */
extern int recupNombreDeVies(void);

/*! \brief  Récupère le Personnage de player
 *  
 * 
 *  \return Personnage
 */ 
extern Personnage *recupJoueur(void);

/*! \brief  Récupère les coordonnées en abscisse du héros
 *  
 * 
 *  \return int
 */
extern int recupJoueurX(void);

/*! \brief  Récupère les coordonnées en ordonnée du héros
 *  
 * 
 *  \return int
 */
extern int recupJoueurY(void);

/*! \brief  Récupère un rendu
 * 
 *  \return SDL_Renderer
 */ 
extern SDL_Renderer *recupRendu(void);

/*! \brief  Récupère les coordonnées de départ en abscisse du personnage
 *      
 * 
 *  \return int
 */ 
extern int recupPersoStartX(void);

/*! \brief  Récupère les coordonnées de départ en ordonnée du personnage
 *      
 * 
 *  \return int
 */ 
extern int recupPersoStartY(void);

/*! \brief  Récupère le tileSet 
 *      
 * 
 *  \return SDL_Texture
 */ 
extern SDL_Texture *recupTileset(void);

/*! \brief  Initialisation globale des outils SDL
 *  
 *  \param[in]  char *titre  Nom de la fenêtre à générer
 * 
 *  \return void
 */ 
extern void init(char *);

/*! \brief  Charge les images pour les pièces et pour la vie 
 *  
 * 
 *  \return void
 */ 
extern void initHUD(void);

/*! \brief  Charge les images de fond pour un niveau donné.
 *  
 *  \param[in]  int niveau   entier lié à un niveau (1, 2, 3 etc...)
 * 
 *  \return void
 */ 
extern void initMaps(int niveau);

/*! \brief  Charge le spritesheet du héros au début du level
 *  
 * 
 *  \return void
 */
extern void initSpriteJoueur(int hero);

/*! \brief  Initialise le héros dans un niveau donné
 *  
 *  param[in]   int nouveauNiveau  Valeur du niveau dans laquelle il faut charger le héros
 * 
 *  \return void
 */
extern void initJoueur(int nouveauNiveau);

/*! \brief  On charge du texte à l'aide de SDL_TTF dans une taille et une police spécifiée
 *  
 *  param[in] char * nom  Chaine à charger
 *  param[in] int taille     Taille du texte à charger
 * 
 *  \return void
 */
extern void chargePolice(char *nom , int taille);

/*! \brief  S'occupe de charger le jeu, c'est-à-dire la map et le sprite du personnage
 *  
 *  \return void
 */ 
extern void chargementJeu();

/*! \brief  Charge une image de nom *nom
 *  
 *  \param[in]  char *nom  Chaine de caractères correspondant un nom de l'image à charger
 * 
 *  \return SDL_Texture 
 */ 
extern SDL_Texture *chargeImage(char *nom);

/*! \brief  Lis le fichier texte et stocke la map dans des matrices pour pouvoir réutiliser facilement les coordonnées ensuite
 *      
 *  param[in] char *nom    Nom de la map à modéliser
 * 
 *  \return void
 */
extern void chargeMap(char *nom);

/*! \brief  Gère les collisions avec les différentes textures de la map
 *      
 *  param[in]   Personnage *personnage  un personnage (texture animée)
 * 
 *  \return void
 */ 
extern void mapCollision(Personnage *personnage);

/*! \brief Défini le nombre de vie(s)
 *  
 *  param[in]  int valeur  Nombre de vie(s)
 * 
 *  \return int
 */
extern void initNombreDeVies(int valeur);

/*! \brief Initialise le nombre de piece(s)
 *  
 *  param[in]  int valeur  Nombre de pièce(s)
 * 
 *  \return int
 */
extern void initNombreDePieces(int valeur);

/*! \brief  Initialise les coordonnées en abscisse du héros
 *  
 *  param[in]   int valeur  Valeur x
 * 
 *  \return void
 */
extern void initJoueurX(int valeur);

/*! \brief  Initialise les coordonnées en ordonnée du héros
 *  
 *  param[in]   int valeur  Valeur y
 * 
 *  \return void
 */
extern void initJoueurY(int valeur);


/*! \brief  Initialise les coordonnées de départ en abscisse sur la map
 *      
 *  param[in]   int valeur Valeur de la coordonnée
 * 
 *  \return void
 */ 
extern void initDepartMapX(int valeur);

/*! \brief  Initialise les coordonnées de départ en ordonnée sur la map
 *      
 *  param[in]   int valeur  Valeur de la coordonnée
 * 
 *  \return void
 */  
extern void initDepartMapY(int valeur);

/*! \brief  Change la valeur du niveau en cours
 *  
 *  param[in]   int valeur  Valeur du niveau
 * 
 *  \return void
 */
extern void changeNiveau(int valeur);

/*! \brief  Fonction qui met à jour les coordonnées du personnage en fonction de la touche entrée par l'utilisateur
 *  
 *  param[in]   Input *touche Touche entrée par l'utilisateur
 * 
 *  \return void
 */
extern void majJoueur(Input *touche);

/*! \brief  Fonction qui va charger et jouer une musique à l'infini
 *  
 *  param[in]   char filename[200] nom du fichier de la musique
 * 
 *  \return void
 */
extern void chargeMusique(char filename[200]);

/*! \brief  Fonction qui va libérer une musique
 *  
 * 
 *  \return void
 */
extern void libereMusique(void);

/*! \brief  Fonction qui va charger un son
 *  
 * 
 *  \return void
 */
extern void chargeSon(void);

/*! \brief  Fonction qui va libérer un son
 *  
 * 
 *  \return void
 */
extern void libereSon(void);

/*! \brief  Fonction qui va jouer un son en fonction d'un évènement
 *  
 *  param[in]   int type type d'évènement
 * 
 *  \return void
 */
extern void joueSon(int type);

/*! \brief  Fonction qui va récupérer le monstre à l'indice nombre
 *  
 *  param[in]   int nombre indice du monstre
 * 
 *  \return void
 */
extern Personnage *recupMonstre(int nombre);

/*! \brief  Fonction qui va récuperer le nombre de monstres
 *  
 *  \return void
 */
extern int recupNombreMonstres(void);

/*! \brief  Fonction qui va initialiser le nombre de monstre à 0
 *   
 *  \return void
 */
extern void resetMonstres(void);

/*! \brief  Fonction qui va charger le sprite du monstre
 *   
 *  \return void
 */
extern void chargeSpriteMonstre(void);

/*! \brief  Fonction qui va libérer le sprite des monstres
 *   
 *  \return void
 */
extern void libereMonstre(void);

/*! \brief  Fonction qui va initialiser un nouveau monstre aux coordonnées données
 *  
 *  param[in]   int x coordonnée x
 *  param[in]   int y coordonnée y
 * 
 *  \return void
 */
extern void initNouveauMonstre(int x, int y);

/*! \brief  Fonction qui va gérer les déplacements et collisions des monstres
 *   
 *  \return void
 */
extern void majMonstre(void);

/*! \brief  Fonction qui va gérer les collisions entre un monstre et le héro
 *  
 *  param[in]   Personnage *joueur objet héro
 *  param[in]   Personnage *monstre objet monstre
 * 
 *  \return void
 */
extern int collisionMonstreJoueur(Personnage *joueur, Personnage *monstre);

/*! \brief  Fonction qui va vérifier si le monstre est sur le sol
 *  
 *  param[in]   Personnage *monstre objet monstre
 * 
 *  \return void
 */
extern int verifSol(Personnage monstre);

/*! \brief  Fonction qui va dessiner le monstre sur notre rendu
 *  
 *  param[in]   Personnage *monstre objet monstre
 * 
 *  \return void
 */
extern void dessineMonstre(Personnage *monstre);

/*! \brief  Fonction qui va retourner la valeur d'une tile
 *  
 *  param[in]   int x coordonnée x
 *  param[in]   int y coordonnée y
 * 
 *  \return void
 */
extern int recupValeurTile(int y, int x);

/*! \brief  Fonction qui va gérer les collisions entre le monstre et la map
 *  
 *  param[in]   Personnage *monstre objet monstre
 * 
 *  \return void
 */
extern void collision_map_monstre(Personnage *monstre);

/*! \brief  Fonction qui va gérer la mort du héro
 *   
 * 
 *  \return void
 */
extern void tuerJoueur();

/*! \brief  Met à jour les compteurs de pièces et de vies en fonction des power-up (tiles spéciales)
 *  
 *  param[in]   int itemNumber Valeur de l'item
 * 
 *  \return void
 */
extern void recupItem(int itemNumber);

/*! \brief  Fonction qui remet le checkpoint du joueur à 0
 *  
 *  \return void
 */
extern void resetCheckpoint(void);

/*! \brief  Fonction qui renvoi 0 si on est en jeu et 1 si on est dans un menu
 *  
 *  \return void
 */
extern int recupStatutMenu(void);

/*! \brief  Fonction qui renvoi le type de menu actuel
 *  
 *  \return void
 */
extern int recupTypeMenu(void);

/*! \brief  Fonction qui définit si on est dans un menu et quel type de menu
 *  
 *  param[in]   int valeur valeur correspond à jeu ou menu
 *  param[in]   int type valeur correspondant au menu start ou menu pause
 * 
 *  \return void
 */
extern void initTypeMenu(int valeur, int type);

/*! \brief  Fonction qui charge l'image du menu
 *  
 *  \return void
 */
extern void initMenus(void);

/*! \brief  Fonction qui libère l'image du menu
 *  
 *  \return void
 */
extern void libereMenus(void);

/*! \brief  Fonction qui gère les évênements du menu start
 *  
 *  param[in]   Input *touche 
 * 
 *  \return void
 */
extern void majMenuPrincipal(Input *touche);

/*! \brief  Fonction qui gère les évênements du menu pause
 *  
 *  param[in]   Input *touche 
 * 
 *  \return void
 */
extern void majMenuPause(Input *touche);


/*! \brief  Fonction qui gère les évênements du menu gameover
 *  
 *  param[in]   Input *touche 
 * 
 *  \return void
 */
extern void majMenuGameover(Input *touche);

/*! \brief  Fonction qui gère les évênements du menu de fin de partie
 *  
 *  param[in]   Input *touche 
 * 
 *  \return void
 */
extern void majMenuFin(Input *touche);

/*! \brief  Fonction qui dessine le menu start à l'écran
 *  
 *  \return void
 */
extern void dessineMenuPrincipal(void);

/*! \brief  Fonction qui dessine le menu pause à l'écran
 *  
 *  \return void
 */
extern void dessineMenuPause(void);

/*! \brief  Fonction qui dessine le menu de fin de partie à l'écran
 *  
 *  \return void
 */
extern void dessineMenuFin(void);

/*! \brief  Fonction qui dessine le menu de gameover
 *  
 *  \return void
 */
extern void dessineMenuGameover(void);

/*! \brief  Test unitaire sur la fonction verifSol()
 *  
 *  param[in]   Personnage *monstre objet monstre
 * 
 *  \return void
 */
extern int testVerifSol(Personnage monstre);

#endif