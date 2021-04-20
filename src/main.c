/**
* \file main.c
* \brief Programme regroupant toutes les fonctions nécessaire au déroulement du jeu Picruise
* \version 1.0
* \date 18 Avril 2021
* \author Mohamed Lemrabott, Julien Mahouin, Gallup Mohamad Jamil, Alexis Nolière
*/
#include <../include/SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>
#include <unistd.h>
#include<../include/SDL2/SDL_ttf.h>
#include<../include/SDL2/SDL_image.h>

#include<../src/accueil.h>
#include "commun.h"

/**
* \fn int main(int argc, char ** argv)
* \brief Fonction principale de ce programme qui lance le jeu Picruise
* @param argc nombre de paramètre effectif
* @param argv chaine de caractère comportant les paramètres effectifs
* \return 1 quand le programme est terminé
*/
int main(int argc, char ** argv)
{
 int quit = 0;
 //Initialisation des dimensions de la fenêtre du jeu, ici pour un pc portable 1366x768
 SCREEN_WIDTH = 1366;
 SCREEN_HEIGHT = 768;

 SDL_Event event;
 //Initialisation de la SDL
 SDL_Init(SDL_INIT_VIDEO);
 TTF_Init();

 //Création de la fenêtre
 SDL_Window * window = SDL_CreateWindow("SDL_ttf in SDL2",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    SCREEN_WIDTH, SCREEN_HEIGHT,
    SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS)/*SDL_CreateWindow("SDL_ttf in SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1366, 768, 0)*/;
 SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
 SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
 SDL_RenderClear(renderer);
 SDL_Surface *background;

 //Affichage de l'écran titre
 accueil(window, renderer);

 //SDL_DestroyTexture(textBackground);//
 SDL_FreeSurface(background);
 SDL_DestroyRenderer(renderer);
 SDL_DestroyWindow(window);
 TTF_Quit();
 SDL_Quit();
 exit(EXIT_SUCCESS);

}
