/*! 
	\file    type.h
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   fichier d'entete de type.cpp
	\remarks Fichier qui contient les entêtes de toutes les fonctions, procédures relatives au type etat_jeux
*/

#ifndef __DEF_TYPE //Pour éviter les inclusions multiples
#define __DEF_TYPE


/*!
	\struct  etat_jeux
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   cette structure permet de définir les points des joueurs ainsi que la quantité et le positionnement des jetons par rapport à un tableau
	\remark  aucune
*/

struct etat_jeux{
	int int_points_joueur1; ///<Points du joueur 1
	int int_points_joueur2; ///<Points du joueur 2
	int tint_trous[12]; ///<Tableau des jetons
};

/*! 
	\fn      void acc_e_points_j1(etat_jeux* pej_jeux, int int_points_joueur1)
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   accesseur en écriture des points du joueur 1
	\param   pej_jeux le pointeur de l'état du jeux (permet de modifier ce dernier)
	\param   int_points_joueur1 le nombre de point que l'on veut mettre au joueur
	\return  rien
	\remarks Tout les accesseurs en écriture utilisent les pointeur pour que l'état soit en lecture/écriture

*/ 
void acc_e_points_j1(etat_jeux* pej_jeux, int int_points_joueur1);

/*! 
	\fn      void acc_e_points_j2(etat_jeux* pej_jeux, int int_points_joueur2)
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   accesseur en écriture des points du joueur 2
	\param   pej_jeux le pointeur de l'état du jeux (permet de modifier ce dernier)
	\param   int_points_joueur2 le nombre de point que l'on veut mettre au joueur
	\return  rien
	\remarks Tout les accesseurs en écriture utilisent les pointeur pour que l'état soit en lecture/écriture

*/ 
void acc_e_points_j2(etat_jeux* pej_jeux, int int_points_joueur2);

/*! 
	\fn      void acc_e_trous(etat_jeux* pej_jeux, int* ptint_trous)
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   accesseur en écriture du tableau entier shématisant les trous dans le jeux
	\param   pej_jeux le pointeur de l'état du jeux (permet de modifier ce dernier)
	\param   ptint_trous le tableau que l'on veut mettre dans l'état
	\return  rien
	\remarks Tout les accesseurs en écriture utilisent les pointeur pour que l'état soit en lecture/écriture

*/ 
void acc_e_trous(etat_jeux* pej_jeux, int* ptint_trous);

/*! 
	\fn      void acc_e_trou(etat_jeux* pej_jeux, int int_case,int int_valeur)
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   accesseur en écriture d'une case du tableau shématisant les trous dans le jeux
	\param   pej_jeux le pointeur de l'état du jeux (permet de modifier ce dernier)
	\param   int_case la case du tableau a modifier
	\param   int_valeur la valeur à mettre dans la case du tableau a modifier
	\return  rien
	\remarks Tout les accesseurs en écriture utilisent les pointeur pour que l'état soit en lecture/écriture

*/ 
void acc_e_trou(etat_jeux* pej_jeux, int int_case,int int_valeur);

/*! 
	\fn      int acc_l_trous(etat_jeux ej_jeux, int int_case)
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   accesseur en lecture d'une case du tableau de trous
	\param   ej_jeux de type etat_jeux
	\param   int_case la case du tableau que l'on veut lire
	\return  int une entier qui est la case que l'on demande
	\remarks Tout les accesseurs en lecture retourne une variable du type du membre de la structure

*/ 
int acc_l_trous(etat_jeux ej_jeux, int int_case);

/*! 
	\fn      int acc_l_points_j1(etat_jeux ej_jeux)
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   accesseur en lecture des points du joueur 1
	\param   ej_jeux de type etat_jeux
	\return  int une entier qui est le nombre de points du joueur 1
	\remarks Tout les accesseurs en lecture retourne une variable du type du membre de la structure

*/ 
int acc_l_points_j1(etat_jeux ej_jeux);

/*! 
	\fn      int acc_l_points_j2(etat_jeux ej_jeux)
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   accesseur en lecture des points du joueur 2
	\param   ej_jeux de type etat_jeux
	\return  int une entier qui est le nombre de points du joueur 2
	\remarks Tout les accesseurs en lecture retourne une variable du type du membre de la structure

*/ 
int acc_l_points_j2(etat_jeux ej_jeux);


/*! 
	\fn      etat_jeux ini_etat_jeux (int int_points_joueur1, int int_points_joueur2, int* ptint_trous)
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   fonction qui crée un etat_jeux en fonction des paramètre que l'on lui passe
	\param   int_points_joueur1 les points du joueur 1
	\param   int_points_joueur2 les points du joueur 2
	\param   ptint_trous le tableau des trous qui contienne les jetons
	\return  etat_jeux qui est la base du jeux Awalé
	\remarks Cette fonction ne fait que réutiliser les précèdent accesseur en écriture pour créer et initialiser une varialbe de type "etat_jeux"

*/ 
etat_jeux ini_etat_jeux (int int_points_joueur1, int int_points_joueur2, int* ptint_trous);

/*! 
	\fn      etat_jeux copie_etat_jeux(etat_jeux ej_jeux)
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   fonction qui copie un état jeux
	\param   ej_jeux l'etat_jeux à copier
	\return  etat_jeux qui est la copie de ej_jeux passé en paral
	\remarks Aucune

*/ 
etat_jeux copie_etat_jeux(etat_jeux ej_jeux);


#endif
