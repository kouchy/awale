/*!
	\file    in_out.cpp
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Fichier qui contient toutes les fonctions et procédures relatives à la saisie et l'affichage
	\remarks Aucune
*/

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h> // Sleep function
#else
#include <unistd.h> // usleep function
#endif

#include "type.h"
#include "regles_jeux.h"
#include "in_out.h"
#include "ia.h"

void pause(float float_temps){
#if defined(_WIN32) || defined(_WIN64)
	Sleep((DWORD)float_temps);
#else
	usleep((unsigned int)(float_temps*1000.f));
#endif
}

void faire_pause(){
	std::cout << "Appuyez sur Entrer pour continuer...";
    std::cin.get();
    std::cin.get();
}

void effacer_affichage(){
	int ret=0;
#if defined(_WIN32) || defined(_WIN64)
	ret = system("CLS");
#else // Linux
	ret = system("clear");
#endif
	if (ret != 0)
	{
		printf("La commande système 'CLS' a retourné %d.\n", ret);
	}
}

void affiche_presentation_jeux(){

	printf(" --------------------------\n");
	printf("|          AWALE           |\n");
	printf("|  0 pour quitter le jeux  |\n");
	printf(" --------------------------\n");
	printf("\n");

}

void affiche_etat_jeux(etat_jeux ej_jeux){

	effacer_affichage(); //Fonction qui permet de rafraichir l'écran

	affiche_presentation_jeux(); //On affiche la bande de présentation du jeux

	printf("    ");  //On affiche l'état du jeux en question
	for(int i=11; i>5; i--){
		if(nb_chiffres(acc_l_trous(ej_jeux, i)) > 1){
			printf(" %d", acc_l_trous(ej_jeux, i));
		}else{
			printf("  %d", acc_l_trous(ej_jeux, i));
		}
		fflush(stdout);
	}

	printf("\n  %d                      %d\n", acc_l_points_j2(ej_jeux), acc_l_points_j1(ej_jeux));

	printf("    ");
	for(int i=0; i<6; i++){
		if(nb_chiffres(acc_l_trous(ej_jeux, i)) > 1){
			printf(" %d", acc_l_trous(ej_jeux, i));
		}else{
			printf("  %d", acc_l_trous(ej_jeux, i));
		}
		fflush(stdout);
	}

	pause(200);	//On fait une pause pendant un certain temps pour que l'on puisse bien voir l'affichage précèdent

}

int affiche_et_retourne_vainqueur(etat_jeux ej_jeux, int bool_affichage){

	if(bool_affichage){
		//On affiche l'état final du jeux
		affiche_etat_jeux(ej_jeux);
		printf("\n\n");
	}


	if(acc_l_points_j1(ej_jeux) > acc_l_points_j2(ej_jeux)){
		if(bool_affichage){
			printf("Le joueur 1 remporte la victoire avec %d graines! :) \n", acc_l_points_j1(ej_jeux));
			printf("Le joueur 2 perd la partie avec %d graines! :(\n", acc_l_points_j2(ej_jeux));
		}
		return(1);
	}else{

		if(acc_l_points_j2(ej_jeux) > acc_l_points_j1(ej_jeux)){
			if(bool_affichage){
				printf("Le joueur 2 remporte la victoire avec %d graines! :) \n", acc_l_points_j2(ej_jeux));
				printf("Le joueur 1 perd la partie avec %d graines! :(\n", acc_l_points_j1(ej_jeux));
			}
			return(2);
		}else{
			if(bool_affichage){
				printf("Les joueurs 1 et 2 sont execaux avec %d graines chacuns! :|\n", acc_l_points_j1(ej_jeux));
			}
			return(0);
		}

	}


}

int saisir_case(){

	int int_case;
	int int_retour;

	do{
		printf("Entrer une case : ");
		int_retour = scanf("%d",&int_case);
		fflush(stdin);
	}while(!int_retour || int_case < 0 || int_case > 6);

	return(int_case);

}

int saisir_case_verif(etat_jeux ej_jeux, int int_joueur){

	int* tint_cases_jouables;
	int tint_cases_jouables2[6];
	int int_taille_cases_jouables2;
	int int_case_verif; //La case que le joueur veut jouer que l'on vérif
	int bool_saisie; //Booléen qui sert de condition de boucle


	do{
		printf("\n\nJoueur %d : ", int_joueur);
		int_case_verif=saisir_case();

		if(!int_case_verif){
			return(-1);
		}
		if(int_joueur == 2){
			int_case_verif = int_case_verif + 5;
		}else{
			int_case_verif = int_case_verif - 1;
		}

		tint_cases_jouables = cases_jouables(ej_jeux, int_joueur);
		int_taille_cases_jouables2 = tint_cases_jouables[0];

		for(int i=0; i<int_taille_cases_jouables2; i++){
			tint_cases_jouables2[i] = tint_cases_jouables[i + 1];
		}

		free(tint_cases_jouables);

		if(appartient_int_tab(int_case_verif, tint_cases_jouables2, int_taille_cases_jouables2)){
			bool_saisie = 0;
		}else{
			printf("Impossible de jouer cette case!");
			bool_saisie = 1;
		}


	}while(bool_saisie);

	return(int_case_verif);
}


int nb_chiffres(int int_nombre){

	int int_nb_chiffres=1;

	int_nombre = int_nombre/10;
	while(int_nombre > 0){
		int_nb_chiffres++;
		int_nombre = int_nombre/10;
	}

	return(int_nb_chiffres);

}

int* cases_jouables(etat_jeux ej_jeux, int int_joueur){

	int* tint_cases_jouables; //Le tableau contenant les cases jouables (la première valeur (0) du tableau correspond aux nombres de cases)
	int int_case_verif; //La case que le joueur veut jouer que l'on vérif
	int int_joueur_adverse; //Le numéro correspndant au joueur adverse
	int int_deb;
	int int_fin;
	int j;

	//Allocation du tableau
	tint_cases_jouables = (int*)malloc(sizeof(int) * 7);

	if(int_joueur == 1){
		int_deb = 0;
		int_fin = 6;
	}else{
		int_deb = 6;
		int_fin = 12;
	}
	if(int_joueur == 1){
		int_joueur_adverse = 2;
	}else{
		int_joueur_adverse = 1;
	}

	tint_cases_jouables[0] = 0;
	j=1;
	for(int_case_verif=int_deb; int_case_verif<int_fin; int_case_verif++){

		//Si le joueur veut jouer un trou ou il n'a pas de graines il ne peut pas
		if(acc_l_trous(ej_jeux, int_case_verif) > 0){

			//Si le joueur adverse n'a plus de graine il faut forcément lui en donner
			if(!graines_joueur(ej_jeux, int_joueur_adverse)){
				if(passe_sur_case_ennemi(ej_jeux, int_case_verif)){
					tint_cases_jouables[0]++;
					tint_cases_jouables[j] = int_case_verif;
					j++;
				}
			}else{
				tint_cases_jouables[0]++;
				tint_cases_jouables[j] = int_case_verif;
				j++;
			}
		}


	}

	return(tint_cases_jouables);

}


void menu_jeux_shell(){

	int** tint_stats = NULL;
	int int_saisie;
	int int_saisie2;
	int int_retour = 1;
	int int_retour2 = 1;
	int int_retour3 = 1;
	int int_points_joueur1=0;
	int int_points_joueur2=0;
	int tint_trous[12]={4,4,4,4,4,4,4,4,4,4,4,4};
	int int_niveau_ia1;
	int int_niveau_ia2;
	int int_indice_stat;
	etat_jeux ej_jeux;
	//int tint_trous[12]={6,6,1,6,6,0,6,5,5,1,0,6};
	//int tint_trous[12]={0,0,0,0,0,0,1,4,2,1,1,0};
	//int tint_trous[12]={0,0,0,0,0,0,0,0,0,0,0,48};


	//On initialise la variable ej_jeux
	ej_jeux = ini_etat_jeux(int_points_joueur1, int_points_joueur2, tint_trous);

	do{
		effacer_affichage();
		affiche_presentation_jeux();
		printf(" 1 - Jouer 1 VS 1\n");
		printf(" 2 - Jouer 1 VS IA\n");
		printf(" 3 - Jouer IA VS IA\n");
		printf(" 4 - Lancer l'outil de statistiques sur les IAs\n");
		printf(" 5 - Regles du jeux\n");
		printf(" 6 - Quitter\n");

		printf("\nEntrez votre choix : ");
		int_retour = scanf("%d", &int_saisie);
		fflush(stdin);

		if(!int_retour || int_saisie < 0 || int_saisie > 6){
			printf("Mauvaise entree...\n");
			pause(1500);
		}

		switch(int_saisie){
			case 1 :
				jeux_1_VS_1 (ej_jeux);
				printf("\n");
				faire_pause();
				break;

			case 2 :
				do{
					effacer_affichage();
					affiche_presentation_jeux();
					printf(" 1 - IA Niveau tres facile\n");
					printf(" 2 - IA Niveau facile\n");
					printf(" 3 - IA Niveau moyen\n");
					printf(" 4 - IA Niveau difficile\n");
					printf(" 5 - Retour\n");

					printf("\nEntrez votre choix : ");
					int_retour2 = scanf("%d", &int_saisie2);
					fflush(stdin);

					if(!int_retour2 || int_saisie2 < 0 || int_saisie2 > 5){
						printf("Mauvaise entree...\n");
						pause(1500);
					}

					if(int_saisie2 == 5){
						int_saisie2 = 0;
					}else{
						if(int_saisie2 >= 1 && int_saisie2 <= 4){
							jeux_1_VS_IA (ej_jeux, int_saisie2);
							printf("\n");
							faire_pause();
							int_saisie2 = 0;
						}
					}

				}while(!int_retour2 || int_saisie2 != 0 );

				break;

			case 3 :
				do{
					printf("Entrez le niveau de l'IA 1 (entre 1 et 4): ");
					int_retour3 = scanf("%d", &int_niveau_ia1);
					fflush(stdin);
					if(!int_retour3 || (int_niveau_ia1 < 1 || int_niveau_ia1 > 4)){
						printf("Mauvaise entree...\n");
					}
				}while(!int_retour3 || (int_niveau_ia1 < 1 || int_niveau_ia1 > 4));

				do{
					printf("Entrez le niveau de l'IA 2 (entre 1 et 4): ");
					int_retour3 = scanf("%d", &int_niveau_ia2);
					fflush(stdin);
					if(!int_retour3 || (int_niveau_ia2 < 1 || int_niveau_ia2 > 4)){
						printf("Mauvaise entree...\n");
					}
				}while(!int_retour3 || (int_niveau_ia2 < 1 || int_niveau_ia2 > 4));

				jeux_IA_VS_IA (ej_jeux, int_niveau_ia1, int_niveau_ia2, 1);
				printf("\n");
				faire_pause();
				break;

			case 4 :
				do{
					printf("Entrez le niveau de la premiere IA (entre 1 et 4): ");
					int_retour3 = scanf("%d", &int_niveau_ia1);
					fflush(stdin);
					if(!int_retour3 || (int_niveau_ia1 < 1 || int_niveau_ia1 > 4)){
						printf("Mauvaise entree...\n");
					}
				}while(!int_retour3 || (int_niveau_ia1 < 1 || int_niveau_ia1 > 4));

				do{
					printf("Entrez le niveau de la deuxieme IA (entre 1 et 4): ");
					int_retour3 = scanf("%d", &int_niveau_ia2);
					fflush(stdin);
					if(!int_retour3 || (int_niveau_ia2 < 1 || int_niveau_ia2 > 4)){
						printf("Mauvaise entree...\n");
					}
				}while(!int_retour3 || (int_niveau_ia2 < 1 || int_niveau_ia2 > 4));

				do{
					printf("Entrez l'indice de stats (attention si l'on depasse 100 c'est tres long): ");
					int_retour3 = scanf("%d", &int_indice_stat);
					fflush(stdin);
					if(!int_retour3 || (int_indice_stat < 0)){
						printf("Mauvaise entree...\n");
					}
				}while(!int_retour3 || (int_indice_stat < 0));

				tint_stats = statistiques_ia(int_niveau_ia1, int_niveau_ia2, int_indice_stat, 1);
				if(tint_stats != NULL){
					free(tint_stats[0]);
					free(tint_stats[1]);
					free(tint_stats[2]);
					free(tint_stats);
				}else{
					printf("Une erreur s'est produite...\n");
				}
				faire_pause();
				break;

			case 5 :

				effacer_affichage();
				affiche_presentation_jeux();
				printf("Bientot disponnible.");
				printf("\n\n");
				faire_pause();
				break;

			case 6 :
				int_saisie = 0;
				break;

			default :
				break;
		}

	}while(!int_retour || int_saisie != 0 );

}
