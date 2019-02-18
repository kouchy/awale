/*!
	\file    main.cpp
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   fichier qui contien la fonction de lancement du programmme (main)
	\remarks aucune

*/

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "type.h"
#include "regles_jeux.h"
#include "in_out.h"
#include "in_out_sdl.h"
#include "ia.h"
#ifdef AWALE_NETWORK
#include "reseau.h"
#endif

/*!
	\fn      void main()
	\author  Adrien CASSAGNE, Guillem BORIE et Romain DURAND SAINT OMER <adrien-cassagne@wanadoo.fr>
	\version 0.1
	\brief   fonction pricipale
	\return  rien
  \remarks aucune
*/
int main(int argc, char** argv)
{
	//apprentissage_reseau();
	srand((int)time(NULL)); //On initialise srand pour utiliser rand()

	if (argc == 1)
	{
#ifdef AWALE_NETWORK
		//Lancer Awalé en réseau
		jeux_en_reseau();
#else
		//Lancer Awalé en mode SDL
		menu_awale_sdl(0, 0);
#endif
	}
	else
	{
		// //Lancer Awalé en shell
		menu_jeux_shell();
	}

	return EXIT_SUCCESS;

}
