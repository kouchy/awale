/*!
	\file    in_out_sdl.h
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   fichier d'entete de in_out_sdl.cpp
	\remarks Fichier qui contient les entêtes de toutes les fonctions et procédures relatives à la saisie et l'affichage en sdl

*/

#ifndef __DEF_IN_OUT_SDL //Pour éviter les inclusions multiples
#define __DEF_IN_OUT_SDL

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#ifdef AWALE_FMOD
#include <fmod.h>
#endif

#define LARGEUR_FENETRE     800
#define HAUTEUR_FENETRE     400
#define HAUTEUR_JEUX        320

/*!
	\struct  elmts_graphiques
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   cette structure permet d'accéder rapidement au élément graphiques pour faciliter leur utilisation
	\remark  aucune
*/
struct elmts_graphiques{
	SDL_Surface *psurf_ecran;
	SDL_Surface	*psurf_image_fond_jeux;
	SDL_Surface *psurf_image_pause;
	SDL_Surface *psurf_image_menu;
	SDL_Surface *psurf_image_bande_bas;
	SDL_Surface	*psurf_texte_pause;
	SDL_Surface *psurf_barre_separation;
	SDL_Surface *psurf_texte_joueur1;
	SDL_Surface *psurf_texte_joueur2;
	SDL_Surface	*psurf_texte_points;
	SDL_Rect position_fond_jeux;
	SDL_Rect position_pause;
	SDL_Rect position_image_menu;
	SDL_Rect position_image_bande_bas;
	SDL_Rect position_texte_pause;
	SDL_Rect position_barre_separation;
	SDL_Rect position_texte_joueur1;
	SDL_Rect position_texte_joueur2;
	SDL_Rect position_points;
	TTF_Font *ppolice_LTO1;
	TTF_Font *ppolice_LTO2;
	SDL_Color couleurBlanche;
};

/*!
	\struct  elmts_sonores
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   cette structure permet d'accéder rapidement au élément sonores pour faciliter leur utilisation
	\remark  aucune
*/
struct elmts_sonores{

	int* bool_son_actif;
#ifdef AWALE_FMOD
	FSOUND_SAMPLE *son_select_menu;
	FSOUND_SAMPLE *son_check;
	FSOUND_SAMPLE *son_distribution;
	FSOUND_SAMPLE *son_win;
	FSOUND_SAMPLE *son_sifflet;
	FSOUND_SAMPLE *son_loose;
#endif

};

/*!
	\fn      int generateur_menu(char** tchar_titres_menu, elmts_graphiques elts_graphs, elmts_sonores elts_sons, etat_jeux ej_jeux)
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   fonction qui génère un menu
	\param   tchar_titres_menu est le tableau des noms de champ que contient le menu
	\param   elts_graphs les éléments graphiques necessaires pour afficher le menu
	\param   elts_sons les élément sonores du menu (et les autres)
	\param	 ej_jeux l'état du jeux actuel
	\param   bool_affiche_etat_jeux un booléen qui détermine si on affiche le jeux (nombres de graines dans les trous) ou pas.
	\return  int la valeur du champ sur lequel l'utilisateur à cliqué
	\remarks Aucune

*/
int generateur_menu(char** tchar_titres_menu, elmts_graphiques elts_graphs, elmts_sonores elts_sons, etat_jeux ej_jeux, int bool_affiche_etat_jeux);


/*!
	\fn      void menu_awale_sdl(int socket, int int_joueur)
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   fonction qui gère les différents menu de l'awalé et lance les parties
	\param   Normalement aucun, les deux param qui son là actuellement ne sont là que pour faire des tests reseaux
	\return  rien
	\remarks Aucune

*/
void menu_awale_sdl(int socket, int int_joueur);



int jeux_1_VS_IA_SDL(etat_jeux ej_jeux, int int_niveau, elmts_graphiques elts_graphs, elmts_sonores elts_sons, int bool_affichage_shell);

int jeux_1_VS_1_SDL(etat_jeux ej_jeux, elmts_graphiques elts_graphs, elmts_sonores elts_sons, int bool_affichage_shell);

#ifdef AWALE_NETWORK
int jeux_1_VS_1_RESEAU_SDL(etat_jeux ej_jeux, elmts_graphiques elts_graphs, elmts_sonores elts_sons, int bool_affichage_shell, int int_joueur, int socket);
#endif

/*
	int_type_de_jeux :
	1 = 1VS1
	2 = 1VS1_RESEAU
	3 = 1VSIA

int lancer_jeux_sdl(int int_type_de_jeux, etat_jeux ej_jeux, elmts_graphiques elts_graphs, elmts_sonores elts_sons, int bool_affichage_shell, int int_joueur, int int_niveau_ia, int socket);
*/

/*!
	\fn      void positions_trous(int tint_positions_trous[12][2])
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Fonction qui initialise le tableau qui contient les positions du centre de tout les trous de l'awalé
	\param   tint_positions_trous[12][2] le tableau des positions => [i][0] = x; [i][1] = y
	\return  rien
	\remarks Permet de changer facilement la position des trous (dans le cas ou le design changerait)

*/
void positions_trous(int tint_positions_trous[12][2]);

/*!
	\fn      void jeux_en_pause(elmts_graphiques elts_graphs) ////// A MODIFIER !!!!!!! \\\\\\
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Fonction qui met le jeux en pause
	\param   elts_graphs les éléments graphique necessaire à la pause en jeux
	\return  rien
	\remarks Aucunes

*/
void jeux_en_pause(elmts_graphiques elts_graphs);

/*!
	\fn      void blit_jeux(elmts_graphiques elts_graphs, etat_jeux ej_jeux, int bool_affiche_etat_jeux)
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Fonction qui blit le jeux en fonction de l'état du jeux, peux aussi juste afficher les images si bool_affiche_etat_jeux = 0;
	\param   elts_graphs les éléments graphiques necessaire pour afficher le jeux en cours
	\param   ej_jeux l'état du jeux à afficher
	\param   bool_affiche_etat_jeux booléen déterminant si on affiche l'état du jeux ou juste les images sans rien
	\return  rien
	\remarks Fonction très souvent utilisé

*/
void blit_jeux(elmts_graphiques elts_graphs, etat_jeux ej_jeux, int bool_affiche_etat_jeux);

/*!
	\fn      void charger_elmts_graphiques(elmts_graphiques* elts_graphs, SDL_Surface *ecran)
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Fonction qui charge les éléments graphiques du jeux dans elts_graphs
	\param   elts_graphs un pointeur vers un type elmts_graphiques
	\param   ecran la surface écran définie de base lors de l'initialisation de SDL
	\return  rien
	\remarks Cette fonction copie l'adresse de la surface écran dans elts_graphs de facon a ce que tout les éléments graphiques soient vraiment contenu dans elts_graphs

*/
void charger_elmts_graphiques(elmts_graphiques* elts_graphs, SDL_Surface *ecran);

/*!
	\fn      void supprimer_elmts_graphiques(elmts_graphiques elts_graphs)
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Fonction qui libère l'espace mémoire occupé par les surface et polices pointé par elts_graphs
	\param   elts_graphs variable qui pointe vers plusieurs surfaces et éléments graphiques
	\return  rien
	\remarks Cette doit etre appellé quand on a plus besoin d'une variable de type elmts_graphiques (important car ce type de variable est très gourmant une fois le chargement effectué)

*/
void supprimer_elmts_graphiques(elmts_graphiques elts_graphs);

/*!
	\fn      void charger_elmts_sonores(elmts_sonores* elts_sons, int bool_son_actif)
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Fonction qui charge les éléments sonores du jeux dans elts_sons
	\param   elts_sons un pointeur vers un type elmts_sonores
	\param   bool_son_actif booléen qui détermine si le son doit etre activé ou pas
	\return  rien
	\remarks Cette focntion initialise, grace a bool_son_actif, l'état sonore (son ou pas son);

*/
void charger_elmts_sonores(elmts_sonores* elts_sons, int bool_son_actif);

/*!
	\fn      void supprimer_elmts_sonores(elmts_sonores elts_sons)
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Fonction qui libère l'espace mémoire occupé par les sons pointé par elts_sons
	\param   elts_sons variable qui pointe vers plusieurs sons
	\return  rien
	\remarks Cette doit etre appellé quand on a plus besoin d'une variable de type elmts_sonores (important car ce type de variable est très gourmant une fois le chargement effectué)

*/
void supprimer_elmts_sonores(elmts_sonores elts_sons);

/*!
	\fn      int animation_distribution_graines(int int_case, etat_jeux* pej_jeux, elmts_graphiques elts_graphs, elmts_sonores elts_sons, int int_vitesse_animation)
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Fonction qui gére l'animation lors de la distribution des graines
	\param   int_case la case que vient de jouer le joueur
	\param   pej_jeux un pointeur vers l'état du jeux avant que le jouer ne joue int_case
	\param	 elts_graphs les éléments graphiques necessaire pour afficher l'animation
	\param   elts_sons les éléments sonores necessaire pour les bruitages durant l'animation
	\param   int_vitesse_animation la vitesse à laquelle la distribution s'effectue (en milliseconde)
	\return  1 normalement et 0 si l'utilisateur veut quitter la partie
	\remarks Cette fonction est directement tiré des la fonction "void calcul_nouveau_tableau(etat_jeux* pej_jeux, int int_case, int bool_affichage);", elle donne donc lieu à une redondance dans le code, mais elle évite de mélanger le centre du jeux avec SDL.

*/
int animation_distribution_graines(int int_case, etat_jeux* pej_jeux, elmts_graphiques elts_graphs, elmts_sonores elts_sons, int int_vitesse_animation);

/*!
	\fn      int attente_et_affichage_sdl(int int_temps_millisecondes, elmts_graphiques elts_graphs, etat_jeux ej_jeux)
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Fonction qui attend le temps donné par (int_temps_millisecondes)
	\param   int_temps_millisecondes le temps que la fonction doit attendre
	\param	 elts_graphs les éléments graphiques necessaire pour afficher le jeux
	\param   ej_jeux l'état du jeux à afficher
	\return  1 normalement et 0 si l'utilisateur veut quitter la partie
	\remarks Fonction qui me permet d'éviter le SDL_Delay() qui gèle tout le prog

*/
int attente_et_affichage_sdl(int int_temps_millisecondes, elmts_graphiques elts_graphs, etat_jeux ej_jeux);

/*!
	\fn      void pause()
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Fonction qui met le prog en pause et attent un évènement pour sortir de ce mode
	\return  rien
	\remarks Aucunes

*/
void pause();

#ifdef AWALE_FMOD
/*!
	\fn      void jouer_un_son(FSOUND_SAMPLE *son_a_jouer, elmts_sonores elts_sons)
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Fonction qui joue un son à la condition que le son soit activé dans le jeux (si il est désactivé alors le son n'est pas joué)
	\param   son_a_jouer le son à jouer
	\param	 elts_sons permet de déterminer si le son est activé ou pas
	\return  rien
	\remarks Aucunes

*/
void jouer_un_son(FSOUND_SAMPLE *son_a_jouer, elmts_sonores elts_sons);
#endif

#endif