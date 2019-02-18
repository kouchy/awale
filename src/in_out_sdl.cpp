/*!
	\file    in_out_sdl.cpp
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Fichier qui contient toutes les fonctions et procédures relatives à la saisie et l'affichage en sdl
	\remarks Aucune

*/

#include <stdlib.h>
#include <stdio.h>
//#include <windows.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#ifdef AWALE_FMOD
#include <fmod.h>
#endif

#include "type.h"
#include "regles_jeux.h"
#include "in_out.h"
#include "in_out_sdl.h"
#include "ia.h"

int generateur_menu(char** tchar_titres_menu, elmts_graphiques elts_graphs, elmts_sonores elts_sons, etat_jeux ej_jeux, int bool_affiche_etat_jeux){

	SDL_Surface* texte_menu[5];
	SDL_Surface* texte_menu_s[5];
	SDL_Rect position_texte_menu[5];
	int bool_texte_menu[5] = {0, 0 , 0, 0, 0};
	int int_prem_pos = 30;
	int bool_continuer=1;
	int bool_passage=0;
	int int_selection=-1;

	SDL_Event event;

	//Création des surface textes du menu
	for(int i=0; i<5; i++){
		if(tchar_titres_menu[i][0] != '0'){
			if( i == 0 ){
				TTF_SetFontStyle(elts_graphs.ppolice_LTO1, TTF_STYLE_UNDERLINE);
				texte_menu[i] = TTF_RenderText_Blended(elts_graphs.ppolice_LTO1, tchar_titres_menu[i], elts_graphs.couleurBlanche);
				TTF_SetFontStyle(elts_graphs.ppolice_LTO1, TTF_STYLE_NORMAL);
			}else{
				TTF_SetFontStyle(elts_graphs.ppolice_LTO2, TTF_STYLE_ITALIC);
				texte_menu[i] = TTF_RenderText_Blended(elts_graphs.ppolice_LTO2, tchar_titres_menu[i], elts_graphs.couleurBlanche);

				TTF_SetFontStyle(elts_graphs.ppolice_LTO2, TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE);
				texte_menu_s[i] = TTF_RenderText_Blended(elts_graphs.ppolice_LTO2, tchar_titres_menu[i], elts_graphs.couleurBlanche);
				TTF_SetFontStyle(elts_graphs.ppolice_LTO2, TTF_STYLE_NORMAL);
			}
		}
	}

	//Création des positons
	int int_temp_pos = int_prem_pos;
	for(int i=0; i<5; i++){
		if(tchar_titres_menu[i][0] != '0'){
			position_texte_menu[i].x = (LARGEUR_FENETRE / 2) - texte_menu[i]->w/2;
			position_texte_menu[i].y = int_temp_pos;
		}
		if( i == 0 ){
			int_temp_pos += 60;
		}else{
			int_temp_pos += 50;
		}
	}

	while(bool_continuer){

		if(!bool_passage){
			SDL_PollEvent(&event);
			bool_passage = 1;
		}else{
			SDL_WaitEvent(&event);
		}

		switch(event.type){
            case SDL_QUIT:
                exit(0);
				break;

			//Si l'utilisateur appuie sur echap alors on sort du menu
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym){
					case SDLK_ESCAPE:
#ifdef AWALE_FMOD
						//Jouer le son de témoin de clic
						jouer_un_son(elts_sons.son_select_menu, elts_sons);
#endif
						int_selection = 0;
						bool_continuer = 0;
						break;
					default:
						break;
				}
				break;

			//On souligne si l'utilisateur à la souris sur un champ du menu
			case SDL_MOUSEMOTION:
				for(int i=0; i<5; i++){
					if(tchar_titres_menu[i][0] != '0'){
						if( (event.button.x > position_texte_menu[i].x && event.button.x < (position_texte_menu[i].x + texte_menu[i]->w)) && (event.button.y > position_texte_menu[i].y && event.button.y < (position_texte_menu[i].y + texte_menu[i]->h)) ){
							bool_texte_menu[i] = 1;
						}
					}
				}
				break;

			//On retourne le numéros du lien sur lequel l'utilisateur a cliqué
			case SDL_MOUSEBUTTONUP:
				for(int i=1; i<5; i++){
					if(tchar_titres_menu[i][0] != '0'){
						if( (event.button.x > position_texte_menu[i].x && event.button.x < (position_texte_menu[i].x + texte_menu[i]->w)) && (event.button.y > position_texte_menu[i].y && event.button.y < (position_texte_menu[i].y + texte_menu[i]->h)) ){

#ifdef FMOD
							//Jouer le son de témoin de clic
							jouer_un_son(elts_sons.son_select_menu, elts_sons);
#endif

							int_selection = i;
							bool_continuer = 0;
						}
					}
				}
				//On met l'évenement position souris à l'origine pour éviter qu'il n'interfère
				event.button.x = 0;
				event.button.y = 0;
				break;
			default:
				break;
		}

		//On affiche ici le menu à proprement parlé
		if(bool_affiche_etat_jeux){
			blit_jeux(elts_graphs,ej_jeux, 1);
		}else{
			blit_jeux(elts_graphs,ej_jeux, 0);
			SDL_BlitSurface(elts_graphs.psurf_image_bande_bas, NULL, elts_graphs.psurf_ecran, &elts_graphs.position_image_bande_bas);
		}
		SDL_BlitSurface(elts_graphs.psurf_image_menu, NULL, elts_graphs.psurf_ecran, &elts_graphs.position_image_menu);


		for(int i=0; i<5; i++){
			if(tchar_titres_menu[i][0] != '0'){
				if(bool_texte_menu[i] && (i != 0)){
					SDL_BlitSurface(texte_menu_s[i], NULL, elts_graphs.psurf_ecran, &position_texte_menu[i]);
					bool_texte_menu[i] = 0;
				}else{
					SDL_BlitSurface(texte_menu[i], NULL, elts_graphs.psurf_ecran, &position_texte_menu[i]);
				}
			}
		}

		SDL_Flip(elts_graphs.psurf_ecran); // Mise à jour de l'écran
	}

	//Libération de l'espace mémoire
	for(int i=0; i<5; i++){
		if(tchar_titres_menu[i][0] != '0'){
			SDL_FreeSurface(texte_menu[i]);
			if( i != 0 ){
				SDL_FreeSurface(texte_menu_s[i]);
			}
		}
	}

	return(int_selection);
}


void menu_awale_sdl(int socket, int int_joueur){

	SDL_Surface *ecran = NULL;
	elmts_graphiques elts_graphs;
	elmts_sonores elts_sons;
	int bool_continuer=1;
	int bool_affichage_shell=0;
	int bool_son_actif=1;
	int bool_affiche_etat_jeux=0;
	int int_niveau_ia;
	int int_selection;
	int int_points_joueur1=0;
	int int_points_joueur2=0;
	int tint_trous[12]={4,4,4,4,4,4,4,4,4,4,4,4};
	char* tchar_titres_menu[5];
	etat_jeux ej_jeux;

	//On initialise la variable ej_jeux
	ej_jeux = ini_etat_jeux(int_points_joueur1, int_points_joueur2, tint_trous);

	//On initialise la SDL ainsi que la librairie qui gère les polices et le son
	TTF_Init();
    SDL_Init(SDL_INIT_VIDEO);

#ifdef AWALE_FMOD
	//On lance Fmod la librairie qui gère le son
	FSOUND_Init(44100, 32, 0); //Qalité du son : CD
#endif

	ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Awale - Le jeu", NULL);

	//On charge les éléments graohiques et sonores
	charger_elmts_graphiques(&elts_graphs, ecran);
	charger_elmts_sonores(&elts_sons, bool_son_actif);

#ifdef AWALE_NETWORK
	if(socket){
		jeux_1_VS_1_RESEAU_SDL(ej_jeux, elts_graphs, elts_sons, bool_affichage_shell, int_joueur, socket);
	}
#endif

	/*
	for(int i=0; i<5; i++){
		tchar_titres_menu[i] = (char*)malloc(sizeof(char) * 60);
	}
	*/

	//On lance le menu et on le gère
	while(bool_continuer){

		tchar_titres_menu[0] = (char*)"Jeu de l'Awalé";
		tchar_titres_menu[1] = (char*)"Jouer en 1 contre 1";
		tchar_titres_menu[2] = (char*)"Jouer contre l'ordinateur";
		tchar_titres_menu[3] = (char*)"Options";
		tchar_titres_menu[4] = (char*)"Quitter le jeux";
		int_selection = generateur_menu(tchar_titres_menu, elts_graphs, elts_sons, ej_jeux, bool_affiche_etat_jeux);
		switch(int_selection){
			case 1:
				jeux_1_VS_1_SDL(ej_jeux, elts_graphs, elts_sons, bool_affichage_shell);
				break;
			case 2:
				tchar_titres_menu[0] = (char*)"Niveau de l'ordinateur";
				tchar_titres_menu[1] = (char*)"Facile";
				tchar_titres_menu[2] = (char*)"Moyen";
				tchar_titres_menu[3] = (char*)"Difficile";
				tchar_titres_menu[4] = (char*)"Retour au menu";
				int_selection = generateur_menu(tchar_titres_menu, elts_graphs, elts_sons, ej_jeux, bool_affiche_etat_jeux);
				switch(int_selection){
					case 1:
						int_niveau_ia = 2;
						break;
					case 2:
						int_niveau_ia = 3;
						break;
					case 3:
						int_niveau_ia = 4;
						break;
					case 4:
						int_niveau_ia = -1;
						break;
					default:
						int_niveau_ia = -1;
						break;
				}
				if(int_niveau_ia != -1){
					jeux_1_VS_IA_SDL(ej_jeux, int_niveau_ia, elts_graphs, elts_sons, bool_affichage_shell);
				}
				break;
			case 3:
				while(int_selection != 4 && int_selection != 0){
					tchar_titres_menu[0] = (char*)"Options";
					if((*elts_sons.bool_son_actif)){
						tchar_titres_menu[1] = (char*)"Son : Activé";
					}else{
						tchar_titres_menu[1] = (char*)"Son : Désactivé";
					}
					tchar_titres_menu[2] = (char*)"0";
					tchar_titres_menu[3] = (char*)"0";
					tchar_titres_menu[4] = (char*)"Retour au menu";
					int_selection = generateur_menu(tchar_titres_menu, elts_graphs, elts_sons, ej_jeux, bool_affiche_etat_jeux);
#ifdef AWALE_FMOD
					if(int_selection == 1){
						if((*elts_sons.bool_son_actif)){
							(*elts_sons.bool_son_actif) = 0;
						}else{
							(*elts_sons.bool_son_actif) = 1;
						}
					}
#endif
				}
				break;
			case 4:
				bool_continuer = 0;
				break;
			default:
				break;
		}

	}

	/*
	for(int i=0; i<5; i++){
		free(tchar_titres_menu[i]);
	}
	*/

	//Libération de l'espace mémoire occupé par les surface et les sons
	supprimer_elmts_graphiques(elts_graphs);
	supprimer_elmts_sonores(elts_sons);

	//On arrete SDL, TFT et FMOD
#ifdef AWALE_FMOD
	FSOUND_Close();
#endif
    TTF_Quit();
    SDL_Quit();

}


int jeux_1_VS_IA_SDL(etat_jeux ej_jeux, int int_niveau, elmts_graphiques elts_graphs, elmts_sonores elts_sons, int bool_affichage_shell){

	SDL_Surface *image_fleche = NULL, *texte_message = NULL, *image_fleche_blanche=NULL;
	SDL_Rect position_fleche, position_message, position_fleche_blanche;
	int tint_positions_trous[12][2];
	int tint_case_possible2[6];
	int* tint_case_possible1;
	int int_taille_case_possible2;
	int bool_continuer = 1;
	int bool_fleche = 0;
	int bool_passage_ia = 0;
	int int_nb_passage = 0;
	int int_case_jouer = 0;
	int int_joueur = 1;
	int vitesse_animation = 30;
	int int_vitesse_animation = 300;
	int temps_actuel=0;
	int temps_actuel2=0;
	int temps_precedent=0;
	int temps_precedent2=0;
	int temps_affichage=2000;
	char tchar_phrase[1024];
	char tchar_phrase_info[1024];
	SDL_Event event;
	etat_jeux ej_jeux_copie;

	//On remplit le tableau des position des trous
	positions_trous(tint_positions_trous);

	//Initialisation des positions
	position_message.x = 260;
	position_message.y = 130;

	//Chargement des images
	image_fleche = IMG_Load("../media/images/img_fleche.png");
	image_fleche_blanche = IMG_Load("../media/images/img_fleche3.png");

	do{
		//On gère le nombre d'image affiché par seconde ici FPS = 1000 / vitesse_animation
		temps_actuel = SDL_GetTicks();
		if (temps_actuel - temps_precedent > vitesse_animation){
			temps_precedent = temps_actuel;
		}else{
			SDL_Delay(vitesse_animation - (temps_actuel - temps_precedent));
		}

		int_case_jouer = -1; //On met -1 dans la case à joueur par défault
		SDL_PollEvent(&event); //On récupère les évènement (Non blocquant)

		if(int_joueur == 1){
			tint_case_possible1 = cases_jouables(ej_jeux, int_joueur); //On récupère le tableau des cases possibles à jouer
			int_taille_case_possible2 = tint_case_possible1[0]; //On récupère la taille du tableau des cases possibles à jouer
			//On recopie le tableau des cases possibles dans un tableau ou la preière case possible à joueur est d'indice 0
			for(int i=0; i<int_taille_case_possible2; i++){
				tint_case_possible2[i] = tint_case_possible1[i+1];
			}
			free(tint_case_possible1);//Libération de l'espace mémoire
		}

        switch(event.type){
            case SDL_QUIT:
				exit(0); //On quitte le prog si l'utilisateur le demande
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym){
					case SDLK_ESCAPE: //On quitte la partie en cours si le joueur appuie sur la touche echap
						bool_continuer = 0;
						event.key.keysym.sym = SDLK_t;
						break;
					case SDLK_p: //On quitte la partie en cours si le joueur appuie sur la touche echap
						jeux_en_pause(elts_graphs);
						event.key.keysym.sym = SDLK_t; //Empeche que la touche p soit prise en évènement ce qui ferai boucler le prog sur la pause.
						break;
					default:
						break;
				}
				break;

			case SDL_MOUSEMOTION:
				if(int_joueur == 1){
					for(int i=0; i<6; i++){
						if( (event.button.x > (tint_positions_trous[i][0] - 30) && event.button.x < (tint_positions_trous[i][0] + 30)) && (event.button.y > (tint_positions_trous[i][1] - 30) && event.button.y < (tint_positions_trous[i][1] + 30)) ){
							position_fleche.x = tint_positions_trous[i][0] - 15;
							position_fleche.y = tint_positions_trous[i][1] + 35;
							if(appartient_int_tab(i, tint_case_possible2, int_taille_case_possible2)){
								bool_fleche = 1;
							}
						}
					}
				}
				break;

			case SDL_MOUSEBUTTONUP:
				if(int_joueur == 1){
					for(int i=0; i<6; i++){
						if( (event.button.x > (tint_positions_trous[i][0] - 30) && event.button.x < (tint_positions_trous[i][0] + 30)) && (event.button.y > (tint_positions_trous[i][1] - 30) && event.button.y < (tint_positions_trous[i][1] + 30)) ){
							int_case_jouer = i;
						}
					}
					if(int_case_jouer != -1){
						if(!appartient_int_tab(int_case_jouer, tint_case_possible2, int_taille_case_possible2)){
							int_case_jouer = -1;
						}
					}
				}
				event.type = SDL_MOUSEBUTTONDOWN;//Empeche que si on ne bouge pas de position, la case et rejouer
				break;

			default:
				break;
        }

		sprintf(tchar_phrase_info, " ");
		if((int_joueur == 1 && int_case_jouer != -1) || int_joueur == 2){
			if(int_joueur == 2){
				temps_actuel2 = SDL_GetTicks();
				if(temps_actuel2 - temps_precedent2 >= temps_affichage){
					temps_precedent2 = temps_actuel2;
					if(int_nb_passage > 0){
						bool_passage_ia = 1;
						int_nb_passage = 0;
					}else{
						int_nb_passage++;
						sprintf(tchar_phrase_info, "L'ordinateur va jouer...");
					}
				}else{
					sprintf(tchar_phrase_info, "L'ordinateur va jouer...");
				}

			if(bool_passage_ia){
					int_case_jouer = jouer_IA(ej_jeux, int_niveau, int_joueur);
				}
			}
			if((int_joueur == 2 && bool_passage_ia) || int_joueur == 1){
				ej_jeux_copie = copie_etat_jeux(ej_jeux); //On copie l'état du jeux avant de jouer
				calcul_nouveau_tableau(&ej_jeux, int_case_jouer, 0); //On calcule le nouveau tableau
				bool_continuer = animation_distribution_graines(int_case_jouer, &ej_jeux_copie, elts_graphs, elts_sons, int_vitesse_animation); //On affiche la distribution des points
				if(bool_affichage_shell){
					affiche_etat_jeux(ej_jeux);	//On affiche l'état actuel du jeux
				}
			}

			//On change de joueur
			if( int_joueur == 1 ){
				int_joueur = 2;
			}else{
				if(bool_passage_ia){
					int_joueur = 1;
					bool_passage_ia = 0;
				}
			}
		}

		//On blite le jeux à l'écran
		blit_jeux(elts_graphs, ej_jeux, 1);

		if(int_joueur == 1){
			position_fleche_blanche.y = elts_graphs.position_texte_joueur1.y + 23;
			position_fleche_blanche.x = elts_graphs.position_texte_joueur1.x - image_fleche_blanche->w - 5;
		}else{
			position_fleche_blanche.y = elts_graphs.position_texte_joueur2.y + 23;
			position_fleche_blanche.x = elts_graphs.position_texte_joueur2.x - image_fleche_blanche->w - 5;
		}
		SDL_BlitSurface(image_fleche_blanche, NULL, elts_graphs.psurf_ecran, &position_fleche_blanche);

		//Si le joueur est sur un trou ou il peut jouer on blite la fleche d'indication
		if(bool_fleche){
			SDL_BlitSurface(image_fleche, NULL, elts_graphs.psurf_ecran, &position_fleche);
			bool_fleche = 0;
		}

		//On blite texte_message
		if(!bool_continuer){
			sprintf(tchar_phrase_info, " ");
		}
		texte_message = TTF_RenderText_Blended(elts_graphs.ppolice_LTO2, tchar_phrase_info, elts_graphs.couleurBlanche);
		SDL_BlitSurface(texte_message, NULL, elts_graphs.psurf_ecran, &position_message);

		//Mise à jour de l'écran
		SDL_Flip(elts_graphs.psurf_ecran);

		//Libération de l'espace mémoire utilisé par le texte_message
		SDL_FreeSurface(texte_message);

	}while(!fin_de_partie(&ej_jeux, int_joueur) && bool_continuer);

	//On affiche le vainqueur de la partie
	if( affiche_et_retourne_vainqueur(ej_jeux, 0) == 1 ) {
		sprintf(tchar_phrase, "Vous remportez la victoire !");
#ifdef AWALE_FMOD
		jouer_un_son(elts_sons.son_win, elts_sons);
#endif
	}else{
		if(affiche_et_retourne_vainqueur(ej_jeux, 0) == 2){
			sprintf(tchar_phrase, "L'ordinateur remporte la victoire !");
#ifdef AWALE_FMOD
			jouer_un_son(elts_sons.son_loose, elts_sons);
#endif
		}else{
			sprintf(tchar_phrase, "Personne ne remporte cette partie.");
		}
	}
	texte_message = TTF_RenderText_Blended(elts_graphs.ppolice_LTO2, tchar_phrase, elts_graphs.couleurBlanche);
	position_message.x = LARGEUR_FENETRE/2 - texte_message->w/2;
	SDL_BlitSurface(texte_message, NULL, elts_graphs.psurf_ecran, &position_message);

	//On rafraichie l'écran
	SDL_Flip(elts_graphs.psurf_ecran);

	//On libére l'espace mémoire occupé par les surfaces
	SDL_FreeSurface(texte_message);
	SDL_FreeSurface(image_fleche);

	pause();

	return(affiche_et_retourne_vainqueur(ej_jeux, bool_affichage_shell));

}

int jeux_1_VS_1_SDL(etat_jeux ej_jeux, elmts_graphiques elts_graphs, elmts_sonores elts_sons, int bool_affichage_shell){

	SDL_Surface *image_fleche = NULL, *image_fleche2 = NULL, *image_fleche_blanche = NULL, *texte_message = NULL;
	SDL_Rect position_fleche, position_fleche_blanche, position_message;
	int tint_positions_trous[12][2];
	int tint_case_possible2[6];
	int* tint_case_possible1;
	int int_taille_case_possible2;
	int bool_continuer = 1;
	int bool_fleche = 0;
	int int_case_jouer = 0;
	int int_joueur = 1;
	int vitesse_animation = 30;
	int int_vitesse_animation = 300;
	int temps_actuel=0;
	int temps_precedent=0;
	char tchar_phrase[1024];
	SDL_Event event;
	etat_jeux ej_jeux_copie;

	//On remplit le tableau des position des trous
	positions_trous(tint_positions_trous);

	//Initialisation des positions
	position_message.x = 260;
	position_message.y = 130;

	//Chargement des images
	image_fleche = IMG_Load("../media/images/img_fleche.png");
	image_fleche2 = IMG_Load("../media/images/img_fleche2.png");
	image_fleche_blanche = IMG_Load("../media/images/img_fleche3.png");

	do{
		//On gère le nombre d'image affiché par seconde ici FPS = 1000 / vitesse_animation
		temps_actuel = SDL_GetTicks();
		if (temps_actuel - temps_precedent > vitesse_animation){
			temps_precedent = temps_actuel;
		}else{
			SDL_Delay(vitesse_animation - (temps_actuel - temps_precedent));
		}

		int_case_jouer = -1; //On met -1 dans la case à joueur par défault
		SDL_PollEvent(&event); //On récupère les évènement (Non blocquant)


		tint_case_possible1 = cases_jouables(ej_jeux, int_joueur); //On récupère le tableau des cases possibles à jouer
		int_taille_case_possible2 = tint_case_possible1[0]; //On récupère la taille du tableau des cases possibles à jouer
		//On recopie le tableau des cases possibles dans un tableau ou la preière case possible à joueur est d'indice 0
		for(int i=0; i<int_taille_case_possible2; i++){
			tint_case_possible2[i] = tint_case_possible1[i+1];
		}
		free(tint_case_possible1);//Libération de l'espace mémoire


        switch(event.type){
            case SDL_QUIT:
				exit(0); //On quitte le prog si l'utilisateur le demande
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym){
					case SDLK_ESCAPE: //On quitte la partie en cours si le joueur appuie sur la touche echap
						bool_continuer = 0;
						event.key.keysym.sym = SDLK_t;
						break;
					case SDLK_p: //On quitte la partie en cours si le joueur appuie sur la touche echap
						jeux_en_pause(elts_graphs);
						event.key.keysym.sym = SDLK_t; //Empeche que la touche p soit prise en évènement ce qui ferai boucler le prog sur la pause.
						break;
					default:
						break;
				}
				break;

			case SDL_MOUSEMOTION:
				if(int_joueur == 1){
					for(int i=0; i<6; i++){
						if( (event.button.x > (tint_positions_trous[i][0] - 30) && event.button.x < (tint_positions_trous[i][0] + 30)) && (event.button.y > (tint_positions_trous[i][1] - 30) && event.button.y < (tint_positions_trous[i][1] + 30)) ){
							position_fleche.x = tint_positions_trous[i][0] - 15;
							position_fleche.y = tint_positions_trous[i][1] + 35;
							if(appartient_int_tab(i, tint_case_possible2, int_taille_case_possible2)){
								bool_fleche = 1;
							}
						}
					}
				}else{
					for(int i=6; i<12; i++){
						if( (event.button.x > (tint_positions_trous[i][0] - 30) && event.button.x < (tint_positions_trous[i][0] + 30)) && (event.button.y > (tint_positions_trous[i][1] - 30) && event.button.y < (tint_positions_trous[i][1] + 30)) ){
							position_fleche.x = tint_positions_trous[i][0] - 15;
							position_fleche.y = tint_positions_trous[i][1] - 35 - image_fleche2->h;
							if(appartient_int_tab(i, tint_case_possible2, int_taille_case_possible2)){
								bool_fleche = 1;
							}
						}
					}
				}
				break;

			case SDL_MOUSEBUTTONUP:
				//if(int_joueur == 1){
					for(int i=0; i<12; i++){
						if( (event.button.x > (tint_positions_trous[i][0] - 30) && event.button.x < (tint_positions_trous[i][0] + 30)) && (event.button.y > (tint_positions_trous[i][1] - 30) && event.button.y < (tint_positions_trous[i][1] + 30)) ){
							int_case_jouer = i;
						}
					}
					if(int_case_jouer != -1){
						if(!appartient_int_tab(int_case_jouer, tint_case_possible2, int_taille_case_possible2)){
							int_case_jouer = -1;
						}
					}
				//}
				event.type = SDL_MOUSEBUTTONDOWN;//Empeche que si on ne bouge pas de position, la case et rejouer
				break;

			default:
				break;
        }

		if( int_case_jouer != -1 ){

			ej_jeux_copie = copie_etat_jeux(ej_jeux); //On copie l'état du jeux avant de jouer
			calcul_nouveau_tableau(&ej_jeux, int_case_jouer, 0); //On calcule le nouveau tableau
			bool_continuer = animation_distribution_graines(int_case_jouer, &ej_jeux_copie, elts_graphs, elts_sons, int_vitesse_animation); //On affiche la distribution des points
			if(bool_affichage_shell){
				affiche_etat_jeux(ej_jeux);	//On affiche l'état actuel du jeux
			}

			//On change de joueur
			if( int_joueur == 1 ){
				int_joueur = 2;
			}else{
				int_joueur = 1;
			}
		}

		//On blite le jeux à l'écran
		blit_jeux(elts_graphs, ej_jeux, 1);

		//Si le joueur est sur un trou ou il peut jouer on blite la fleche d'indication
		if(bool_fleche){
			if(int_joueur == 1){
				SDL_BlitSurface(image_fleche, NULL, elts_graphs.psurf_ecran, &position_fleche);
			}else{
				SDL_BlitSurface(image_fleche2, NULL, elts_graphs.psurf_ecran, &position_fleche);
			}
			bool_fleche = 0;
		}

		if(int_joueur == 1){
			position_fleche_blanche.y = elts_graphs.position_texte_joueur1.y + 23;
			position_fleche_blanche.x = elts_graphs.position_texte_joueur1.x - image_fleche_blanche->w - 5;
		}else{
			position_fleche_blanche.y = elts_graphs.position_texte_joueur2.y + 23;
			position_fleche_blanche.x = elts_graphs.position_texte_joueur2.x - image_fleche_blanche->w - 5;
		}
		SDL_BlitSurface(image_fleche_blanche, NULL, elts_graphs.psurf_ecran, &position_fleche_blanche);

		//Mise à jour de l'écran
		SDL_Flip(elts_graphs.psurf_ecran);

		//Libération de l'espace mémoire utilisé par le texte_message
		SDL_FreeSurface(texte_message);

	}while(!fin_de_partie(&ej_jeux, int_joueur) && bool_continuer);

	//On affiche le vainqueur de la partie
	if( affiche_et_retourne_vainqueur(ej_jeux, 0) == 1 ) {
		sprintf(tchar_phrase, "Le joueur 1 remporte la victoire !");
#ifdef AWALE_FMOD
		jouer_un_son(elts_sons.son_sifflet, elts_sons);
#endif
	}else{
		if(affiche_et_retourne_vainqueur(ej_jeux, 0) == 2){
			sprintf(tchar_phrase, "Le joueur 2 remporte la victoire !");
#ifdef AWALE_FMOD
			jouer_un_son(elts_sons.son_sifflet, elts_sons);
#endif
		}else{
			sprintf(tchar_phrase, "Personne ne remporte cette partie.");
		}
	}
	texte_message = TTF_RenderText_Blended(elts_graphs.ppolice_LTO2, tchar_phrase, elts_graphs.couleurBlanche);
	position_message.x = LARGEUR_FENETRE/2 - texte_message->w/2;
	SDL_BlitSurface(texte_message, NULL, elts_graphs.psurf_ecran, &position_message);

	//On rafraichie l'écran
	SDL_Flip(elts_graphs.psurf_ecran);

	//On libére l'espace mémoire occupé par les surfaces
	SDL_FreeSurface(texte_message);
	SDL_FreeSurface(image_fleche);

	pause();

	return(affiche_et_retourne_vainqueur(ej_jeux, bool_affichage_shell));

}

#ifdef AWALE_NETWORK
int jeux_1_VS_1_RESEAU_SDL(etat_jeux ej_jeux, elmts_graphiques elts_graphs, elmts_sonores elts_sons, int bool_affichage_shell, int int_joueur, int socket){

	SDL_Surface *image_fleche = NULL, *image_fleche2 = NULL, *image_fleche_blanche = NULL, *texte_message = NULL;
	SDL_Rect position_fleche, position_fleche_blanche, position_message;
	int tint_positions_trous[12][2];
	int tint_case_possible2[6];
	int* tint_case_possible1;
	int int_taille_case_possible2;
	int bool_continuer = 1;
	int bool_fleche = 0;
	int int_case_jouer = 0;
	int int_joueur_qui_doit_jouer = 1;
	int int_joueur_adverse;
	int vitesse_animation = 30;
	int int_vitesse_animation = 300;
	int temps_actuel=0;
	int temps_precedent=0;
	int int_nb_eve;
	char tchar_phrase[1024];
	SDL_Event event;
	etat_jeux ej_jeux_copie;
	char buffer_case_jouer[1];
	fd_set fd_set_sok;
	timeval timeval_temps;
	timeval_temps.tv_sec = 0;
	timeval_temps.tv_usec = 1;
	fd_set_sok.fd_count=1;
	fd_set_sok.fd_array[0] = socket;

	if(int_joueur == 1){
		int_joueur_adverse = 2;
	}else{
		int_joueur_adverse = 1;
	}

	//On remplit le tableau des position des trous
	positions_trous(tint_positions_trous);

	//Initialisation des positions
	position_message.x = 260;
	position_message.y = 130;

	//Chargement des images
	image_fleche = IMG_Load("../media/images/img_fleche.png");
	image_fleche2 = IMG_Load("../media/images/img_fleche2.png");
	image_fleche_blanche = IMG_Load("../media/images/img_fleche3.png");

	do{
		//On gère le nombre d'image affiché par seconde ici FPS = 1000 / vitesse_animation
		temps_actuel = SDL_GetTicks();
		if (temps_actuel - temps_precedent > vitesse_animation){
			temps_precedent = temps_actuel;
		}else{
			SDL_Delay(vitesse_animation - (temps_actuel - temps_precedent));
		}

		int_case_jouer = -1; //On met -1 dans la case à joueur par défault
		SDL_PollEvent(&event); //On récupère les évènement (Non blocquant)


		tint_case_possible1 = cases_jouables(ej_jeux, int_joueur); //On récupère le tableau des cases possibles à jouer
		int_taille_case_possible2 = tint_case_possible1[0]; //On récupère la taille du tableau des cases possibles à jouer
		//On recopie le tableau des cases possibles dans un tableau ou la preière case possible à joueur est d'indice 0
		for(int i=0; i<int_taille_case_possible2; i++){
			tint_case_possible2[i] = tint_case_possible1[i+1];
		}
		free(tint_case_possible1);//Libération de l'espace mémoire


        switch(event.type){
            case SDL_QUIT:
				exit(0); //On quitte le prog si l'utilisateur le demande
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym){
					case SDLK_ESCAPE: //On quitte la partie en cours si le joueur appuie sur la touche echap
						bool_continuer = 0;
						event.key.keysym.sym = SDLK_t;
						break;
					case SDLK_p: //On quitte la partie en cours si le joueur appuie sur la touche echap
						jeux_en_pause(elts_graphs);
						event.key.keysym.sym = SDLK_t; //Empeche que la touche p soit prise en évènement ce qui ferai boucler le prog sur la pause.
						break;

				}
				break;

			case SDL_MOUSEMOTION:
				if(int_joueur == 1){
					for(int i=0; i<6; i++){
						if( (event.button.x > (tint_positions_trous[i][0] - 30) && event.button.x < (tint_positions_trous[i][0] + 30)) && (event.button.y > (tint_positions_trous[i][1] - 30) && event.button.y < (tint_positions_trous[i][1] + 30)) ){
							position_fleche.x = tint_positions_trous[i][0] - 15;
							position_fleche.y = tint_positions_trous[i][1] + 35;
							if(appartient_int_tab(i, tint_case_possible2, int_taille_case_possible2)){
								bool_fleche = 1;
							}
						}
					}
				}else{
					for(int i=6; i<12; i++){
						if( (event.button.x > (tint_positions_trous[i][0] - 30) && event.button.x < (tint_positions_trous[i][0] + 30)) && (event.button.y > (tint_positions_trous[i][1] - 30) && event.button.y < (tint_positions_trous[i][1] + 30)) ){
							position_fleche.x = tint_positions_trous[i][0] - 15;
							position_fleche.y = tint_positions_trous[i][1] - 35 - image_fleche2->h;
							if(appartient_int_tab(i, tint_case_possible2, int_taille_case_possible2)){
								bool_fleche = 1;
							}
						}
					}
				}
				break;

			case SDL_MOUSEBUTTONUP:
				//if(int_joueur == 1){
					for(int i=0; i<12; i++){
						if( (event.button.x > (tint_positions_trous[i][0] - 30) && event.button.x < (tint_positions_trous[i][0] + 30)) && (event.button.y > (tint_positions_trous[i][1] - 30) && event.button.y < (tint_positions_trous[i][1] + 30)) ){
							int_case_jouer = i;
						}
					}
					if(int_case_jouer != -1){
						if(!appartient_int_tab(int_case_jouer, tint_case_possible2, int_taille_case_possible2)){
							int_case_jouer = -1;
						}
					}
				//}
				event.type = SDL_MOUSEBUTTONDOWN;//Empeche que si on ne bouge pas de position, la case et rejouer
				break;

			default:
				break;
        }

		if(int_joueur_qui_doit_jouer != int_joueur){

			fd_set_sok.fd_count=1;
			//if(int select(int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, const struct timeval* timeout)){
			int_nb_eve = select(socket, &fd_set_sok, NULL, NULL, &timeval_temps);
			if(int_nb_eve>0){
				if(recv(socket, buffer_case_jouer, sizeof(char), 0) != SOCKET_ERROR){
					int_case_jouer = buffer_case_jouer[0];
					ej_jeux_copie = copie_etat_jeux(ej_jeux); //On copie l'état du jeux avant de jouer
					calcul_nouveau_tableau(&ej_jeux, int_case_jouer, 0); //On calcule le nouveau tableau
					bool_continuer = animation_distribution_graines(int_case_jouer, &ej_jeux_copie, elts_graphs, elts_sons, int_vitesse_animation); //On affiche la distribution des points

					if(bool_affichage_shell){
						affiche_etat_jeux(ej_jeux);	//On affiche l'état actuel du jeux
					}

					int_joueur_qui_doit_jouer = int_joueur;
				}

			}

		}else{
			if( int_case_jouer != -1 ){

				ej_jeux_copie = copie_etat_jeux(ej_jeux); //On copie l'état du jeux avant de jouer
				calcul_nouveau_tableau(&ej_jeux, int_case_jouer, 0); //On calcule le nouveau tableau
				buffer_case_jouer[0] = int_case_jouer;
				while(send(socket, buffer_case_jouer, sizeof(char), 0) == SOCKET_ERROR);

				bool_continuer = animation_distribution_graines(int_case_jouer, &ej_jeux_copie, elts_graphs, elts_sons, int_vitesse_animation); //On affiche la distribution des points
				if(bool_affichage_shell){
					affiche_etat_jeux(ej_jeux);	//On affiche l'état actuel du jeux
				}

				int_joueur_qui_doit_jouer = int_joueur_adverse;

			}
		}

		//On blite le jeux à l'écran
		blit_jeux(elts_graphs, ej_jeux, 1);

		//Si le joueur est sur un trou ou il peut jouer on blite la fleche d'indication
		if(bool_fleche){
			if(int_joueur == 1){
				SDL_BlitSurface(image_fleche, NULL, elts_graphs.psurf_ecran, &position_fleche);
			}else{
				SDL_BlitSurface(image_fleche2, NULL, elts_graphs.psurf_ecran, &position_fleche);
			}
			bool_fleche = 0;
		}

		if(int_joueur_qui_doit_jouer == 1){
			position_fleche_blanche.y = elts_graphs.position_texte_joueur1.y + 23;
			position_fleche_blanche.x = elts_graphs.position_texte_joueur1.x - image_fleche_blanche->w - 5;
		}else{
			position_fleche_blanche.y = elts_graphs.position_texte_joueur2.y + 23;
			position_fleche_blanche.x = elts_graphs.position_texte_joueur2.x - image_fleche_blanche->w - 5;
		}
		SDL_BlitSurface(image_fleche_blanche, NULL, elts_graphs.psurf_ecran, &position_fleche_blanche);

		//Mise à jour de l'écran
		SDL_Flip(elts_graphs.psurf_ecran);

		//Libération de l'espace mémoire utilisé par le texte_message
		SDL_FreeSurface(texte_message);

	}while(!fin_de_partie(&ej_jeux, int_joueur_qui_doit_jouer) && bool_continuer);

	//On affiche le vainqueur de la partie
	if( affiche_et_retourne_vainqueur(ej_jeux, 0) == int_joueur) {
		sprintf(tchar_phrase, "Vous remportez la victoire !");
#ifdef AWALE_FMOD
		jouer_un_son(elts_sons.son_win, elts_sons);
#endif
	}else{
		if(affiche_et_retourne_vainqueur(ej_jeux, 0) == int_joueur_adverse){
			sprintf(tchar_phrase, "Vous avez perdu...");
#ifdef AWALE_FMOD
			jouer_un_son(elts_sons.son_loose, elts_sons);
#endif
		}else{
			sprintf(tchar_phrase, "Personne ne remporte cette partie.");
		}
	}
	texte_message = TTF_RenderText_Blended(elts_graphs.ppolice_LTO2, tchar_phrase, elts_graphs.couleurBlanche);
	position_message.x = LARGEUR_FENETRE/2 - texte_message->w/2;
	SDL_BlitSurface(texte_message, NULL, elts_graphs.psurf_ecran, &position_message);

	//On rafraichie l'écran
	SDL_Flip(elts_graphs.psurf_ecran);

	//On libére l'espace mémoire occupé par les surfaces
	SDL_FreeSurface(texte_message);
	SDL_FreeSurface(image_fleche);

	pause();

	return(affiche_et_retourne_vainqueur(ej_jeux, bool_affichage_shell));

}
#endif

void positions_trous(int tint_positions_trous[12][2]){
	tint_positions_trous[0][0] = 116;
	tint_positions_trous[0][1] = 224;
	tint_positions_trous[1][0] = 236;
	tint_positions_trous[1][1] = 224;
	tint_positions_trous[2][0] = 344;
	tint_positions_trous[2][1] = 224;
	tint_positions_trous[3][0] = 450;
	tint_positions_trous[3][1] = 224;
	tint_positions_trous[4][0] = 560;
	tint_positions_trous[4][1] = 224;
	tint_positions_trous[5][0] = 677;
	tint_positions_trous[5][1] = 224;
	tint_positions_trous[6][0] = 677;
	tint_positions_trous[6][1] = 89;
	tint_positions_trous[7][0] = 560;
	tint_positions_trous[7][1] = 89;
	tint_positions_trous[8][0] = 450;
	tint_positions_trous[8][1] = 89;
	tint_positions_trous[9][0] = 344;
	tint_positions_trous[9][1] = 89;
	tint_positions_trous[10][0] = 236;
	tint_positions_trous[10][1] = 89;
	tint_positions_trous[11][0] = 116;
	tint_positions_trous[11][1] = 89;
}

void jeux_en_pause(elmts_graphiques elts_graphs){

	char tchar_phrase[1024];

	//On charge les textes qui affiche les points des joueurs
	sprintf(tchar_phrase, "Pause...");
	elts_graphs.psurf_texte_pause = TTF_RenderText_Blended(elts_graphs.ppolice_LTO1, tchar_phrase, elts_graphs.couleurBlanche);

    int continuer = 1;
    SDL_Event event;

	//On change la position du texte
	elts_graphs.position_texte_pause.x = (LARGEUR_FENETRE / 2) - (elts_graphs.psurf_texte_pause->w / 2);;
	elts_graphs.position_texte_pause.y = (320 / 2) - (elts_graphs.psurf_texte_pause->h / 2);;

	//On blite les surfaces
	SDL_BlitSurface(elts_graphs.psurf_image_pause, NULL, elts_graphs.psurf_ecran, &elts_graphs.position_pause);
	SDL_BlitSurface(elts_graphs.psurf_texte_pause, NULL, elts_graphs.psurf_ecran, &elts_graphs.position_texte_pause);
	SDL_Flip(elts_graphs.psurf_ecran);
	SDL_FreeSurface(elts_graphs.psurf_texte_pause);
	elts_graphs.psurf_texte_pause = NULL;

    while (continuer){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                exit(0);
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym){
					case SDLK_ESCAPE:
						continuer = 0;
						break;
					case SDLK_p:
						continuer = 0;
						break;
					default:
						break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				continuer = 0;
				break;
			default:
				break;
        }
    }
}

void blit_jeux(elmts_graphiques elts_graphs, etat_jeux ej_jeux, int bool_affiche_etat_jeux){

	char tchar_phrase[1024];
	int tint_positions_trous[12][2];

	//On remplit le tableau des position des trous
	positions_trous(tint_positions_trous);

	//On rafraichie l'écran
	SDL_FillRect(elts_graphs.psurf_ecran, NULL, SDL_MapRGB(elts_graphs.psurf_ecran->format, 105, 53, 31));

	//On blite l'image de fond
	SDL_BlitSurface(elts_graphs.psurf_image_fond_jeux, NULL, elts_graphs.psurf_ecran, &(elts_graphs.position_fond_jeux));

	//On blite la séparation
	SDL_BlitSurface(elts_graphs.psurf_barre_separation, NULL, elts_graphs.psurf_ecran, &(elts_graphs.position_barre_separation));

	if(bool_affiche_etat_jeux){

		//On charge les textes qui affiche les points des joueurs
		sprintf(tchar_phrase, "Joueur 1 : %d points", acc_l_points_j1(ej_jeux));
		elts_graphs.psurf_texte_joueur1 = TTF_RenderText_Blended(elts_graphs.ppolice_LTO1, tchar_phrase, elts_graphs.couleurBlanche);

		sprintf(tchar_phrase, "Joueur 2 : %d points", acc_l_points_j2(ej_jeux));
		elts_graphs.psurf_texte_joueur2 = TTF_RenderText_Blended(elts_graphs.ppolice_LTO1, tchar_phrase, elts_graphs.couleurBlanche);

		//On blite les textes correspondant on nombre de graines dans les trous
		for(int i=0; i<12; i++){
			sprintf(tchar_phrase, "%d", acc_l_trous(ej_jeux, i));
			elts_graphs.psurf_texte_points = TTF_RenderText_Blended(elts_graphs.ppolice_LTO1, tchar_phrase, elts_graphs.couleurBlanche);
			elts_graphs.position_points.x = tint_positions_trous[i][0] - ((elts_graphs.psurf_texte_points->w)/2);
			elts_graphs.position_points.y = tint_positions_trous[i][1] - ((elts_graphs.psurf_texte_points->h)/2);
			SDL_BlitSurface(elts_graphs.psurf_texte_points, NULL, elts_graphs.psurf_ecran, &elts_graphs.position_points);
			SDL_FreeSurface(elts_graphs.psurf_texte_points);
			elts_graphs.psurf_texte_points = NULL;
		}

		//On blite les point des joueurs
		SDL_BlitSurface(elts_graphs.psurf_texte_joueur1, NULL, elts_graphs.psurf_ecran, &elts_graphs.position_texte_joueur1);
		SDL_BlitSurface(elts_graphs.psurf_texte_joueur2, NULL, elts_graphs.psurf_ecran, &elts_graphs.position_texte_joueur2);

		//Libération de l'espace mémoire utilisé par les surfaces textes
		SDL_FreeSurface(elts_graphs.psurf_texte_joueur1);
		elts_graphs.psurf_texte_joueur1 = NULL;
		SDL_FreeSurface(elts_graphs.psurf_texte_joueur2);
		elts_graphs.psurf_texte_joueur2 = NULL;

	}

}


void charger_elmts_graphiques(elmts_graphiques* elts_graphs, SDL_Surface *ecran){

	elts_graphs->couleurBlanche.r = 255;
	elts_graphs->couleurBlanche.g = 255;
	elts_graphs->couleurBlanche.b = 255;

	elts_graphs->position_barre_separation.x = 0;
	elts_graphs->position_barre_separation.y = 320;
	elts_graphs->position_fond_jeux.x = 0;
	elts_graphs->position_fond_jeux.y = 0;
	elts_graphs->position_points.x = 0;
	elts_graphs->position_points.y = 0;
	elts_graphs->position_texte_joueur1.x = 50;
	elts_graphs->position_texte_joueur1.y = HAUTEUR_FENETRE - 75;
	elts_graphs->position_texte_joueur2.x = (LARGEUR_FENETRE / 2) + 50;
	elts_graphs->position_texte_joueur2.y = HAUTEUR_FENETRE - 75;
	elts_graphs->position_texte_pause.x = 0;
	elts_graphs->position_texte_pause.y = 0;

	elts_graphs->ppolice_LTO1 = TTF_OpenFont("../media/fonts/LITTLELO.TTF", 65);
	elts_graphs->ppolice_LTO2 = TTF_OpenFont("../media/fonts/LITTLELO.TTF", 50);

	elts_graphs->psurf_barre_separation = SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR_FENETRE, 5, 32, 0, 0, 0, 0);
	SDL_FillRect(elts_graphs->psurf_barre_separation, NULL, SDL_MapRGB(ecran->format, 65, 32, 21));
	elts_graphs->psurf_ecran = ecran;
	elts_graphs->psurf_image_fond_jeux = IMG_Load("../media/images/img_awale_jeux.jpg");
	elts_graphs->psurf_image_pause = IMG_Load("../media/images/img_awale_pause.png");
	elts_graphs->psurf_image_menu = IMG_Load("../media/images/img_awale_menu.png");
	elts_graphs->position_pause.x = (LARGEUR_FENETRE / 2) - (elts_graphs->psurf_image_pause->w / 2);
	elts_graphs->position_pause.y = (HAUTEUR_JEUX  / 2) - (elts_graphs->psurf_image_pause->h / 2);
	elts_graphs->position_image_menu.x = (LARGEUR_FENETRE / 2) - (elts_graphs->psurf_image_menu->w / 2);
	elts_graphs->position_image_menu.y = (HAUTEUR_JEUX  / 2) - (elts_graphs->psurf_image_menu->h / 2);
	elts_graphs->psurf_texte_joueur1 = NULL;
	elts_graphs->psurf_texte_joueur2 = NULL;
	elts_graphs->psurf_texte_pause = NULL;
	elts_graphs->psurf_texte_points = NULL;

	elts_graphs->psurf_image_bande_bas = IMG_Load("../media/images/img_awale_bande2.jpg");
	elts_graphs->position_image_bande_bas.x = 0;
	elts_graphs->position_image_bande_bas.y = elts_graphs->psurf_image_fond_jeux->h + elts_graphs->psurf_barre_separation->h;

}

void supprimer_elmts_graphiques(elmts_graphiques elts_graphs){

	if(elts_graphs.ppolice_LTO1 != NULL){
		TTF_CloseFont(elts_graphs.ppolice_LTO1);
	}
	if(elts_graphs.ppolice_LTO2 != NULL){
		TTF_CloseFont(elts_graphs.ppolice_LTO2);
	}
	if(elts_graphs.psurf_barre_separation != NULL){
		SDL_FreeSurface(elts_graphs.psurf_barre_separation);
	}
	if(elts_graphs.psurf_image_fond_jeux != NULL){
		SDL_FreeSurface(elts_graphs.psurf_image_fond_jeux);
	}
	if(elts_graphs.psurf_texte_joueur1 != NULL){
		SDL_FreeSurface(elts_graphs.psurf_texte_joueur1);
	}
	if(elts_graphs.psurf_texte_joueur2 != NULL){
		SDL_FreeSurface(elts_graphs.psurf_texte_joueur2);
	}
	if(elts_graphs.psurf_texte_points != NULL){
		SDL_FreeSurface(elts_graphs.psurf_texte_points);
	}
	if(elts_graphs.psurf_texte_pause != NULL){
		SDL_FreeSurface(elts_graphs.psurf_texte_pause);
	}
	if(elts_graphs.psurf_image_pause != NULL){
		SDL_FreeSurface(elts_graphs.psurf_image_pause);
	}
	if(elts_graphs.psurf_image_bande_bas != NULL){
		SDL_FreeSurface(elts_graphs.psurf_image_bande_bas);
	}

}

void charger_elmts_sonores(elmts_sonores* elts_sons, int bool_son_actif){

	elts_sons->bool_son_actif = (int*)malloc(sizeof(int));
#ifdef AWALE_FMOD
	(*elts_sons->bool_son_actif) = bool_son_actif;
	elts_sons->son_check = FSOUND_Sample_Load(FSOUND_FREE, "../media/sons/bois1.mp3", 0, 0, 0);
	elts_sons->son_distribution = FSOUND_Sample_Load(FSOUND_FREE, "../media/sons/bois3.mp3", 0, 0, 0);
	elts_sons->son_select_menu = FSOUND_Sample_Load(FSOUND_FREE, "../media/sons/bois2.mp3", 0, 0, 0);
	elts_sons->son_loose = FSOUND_Sample_Load(FSOUND_FREE, "../media/sons/loose.mp3", 0, 0, 0);
	elts_sons->son_win = FSOUND_Sample_Load(FSOUND_FREE, "../media/sons/win.mp3", 0, 0, 0);
	elts_sons->son_sifflet = FSOUND_Sample_Load(FSOUND_FREE, "../media/sons/sifflet.wav", 0, 0, 0);
#else
	(*elts_sons->bool_son_actif) = 0;
#endif

}

void supprimer_elmts_sonores(elmts_sonores elts_sons){

#ifdef AWALE_FMOD
	FSOUND_Sample_Free(elts_sons.son_check);
	FSOUND_Sample_Free(elts_sons.son_distribution);
	FSOUND_Sample_Free(elts_sons.son_select_menu);
	FSOUND_Sample_Free(elts_sons.son_loose);
	FSOUND_Sample_Free(elts_sons.son_win);
	FSOUND_Sample_Free(elts_sons.son_sifflet);
#endif
	free(elts_sons.bool_son_actif);

}



int animation_distribution_graines(int int_case, etat_jeux* pej_jeux, elmts_graphiques elts_graphs, elmts_sonores elts_sons, int int_vitesse_animation){

	int int_final_case ;
	int j=0;
	int tint_cases_ennemi[6]; //Contient les cases de l'ennemi (à déduire en fonction de int_case)
	int int_der_case; //Contiendra la dernière case joué
	int total_points;

	int_final_case = int_case + acc_l_trous((*pej_jeux), int_case); //On calcule la dernière case jusqu'a laquelle on distribut des jetons

	acc_e_trou(pej_jeux, int_case, 0); // On enlève tout les jetons dans la case choisi par l'utilisateur

#ifdef AWALE_FMOD
	jouer_un_son(elts_sons.son_check, elts_sons);
#endif

	//Attente et affichage
	if(!attente_et_affichage_sdl(int_vitesse_animation, elts_graphs, (*pej_jeux))){
		return(0);
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

#ifdef AWALE_FMOD
			jouer_un_son(elts_sons.son_distribution, elts_sons);
#endif

			//Attente et affichage
			if(!attente_et_affichage_sdl(int_vitesse_animation, elts_graphs, (*pej_jeux))){
				return(0);
			}

		}else{
			int_final_case++; //On ajoute + 1 à la dernière case à jouer car on a sauté la case ou l'on a enlevé les jetons
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

	total_points = acc_l_points_j1(*pej_jeux) + acc_l_points_j2(*pej_jeux);

	//On comptabilise les points si il y a des points à comptabiliser
	rajoute_points(pej_jeux, int_der_case, tint_cases_ennemi, 6);

	if( (acc_l_points_j1(*pej_jeux) + acc_l_points_j2(*pej_jeux)) > total_points ){

#ifdef AWALE_FMOD
		jouer_un_son(elts_sons.son_check, elts_sons);
#endif

		//Attente et affichage
		if(!attente_et_affichage_sdl(int_vitesse_animation, elts_graphs, (*pej_jeux))){
			return(0);
		}

	}

	return(1);

}

int attente_et_affichage_sdl(int int_temps_millisecondes, elmts_graphiques elts_graphs, etat_jeux ej_jeux){

	int temps_actuel;
	int temps_precedent = SDL_GetTicks();
	int vitesse_repetition=30;
	int temps_ecoule = 0;
	int temps_base = SDL_GetTicks();
	SDL_Event event;

	while ((int_temps_millisecondes > temps_ecoule))
    {
		temps_actuel = SDL_GetTicks();
		if (temps_actuel - temps_precedent > vitesse_repetition){
			temps_precedent = temps_actuel;
		}else{
			SDL_Delay(vitesse_repetition - (temps_actuel - temps_precedent));
		}

		temps_ecoule = temps_actuel - temps_base;

        SDL_PollEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                exit(0);
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym){
					case SDLK_ESCAPE:
						return(0);
						break;
					case SDLK_p:
						jeux_en_pause(elts_graphs);
						event.key.keysym.sym = SDLK_t;
						break;
					default:
						break;
				}
				break;
			default:
				break;
        }

		blit_jeux(elts_graphs, ej_jeux, 1);
		SDL_Flip(elts_graphs.psurf_ecran);
    }

	return(1);

}

void pause(){

    int continuer = 1;
    SDL_Event event;
    while (continuer){

        SDL_WaitEvent(&event);

        switch(event.type){
            case SDL_QUIT:
                exit(0);
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym){
					case SDLK_ESCAPE:
						continuer = 0;
						break;
					case SDLK_RETURN:
						continuer = 0;
						break;
					default:
						break;
				}
				break;

			case SDL_MOUSEBUTTONUP:
				continuer = 0;
				break;
			default:
				break;
        }
    }
}

#ifdef AWALE_FMOD
void jouer_un_son(FSOUND_SAMPLE *son_a_jouer, elmts_sonores elts_sons){

	if((*elts_sons.bool_son_actif)){
		FSOUND_PlaySound(FSOUND_FREE, son_a_jouer);
	}
}
#endif
