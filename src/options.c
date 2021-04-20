/**
* \file options.c
* \brief Fonction réalisant la page de redimensionnement de l'écran de jeu Picruise
* \version 1.0
* \date 18 Avril 2021
* \author Mohamed Lemrabott, Julien Mahouin, Gallup Mohamad Jamil, Alexis Nolière
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>
#include <unistd.h>

#include<../src/options.h>


/**
* \fn int options(SDL_Window * window, SDL_Renderer * renderer)
* \brief Fonction qui permet à l'utilisateur de choisir les dimensions de l'ecran de jeu
* @param window est une fenêtre générée avec SDL dans laquelle se déroulera l'affichage du jeu Picruise
* @param renderer est le moteur de rendu de la fenêtre, l'espace où nous allons pouvoir faire notre affichage
* \return 0 quand la fonction est terminée
*/
 //Page de sélection des dimensions de l'écran
extern
  int options(SDL_Window * window, SDL_Renderer * renderer){
    //Variable d'arrêt si le joueur décide de ferme la fenêtre de jeu
    int quit = 0;
    //Coordonnées de la souris
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

    //Affichage du bouton pour une fenêtre de 1920 sur 1080 pixels
    dest.x = (SCREEN_WIDTH/2) - (SCREEN_WIDTH/8);
    dest.y = (SCREEN_HEIGHT/2) - 2*(SCREEN_HEIGHT/5);
    dest.w = SCREEN_WIDTH/4;
    dest.h = SCREEN_HEIGHT/5;
    background = SDL_LoadBMP("../sprites/1920x1080.bmp");
    textBackground = SDL_CreateTextureFromSurface(renderer,background);
    SDL_RenderCopy(renderer, textBackground, NULL, &dest);
    SDL_RenderPresent(renderer);

    //Affichage du bouton pour une fenêtre de 1366 sur 768 pixels
    dest.x = (SCREEN_WIDTH/2) - (SCREEN_WIDTH/8);
    dest.y = (SCREEN_HEIGHT/2) - (SCREEN_HEIGHT/5);
    dest.w = SCREEN_WIDTH/4;
    dest.h = SCREEN_HEIGHT/5;
    background = SDL_LoadBMP("../sprites/1366x768.bmp");
    textBackground = SDL_CreateTextureFromSurface(renderer,background);
    SDL_RenderCopy(renderer, textBackground, NULL, &dest);
    SDL_RenderPresent(renderer);

    //Affichage du bouton pour une fenêtre de 720 sur 480 pixels
    dest.x = (SCREEN_WIDTH/2) - (SCREEN_WIDTH/8);
    dest.y = SCREEN_HEIGHT/2;
    dest.w = SCREEN_WIDTH/4;
    dest.h = SCREEN_HEIGHT/5;
    background = SDL_LoadBMP("../sprites/720x480.bmp");
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
            accueil(window, renderer);
            return 0;
          }
          //Redimensionne la fenêtre en 720x480px si l'on clique sur le bouton correspondant
          if(event.button.button == SDL_BUTTON_LEFT && (xMouse>((SCREEN_WIDTH/2) - (SCREEN_WIDTH/8)) && xMouse<(((SCREEN_WIDTH/2) - (SCREEN_WIDTH/8)) + (SCREEN_WIDTH/4))) && (yMouse>((SCREEN_HEIGHT/2) - 2*(SCREEN_HEIGHT/5)) && yMouse<(((SCREEN_HEIGHT/2) - 2*(SCREEN_HEIGHT/5)) + (SCREEN_HEIGHT/5)))){
            SCREEN_WIDTH = 1920 ;
            SCREEN_HEIGHT = 1080 ;
            SDL_SetWindowSize(window, SCREEN_WIDTH, SCREEN_HEIGHT);
            options(window, renderer);
          }
          //Redimensionne la fenêtre en 720x480px si l'on clique sur le bouton correspondant
          if(event.button.button == SDL_BUTTON_LEFT && (xMouse>((SCREEN_WIDTH/2) - (SCREEN_WIDTH/8)) && xMouse<(((SCREEN_WIDTH/2) - (SCREEN_WIDTH/8)) + (SCREEN_WIDTH/4))) && (yMouse>((SCREEN_HEIGHT/2) - (SCREEN_HEIGHT/5)) && yMouse<(((SCREEN_HEIGHT/2) - (SCREEN_HEIGHT/5)) + (SCREEN_HEIGHT/5)))){
            SCREEN_WIDTH = 1366 ;
            SCREEN_HEIGHT = 768 ;
            SDL_SetWindowSize(window, SCREEN_WIDTH, SCREEN_HEIGHT);
            options(window, renderer);
          }
          //Redimensionne la fenêtre en 720x480px si l'on clique sur le bouton correspondant
          if(event.button.button == SDL_BUTTON_LEFT && (xMouse>((SCREEN_WIDTH/2) - (SCREEN_WIDTH/8)) && xMouse<(((SCREEN_WIDTH/2) - (SCREEN_WIDTH/8)) + (SCREEN_WIDTH/4))) && (yMouse>(SCREEN_HEIGHT/2) && yMouse<((SCREEN_HEIGHT/2) + (SCREEN_HEIGHT/5)))){
            SCREEN_WIDTH = 720 ;
            SCREEN_HEIGHT = 480 ;
            SDL_SetWindowSize(window, SCREEN_WIDTH, SCREEN_HEIGHT);
            options(window, renderer);
          }
     }
    }

    return 0;
  }
