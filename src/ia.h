/*! 
	\file    ia.h
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   fichier d'entete de ia.cpp
	\remarks Fichier qui contient les entêtes de toutes les fonctions et procédures relatives à l'intelligence artificielle

*/

#ifndef __DEF_IA_ //Pour éviter les inclusions multiples
#define __DEF_IA_


/*! 
	\fn      int jouer_IA(etat_jeux ej_jeux, int int_niveau, int int_joueur)
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   C'est la fonction centrale de l'intelligence artificielle, elle retourne le coup que va jouer l'IA
	\param   ej_jeux l'état actuel du jeux
	\param   int_niveau le niveau de l'IA (compris entre 1 et 3)
	\param   int_joueur le joueur que joue l'IA
	\return  un entier compris entre 6 et 11 
	\remarks Aucune

*/ 
int jouer_IA(etat_jeux ej_jeux, int int_niveau, int int_joueur);

/*! 
	\fn      int** meilleur_coup_attaque(etat_jeux ej_jeux, int int_joueur)
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Fonction qui retourne un tableau des cases qui permette de prendre le maximum de case a l'adversaire
	\param   ej_jeux l'état actuel du jeux
	\param   int_joueur le joueur que joue l'IA
	\return  une tableau d'entier en 2D
	\remarks Tableau 2D, [0][0] taille du tableau [0][i], [1][0] valeur des cases du tableau à jouer

*/ 
int** meilleur_coup_attaque(etat_jeux ej_jeux, int int_joueur);

/*! 
	\fn      int** tableau_des_gains(etat_jeux ej_jeux, int int_joueur)
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Fonction qui retourne un tableau 2D contenant les gains qu'enjendre chaque case que l'on peut jouer.
	\param   ej_jeux l'état actuel du jeux
	\param   int_joueur le joueur que joue l'IA
	\return  une tableau d'entier en 2D
	\remarks Tableau 2D, [0][0] taille du tableau, [0][1] le max des gains, [1][i] cases, [2][i] valeur des gains correspondant aux cases.

*/ 
int** tableau_des_gains(etat_jeux ej_jeux, int int_joueur);

/*! 
	\fn      int** tableau_des_pertes(etat_jeux ej_jeux, int int_joueur)
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Fonction qui retourne un tableau 2D contenant les pertes qu'enjendre chaque case que l'on peut jouer.
	\param   ej_jeux l'état actuel du jeux
	\param   int_joueur le joueur que joue l'IA
	\return  une tableau d'entier en 2D
	\remarks Tableau 2D, [0][0] taille du tableau, [0][1] le max des pertes, [1][i] cases, [2][i] valeur des gains correspondant aux cases.

*/ 
int** tableau_des_pertes(etat_jeux ej_jeux, int int_joueur);

/*! 
	\fn      int** tableau_des_gains_hypothetiques(etat_jeux ej_jeux, int int_joueur)
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Fonction qui retourne un tableau 2D contenant les gains hypothetiques du tour suivant
	\param   ej_jeux l'état actuel du jeux
	\param   int_joueur le joueur que joue l'IA
	\return  une tableau d'entier en 2D
	\remarks Tableau 2D, [0][0] taille du tableau, [0][1] le max des gains, [0][2] le max des chances de réussite, [1][i] cases, [2][i] valeur des gains correspondant aux cases, [3][i] valeur des chances de réaliser ces gain (en %)

*/ 
int** tableau_des_gains_hypothetiques(etat_jeux ej_jeux, int int_joueur);

/*! 
	\fn      int arrondir(float float_nombre)
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Fonction qui retourne un tableau 2D contenant les gains hypothetiques du tour suivant
	\param   float_nombre un réel
	\return  un arrondi entier du nombre réel
	\remarks Aucune

*/ 
int arrondir(double double_nombre);

#endif