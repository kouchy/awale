/*! 
	\file    type.h
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   fichier d'entete de type.cpp
	\remarks Fichier qui contient les ent�tes de toutes les fonctions, proc�dures relatives au type etat_jeux
*/

#ifndef __DEF_TYPE //Pour �viter les inclusions multiples
#define __DEF_TYPE


/*!
	\struct  etat_jeux
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   cette structure permet de d�finir les points des joueurs ainsi que la quantit� et le positionnement des jetons par rapport � un tableau
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
	\brief   accesseur en �criture des points du joueur 1
	\param   pej_jeux le pointeur de l'�tat du jeux (permet de modifier ce dernier)
	\param   int_points_joueur1 le nombre de point que l'on veut mettre au joueur
	\return  rien
	\remarks Tout les accesseurs en �criture utilisent les pointeur pour que l'�tat soit en lecture/�criture

*/ 
void acc_e_points_j1(etat_jeux* pej_jeux, int int_points_joueur1);

/*! 
	\fn      void acc_e_points_j2(etat_jeux* pej_jeux, int int_points_joueur2)
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   accesseur en �criture des points du joueur 2
	\param   pej_jeux le pointeur de l'�tat du jeux (permet de modifier ce dernier)
	\param   int_points_joueur2 le nombre de point que l'on veut mettre au joueur
	\return  rien
	\remarks Tout les accesseurs en �criture utilisent les pointeur pour que l'�tat soit en lecture/�criture

*/ 
void acc_e_points_j2(etat_jeux* pej_jeux, int int_points_joueur2);

/*! 
	\fn      void acc_e_trous(etat_jeux* pej_jeux, int* ptint_trous)
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   accesseur en �criture du tableau entier sh�matisant les trous dans le jeux
	\param   pej_jeux le pointeur de l'�tat du jeux (permet de modifier ce dernier)
	\param   ptint_trous le tableau que l'on veut mettre dans l'�tat
	\return  rien
	\remarks Tout les accesseurs en �criture utilisent les pointeur pour que l'�tat soit en lecture/�criture

*/ 
void acc_e_trous(etat_jeux* pej_jeux, int* ptint_trous);

/*! 
	\fn      void acc_e_trou(etat_jeux* pej_jeux, int int_case,int int_valeur)
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   accesseur en �criture d'une case du tableau sh�matisant les trous dans le jeux
	\param   pej_jeux le pointeur de l'�tat du jeux (permet de modifier ce dernier)
	\param   int_case la case du tableau a modifier
	\param   int_valeur la valeur � mettre dans la case du tableau a modifier
	\return  rien
	\remarks Tout les accesseurs en �criture utilisent les pointeur pour que l'�tat soit en lecture/�criture

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
	\brief   fonction qui cr�e un etat_jeux en fonction des param�tre que l'on lui passe
	\param   int_points_joueur1 les points du joueur 1
	\param   int_points_joueur2 les points du joueur 2
	\param   ptint_trous le tableau des trous qui contienne les jetons
	\return  etat_jeux qui est la base du jeux Awal�
	\remarks Cette fonction ne fait que r�utiliser les pr�c�dent accesseur en �criture pour cr�er et initialiser une varialbe de type "etat_jeux"

*/ 
etat_jeux ini_etat_jeux (int int_points_joueur1, int int_points_joueur2, int* ptint_trous);

/*! 
	\fn      etat_jeux copie_etat_jeux(etat_jeux ej_jeux)
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   fonction qui copie un �tat jeux
	\param   ej_jeux l'etat_jeux � copier
	\return  etat_jeux qui est la copie de ej_jeux pass� en paral
	\remarks Aucune

*/ 
etat_jeux copie_etat_jeux(etat_jeux ej_jeux);


#endif
