/**
* \file jeu.c
* \brief Fonctions réalisant la phase d'intéraction du joueur avec la grille
* \version 1.0
* \date 18 Avril 2021
* \author Mohamed Lemrabott, Julien Mahouin, Gallup Mohamad Jamil, Alexis Nolière
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>
#include <unistd.h>

#include <../src/jeu.h>

/**
* \fn int jouer(SDL_Window * window, SDL_Renderer* renderer ,SDL_Rect * r,int * grille, int * mat_cond_l, int * mat_cond_c, int nb_max_cond_lignes, int nb_max_cond_colonnes, int format)
* \brief Fonction réalise la phase d'intéraction du joueur sur la grille
* @param window est une fenêtre générée avec SDL dans laquelle se déroulera l'affichage du jeu Picruise
* @param renderer est le moteur de rendu de la fenêtre, l'espace où nous allons pouvoir faire notre affichage
* @param grille est un pointeur d'entier qui pointe sur les cases de la grille du joueur
* @param mat_cond_l est un pointeur d'entier qui pointe sur les conditions des lignes du picross
* @param mat_cond_c est un pointeur d'entier qui pointe sur les conditions des colonnes du picross
* @param nb_max_cond_lignes est le nombre maximale de condition qu'une ligne du picross puisse obtenir
* @param nb_max_cond_colonnes est le nombre maximale de condition qu'une colonne du picross puisse obtenir
* @param format représente la taille de la matrice
* \return une variable utilisée pour perpétuer la boucle d'intéraction, sa valeur sera 0 quand on arretera le jeu
*/
int jouer(SDL_Window * window, SDL_Renderer* renderer ,SDL_Rect * r,int * grille, int * mat_cond_l, int * mat_cond_c, int nb_max_cond_lignes, int nb_max_cond_colonnes, int format)
{
  //Variable d'arrêt si le joueur ferme la fenêtre du jeu
  int continuer = 1;
  //Variable d'arrêt si le joueur clique sur l'un des boutons pour quitter la partie
	int quitter = 1;
  int i,j;
  int v;
  //Coordonnées de la souris
  int xMouse,yMouse;
	SDL_Event event;

	SDL_Rect dest;
	SDL_Surface *background;
	SDL_Texture *textBackground;

  //Laisse jouer l'utilisateur tant qu'il n'a pas terminé la grille ou décidé de quitter la partie
	while(continuer && (!verif_lignes(mat_cond_l, grille, format) || !verif_colonnes(mat_cond_c, grille, format)))
	{
		SDL_PollEvent(&event);
		switch (event.type) {
        //Si le joueur ferme la fenêtre, quitte la boucle
        case SDL_QUIT:
				    continuer = 0;
        case SDL_MOUSEBUTTONUP:
            xMouse=event.motion.x;
            yMouse=event.motion.y;
            //Si l'on clique sur la croix en haut à droite, affiche la fenêtre pour quitter
            if(event.button.button == SDL_BUTTON_LEFT && (xMouse>((SCREEN_WIDTH/2)+(SCREEN_WIDTH/4)+(SCREEN_WIDTH/5)+(SCREEN_WIDTH/190)) && xMouse<((SCREEN_WIDTH/2)+(SCREEN_WIDTH/4)+(SCREEN_WIDTH/5)+(SCREEN_WIDTH/190)+SCREEN_WIDTH/22)) && (yMouse>0 && yMouse<SCREEN_HEIGHT/12)){
              dest.x = (SCREEN_WIDTH/2)-(SCREEN_WIDTH/8);
              dest.y = (SCREEN_HEIGHT/2)-(SCREEN_HEIGHT/14);
              dest.w = SCREEN_WIDTH/4;
              dest.h = SCREEN_HEIGHT/7;
              background = SDL_LoadBMP("../sprites/quitteron.bmp");
              textBackground = SDL_CreateTextureFromSurface(renderer,background);
              SDL_RenderCopy(renderer, textBackground, NULL, &dest);
              SDL_RenderPresent(renderer);

              dest.x = (SCREEN_WIDTH/2)-(SCREEN_WIDTH/8);
              dest.y = (SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/14);
              dest.w = SCREEN_WIDTH/8;
              dest.h = SCREEN_HEIGHT/14;
              background = SDL_LoadBMP("../sprites/oui.bmp");
              textBackground = SDL_CreateTextureFromSurface(renderer,background);
              SDL_RenderCopy(renderer, textBackground, NULL, &dest);
              SDL_RenderPresent(renderer);

              dest.x = (SCREEN_WIDTH/2);
              dest.y = (SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/14);
              dest.w = SCREEN_WIDTH/8;
              dest.h = SCREEN_HEIGHT/14;
              background = SDL_LoadBMP("../sprites/non.bmp");
              textBackground = SDL_CreateTextureFromSurface(renderer,background);
              SDL_RenderCopy(renderer, textBackground, NULL, &dest);
              SDL_RenderPresent(renderer);

              //Tant que le joueur n'a pas décidé de quitter ou non
							while(quitter)
							{
							   SDL_PollEvent(&event);
							   switch (event.type) {
								    case SDL_QUIT:
											continuer = 0;
											quitter = 0;
										case SDL_MOUSEBUTTONUP :
											xMouse=event.motion.x;
				              yMouse=event.motion.y;
											//Retourne à la page d'accueil si on clique sur le bouton de oui
											if(event.button.button == SDL_BUTTON_LEFT && (xMouse>((SCREEN_WIDTH/2)-(SCREEN_WIDTH/8)) && xMouse<(((SCREEN_WIDTH/2)-(SCREEN_WIDTH/8)) + (SCREEN_WIDTH/8))) && (yMouse>((SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/14)) && yMouse<(((SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/14)) + (SCREEN_HEIGHT/14)))){
												return -1;
											}
											if(event.button.button == SDL_BUTTON_LEFT && (xMouse>(SCREEN_WIDTH/2) && xMouse<(((SCREEN_WIDTH/2) + (SCREEN_WIDTH/8)))) && (yMouse>((SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/14)) && yMouse<(((SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/14)) + (SCREEN_HEIGHT/14)))){
												quitter = 0;
												affiche_jeu(window, renderer, r, grille, mat_cond_l, mat_cond_c, format, nb_max_cond_lignes, nb_max_cond_colonnes);
											}
									}
								}
								quitter = 1;
            }

            //Modification de la grille et de son affichage selon les actions du joueur
            for(i=0;i<format;i++){
              for(j=0;j<format;j++){
                //Si il clique gauceh sur une case blanche, la noircie et la met à 1
                if (event.button.button == SDL_BUTTON_LEFT && (xMouse>(r[i*format + j].x) && xMouse<(r[i*format + j].x+r[i*format + j].w))&&(yMouse>r[i*format + j].y && yMouse<r[i*format + j].y+r[i*format + j].h) && grille[i*format + j]==0){
                  dest.x = r[i*format + j].x;
                  dest.y = r[i*format + j].y;
                  dest.w = r[i*format + j].w;
                  dest.h = r[i*format + j].h;
                  background = SDL_LoadBMP("../sprites/case_noire.bmp");
                  textBackground = SDL_CreateTextureFromSurface(renderer,background);
                  SDL_RenderCopy(renderer, textBackground, NULL, &dest);
                  SDL_RenderPresent(renderer);
                  grille[i*format + j]=1;
                }
                //Sinon, si c'est une case blanche, la blanchie et la met à 0
                else if (event.button.button == SDL_BUTTON_LEFT && (xMouse>r[i*format + j].x && xMouse<r[i*format + j].x+r[i*format + j].w)&&(yMouse>r[i*format + j].y && yMouse<r[i*format + j].y+r[i*format + j].h) && grille[i*format + j]==1){
                  dest.x = r[i*format + j].x;
                  dest.y = r[i*format + j].y;
                  dest.w = r[i*format + j].w;
                  dest.h = r[i*format + j].h;
                  background = SDL_LoadBMP("../sprites/case_vide.bmp");
                  textBackground = SDL_CreateTextureFromSurface(renderer,background);
                  SDL_RenderCopy(renderer, textBackground, NULL, &dest);
                  SDL_RenderPresent(renderer);
                  grille[i*format + j]=0;
                }
                //Sinon, si il effectue un clique droit, barre la case et la met à -1 pour la bloquer par rapport au clic gauche
                else if (event.button.button == SDL_BUTTON_RIGHT && (xMouse>r[i*format + j].x && xMouse<r[i*format + j].x+r[i*format + j].w)&&(yMouse>r[i*format + j].y && yMouse<r[i*format + j].y+r[i*format + j].h) && grille[i*format + j] != -1){
                  dest.x = r[i*format + j].x;
                  dest.y = r[i*format + j].y;
                  dest.w = r[i*format + j].w;
                  dest.h = r[i*format + j].h;
                  background = SDL_LoadBMP("../sprites/case_barree.bmp");
                  textBackground = SDL_CreateTextureFromSurface(renderer,background);
                  SDL_RenderCopy(renderer, textBackground, NULL, &dest);
                  SDL_RenderPresent(renderer);
                  grille[i*format + j]=-1;
                }
                //Enfin, si il clique droit sur une case barrée, la débloque en la mettant à 0 et en la blanchissants
                else if (event.button.button == SDL_BUTTON_RIGHT && (xMouse>r[i*format + j].x && xMouse<r[i*format + j].x+r[i*format + j].w)&&(yMouse>r[i*format + j].y && yMouse<r[i*format + j].y+r[i*format + j].h) && grille[i*format + j] == -1){
                  dest.x = r[i*format + j].x;
                  dest.y = r[i*format + j].y;
                  dest.w = r[i*format + j].w;
                  dest.h = r[i*format + j].h;
                  background = SDL_LoadBMP("../sprites/case_vide.bmp");
                  textBackground = SDL_CreateTextureFromSurface(renderer,background);
                  SDL_RenderCopy(renderer, textBackground, NULL, &dest);
                  SDL_RenderPresent(renderer);
                  grille[i*format + j]=0;
                }
                dest.x = 0;
                dest.y = 0;
                dest.w = 0;
                dest.h = 0;
              }

            }
            break;
		}
    //Réinitialise l'évènement
		event.type = 0;
	}
	return continuer;
}


/**
* \fn int nb_max_cond(int * mat_cond, int format)
* \brief Calcul le nombre maximum de conditions de la matrice
* @param mat_cond est un pointeur d'entier qui pointe sur les conditions du picross
* @param format représente la taille de la matrice
* \return nb_max_cond un entier représentant le nombre maximal de condition qu'une matrice peut posséder
*/
int nb_max_cond(int * mat_cond, int format){
  int i, j;
  int nb_max_cond, cpt;
  for(i = 0, nb_max_cond = 0; i < format; i++){
    //Calcul le nombre de conditions par ligne / colonne
    for(j = 0, cpt = 0; j < format && mat_cond[i*format + j]; j++)
      cpt++;
    if(nb_max_cond < cpt)
      nb_max_cond = cpt;
  }
  return nb_max_cond;
}


/**
* \fn int jeu (SDL_Window * window, SDL_Renderer * renderer, int format, char * grille_predef, int joueur)
* \brief Fonction qui démarre un picross aléatoire ou prédéfinis selon le choix du joueur
* @param window est une fenêtre générée avec SDL dans laquelle se déroulera l'affichage du jeu Picruise
* @param renderer est le moteur de rendu de la fenêtre, l'espace où nous allons pouvoir faire notre affichage
* @param format représente la taille de la matrice
* @param grille_predef est une chaine de caractère comportant le nom de la matrice prédéfinie
* @param joueur représente le mode de jeu choisit par le joueur
* \return 0 quand la fonction est terminée
*/
int jeu (SDL_Window * window, SDL_Renderer * renderer, int format, char * grille_predef, int joueur){
    SDL_Rect dest;
    //Coordonnées de la souris
    int xMouse;
    int yMouse;

	  SDL_Surface *background;
	  SDL_Texture *textBackground;
    //Initialisation de la police d'écriture
	  TTF_Font * font = TTF_OpenFont("arial.ttf", 25);
    const char * error = TTF_GetError();
    SDL_Color color = { 0, 0, 0 };
    SDL_Surface * surface = NULL;
    SDL_Texture * texture = NULL;
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = { 0, 0, texW, texH };

    //Variable d'arrêt si le joueur ferme la fenêtre du jeu
	  int quit = 0;
    int i,j, k;
    //Initialisation de la grille de jeu et des matrices des conditions des lignes et colonnes
    int grille[format][format];
	  int grille_final[format][format];
    int mat_cond_l[format][format];
    int mat_cond_c[format][format];
    init_matrice(&(grille[0][0]), format);
	  init_matrice(&(grille_final[0][0]), format);
    init_matrice(&(mat_cond_l[0][0]), format);
    init_matrice(&(mat_cond_c[0][0]), format);

    //Matrice de doordonnées et dimensions des cases de la grille
	  SDL_Rect r[format][format];

	  //Si aucun nom de grille prédéfinie n'est passé en paramètre, alors on lance la procédure de génération aléatoire
    if(grille_predef == NULL){
		   genera_aleatoire(&(grille_final[0][0]), format);
	  }
	  //Sinon, charge la grille correspondante
    else{
	     affecter_matrice_predef(&(grille_final[0][0]), format, grille_predef);
    }
    //Génération des conditions
    generat_condi_lignes(&(grille_final[0][0]), &(mat_cond_l[0][0]), format);
    generat_condi_colonnes(&(grille_final[0][0]), &(mat_cond_c[0][0]), format);
    //Calcul du nombre maximale de conditions pour les lignes et les colonnes
    int nb_max_cond_lignes = nb_max_cond(&(mat_cond_l[0][0]), format);
    int nb_max_cond_colonnes = nb_max_cond(&(mat_cond_c[0][0]), format);

    SDL_Event event;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    //Valeur déterminant si le joueur a gagné ou non
    int victoire = 0;
    //Affichage de l'interface de jeu
    affiche_jeu(window, renderer, &(r[0][0]), &(grille[0][0]), &(mat_cond_l[0][0]), &(mat_cond_c[0][0]), format, nb_max_cond_lignes, nb_max_cond_colonnes);
    //Lance la fonction de jeu pour le joueur si il a sélectionné le mode correspondant
    if(joueur)
 	    victoire = jouer(window, renderer , &(r[0][0]), &(grille[0][0]), &(mat_cond_l[0][0]), &(mat_cond_c[0][0]), nb_max_cond_lignes, nb_max_cond_colonnes, format);
    //Sinon, lance le solveur
    else
      solveur(&(grille_final[0][0]), &(grille[0][0]), &(mat_cond_l[0][0]), &(mat_cond_c[0][0]), format);

	  //Si le jouer a quitté en cours de partie, retourne à l'écran titre
	  if(victoire == -1){
		  accueil(window, renderer);
	  }
	  //Sinon, si il a terminé la grille, affiche l'écran de victoire
	  else if(victoire == 1){
      dest.x = (SCREEN_WIDTH/2)-(SCREEN_WIDTH/8);
      dest.y = (SCREEN_HEIGHT/2)-(SCREEN_HEIGHT/14);
      dest.w = SCREEN_WIDTH/4;
      dest.h = SCREEN_HEIGHT/7;
		  background = SDL_LoadBMP("../sprites/victoire.bmp");
		  textBackground = SDL_CreateTextureFromSurface(renderer,background);
		  SDL_RenderCopy(renderer, textBackground, NULL, &dest);
		  SDL_RenderPresent(renderer);

      dest.x = (SCREEN_WIDTH/2)-(SCREEN_WIDTH/8);
      dest.y = (SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/14);
      dest.w = SCREEN_WIDTH/8;
      dest.h = SCREEN_HEIGHT/14;
		  background = SDL_LoadBMP("../sprites/recommencer.bmp");
		  textBackground = SDL_CreateTextureFromSurface(renderer,background);
		  SDL_RenderCopy(renderer, textBackground, NULL, &dest);
		  SDL_RenderPresent(renderer);

      dest.x = (SCREEN_WIDTH/2);
      dest.y = (SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/14);
      dest.w = SCREEN_WIDTH/8;
      dest.h = SCREEN_HEIGHT/14;
		  background = SDL_LoadBMP("../sprites/bquitter.bmp");
		  textBackground = SDL_CreateTextureFromSurface(renderer,background);
		  SDL_RenderCopy(renderer, textBackground, NULL, &dest);
		  SDL_RenderPresent(renderer);

      //Tant que le joueur ne ferme pas la fenêtre de jeu
		  while (!quit)
		  {
		      SDL_WaitEvent(&event);
		      switch (event.type)
		      {
          //Quitte la boucle si le joueur ferme la fenêtre
		      case SDL_QUIT:
			       quit = 1;
			       break;
		      case SDL_MOUSEBUTTONUP :
			       xMouse=event.motion.x;
			       yMouse=event.motion.y;
			       //Retourne à la page d'accueil si on clique sur le bouton "quitter"
			       if(event.button.button == SDL_BUTTON_LEFT && (xMouse>(SCREEN_WIDTH/2) && xMouse<((SCREEN_WIDTH/2) + (SCREEN_WIDTH/8))) && (yMouse>((SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/14)) && yMouse<(((SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/14)) + (SCREEN_HEIGHT/14)))){
				        accueil(window, renderer);
				        return 0;
			       }
			       //Relance la partie si on clique sur le bouton "recommencer"
			       if(event.button.button == SDL_BUTTON_LEFT && (xMouse>((SCREEN_WIDTH/2)-(SCREEN_WIDTH/8)) && xMouse<(((SCREEN_WIDTH/2)-(SCREEN_WIDTH/8)) + (SCREEN_WIDTH/8))) && (yMouse>((SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/14)) && yMouse<(((SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/14)) + (SCREEN_HEIGHT/14)))){
				        jeu(window, renderer, format, grille_predef, joueur);
				        return 0;
			       }
		       }

	         SDL_RenderCopy(renderer, texture, NULL, &dstrect);
		       SDL_RenderPresent(renderer);
		  }
	  }
    //Sinon, la grille a été terminée par le solveur, on affiche alors le bouton pour quitter
    else{
      affiche_jeu(window, renderer, &(r[0][0]), &(grille[0][0]), &(mat_cond_l[0][0]), &(mat_cond_c[0][0]), format, nb_max_cond_lignes, nb_max_cond_colonnes);
      dest.x = (SCREEN_WIDTH/2)+(SCREEN_WIDTH/8);
      dest.y = (SCREEN_HEIGHT/2)-(SCREEN_HEIGHT/14);
      dest.w = SCREEN_WIDTH/4;
      dest.h = SCREEN_HEIGHT/7;
		  background = SDL_LoadBMP("../sprites/bquitter.bmp");
		  textBackground = SDL_CreateTextureFromSurface(renderer,background);
		  SDL_RenderCopy(renderer, textBackground, NULL, &dest);
		  SDL_RenderPresent(renderer);

      //Tant que le joueur ne ferme pas la fenêtre de jeu
      while (!quit)
		  {
		      SDL_WaitEvent(&event);
		      switch (event.type)
		      {
          //Quitte la boucle si le joueur ferme la fenêtre
		      case SDL_QUIT:
			       quit = 1;
			       break;
		      case SDL_MOUSEBUTTONUP :
			       xMouse=event.motion.x;
			       yMouse=event.motion.y;
			       //Retourne à la page d'accueil si on clique sur le bouton "quitter"
			       if(event.button.button == SDL_BUTTON_LEFT && (xMouse>((SCREEN_WIDTH/2)+(SCREEN_WIDTH/8)) && xMouse<(((SCREEN_WIDTH/2)+(SCREEN_WIDTH/8)) + (SCREEN_WIDTH/4))) && (yMouse>((SCREEN_HEIGHT/2)-(SCREEN_HEIGHT/14)) && yMouse<(((SCREEN_HEIGHT/2)-(SCREEN_HEIGHT/14)) + (SCREEN_HEIGHT/7)))){
				        accueil(window, renderer);
				        return 0;
			       }
		       }

		       SDL_RenderCopy(renderer, texture, NULL, &dstrect);
		       SDL_RenderPresent(renderer);
		 }
    }


  return 0;
}
