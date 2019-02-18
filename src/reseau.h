#ifdef AWALE_NETWORK
/*!
	\file    reseau.h
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   fichier d'entete de type.cpp
	\remarks Fichier qui contient les ent�tes de toutes les fonctions, proc�dures relatives au jeux en r�seau
*/

#ifndef __DEF_RESEAU //Pour �viter les inclusions multiples
#define __DEF_RESEAU

/*
struct SOCKADDR_IN{
    short      sin_family;
    unsigned short   sin_port;
    struct   in_addr   sin_addr;
    char   sin_zero[8];
};
*/



void apprentissage_reseau();

void jeux_en_reseau();

void serveur();

void client();


#endif
#endif