/*!
	\file    regles_jeux.cpp
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Fichier qui contient toutes les fonctions et procédures relatives au jeux et à ses règles
	\remarks Aucune
*/

#include <stdlib.h>
#include <stdio.h>

#include "type.h"
#include "regles_jeux.h"
#include "in_out.h"
#include "ia.h"


int jeux_1_VS_1 (etat_jeux ej_jeux){

	int int_case_jouer;
	int int_joueur; //Varible qui contient le numéros du joueur qui joue (1 ou 2)

	affiche_etat_jeux(ej_jeux); //On affiche l'état actuel du jeux //A enlever pour SDL

	//par défault le joueur 1 commence (ca peut bien évidemment se changer pour Romain)
	int_joueur = 1;
	do{

		int_case_jouer = saisir_case_verif(ej_jeux, int_joueur);
		if(int_case_jouer != -1){
			calcul_nouveau_tableau(&ej_jeux, int_case_jouer, 1); //On calcule le nouveau tableau
			affiche_etat_jeux(ej_jeux);	//On affiche l'état actuel du jeux

			//On change de joueur
			if( int_joueur == 1 ){
				int_joueur = 2;
			}else{
				int_joueur = 1;
			}
		}


	}while( !fin_de_partie(&ej_jeux, int_joueur) && (int_case_jouer != -1));

	//On affiche et retourne le vainqueur et l'état de fin de partie !
	return(affiche_et_retourne_vainqueur(ej_jeux, 1));

}


int jeux_1_VS_IA (etat_jeux ej_jeux, int int_niveau){

	int int_case_jouer;
	int int_joueur; //Varible qui contient le numéros du joueur qui joue (1 ou 2)

	affiche_etat_jeux(ej_jeux); //On affiche l'état actuel du jeux //A enlever pour SDL

	//par défault le joueur 1 commence (ca peut bien évidemment se changer pour Romain)
	int_joueur = 1;
	do{

		if(int_joueur == 1){
			int_case_jouer = saisir_case_verif(ej_jeux, int_joueur);
		}else{
			printf("\n\nL'ordinateur va jouer...");
			fflush(stdout);
			pause(1000);
			int_case_jouer = jouer_IA(ej_jeux, int_niveau, int_joueur);
		}
		if(int_case_jouer != -1){
			calcul_nouveau_tableau(&ej_jeux, int_case_jouer, 1); //On calcule le nouveau tableau
			affiche_etat_jeux(ej_jeux);	//On affiche l'état actuel du jeux

			//On change de joueur
			if( int_joueur == 1 ){
				int_joueur = 2;
			}else{
				int_joueur = 1;
			}
		}


	}while( !fin_de_partie(&ej_jeux, int_joueur) && (int_case_jouer != -1));

	//On affiche et retourne le vainqueur et l'état de fin de partie !
	return(affiche_et_retourne_vainqueur(ej_jeux, 1));

}


int jeux_IA_VS_IA (etat_jeux ej_jeux, int int_niveau_ia1, int int_niveau_ia2, int bool_affichage){

	int int_case_jouer;
	int int_joueur; //Varible qui contient le numéros du joueur qui joue (1 ou 2)

	if(bool_affichage){
		affiche_etat_jeux(ej_jeux); //On affiche l'état actuel du jeux //A enlever pour SDL
	}

	//par défault le joueur 1 commence (ca peut bien évidemment se changer pour Romain)
	int_joueur = 1;
	do{

		if(int_joueur == 1){
			if(bool_affichage){
				printf("\n\nL'ordinateur 1 va jouer... (Niveau %d)", int_niveau_ia1);
				fflush(stdout);
				pause(1000);
			}
			int_case_jouer = jouer_IA(ej_jeux, int_niveau_ia1, int_joueur);
		}else{
			if(bool_affichage){
				printf("\n\nL'ordinateur 2 va jouer... (Niveau %d)", int_niveau_ia2);
				fflush(stdout);
				pause(1000);
			}
			int_case_jouer = jouer_IA(ej_jeux, int_niveau_ia2, int_joueur);
		}
		if(int_case_jouer != -1){
			calcul_nouveau_tableau(&ej_jeux, int_case_jouer, bool_affichage); //On calcule le nouveau tableau
			if(bool_affichage){
				affiche_etat_jeux(ej_jeux);	//On affiche l'état actuel du jeux
			}

			//On change de joueur
			if( int_joueur == 1 ){
				int_joueur = 2;
			}else{
				int_joueur = 1;
			}
		}


	}while( !fin_de_partie(&ej_jeux, int_joueur) && (int_case_jouer != -1));

	//On affiche et retourne le vainqueur et l'état de fin de partie !
	return(affiche_et_retourne_vainqueur(ej_jeux, bool_affichage));

}



void calcul_nouveau_tableau(etat_jeux* pej_jeux, int int_case, int bool_affichage){

	int int_final_case ;
	int j=0;
	int tint_cases_ennemi[6]; //Contient les cases de l'ennemi (à déduire en fonction de int_case)
	int int_der_case; //Contiendra la dernière case joué


	int_final_case = int_case + acc_l_trous((*pej_jeux), int_case); //On calcule la dernière case jusqu'a laquelle on distribut des jetons

	acc_e_trou(pej_jeux, int_case, 0); // On enlève tout les jetons dans la case choisi par l'utilisateur

	if(bool_affichage){
		affiche_etat_jeux(*pej_jeux); //On affiche le jeux //A enlever pour SDL
	}

	for(int i=int_case+1 ; i<=int_final_case; i++){ //On distribue 1 jeton de la case choisit par l'utilisateur à la case + son nombre de jetons
		//On résoud ici le problème quand on arrive à la case 11 du tableau, dans ce cas on repasse à 0 etc...
		if(i > 11){
			j = i - ((i/12)*12);
		}else{
			j = i;
		}

		//Cette condition permet de sauter quand on repasse sur la case que l'on a joué
		if( j != int_case){
			//On ajoute 1 jeton à la case j
			acc_e_trou(pej_jeux, j, acc_l_trous((*pej_jeux), j) + 1 );
		}else{
			int_final_case++; //On ajoute + 1 à la dernière case à jouer car on a sauté la case ou l'on a enlevé les jetons
		}

		if(bool_affichage){
			//On affiche le jeux //A enlever pour SDL
			affiche_etat_jeux(*pej_jeux);
		}
	}

	int_der_case = j; //La dernière case sur laquelle on s'arrete est j, on met j dans int_der_case pour des raison de compréhension

	//Il faut maintenant savoir si on est chez l'ennemi ou chez nous, si on est chez l'enemi alors on va essayer de voir si on peut gagner des points via la fonction "rajoute_points"
	//On crée ici le tableau des cases ennemi par rapport à notre case de départ :
	if( (int_case >= 0) && (int_case < 6) ){
		tint_cases_ennemi[0] = 6;
		tint_cases_ennemi[1] = 7;
		tint_cases_ennemi[2] = 8;
		tint_cases_ennemi[3] = 9;
		tint_cases_ennemi[4] = 10;
		tint_cases_ennemi[5] = 11;
	}else{
		tint_cases_ennemi[0] = 0;
		tint_cases_ennemi[1] = 1;
		tint_cases_ennemi[2] = 2;
		tint_cases_ennemi[3] = 3;
		tint_cases_ennemi[4] = 4;
		tint_cases_ennemi[5] = 5;
	}


	//On comptabilise les points si il y a des points à comptabiliser
	rajoute_points(pej_jeux, int_der_case, tint_cases_ennemi, 6);

}

int appartient_int_tab(int int_valeur, int* ptint_valeurs, int int_taille_ptint_valeurs){

	int bool_return=0;
	int i=0;

	if(int_taille_ptint_valeurs){
		do{
			if(ptint_valeurs[i] == int_valeur){
				bool_return=1;
			}
			i=i+1;
		}while( (i < int_taille_ptint_valeurs) && (bool_return == 0) );

		return(bool_return);
	}else{
		return(0);
	}
}

void rajoute_points(etat_jeux* pej_jeux, int int_der_case, int* ptint_valeurs, int int_taille_ptint_valeurs){

	int int_case;
	int bool_continue=1;
	int bool_case_ennemi;
	int int_compteur_points=0;

	//Si le coup que l'on veut jouer n'affame (prendre toutes ses graines) pas le joueur adverse alors on regarde si on peut gagner des points
	if (!test_affame(pej_jeux, int_der_case, ptint_valeurs, int_taille_ptint_valeurs)){

		bool_case_ennemi = appartient_int_tab(int_der_case, ptint_valeurs, int_taille_ptint_valeurs);
		while( bool_case_ennemi && bool_continue){
			int_case = acc_l_trous(*pej_jeux, int_der_case);
			if(int_case>1 && int_case<4){
				int_compteur_points = int_compteur_points + int_case;
				acc_e_trou(pej_jeux,int_der_case,0);
				int_der_case = int_der_case-1;
				bool_case_ennemi = appartient_int_tab(int_der_case, ptint_valeurs, int_taille_ptint_valeurs);
			}else{
				bool_continue=0;
			}
		}
		if(ptint_valeurs[0] == 0){
			acc_e_points_j2(pej_jeux, acc_l_points_j2(*pej_jeux) + int_compteur_points);
		}else{
			acc_e_points_j1(pej_jeux, acc_l_points_j1(*pej_jeux) + int_compteur_points);
		}
	}
}

int fin_de_partie(etat_jeux* pej_jeux, int int_joueur){

	int int_case;
	int int_nourrir;
	int int_valeur_case;
	int int_points1=0;
	int int_points2=0;
	int int_points_total;

	//On teste si un joueur à ateint les 25 points, si c'est le cas la partie est terminé
	int_points1= acc_l_points_j1(*pej_jeux);
	int_points2= acc_l_points_j2(*pej_jeux);
	if(int_points1>=25 || int_points2>=25 ){
		return(1);
	}

	//On remet les points à 0 pour compter les graines dans les trous maintenant
	int_points1 = 0;
	int_points2 = 0;
	//On teste si il reste moins de 6 graines en jeux, si c le cas la partie est terminé
	for(int i=0; i<6; i++){
		int_valeur_case = acc_l_trous(*pej_jeux, i);
		int_points1 = int_points1 + int_valeur_case;
	}
	for(int i=6; i<12; i++){
		int_valeur_case = acc_l_trous(*pej_jeux, i);
		int_points2 = int_points2 + int_valeur_case;
	}
	int_points_total = int_points1 + int_points2;
	if(int_points_total <= 6){
		return(1);
	}

	//ici on vérifie si le joueur qui va joueur peut joueur et selon les cas on lui attribu les points selon les règles du jeux
	//Si on a affaire au joueur 1
	if(int_joueur == 1){
		//Si ce dernier n'a plus de graines de son coté
		if(int_points1==0){
			//Alors il ne peut pas joueur et l'adversaire récupère toute ses graines
			acc_e_points_j2(pej_jeux, acc_l_points_j2(*pej_jeux) + int_points2);
			return(1);
		}else{
			//Sinon si il a des graines mais son adversaire n'en a pas
			if(int_points2==0){
				//Alors on regarde si le joueur qui va joueur peut donner des graines à l'adversaire
				int_case=0;
				do{
					int_nourrir=passe_sur_case_ennemi(*pej_jeux, int_case);
					int_case = int_case + 1;
				}while(int_nourrir==0 && int_case<6);
				//Si il ne peut pas alors le joueur remporte les graines qui sont de sont côté
				if(int_nourrir==0){
					for(int i=0; i<6; i++){
						acc_e_trou(pej_jeux, i, 0);
					}
					acc_e_points_j1(pej_jeux, acc_l_points_j1(*pej_jeux) + int_points1);
					return(1);
				//Si le joueur peut nourrir l'adversaire alors la partie continu
				}else{
					return(0);
				}
			}else{
				return(0);
			}
		}
	//Si on a affaire au joueur 2
	}else{
		//Si ce dernier n'a plus de graines de son coté
		if(int_points2==0){
			//Alors il ne peut pas joueur et l'adversaire récupère toute ses graines
			acc_e_points_j1(pej_jeux, acc_l_points_j1(*pej_jeux) + int_points1);
			return(1);
		}else{
			//Sinon si il a des graines mais que son adversaire n'en a pas
			if(int_points1==0){
				//Alors on regarde si le joueur qui va joueur peut donner des graines à l'adversaire
				int_case=6;
				do{
					int_nourrir=passe_sur_case_ennemi(*pej_jeux, int_case);
					int_case = int_case + 1;
				}while(int_nourrir==0 && int_case<12);
				//Si il ne peut pas alors le joueur remporte les graines qui sont de sont côté
				if(int_nourrir==0){
					for(int i=6; i<12; i++){
						acc_e_trou(pej_jeux, i, 0);
					}
					acc_e_points_j2(pej_jeux, acc_l_points_j2(*pej_jeux) + int_points2);
					return(1);
				//Si le joueur peut nourrir l'adversaire alors la partie continu
				}else{
					return(0);
				}
			}else{
				return(0);
			}
		}
	}

}

int test_affame(etat_jeux* pej_jeux, int int_der_case, int* ptint_valeurs, int int_taille_ptint_valeurs){

	int int_return=0;
	int int_temp = int_der_case;
	int bool_sortie_boucle1 = 1;
	int bool_sortie_boucle2 = 1;
	int bool_case;
	int int_case;
	bool_case = appartient_int_tab(int_der_case, ptint_valeurs, int_taille_ptint_valeurs);

	if(bool_case){
		while(bool_case && bool_sortie_boucle1){
			int_case = acc_l_trous(*pej_jeux, int_temp);
			if(int_case>1 && int_case<4){
				int_temp = int_temp-1;
				bool_case = appartient_int_tab(int_temp, ptint_valeurs, int_taille_ptint_valeurs);
			}else{
				bool_sortie_boucle1=0;
			}
		}
		int_der_case = int_der_case + 1;
		bool_case = appartient_int_tab(int_der_case, ptint_valeurs, int_taille_ptint_valeurs);
		while(bool_case && bool_sortie_boucle2){
			int_case = acc_l_trous(*pej_jeux, int_der_case);
			if(int_case==0){
				int_der_case=int_der_case +1;
				bool_case = appartient_int_tab(int_der_case, ptint_valeurs, int_taille_ptint_valeurs);
			}else{
				bool_sortie_boucle2=0;
			}
		}
		if(bool_sortie_boucle1 && bool_sortie_boucle2){
			int_return=1;
		}
	}
	return(int_return);
}


int graines_joueur(etat_jeux ej_jeux, int int_joueur){

	int bool_graines_joueur = 0;
	int i,j;

	if(int_joueur == 1){
		i=0;
		j=5;
	}else{
		i=6;
		j=11;
	}

	do{
		if(acc_l_trous(ej_jeux, i) > 0){
			bool_graines_joueur = 1;
		}
		i++;
	}while(i<=j && !bool_graines_joueur);

	return(bool_graines_joueur);

}


int passe_sur_case_ennemi(etat_jeux ej_jeux, int int_case){

	int tint_cases_ennemi[6];
	int int_case_finale;
	int int_der_case;
	int bool_passage=0;

	//On crée le tableau qui contient les indices des cases ennemi
	if( (int_case >= 6) && (int_case <= 11) ){
		tint_cases_ennemi[0] = 0;
		tint_cases_ennemi[1] = 1;
		tint_cases_ennemi[2] = 2;
		tint_cases_ennemi[3] = 3;
		tint_cases_ennemi[4] = 4;
		tint_cases_ennemi[5] = 5;
	}else{
		tint_cases_ennemi[0] = 6;
		tint_cases_ennemi[1] = 7;
		tint_cases_ennemi[2] = 8;
		tint_cases_ennemi[3] = 9;
		tint_cases_ennemi[4] = 10;
		tint_cases_ennemi[5] = 11;
	}


	int_case_finale = acc_l_trous(ej_jeux, int_case) + int_case; //int_case_finale contient le nombre de fois que l'on doit faire la boucle au max

	int i=(int_case+1); //On commence à la case + 1 choisit par le joueur puisqu'on distribu à partir de la case d'après (logique)
	while((i<=int_case_finale) && !bool_passage){

		if(i > 11){
			int_der_case = i - ((i/12)*12);
		}else{
			int_der_case = i;
		}
		//Si lors de la distribution on passe au moin une fois chez l'ennemi alors on met vrai dans bool_passage
		if( appartient_int_tab(int_der_case, tint_cases_ennemi, 6) ){
			bool_passage = 1;
		}
		i++;

	}
	return( bool_passage );


}


int** statistiques_ia(int int_premiere_ia, int int_derniere_ia, int int_indice_stat, int bool_affichage){

	int** tint_nb_victoires_defaites;
	int int_taille_tabs;
	int int_points_joueur1=0;
	int int_points_joueur2=0;
	int int_total_passage;
	int int_passage_actuel;
	int int_resultat_jeux_ia;
	int tint_trous[12]={4,4,4,4,4,4,4,4,4,4,4,4};
	etat_jeux ej_jeux;

	int_taille_tabs = int_derniere_ia - int_premiere_ia + 1;

	if(int_taille_tabs > 0){


		//On initialise la variable ej_jeux
		ej_jeux = ini_etat_jeux(int_points_joueur1, int_points_joueur2, tint_trous);

		tint_nb_victoires_defaites = (int**)malloc(sizeof(int*) * 3);
		tint_nb_victoires_defaites[0] = (int*)malloc(sizeof(int) * int_taille_tabs);
		tint_nb_victoires_defaites[1] = (int*)malloc(sizeof(int) * int_taille_tabs);
		tint_nb_victoires_defaites[2] = (int*)malloc(sizeof(int) * int_taille_tabs);

		//Initialisation de tout les tableaux;
		for(int i=0; i<int_taille_tabs; i++){

			tint_nb_victoires_defaites[0][i] = int_premiere_ia + i;
			tint_nb_victoires_defaites[1][i] = 0;
			tint_nb_victoires_defaites[2][i] = 0;

		}

		int_total_passage = (int_taille_tabs * int_taille_tabs * int_indice_stat) - (int_taille_tabs * int_indice_stat);
		int_passage_actuel = 0;

		if(bool_affichage){
			effacer_affichage();
			affiche_presentation_jeux();
			printf("Veuillez pentientez, les statistiques sont en train d'etre calcules...\n\n");
			printf("Avancement : %d/%d (Indice de stats : %d)\n\n", int_passage_actuel, int_total_passage, int_indice_stat);
			for(int i=0; i<int_taille_tabs; i++){
				printf("IA Niveau %d : %d victoires et %d defaites\n", tint_nb_victoires_defaites[0][i], tint_nb_victoires_defaites[1][i], tint_nb_victoires_defaites[2][i]);
			}
		}

		for(int i=0; i<int_taille_tabs; i++){
			for(int j=0; j<int_taille_tabs; j++){
				if(j != i){
					for(int k=0; k<int_indice_stat; k++){
						int_resultat_jeux_ia = jeux_IA_VS_IA (ej_jeux, (i + int_premiere_ia), (j + int_premiere_ia), 0);
						if(int_resultat_jeux_ia == 1){
							tint_nb_victoires_defaites[1][i]++;
							tint_nb_victoires_defaites[2][j]++;
						}else{
							if(int_resultat_jeux_ia != 0){
								tint_nb_victoires_defaites[1][j]++;
								tint_nb_victoires_defaites[2][i]++;
							}
						}

						int_passage_actuel++;
						if(bool_affichage && (!(int_passage_actuel%10) || int_passage_actuel == int_total_passage)){
							effacer_affichage();
							affiche_presentation_jeux();
							printf("Veuillez pentientez, les statistiques sont en train d'etre calcules...\n\n");
							printf("Avancement : %d/%d (Indice de stats : %d)\n\n", int_passage_actuel, int_total_passage, int_indice_stat);
							for(int l=0; l<int_taille_tabs; l++){
								printf("IA Niveau %d : %d victoires et %d defaites\n", tint_nb_victoires_defaites[0][l], tint_nb_victoires_defaites[1][l], tint_nb_victoires_defaites[2][l]);
							}
							if(int_passage_actuel != int_total_passage){
								printf("\nEn cours : IA Niveau %d VS IA Niveau %d", (i + int_premiere_ia), (j + int_premiere_ia));
							}
							fflush(stdout);
						}
					}
				}

			}
		}

		if(bool_affichage){
			printf("\nTravail effectue !\n");
		}

		return(tint_nb_victoires_defaites);

	}else{
		return(NULL);
	}
}
