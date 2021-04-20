/**
* \file accueil.c
* \brief Fonction réalisant le menu d'accueil du jeu Picruise
* \version 1.0
* \date 18 Avril 2021
* \author Mohamed Lemrabott, Julien Mahouin, Gallup Mohamad Jamil, Alexis Nolière
*/
#include<../src/options.h>
#include<../src/choix_type_grille.h>
#include<../src/accueil.h>
#include "commun.h"

/**
* \fn int accueil(SDL_Window * window, SDL_Renderer * renderer)
* \brief Fonction qui réalise la page d'accueil du jeu Picruise
* @param window est une fenêtre générée avec SDL dans laquelle se déroulera l'affichage du jeu Picruise
* @param renderer est le moteur de rendu de la fenêtre, l'espace où nous allons pouvoir faire notre affichage
* \return 0 quand la fonction est terminée
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>
#include <unistd.h>

extern
int accueil(SDL_Window * window, SDL_Renderer * renderer){
  //Coordonnées de la souris
  int xMouse;
  int yMouse;
  //Affichage du fond d'écran
  SDL_Surface * background = SDL_LoadBMP("../sprites/51673.bmp");
  if(background == NULL){
     SDL_ShowSimpleMessageBox(0, "Background init error",         SDL_GetError(), window);
  }
  SDL_Texture *textBackground = SDL_CreateTextureFromSurface(renderer,background);
  if(textBackground == NULL){
     SDL_ShowSimpleMessageBox(0, "Texture init error", SDL_GetError(), window);
  }
  SDL_RenderCopy(renderer, textBackground, NULL, NULL);
  SDL_RenderPresent(renderer);
  //Variable d'arrêt si le joueur décide de ferme la fenêtre de jeu
  int quit = 0;
  SDL_Event event;

  //Affichage du titre
  //Coordonées et dimensions de l'affichage
  SDL_Rect dest = { SCREEN_WIDTH/4, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT/4};
  background = SDL_LoadBMP("../sprites/titre.bmp");
  textBackground = SDL_CreateTextureFromSurface(renderer,background);
  SDL_RenderCopy(renderer, textBackground, NULL, &dest);
  SDL_RenderPresent(renderer);

  //Affichage du bouton jouer
  dest.x = SCREEN_WIDTH/4;
  dest.y = SCREEN_HEIGHT/3;
  dest.w = SCREEN_WIDTH/4;
  dest.h = SCREEN_HEIGHT/6;
  background = SDL_LoadBMP("../sprites/jouer.bmp");
  textBackground = SDL_CreateTextureFromSurface(renderer,background);
  SDL_RenderCopy(renderer, textBackground, NULL, &dest);
  SDL_RenderPresent(renderer);

  //Affichage du bouton tutoriel
  dest.x = SCREEN_WIDTH/4;
  dest.y = SCREEN_HEIGHT/2;
  dest.w = SCREEN_WIDTH/4;
  dest.h = SCREEN_HEIGHT/6;
  background = SDL_LoadBMP("../sprites/tutoriel.bmp");
  textBackground = SDL_CreateTextureFromSurface(renderer,background);
  SDL_RenderCopy(renderer, textBackground, NULL, &dest);
  SDL_RenderPresent(renderer);

  //Affichage du bouton options
  dest.x = SCREEN_WIDTH/4;
  dest.y = (SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/6);
  dest.w = SCREEN_WIDTH/4;
  dest.h = SCREEN_HEIGHT/6;
  background = SDL_LoadBMP("../sprites/options.bmp");
  textBackground = SDL_CreateTextureFromSurface(renderer,background);
  SDL_RenderCopy(renderer, textBackground, NULL, &dest);
  SDL_RenderPresent(renderer);

  //Affichage du bouton quitter
  dest.x = SCREEN_WIDTH/4;
  dest.y = (SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/6)*2;
  dest.w = SCREEN_WIDTH/4;
  dest.h = SCREEN_HEIGHT/6;
  background = SDL_LoadBMP("../sprites/quitter.bmp");
  textBackground = SDL_CreateTextureFromSurface(renderer,background);
  SDL_RenderCopy(renderer, textBackground, NULL, &dest);
  SDL_RenderPresent(renderer);

  //Tant que le joueur ne ferme pas la fenêtre
  while (!quit)
  {
   SDL_WaitEvent(&event);
   switch (event.type)
   {
     //Si le joueur ferme la fenêtre, on quitte la boucle
     case SDL_QUIT:
        quit = 1;
        break;
     case SDL_MOUSEBUTTONUP :
        xMouse=event.motion.x;
        yMouse=event.motion.y;
        //Renvoi vers la page de sélection du type de grille si on clique sur le bouton "jouer"
        if(event.button.button == SDL_BUTTON_LEFT && (xMouse>(SCREEN_WIDTH/4) && xMouse<((SCREEN_WIDTH/4)+(SCREEN_WIDTH/4))) && (yMouse>(SCREEN_HEIGHT/3) && yMouse<((SCREEN_HEIGHT/3) + (SCREEN_HEIGHT/6)))){
          choix_type_grille(window, renderer);
          return 0;
        }
        //Renvoi vers la page des options si on clique sur le bouton "options"
        if(event.button.button == SDL_BUTTON_LEFT && (xMouse>(SCREEN_WIDTH/4) && xMouse<((SCREEN_WIDTH/4)+(SCREEN_WIDTH/4))) && (yMouse>((SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/6)) && yMouse<(((SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/6)) + (SCREEN_HEIGHT/6)))){
          options(window, renderer);
          return 0;
        }
        //Renvoi vers la page explicative du picross si on clique sur le bouton tutoriel

        //Quitte le jeu si on clique sur le bouton "quitter" après avoir libéré toutes les ressources
        if(event.button.button == SDL_BUTTON_LEFT && (xMouse>(SCREEN_WIDTH/4) && xMouse<((SCREEN_WIDTH/4)+(SCREEN_WIDTH/4))) && (yMouse>((SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/6)*2) && yMouse<(((SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/6)*2) + (SCREEN_HEIGHT/6)))){
          return 0;
        }
    }
  }

  return 0;
}
