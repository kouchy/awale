/*! 
	\file    regles_jeux.h
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   fichier d'entete de regles_jeux.cpp
	\remarks Fichier qui contient les ent�tes de toutes les fonctions et proc�dures relatives au jeux et � ses r�gles
*/

#ifndef __DEF_REGLES_JEUX //Pour �viter les inclusions multiples
#define __DEF_REGLES_JEUX


/*! 
	\fn      int jeux_1_VS_1 (etat_jeux ej_jeux)
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   fonction pricipale qui lance le jeux en lui m�me ( 1 contre 1 sans IA )
	\param   ej_jeux un �tat du jeux (je jeux au d�part)
	\return  1, si le joueur 1 gagne, 2 si le joueur 2 gagne, 0 si execaux
    \remarks aucune	
*/
int jeux_1_VS_1 (etat_jeux ej_jeux);

/*! 
	\fn      int jeux_1_VS_IA (etat_jeux ej_jeux, int int_niveau)
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   fonction pricipale qui lance le jeux en lui m�me ( 1 contre IA )
	\param   ej_jeux un �tat du jeux (je jeux au d�part)
	\param   int_niveau le niveau de l'IA
	\return  1, si le joueur 1 gagne, 2 si le joueur 2 gagne, 0 si execaux
    \remarks aucune	
*/
int jeux_1_VS_IA (etat_jeux ej_jeux, int int_niveau);

/*! 
	\fn      int jeux_IA_VS_IA (etat_jeux ej_jeux, int int_niveau_ia1, int int_niveau_ia2, int bool_affichage)
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   fonction pricipale qui lance le jeux en lui m�me ( IA contre IA )
	\param   ej_jeux un �tat du jeux (je jeux au d�part)
	\param   int_niveau_ia1 le niveau de la premi�re IA
	\param   int_niveau_ia2 le niveau de la deuxi�me IA
	\param   bool_affichage s'il vaut 1 on affiche dans le shell sinon on affiche rien
	\return  1, si le joueur 1 gagne, 2 si le joueur 2 gagne, 0 si execaux
    \remarks Cette fonction nous permez de comparer nos IA et des vraiment voir si elle sont efficace ou pas.	
*/
int jeux_IA_VS_IA (etat_jeux ej_jeux, int int_niveau_ia1, int int_niveau_ia2, int bool_affichage);

/*! 
	\fn      int calcul_nouveau_tableau(etat_jeux* pej_jeux, int int_case, int bool_affichage)
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   proc�dure qui "calcule" ou "change" l'�tat du jeux, suivant ses r�gles, pour le tour suivant.
	\param   pej_jeux le pointeur de l'�tat du jeux (permet de modifier ce dernier)
	\param   int_case la case que joue le joueur
	\return  rien
	\remarks La utilise un pointeur "pej_jeux" pour passer son adresse et pouvoir modifier la variable "ej_jeux"

*/ 
void calcul_nouveau_tableau(etat_jeux* pej_jeux, int int_case, int bool_affichage);

/*! 
	\fn      int appartient_int_tab(int int_valeur, int* ptint_valeurs, int int_taille_ptint_valeurs)
	\author  Adrien CASSAGNE, Guillem BORIE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   fonction qui regarde si un valeur appartient � un tableau, c'est une fonction de recherche
	\param   int_valeur la valeur que l'on recherche dans le tableau
	\param   ptint_valeurs le tableau de valeurs � parcourir
	\param   int_taille_ptint_valeurs la taille du tableau de valeur � parcourir
	\return  1 si au moins une case du tableau contient int_valeur, 0 sinon
	\remarks Cette fonction est un pr�dicat (fonction qui dit si c'est vrai ou faux) et retourne en r�alit� un bool�en (0 ou 1)

*/ 
int appartient_int_tab(int int_valeur, int* ptint_valeurs, int int_taille_ptint_valeurs);

/*! 
	\fn      void rajoute_points(etat_jeux* pej_jeux, int int_der_case)
	\author  Adrien CASSAGNE, Guillem BORIE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   cette proc�dure regarde si elle peut ajouter des points � un joueur, si elle le peut elle le fait sinon elle ne fait rien (c'est cette fonction qui regarde en arri�re pour voir si elle peut pas gagner d'autre point dans les cases pr�c�dent � la derni�re case)
	\param   pej_jeux le pointeur de l'�tat du jeux (permet de modifier ce dernier)
	\param   int_der_case la valeur de la derniere case ou l'on s'est arr�t�
	\return  rien
	\remarks Aucune

*/


void rajoute_points(etat_jeux* pej_jeux, int int_der_case, int* ptint_valeurs, int int_taille_ptint_valeurs);
 

/*! 
	\fn      int fin_de_partie(etat_jeux ej_jeux)
	\author  Guillem BORIE et Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Cette fonction d�termine si la partie est termin� ou non et qui la gagne (distribu �ventuellement les derniers points)
	\param   pej_jeux l'�tat actuel du jeux
	\param   int_joueur le joueur qui va jouer
	\return  0 si la partie n'est pas termin�, 1 si la partie est termin�
	\remarks Aucune

*/ 
int fin_de_partie(etat_jeux* pej_jeux, int int_joueur); /////////////////// A CODER ///////////////////////////


/*! 
	\fn      int test_affame(etat_jeux* pej_jeux, int int_der_case, int* ptint_valeurs, int int_taille_ptint_valeurs)
	\author  Guillem BORIE
	\version 0.1
	\brief   Cette permet de savoir quand l'on "affame" (prend toute les graines) notre adversaire
	\param   pej_jeux
	\param   int_der_case
	\param   ptint_valeurs
	\param   int_taille_ptint_valeurs
	\return  1 si le coup prend toute les graines au joueur, 0 sinon
	\remarks Aucune

*/
int test_affame(etat_jeux* pej_jeux, int int_der_case, int* ptint_valeurs, int int_taille_ptint_valeurs);

/*! 
	\fn      int graines_joueur(etat_jeux ej_jeux, int int_joueur)
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Cette fonction d�termine si le joueur 1 ou 2 � des graines de son c�t�
	\param   ej_jeux l'�tat actuel du jeux
	\param   int_joueur le joueur sur lequel on teste s'il lui reste des graines
	\return  1 si le joueur � des graines (jetons) 0 s'il n'en a plus
	\remarks Aucune

*/ 
int graines_joueur(etat_jeux ej_jeux, int int_joueur);


/*! 
	\fn      int passe_sur_case_ennemi(etat_jeux ej_jeux, int int_joueur, int int_case)
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Cette fonction permet de savoir si la distribution des graines passe chez l'ennemi
	\param   ej_jeux l'�tat actuel du jeux
	\param   int_case la case que veut joueur le joueur (entre 0 et 11)
	\return  1 si la distribution passe chez l'ennemi, 0 sinon
	\remarks Aucune

*/ 
int passe_sur_case_ennemi(etat_jeux ej_jeux, int int_case);


/*! 
	\fn      int** statistiques_ia(int int_premiere_ia,int int_derniere_ia, int int_indice_stat, int bool_affichage)
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Cette fonction permet d'�tablir des statistiques de toutes les IA et de d�terminer lesquelles sont les plus fortes
	\param   int_premiere_ia premi�re IA � tester
	\param   int_derniere_ia derni�re IA � tester
	\param   int_indice_stat indice qui a un impact direct sur le nombre d'affrontement des IA, plus ce nombre est grand plus les statistiques sont justes (mais attention plus il est grand plus c'est long)
	\param   bool_affichage si 1 alors on affiche les r�sultats, si 0 on n'affiche pas
	\return  le tableau pr�cis des r�sultats
	\remarks Aucune

*/ 
int** statistiques_ia(int int_premiere_ia, int int_derniere_ia, int int_indice_stat, int bool_affichage);


#endif