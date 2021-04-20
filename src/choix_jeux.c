/**
* \file choix_jeux.c
* \brief Fonction proposant les modes de jeu jouer/solveur du jeu Picruise
* \version 1.0
* \date 18 Avril 2021
* \author Mohamed Lemrabott, Julien Mahouin, Gallup Mohamad Jamil, Alexis Nolière
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>
#include <unistd.h>

#include<../src/choix_jeux.h>

/**
* \fn int choix_jeu(SDL_Window * window, SDL_Renderer * renderer, int format, char * grille_predef)
* \brief Fonction qui réalise la page de sélection du mode joueur ou solveur
* @param window est une fenêtre générée avec SDL dans laquelle se déroulera l'affichage du jeu Picruise
* @param renderer est le moteur de rendu de la fenêtre, l'espace où nous allons pouvoir faire notre affichage
* @param format représente la taille de la matrice
* @param grille_predef est une chaine de caractère comportant le nom de la matrice prédéfinie
* \return 0 quand la fonction est terminée
*/
//Page de sélection du mode joueur ou solveur
extern
int choix_jeu(SDL_Window * window, SDL_Renderer * renderer, int format, char * grille_predef){
  //Variable d'arrêt si le joueur décide de ferme la fenêtre de jeu
  int quit = 0;
  int xMouse;
  int yMouse;

  SDL_Event event;

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  //Affichage du fond d'écran
  SDL_Surface *background = SDL_LoadBMP("../sprites/51673.bmp");
  if(background == NULL){
     SDL_ShowSimpleMessageBox(0, "Background init error",         SDL_GetError(), window);
  }
  SDL_Texture *textBackground = SDL_CreateTextureFromSurface(renderer,background);
  if(textBackground == NULL){
     SDL_ShowSimpleMessageBox(0, "Texture init error", SDL_GetError(), window);
  }
  SDL_RenderCopy(renderer, textBackground, NULL, NULL);
  SDL_RenderPresent(renderer);

  //Affichage du bouton de retour à la page précédente
  SDL_Rect dest = { 0, 0, SCREEN_WIDTH/20, SCREEN_HEIGHT/10};
  background = SDL_LoadBMP("../sprites/retour.bmp");
  textBackground = SDL_CreateTextureFromSurface(renderer,background);
  SDL_RenderCopy(renderer, textBackground, NULL, &dest);
  SDL_RenderPresent(renderer);

  //Affichage du bouton de choix de jouer
  dest.x = (SCREEN_WIDTH/2)-(SCREEN_WIDTH/8);
  dest.y = (SCREEN_HEIGHT/2)-(SCREEN_HEIGHT/4);
  dest.w = SCREEN_WIDTH/4;
  dest.h = SCREEN_HEIGHT/4;
  background = SDL_LoadBMP("../sprites/joueur.bmp");
  textBackground = SDL_CreateTextureFromSurface(renderer,background);
  SDL_RenderCopy(renderer, textBackground, NULL, &dest);
  SDL_RenderPresent(renderer);

  //Affichage du bouton de choix de lancer le solveur
  dest.x = (SCREEN_WIDTH/2)-(SCREEN_WIDTH/8);
  dest.y = SCREEN_HEIGHT/2;
  dest.w = SCREEN_WIDTH/4;
  dest.h = SCREEN_HEIGHT/4;
  background = SDL_LoadBMP("../sprites/solveur.bmp");
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
      //Retourne à la page précédente si on clique sur le bouton de retour
      if(event.button.button == SDL_BUTTON_LEFT && (xMouse>0 && xMouse<(0 + (SCREEN_WIDTH/20))) && (yMouse>0 && yMouse<(0 + (SCREEN_WIDTH/10)))){
        if(grille_predef == NULL){
          choix_format(window, renderer);
          return 0;
        }
        else{
          predefinie(window, renderer);
          return 0;
        }
      }
      //Lance le jeu en mode joueur
      if(event.button.button == SDL_BUTTON_LEFT && (xMouse>((SCREEN_WIDTH/2) - (SCREEN_WIDTH/8)) && xMouse<(((SCREEN_WIDTH/2) - (SCREEN_WIDTH/8)) + (SCREEN_WIDTH/4))) && (yMouse>((SCREEN_HEIGHT/2) - (SCREEN_HEIGHT/4)) && yMouse<(((SCREEN_HEIGHT/2) - (SCREEN_HEIGHT/4)) + (SCREEN_HEIGHT/4)))){
        jeu(window, renderer, format, grille_predef, 1);
        return 0;
      }
      //Lance le jeu en mode solveur
      if(event.button.button == SDL_BUTTON_LEFT && (xMouse>((SCREEN_WIDTH/2) - (SCREEN_WIDTH/8)) && xMouse<(((SCREEN_WIDTH/2) - (SCREEN_WIDTH/8)) + (SCREEN_WIDTH/4))) && (yMouse>(SCREEN_HEIGHT/2) && yMouse<((SCREEN_HEIGHT/2) + (SCREEN_HEIGHT/4)))){
        jeu(window, renderer, format, grille_predef, 0);
        return 0;
      }
   }
  }

  return 0;
}
