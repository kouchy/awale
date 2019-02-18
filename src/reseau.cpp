#ifdef AWALE_NETWORK
/*!
	\file    reseau.cpp
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   Fichier qui contient toutes les fonctions et procédures relatives au jeux en réseau
	\remarks Aucune
*/

//INCLUSION DES SOURCES POUR UTILISER LES SOCKETS
//Si nous sommes sous Windows
#if defined (WIN32)

#include <winsock2.h>
#pragma comment(lib,"WS2_32.lib")

// Sinon, si nous sommes sous Linux
#elif defined (linux)

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

// Define, qui nous serviront par la suite
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close (s)

// De même
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

#endif

#include <stdlib.h>
#include <stdio.h>

#include "type.h"
#include "regles_jeux.h"
#include "in_out.h"
#include "ia.h"
#include "reseau.h"
#include "in_out_sdl.h"

#define PORT 23


void apprentissage_reseau(){

	int int_choix;

#if defined (WIN32)
	WSADATA WSAData;
	int erreur = WSAStartup(MAKEWORD(2,0), &WSAData);
#else
	int erreur = 0;
#endif


	printf("1 - Client\n");
	printf("2 - Serveur\n");
	scanf("%d", &int_choix);

	if(int_choix == 1){

		 #if defined (WIN32)
			WSADATA WSAData;
			int erreur = WSAStartup(MAKEWORD(2,0), &WSAData);
		#else
			int erreur = 0;
		#endif

		SOCKET sock;
		SOCKADDR_IN sin;
		char buffer_bonjour[31] = "Bonjours a toi chers client !!";

		if(!erreur)
		{
			/* Création de la socket */
			sock = socket(AF_INET, SOCK_STREAM, 0);

			/* Configuration de la connexion */
			sin.sin_addr.s_addr = inet_addr("127.0.0.1");
			sin.sin_family = AF_INET;
			sin.sin_port = htons(PORT);

			while(connect(sock, (SOCKADDR *)&sin, sizeof(sin)) == SOCKET_ERROR);
			printf("Connexion a %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));

			if(send(sock, buffer_bonjour, (strlen(buffer_bonjour)+1 * sizeof(char)), 0) != SOCKET_ERROR){
				printf("Je lui envoi le bonjour ;)!\n");
			}else{
				printf("Echec pour envoyer le bonjour :S\n");
			}


			/* Si le client arrive à se connecté */
			/*
			if(connect(sock, (SOCKADDR *)&sin, sizeof(sin)) != SOCKET_ERROR)
				printf("Connexion a %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));
			else
				printf("Impossible de se connecter\n");
			*/
			/* On ferme la socket précédemment ouverte */
			closesocket(sock);

			#if defined (WIN32)
				WSACleanup();
			#endif
		}


	}else{

		char buffer_bonjour[31] = "";

		/* Socket et contex   te d'adressage du serveur */
		SOCKADDR_IN sin;
		SOCKET sock;
		int recsize = (unsigned int) sizeof sin;

		/* Socket et contexte d'adressage du client */
		SOCKADDR_IN csin;
		SOCKET csock;
		int crecsize = (unsigned int) sizeof csin;

		int sock_err;


		if(!erreur)
		{
			/* Création d'une socket */
			sock = socket(AF_INET, SOCK_STREAM, 0);

			/* Si la socket est valide */
			if(sock != INVALID_SOCKET)
			{
				printf("La socket %d est maintenant ouverte en mode TCP/IP\n", sock);

				/* Configuration */
				sin.sin_addr.s_addr = htonl(INADDR_ANY);  /* Adresse IP automatique */
				sin.sin_family = AF_INET;                 /* Protocole familial (IP) */
				sin.sin_port = htons(PORT);               /* Listage du port */
				sock_err = bind(sock, (SOCKADDR *) &sin, recsize); //On associe les info à la socket

				/* Si la socket fonctionne */
				if(sock_err != SOCKET_ERROR)
				{
					/* Démarrage du listage (mode server) */
					sock_err = listen(sock, 5);
					printf("Listage du port %d...\n", PORT);

					/* Si la socket fonctionne */
					if(sock_err != SOCKET_ERROR)
					{
						/* Attente pendant laquelle le client se connecte */
						printf("Patientez pendant que le client se connecte sur le port %d...\n", PORT);
						csock = accept(sock, (SOCKADDR *) &csin, &crecsize);
						printf("Un client se connecte avec la socket %d de %s:%d\n", csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));
						while(recv(csock, buffer_bonjour,31 * sizeof(char), 0) == SOCKET_ERROR);
						printf("J ai recu un message du client : %s\n", buffer_bonjour);

						/* Il ne faut pas oublier de fermer la connexion (fermée dans les deux sens) */
						 shutdown(csock, 2);

					}
					else
						perror("listen");
				}
				else
					perror("bind");

				/* Fermeture de la socket client et de la socket serveur */
				printf("Fermeture de la socket client\n");
				closesocket(csock);
				 printf("Fermeture de la socket serveur\n");
				closesocket(sock);
				printf("Fermeture du serveur terminée\n");
			}
			else
				perror("socket");

			#if defined (WIN32)
				WSACleanup();
			#endif
		}

	}

	system("PAUSE");

}


void jeux_en_reseau(){

	int int_retour=1;
	int int_saisie;

#if defined (WIN32)
	WSADATA WSAData;
	int erreur = WSAStartup(MAKEWORD(2,0), &WSAData);
#else
	int erreur = 0;
#endif

	if(!erreur){
		do{
			effacer_affichage();
			affiche_presentation_jeux();
			printf(" 1 - Serveur\n");
			printf(" 2 - Client\n");
			printf(" 3 - Demarer Awale normalement\n");
			printf(" 4 - Quitter\n");

			printf("\nEntrez votre choix : ");
			int_retour = scanf("%d", &int_saisie);
			fflush(stdin);

			if(!int_retour || int_saisie < 0 || int_saisie > 4){
				printf("Mauvaise entree...\n");
				pause(1500);
			}

			switch(int_saisie){
				case 1 :
					serveur();
					system("PAUSE");
					break;
				case 2 :
					client();
					system("PAUSE");
					break;
				case 3 :
					//menu_sdl(0, 0);
					menu_awale_sdl(0, 0);
					break;

				default :
					break;
			}
		}while(!int_retour || int_saisie < 0 || int_saisie > 4);
	}


	#if defined (WIN32)
		WSACleanup();
	#endif
}


void serveur(){

	char buffer_joueur[1];
	int int_joueur;
	int int_joueur_adverse;
	int int_retour=1;

	/* Socket et contex   te d'adressage du serveur */
	SOCKADDR_IN sin;
	SOCKET sock;
	int recsize = (unsigned int) sizeof sin;

	/* Socket et contexte d'adressage du client */
	SOCKADDR_IN csin;
	SOCKET csock;
	int crecsize = (unsigned int) sizeof csin;

	int sock_err;

	/* Création d'une socket */
	sock = socket(AF_INET, SOCK_STREAM, 0);

	/* Si la socket est valide */
	if(sock != INVALID_SOCKET){

		printf("La socket %d est maintenant ouverte en mode TCP/IP\n", sock);

		/* Configuration */
		sin.sin_addr.s_addr = htonl(INADDR_ANY);  /* Adresse IP automatique */
		sin.sin_family = AF_INET;                 /* Protocole familial (IP) */
		sin.sin_port = htons(PORT);               /* Listage du port */
		sock_err = bind(sock, (SOCKADDR *) &sin, recsize); //On associe les info à la socket

		/* Si la socket fonctionne */
		if(sock_err != SOCKET_ERROR){

			/* Démarrage du listage (mode server) */
			sock_err = listen(sock, 5);
			printf("Listage du port %d...\n", PORT);

			/* Si la socket fonctionne */
			if(sock_err != SOCKET_ERROR){

				/* Attente pendant laquelle le client se connecte */
				printf("Patientez pendant que le client se connecte sur le port %d...\n", PORT);
				csock = accept(sock, (SOCKADDR *) &csin, &crecsize);
				printf("Un client se connecte avec la socket %d de %s:%d\n", csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));

				do{
					printf("Choisissez votre numero de joueur (1 ou 2): ");
					int_retour = scanf("%d", &int_joueur);
				}while(!int_retour || (int_joueur < 1 || int_joueur > 2));


				if(int_joueur == 1){
					int_joueur_adverse = 2;
				}else{
					int_joueur_adverse = 1;
				}

				buffer_joueur[0] = int_joueur_adverse;

				if(send(csock, buffer_joueur, sizeof(char), 0) != SOCKET_ERROR){
					printf("Le client a ete informe de son numero de joueur!\nLa partie est en cour de lancement...\n");
					//menu_sdl(csock, int_joueur);
					menu_awale_sdl(csock, int_joueur);
				}else{
					printf("Echec du transfert de numero de joueur! Le jeux ne se lancera pas.\n");
				}

				/* Il ne faut pas oublier de fermer la connexion (fermée dans les deux sens) */
				 shutdown(csock, 2);
			}else{
				perror("listen");
			}
		}else{
			perror("bind");
		}

		/* Fermeture de la socket client et de la socket serveur */
		printf("Fermeture de la socket client\n");
		closesocket(csock);
		 printf("Fermeture de la socket serveur\n");
		closesocket(sock);
		printf("Fermeture du serveur terminee\n");
	}else{
		perror("socket");
	}

}


void client(){

	char buffer_joueur[1];
	char tchar_addr_ip_serveur[30];
	int int_joueur;
	int int_joueur_adverse;
	int int_retour=1;

	SOCKET sock;
	SOCKADDR_IN sin;


	do{
		printf("Entrez l'adresse IP du serveur pour vous connecter : ");
		int_retour = scanf("%s", tchar_addr_ip_serveur);
	}while(!int_retour);

	printf("Recherche du serveur...\n");

	/* Création de la socket */
	sock = socket(AF_INET, SOCK_STREAM, 0);

	/* Configuration de la connexion */
	sin.sin_addr.s_addr = inet_addr(tchar_addr_ip_serveur);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);

	/* Si le client arrive à se connecté */
	while(connect(sock, (SOCKADDR *)&sin, sizeof(sin)) == SOCKET_ERROR);
	printf("Connexion a %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));

	while(recv(sock, buffer_joueur, sizeof(char), 0) == SOCKET_ERROR);

	if(buffer_joueur[0] == 1){
		int_joueur = 1;
		int_joueur_adverse = 2;
	}else{
		int_joueur = 2;
		int_joueur_adverse = 1;
	}

	printf("Le serveur est le joueur %d et vous etes le joueur %d.\n", int_joueur_adverse, int_joueur);
	printf("La partie est en cour de lancement...\n");

	menu_awale_sdl(sock, int_joueur);
	//menu_sdl(sock, int_joueur);

	/* On ferme la socket précédemment ouverte */
	closesocket(sock);


}
#endif