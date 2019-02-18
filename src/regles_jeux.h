/*! 
	\file    regles_jeux.h
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   fichier d'entete de regles_jeux.cpp
	\remarks Fichier qui contient les entêtes de toutes les fonctions et procédures relatives au jeux et à ses règles
*/

#ifndef __DEF_REGLES_JEUX //Pour éviter les inclusions multiples
#define __DEF_REGLES_JEUX


/*! 
	\fn      int jeux_1_VS_1 (etat_jeux ej_jeux)
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   fonction pricipale qui lance le jeux en lui même ( 1 contre 1 sans IA )
	\param   ej_jeux un état du jeux (je jeux au départ)
	\return  1, si le joueur 1 gagne, 2 si le joueur 2 gagne, 0 si execaux
    \remarks aucune	
*/
int jeux_1_VS_1 (etat_jeux ej_jeux);

/*! 
	\fn      int jeux_1_VS_IA (etat_jeux ej_jeux, int int_niveau)
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   fonction pricipale qui lance le jeux en lui même ( 1 contre IA )
	\param   ej_jeux un état du jeux (je jeux au départ)
	\param   int_niveau le niveau de l'IA
	\return  1, si le joueur 1 gagne, 2 si le joueur 2 gagne, 0 si execaux
    \remarks aucune	
*/
int jeux_1_VS_IA (etat_jeux ej_jeux, int int_niveau);

/*! 
	\fn      int jeux_IA_VS_IA (etat_jeux ej_jeux, int int_niveau_ia1, int int_niveau_ia2, int bool_affichage)
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   fonction pricipale qui lance le jeux en lui même ( IA contre IA )
	\param   ej_jeux un état du jeux (je jeux au départ)
	\param   int_niveau_ia1 le niveau de la première IA
	\param   int_niveau_ia2 le niveau de la deuxième IA
	\param   bool_affichage s'il vaut 1 on affiche dans le shell sinon on affiche rien
	\return  1, si le joueur 1 gagne, 2 si le joueur 2 gagne, 0 si execaux
    \remarks Cette fonction nous permez de comparer nos IA et des vraiment voir si elle sont efficace ou pas.	
*/
int jeux_IA_VS_IA (etat_jeux ej_jeux, int int_niveau_ia1, int int_niveau_ia2, int bool_affichage);

/*! 
	\fn      int calcul_nouveau_tableau(etat_jeux* pej_jeux, int int_case, int bool_affichage)
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   procédure qui "calcule" ou "change" l'état du jeux, suivant ses règles, pour le tour suivant.
	\param   pej_jeux le pointeur de l'état du jeux (permet de modifier ce dernier)
	\param   int_case la case que joue le joueur
	\return  rien
	\remarks La utilise un pointeur "pej_jeux" pour passer son adresse et pouvoir modifier la variable "ej_jeux"

*/ 
void calcul_nouveau_tableau(etat_jeux* pej_jeux, int int_case, int bool_affichage);

/*! 
	\fn      int appartient_int_tab(int int_valeur, int* ptint_valeurs, int int_taille_ptint_valeurs)
	\author  Adrien CASSAGNE, Guillem BORIE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   fonction qui regarde si un valeur appartient à un tableau, c'est une fonction de recherche
	\param   int_valeur la valeur que l'on recherche dans le tableau
	\param   ptint_valeurs le tableau de valeurs à parcourir
	\param   int_taille_ptint_valeurs la taille du tableau de valeur à parcourir
	\return  1 si au moins une case du tableau contient int_valeur, 0 sinon
	\remarks Cette fonction est un prédicat (fonction qui dit si c'est vrai ou faux) et retourne en réalité un booléen (0 ou 1)

*/ 
int appartient_int_tab(int int_valeur, int* ptint_valeurs, int int_taille_ptint_valeurs);

/*! 
	\fn      void rajoute_points(etat_jeux* pej_jeux, int int_der_case)
	\author  Adrien CASSAGNE, Guillem BORIE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   cette procédure regarde si elle peut ajouter des points à un joueur, si elle le peut elle le fait sinon elle ne fait rien (c'est cette fonction qui regarde en arrière pour voir si elle peut pas gagner d'autre point dans les cases précèdent à la dernière case)
	\param   pej_jeux le pointeur de l'état du jeux (permet de modifier ce dernier)
	\param   int_der_case la valeur de la derniere case ou l'on s'est arrété
	\return  rien
	\remarks Aucune

*/


void rajoute_points(etat_jeux* pej_jeux, int int_der_case, int* ptint_valeurs, int int_taille_ptint_valeurs);
 

/*! 
	\fn      int fin_de_partie(etat_jeux ej_jeux)
	\author  Guillem BORIE et Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Cette fonction détermine si la partie est terminé ou non et qui la gagne (distribu éventuellement les derniers points)
	\param   pej_jeux l'état actuel du jeux
	\param   int_joueur le joueur qui va jouer
	\return  0 si la partie n'est pas terminé, 1 si la partie est terminé
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
	\brief   Cette fonction détermine si le joueur 1 ou 2 à des graines de son côté
	\param   ej_jeux l'état actuel du jeux
	\param   int_joueur le joueur sur lequel on teste s'il lui reste des graines
	\return  1 si le joueur à des graines (jetons) 0 s'il n'en a plus
	\remarks Aucune

*/ 
int graines_joueur(etat_jeux ej_jeux, int int_joueur);


/*! 
	\fn      int passe_sur_case_ennemi(etat_jeux ej_jeux, int int_joueur, int int_case)
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Cette fonction permet de savoir si la distribution des graines passe chez l'ennemi
	\param   ej_jeux l'état actuel du jeux
	\param   int_case la case que veut joueur le joueur (entre 0 et 11)
	\return  1 si la distribution passe chez l'ennemi, 0 sinon
	\remarks Aucune

*/ 
int passe_sur_case_ennemi(etat_jeux ej_jeux, int int_case);


/*! 
	\fn      int** statistiques_ia(int int_premiere_ia,int int_derniere_ia, int int_indice_stat, int bool_affichage)
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Cette fonction permet d'établir des statistiques de toutes les IA et de déterminer lesquelles sont les plus fortes
	\param   int_premiere_ia première IA à tester
	\param   int_derniere_ia dernière IA à tester
	\param   int_indice_stat indice qui a un impact direct sur le nombre d'affrontement des IA, plus ce nombre est grand plus les statistiques sont justes (mais attention plus il est grand plus c'est long)
	\param   bool_affichage si 1 alors on affiche les résultats, si 0 on n'affiche pas
	\return  le tableau précis des résultats
	\remarks Aucune

*/ 
int** statistiques_ia(int int_premiere_ia, int int_derniere_ia, int int_indice_stat, int bool_affichage);


#endif