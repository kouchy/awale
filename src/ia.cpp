/*!
	\file    ia.cpp
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Fichier qui contient les fonctions et procédures relatives à l'intelligence artificielle
	\remarks Aucune

*/

#include <stdlib.h>
#include <stdio.h>
//#include <windows.h>

#include "type.h"
#include "regles_jeux.h"
#include "in_out.h"
#include "ia.h"

int jouer_IA(etat_jeux ej_jeux, int int_niveau, int int_joueur){

	int** tint_ncases_et_nbpoints = NULL;
	int** tint_tab_gain = NULL;
	int** tint_tab_pertes = NULL;
	int** tint_points_hypothetiques = NULL;
	int tint_diff[6];
	int tint_perte_zero[7];
	int tint_diff_max_gain[7];
	int tint_diff_max_gain2[6];
	int tint_max_points_hypothetiques[7];
	int int_max_gain;
	int int_nb_case;
	int int_max_chance_hypothetiques;
	int int_max_gain_hypothetiques;
	int int_case_jouer=0;
	int bool_test1=0;
	int bool_test2=0;
	int bool_passage=0;


	//Cette IA ne regarde pas si elle se fait manger des graines, elle cherche uniquement a manger des graines de l'adversaire, c'est la plus faible des 3 IA
	if(int_niveau == 1 || int_niveau == 2){

		//On récupère le tableau des meilleurs coup d'attaque possible
		tint_ncases_et_nbpoints = meilleur_coup_attaque(ej_jeux, int_joueur);

		//On tire une case au sort parmis les meilleures
		int_nb_case = (rand() % tint_ncases_et_nbpoints[0][0]);
		int_case_jouer = tint_ncases_et_nbpoints[1][int_nb_case];


		/* DEBUG ////
		printf("\n\n");
		printf("nb case : %d\n", tint_ncases_et_nbpoints[0][0]);
		printf("nb points max : %d\n\n", tint_ncases_et_nbpoints[0][1]);
		for(int i=0; i<tint_ncases_et_nbpoints[0][0]; i++){
			printf("Case %d\n", tint_ncases_et_nbpoints[1][i]);
		}
		printf("\n");
		system("PAUSE");
		//pause(10000);
		*/ //////

		//Libération de l'espace mémoire utilisé
		free(tint_ncases_et_nbpoints[0]);
		free(tint_ncases_et_nbpoints[1]);
		free(tint_ncases_et_nbpoints);

	}

	//L'objectif de cette IA est de privilégier la défence avant tout et mangé si il n'y a aucun danger(sauf si elle est coincé, dans ce cas elle va essayer de manger meme si elle se fait manger), c'est une IA moyenne
	if(int_niveau == 2){
		tint_tab_pertes = tableau_des_pertes(ej_jeux, int_joueur);//On récupère le tableau des pertes

		tint_perte_zero[0] = 0;
		int j=1;
		for(int i=0; i<tint_tab_pertes[0][0]; i++){
			if(tint_tab_pertes[2][i] != 0){
				bool_test1 = 1;
			}
			if(tint_tab_pertes[2][i] == 0){
				bool_test2 = 1;
				tint_perte_zero[0]++;
				tint_perte_zero[j] = tint_tab_pertes[1][i];
				j++;
			}

		}

		//Si il y a des pertes et la possibilité des les éviter alors on joue pour les éviter
		if(bool_test1 && bool_test2){

			int_nb_case = (rand() % tint_perte_zero[0]) + 1;
			int_case_jouer = tint_perte_zero[int_nb_case];

		}

		//Libération de l'espace mémoire occupé
		free(tint_tab_pertes[0]);
		free(tint_tab_pertes[1]);
		free(tint_tab_pertes[2]);
		free(tint_tab_pertes);

	}

	//L'objectif de cette IA est de choisir la case qui permet d'avoir le maximum de gain meme si il faut se faire prendre des graines pour y arriver, cette IA commence à etre difficile à battre.
	if(int_niveau == 3 || int_niveau == 4 || int_niveau == 5){

		tint_tab_gain = tableau_des_gains(ej_jeux, int_joueur);//On récupère le tableau des gains
		tint_tab_pertes = tableau_des_pertes(ej_jeux, int_joueur);//On récupère le tableau des pertes

		for(int i=0; i<tint_tab_gain[0][0] ; i++){
			tint_diff[i] = tint_tab_gain[2][i] - tint_tab_pertes[2][i];

			if( i == 0 ){
				int_max_gain = tint_diff[i];
			}else{
				if(tint_diff[i] > int_max_gain){
					int_max_gain = tint_diff[i];
				}
			}

		}

		int j=1;
		tint_diff_max_gain[0] = 0;
		for(int i=0; i<tint_tab_gain[0][0] ; i++){
			if(tint_diff[i] >= int_max_gain){
				tint_diff_max_gain[0]++; //Au rajoute un élément au tableau
				tint_diff_max_gain[j] = tint_tab_pertes[1][i]; //On récupère la case a jouer
				j++;
			}
		}

		/* DEBUG ////
		printf("\n\n");
		printf("nb case : %d\n", tint_diff_max_gain[0]);
		printf("nb points max : %d\n\n", int_max_gain);
		for(int i=1; i<=tint_diff_max_gain[0]; i++){
			printf("Case %d\n", tint_diff_max_gain[i]);
		}
		printf("\n");
		system("PAUSE");
		//pause(10000);
		*/ //////

		int_nb_case = (rand() % tint_diff_max_gain[0]) + 1; //Choix aléatoire parmis les meilleurs
		int_case_jouer = tint_diff_max_gain[int_nb_case];


		//Cette ia est capable de jouer des coup qui ne réussiront pas forcément mais elle est agressive puisqu'elle essaiera de jouer des coups pouvant lui permettre de prendre des graines au tour d'après.
		if(int_niveau == 4){

			//On recopie le tableau du max des gain dans un tableau ou la première case n'est pas la taille du tableau afin du l'utiliset pour la fonction appartient_int_tab
			for(int i=1; i<=tint_diff_max_gain[0]; i++){
				tint_diff_max_gain2[i - 1] = tint_diff_max_gain[i];
			}

			//On récupère le tableau des points hypothetiques
			tint_points_hypothetiques = tableau_des_gains_hypothetiques(ej_jeux, int_joueur);


			int_max_chance_hypothetiques = 0;
			int_max_gain_hypothetiques = 0;
			//Recherche du maximum de chance possible à jouer ainsi que les gains max dans le tableau tint_points_hypothetiques en fonction du précèdent tableau : tint_diff_max_gain
			for(int i=0 ; i<tint_points_hypothetiques[0][0] ; i++){
				if( (i == 0) && appartient_int_tab(tint_points_hypothetiques[1][i], tint_diff_max_gain2, tint_diff_max_gain[0])){
					int_max_chance_hypothetiques = tint_points_hypothetiques[3][i];
					int_max_gain_hypothetiques = tint_points_hypothetiques[2][i];
					bool_passage = 1;
				}else{
					if( (tint_points_hypothetiques[3][i] >= int_max_chance_hypothetiques) && appartient_int_tab(tint_points_hypothetiques[1][i], tint_diff_max_gain2, tint_diff_max_gain[0])){
						if(tint_points_hypothetiques[3][i] > int_max_chance_hypothetiques){
							bool_passage = 0;
						}
						int_max_chance_hypothetiques = tint_points_hypothetiques[3][i];

						if(!bool_passage){
							int_max_gain_hypothetiques = tint_points_hypothetiques[2][i];
							bool_passage = 1;
						}else{
							if( (tint_points_hypothetiques[2][i] > int_max_gain_hypothetiques) && appartient_int_tab(tint_points_hypothetiques[1][i], tint_diff_max_gain2, tint_diff_max_gain[0])){
								int_max_gain_hypothetiques = tint_points_hypothetiques[2][i];
							}
						}
					}
				}
			}

			/* DEBUG /////////
			printf("\n\n");
			printf("nb cases : %d\n", tint_points_hypothetiques[0][0]);
			printf("nb points max : %d\n", tint_points_hypothetiques[0][1]);
			printf("nb chance max : %d\n\n", tint_points_hypothetiques[0][2]);
			printf("nb points max dans tab max diff : %d\n", int_max_gain_hypothetiques);
			printf("nb chance max dans tab max diff : %d\n\n", int_max_chance_hypothetiques);
			for(int i=0; i<tint_points_hypothetiques[0][0]; i++){
				printf("Case %d : Point moy = %d ; Nb chance = %d\n", tint_points_hypothetiques[1][i], tint_points_hypothetiques[2][i], tint_points_hypothetiques[3][i]);
			}

			printf("\n");
			system("PAUSE");
			//pause(10000);
			*/ //////////////

			tint_max_points_hypothetiques[0] = 0;
			int k=1;
			//S'il y a des opportunitées sur le tour suivant alors on va les tenter
			if( int_max_gain_hypothetiques > 0){
				for(int i=0 ; i<tint_points_hypothetiques[0][0] ; i++){
					if((tint_points_hypothetiques[2][i] >= int_max_gain_hypothetiques) && (tint_points_hypothetiques[3][i] >= int_max_chance_hypothetiques)){
						if( appartient_int_tab(tint_points_hypothetiques[1][i], tint_diff_max_gain2, tint_diff_max_gain[0]) ){
							tint_max_points_hypothetiques[0]++;
							tint_max_points_hypothetiques[k] = tint_points_hypothetiques[1][i];
							k++;
						}
					}
				}

				if(tint_max_points_hypothetiques[0]){
					int_nb_case = (rand() % tint_max_points_hypothetiques[0]) + 1; //Choix aléatoire parmis les meilleurs
					int_case_jouer = tint_max_points_hypothetiques[int_nb_case];
				}

			}

			//Libération de l'espace mémoire occupé
			free(tint_points_hypothetiques[0]);
			free(tint_points_hypothetiques[1]);
			free(tint_points_hypothetiques[2]);
			free(tint_points_hypothetiques[3]);
			free(tint_points_hypothetiques);

		}


		//Libération de l'espace mémoire occupé
		free(tint_tab_pertes[0]);
		free(tint_tab_pertes[1]);
		free(tint_tab_pertes[2]);
		free(tint_tab_pertes);
		free(tint_tab_gain[0]);
		free(tint_tab_gain[1]);
		free(tint_tab_gain[2]);
		free(tint_tab_gain);

	}

	return(int_case_jouer);

}


int** meilleur_coup_attaque(etat_jeux ej_jeux, int int_joueur){

	int** tint_ncases_et_nbpoints = NULL;
	int** tint_tab_gain = NULL;
	int j;

	tint_ncases_et_nbpoints = (int**)malloc(sizeof(int*) * 2);
	tint_ncases_et_nbpoints[0] = (int*)malloc(sizeof(int) * 2);
	tint_ncases_et_nbpoints[1] = (int*)malloc(sizeof(int) * 7);

	//On récupère le tableau des gains
	tint_tab_gain = tableau_des_gains(ej_jeux, int_joueur);

	//On met tout les meilleurs coups dans un tableau; la première case du tableau contient le nombre de meilleurs coups
	tint_ncases_et_nbpoints[0][0] = 0;
	tint_ncases_et_nbpoints[0][1] = tint_tab_gain[0][1];
	j = 0;
	for(int i=0; i<tint_tab_gain[0][0]; i++){
		if(tint_tab_gain[2][i] >= tint_tab_gain[0][1]){
			tint_ncases_et_nbpoints[0][0]++;
			tint_ncases_et_nbpoints[1][j] = tint_tab_gain[1][i];
			j++;
		}
	}

	//Libération de l'espace mémoire
	free(tint_tab_gain[0]);
	free(tint_tab_gain[1]);
	free(tint_tab_gain[2]);
	free(tint_tab_gain);

	return(tint_ncases_et_nbpoints);

}

int** tableau_des_gains(etat_jeux ej_jeux, int int_joueur){

	int** tint_points = NULL;
	int* ptint_cases_jouables = NULL;
	int int_case_valide;
	int int_nb_points_actuel;
	int int_nb_points_nouv;
	int int_nb_points_diff;
	etat_jeux ej_jeux_simulation;

	tint_points = (int**)malloc(sizeof(int*) * 3);
	tint_points[0] = (int*)malloc(sizeof(int) * 2); //nb de case possible a jouer [0] et maximum des gains [1]
	tint_points[1] = (int*)malloc(sizeof(int) * 6); //Numéros des cases
	tint_points[2] = (int*)malloc(sizeof(int) * 6); //Gains que rapporte de jouer ces cases

	ptint_cases_jouables = cases_jouables(ej_jeux, int_joueur);
	tint_points[0][0] = ptint_cases_jouables[0];
	tint_points[0][1] = 0;

	//On simule le jeux selon les cases de l'ordinateur et on rempli un tableau représentant les points que l'on ferait selon les 6 cases de l'ordinateur
	for(int i=0 ; i<ptint_cases_jouables[0] ; i++){

		int_case_valide = ptint_cases_jouables[i + 1];
		tint_points[1][i] = int_case_valide;

		ej_jeux_simulation = copie_etat_jeux(ej_jeux);

		if(int_joueur == 2){
			int_nb_points_actuel = acc_l_points_j2(ej_jeux_simulation);
		}else{
			int_nb_points_actuel = acc_l_points_j1(ej_jeux_simulation);
		}
		calcul_nouveau_tableau(&ej_jeux_simulation, int_case_valide, 0);
		if(int_joueur == 2){
			int_nb_points_nouv = acc_l_points_j2(ej_jeux_simulation);
		}else{
			int_nb_points_nouv = acc_l_points_j1(ej_jeux_simulation);
		}
		int_nb_points_diff = int_nb_points_nouv - int_nb_points_actuel;

		tint_points[2][i] = int_nb_points_diff;

		//On recherche le maximum
		if(int_nb_points_diff > tint_points[0][1]){
			tint_points[0][1] = int_nb_points_diff;
		}

	}

	//Libération de l'espace mémoire
	free(ptint_cases_jouables);

	return(tint_points);
}

int** tableau_des_pertes(etat_jeux ej_jeux, int int_joueur){

	int** tint_points_pertes = NULL;
	int* ptint_cases_jouables1 = NULL;
	int* ptint_cases_jouables2 = NULL;
	int int_case_valide1;
	int int_case_valide2;
	int int_nb_points_actuel;
	int int_nb_points_nouv;
	int int_nb_points_diff;
	int int_joueur_adverse;
	etat_jeux ej_jeux_simulation1;
	etat_jeux ej_jeux_simulation2;

	tint_points_pertes = (int**)malloc(sizeof(int*) * 3);
	tint_points_pertes[0] = (int*)malloc(sizeof(int) * 2); //nbr de case possible a jouer [0] et maximum des pertes [1]
	tint_points_pertes[1] = (int*)malloc(sizeof(int) * 6); //Numéros des cases
	tint_points_pertes[2] = (int*)malloc(sizeof(int) * 6); //Pertes subit en jouant ces cases

	ptint_cases_jouables1 = cases_jouables(ej_jeux, int_joueur);

	if(int_joueur == 1){
		int_joueur_adverse = 2;
	}else{
		int_joueur_adverse = 1;
	}

	tint_points_pertes[0][0] = ptint_cases_jouables1[0];

	//On simule tout les cas possible que peux jouer l'IA
	for(int i=0 ; i<ptint_cases_jouables1[0] ; i++){

		int_case_valide1 = ptint_cases_jouables1[i + 1];
		tint_points_pertes[1][i] = int_case_valide1;
		ej_jeux_simulation1 = copie_etat_jeux(ej_jeux);
		calcul_nouveau_tableau(&ej_jeux_simulation1, int_case_valide1, 0);

		ptint_cases_jouables2 = cases_jouables(ej_jeux_simulation1, int_joueur_adverse);
		//On simule tout les cas possibles que peux jouer le joueur et on garde ses meilleurs choix
		for(int j=0 ; j<ptint_cases_jouables2[0] ; j++){

			int_case_valide2 = ptint_cases_jouables2[j + 1];
			ej_jeux_simulation2 = copie_etat_jeux(ej_jeux_simulation1);
			if(int_joueur == 2){
				int_nb_points_actuel = acc_l_points_j1(ej_jeux_simulation2);
			}else{
				int_nb_points_actuel = acc_l_points_j2(ej_jeux_simulation2);
			}
			calcul_nouveau_tableau(&ej_jeux_simulation2, int_case_valide2, 0);
			if(int_joueur == 2){
				int_nb_points_nouv = acc_l_points_j1(ej_jeux_simulation2);
			}else{
				int_nb_points_nouv = acc_l_points_j2(ej_jeux_simulation2);
			}
			int_nb_points_diff = int_nb_points_nouv - int_nb_points_actuel;

			//On recherche le maximum
			if(j == 0){
				tint_points_pertes[2][i] = int_nb_points_diff;
			}else{
				if(int_nb_points_diff > tint_points_pertes[2][i]){
					tint_points_pertes[2][i] = int_nb_points_diff;
				}
			}

		}

		//On recherche le maximum
		if(i == 0){
			tint_points_pertes[0][1] = tint_points_pertes[2][i];
		}else{
			if(tint_points_pertes[2][i] > tint_points_pertes[0][1]){
				tint_points_pertes[0][1] = tint_points_pertes[2][i];
			}
		}

		//Libération de l'espace mémoire
		free(ptint_cases_jouables2);

	}

	//Libération de l'espace mémoire
	free(ptint_cases_jouables1);


	return(tint_points_pertes);

}

int** tableau_des_gains_hypothetiques(etat_jeux ej_jeux, int int_joueur){

	int** tint_points_hypothetiques = NULL;
	int** tint_tab_gain = NULL;
	int* ptint_cases_jouables1 = NULL;
	int* ptint_cases_jouables2 = NULL;
	int int_case_valide1;
	int int_case_valide2;
	int int_joueur_adverse;
	etat_jeux ej_jeux_simulation1;
	etat_jeux ej_jeux_simulation2;

	if(int_joueur == 1){
		int_joueur_adverse = 2;
	}else{
		int_joueur_adverse = 1;
	}

	tint_points_hypothetiques = (int**)malloc(sizeof(int*) * 4);
	tint_points_hypothetiques[0] = (int*)malloc(sizeof(int) * 3); //nbr de case possible a jouer [0] et maximum des gains [1] et maximum de chance de réussite [2]
	tint_points_hypothetiques[1] = (int*)malloc(sizeof(int) * 6); //Numéros des cases
	tint_points_hypothetiques[2] = (int*)malloc(sizeof(int) * 6); //Gains gagné en moyenne en jouant ces cases
	tint_points_hypothetiques[3] = (int*)malloc(sizeof(int) * 6); //pourcentage de chance de réussite du coup

	ptint_cases_jouables1 = cases_jouables(ej_jeux, int_joueur);

	tint_points_hypothetiques[0][0] = ptint_cases_jouables1[0];

	//On simule tout les cas possible que peux jouer l'IA
	for(int i=0 ; i<ptint_cases_jouables1[0] ; i++){

		int_case_valide1 = ptint_cases_jouables1[i + 1];
		tint_points_hypothetiques[1][i] = int_case_valide1;
		ej_jeux_simulation1 = copie_etat_jeux(ej_jeux);
		calcul_nouveau_tableau(&ej_jeux_simulation1, int_case_valide1, 0);

		ptint_cases_jouables2 = cases_jouables(ej_jeux_simulation1, int_joueur_adverse);
		tint_points_hypothetiques[3][i] = 0;
		tint_points_hypothetiques[2][i] = 0;
		//On simule tout les cas possibles que peux jouer le joueur
		for(int j=0 ; j<ptint_cases_jouables2[0] ; j++){

			int_case_valide2 = ptint_cases_jouables2[j + 1];
			ej_jeux_simulation2 = copie_etat_jeux(ej_jeux_simulation1);
			calcul_nouveau_tableau(&ej_jeux_simulation2, int_case_valide2, 0);

			tint_tab_gain = tableau_des_gains(ej_jeux_simulation2, int_joueur);

			if(tint_tab_gain[0][1] > 0){
				tint_points_hypothetiques[2][i] += tint_tab_gain[0][1];
				tint_points_hypothetiques[3][i]++;
			}

			//Libération de l'espace mémoire
			free(tint_tab_gain[0]);
			free(tint_tab_gain[1]);
			free(tint_tab_gain[2]);
			free(tint_tab_gain);

		}

		//Calcule la moyenne des graines remporté en jouant cette case
		if(tint_points_hypothetiques[3][i]){
			tint_points_hypothetiques[2][i] = arrondir((tint_points_hypothetiques[2][i] * 1.0) / tint_points_hypothetiques[3][i]);
		}else{
			tint_points_hypothetiques[2][i] = 0;
		}

		//Calcule de un pourcentage de réussir le coup
		if(ptint_cases_jouables2[0]){
			tint_points_hypothetiques[3][i] = arrondir((tint_points_hypothetiques[3][i] * 100.0) / ptint_cases_jouables2[0]);
		}else{
			tint_points_hypothetiques[3][i] = 0;
		}

		//On recherche le maximum
		if(i == 0){
			tint_points_hypothetiques[0][1] = tint_points_hypothetiques[2][i];
			tint_points_hypothetiques[0][2] = tint_points_hypothetiques[3][i];
		}else{
			if(tint_points_hypothetiques[3][i] >= tint_points_hypothetiques[0][2]){
				tint_points_hypothetiques[0][2] = tint_points_hypothetiques[3][i];
				if(tint_points_hypothetiques[3][i] == tint_points_hypothetiques[0][2]){
					if(tint_points_hypothetiques[0][1] < tint_points_hypothetiques[2][i]){
						tint_points_hypothetiques[0][1] = tint_points_hypothetiques[2][i];
					}
				}else{
					tint_points_hypothetiques[0][1] = tint_points_hypothetiques[2][i];
				}
			}
		}

		//Libération de l'espace mémoire
		free(ptint_cases_jouables2);

	}

	//Libération de l'espace mémoire
	free(ptint_cases_jouables1);

	return(tint_points_hypothetiques);

}

int arrondir(double double_nombre){

	int int_nombre;

	int_nombre = (int)double_nombre;
	if( (double_nombre - int_nombre) >= 0.5 ){
		return(int_nombre + 1);
	}else{
		return(int_nombre);
	}

}