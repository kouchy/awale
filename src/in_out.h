/*! 
	\file    in_out.h
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   fichier d'entete de in_out.cpp
	\remarks Fichier qui contient les entêtes de toutes les fonctions et procédures relatives à la saisie et l'affichage

*/

#ifndef __DEF_IN_OUT //Pour éviter les inclusions multiples
#define __DEF_IN_OUT 


/*! 
	\fn      void pause(float float_temps)
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Met le shell en pause
	\param   float_temps en miliseconde
	\return  rien
	\remarks La fonction utilise un appel système, elle a été créé pour la portabilité

*/ 
void pause(float float_temps);

/*! 
	\fn      void effacer_affichage()
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Efface le contenu du shell
	\return  rien
	\remarks La fonction utilise un appel système, elle a été créé pour la portabilité

*/ 
void effacer_affichage();

/*! 
	\fn      void affiche_presentation_jeux()
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Affiche la bande de présentation du jeux en shell
	\return  rien
	\remarks Aucune

*/ 
void affiche_presentation_jeux();

/*! 
	\fn      void affiche_etat_jeux(etat_jeux ej_jeux)
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Affiche un état du jeux dans le shell à un état donné
	\param   ej_jeux un état du jeux
	\return  rien
	\remarks Aucune

*/ 
void affiche_etat_jeux(etat_jeux ej_jeux);

/*! 
	\fn      void affiche_etat_jeux(etat_jeux ej_jeux)
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Affiche l'état du jeux en fin de partie
	\param   ej_jeux un état du jeux
	\param   bool_affichage si 1, on affiche le vainquer à l'écran, si 0 on ne l'affiche pas
	\return  1 si le joueur 1 gagne, 2 si le joueur 2 gagne, 0 s'ils sont exécaux
	\remarks Aucune

*/ 
int affiche_et_retourne_vainqueur(etat_jeux ej_jeux, int bool_affichage); //A CODER /////////////////////////////////////////////////////

/*! 
	\fn      int saisir_case(int int_joueur)
	\author  Adrien CASSAGNE, Guillem BORIE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   fonction qui demande une case entre 1 et 6 pour les deux joueur
	\param   int_joueur l'indicateur du joueur
	\return  un entier compris entre 1 et 6
	\remarks Cette fonction estdirectement utilisé par la fonction saisir_case_verif. l'objectif de saisir_case est d'être à terme remplacé par une fonction du même nom mais en SQL (Graphique)

*/ 
int saisir_case();


/*! 
	\fn      int saisir_case_verif(etat_jeux ej_jeux, int int_joueur)
	\author  Adrien CASSAGNE, Guillem BORIE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   fonction qui demande une case entre 1 et 6 pour les deux joueur et suivant si c'est le joueur 1 ou 2 retourne la bonne case du tableau correspondante (ex : joueur 2 tape 6, la case est alors 11)
	\param   ej_jeux l'état du jeux
	\param   int_joueur l'indicateur du joueur
	\return  un entier représentant une case (entre 0 et 11 compris)
	\remarks Cette fonction utilise directement la fonction saisir_case mais fait des vérifications et des calculs dessus (ex : saisir case retourn 4 et le joueur est le 2 alors saisir_case_verif retourne 9). De plus elle effectue une série de test selon les règles du jeux afin de savoir si le joueur à le droit de jouer la case qu'il veut jouer.

*/ 
int saisir_case_verif(etat_jeux ej_jeux, int int_joueur);

/*! 
	\fn      int nb_chiffres(int int_nombre)
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Fonction qui compte le nombre de chiffre qu'il y a dans un nombre
	\param   int_nombre un nombre entier
	\return  le nombre de chiffre que contient int_nombre
	\remarks Utile au niveau de l'affiche quand on a un nombre a deux chiffre on peut le prévoir et afficher correctement (en shell)

*/ 
int nb_chiffres(int int_nombre);


/*! 
	\fn      int* cases_jouables(etat_jeux ej_jeux, int int_joueur)
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Fonction qui retourne un tableau des cases qui sont possibles de joueur selon les règles de l'awalé
	\param   ej_jeux le jeux actuel
	\param   int_joueur le numéro du joueur (1 ou 2)
	\return  int* un tableau qui contient les cases jouables (la case 0 contient le nombre de case jouable)
	\remarks Aucune

*/ 
int* cases_jouables(etat_jeux ej_jeux, int int_joueur);

/*! 
	\fn      void menu_jeux()
	\author  Adrien CASSAGNE <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Fonction qui lance le menu du jeux en shell(permet de choisir les différents types de jeux)
	\return  rien
	\remarks Aucune

*/ 
void menu_jeux_shell();




#endif