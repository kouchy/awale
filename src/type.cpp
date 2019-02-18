/*! 
	\file    type.cpp
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Fichier qui contient toutes les fonctions et procédures relatives au type etat_jeux
	\remarks Aucune
*/

#include <stdlib.h>
#include <stdio.h>

#include "type.h"
#include "regles_jeux.h"
#include "in_out.h"
#include "ia.h"


void acc_e_points_j1(etat_jeux* pej_jeux, int int_points_joueur1){
	(*pej_jeux).int_points_joueur1 = int_points_joueur1;
}

void acc_e_points_j2(etat_jeux* pej_jeux, int int_points_joueur2){
	(*pej_jeux).int_points_joueur2 = int_points_joueur2;
}

void acc_e_trous(etat_jeux* pej_jeux, int* ptint_trous){
	for(int i=0; i<12; i++){
		(*pej_jeux).tint_trous[i] = ptint_trous[i];
	}
}

void acc_e_trou(etat_jeux* pej_jeux, int int_case,int int_valeur){
	(*pej_jeux).tint_trous[int_case] = int_valeur;
}

int acc_l_trous(etat_jeux ej_jeux, int int_case){

	//Comme les cases du tableaux sont forcément comprise entre 0 et 11 inclus si int_case diffère alors il y a un problème dans le programme
	if(int_case > 11 || int_case < 0){
		fprintf(stderr, "\nMauvais acces au tableau tint_trous dans la structure etat_jeux, case : %d\n", int_case);
		fprintf(stderr, "\nHey le pin'S tu sais plus coder (Adrien version)\nHey gros BolOSS retourne a l'EPSI (Romain et Guilhem version) !!!\n");
		
		pause(5000);
		return(0);
	}else{
		return(ej_jeux.tint_trous[int_case]);
	}
}

int acc_l_points_j1(etat_jeux ej_jeux){
	return(ej_jeux.int_points_joueur1);
}

int acc_l_points_j2(etat_jeux ej_jeux){
	return(ej_jeux.int_points_joueur2);
}

etat_jeux ini_etat_jeux (int int_points_joueur1, int int_points_joueur2, int* ptint_trous){

	etat_jeux ej_debut;

	acc_e_points_j1(&ej_debut, int_points_joueur1);
	acc_e_points_j2(&ej_debut, int_points_joueur2);
	acc_e_trous(&ej_debut, ptint_trous);

	return(ej_debut);

}

etat_jeux copie_etat_jeux(etat_jeux ej_jeux){

	etat_jeux ej_jeux_copie;

	acc_e_points_j1(&ej_jeux_copie, acc_l_points_j1(ej_jeux));
	acc_e_points_j2(&ej_jeux_copie, acc_l_points_j2(ej_jeux));

	for(int i=0 ; i<12 ; i++){
		acc_e_trou(&ej_jeux_copie, i, acc_l_trous(ej_jeux, i));
	}

	return(ej_jeux_copie);

}

