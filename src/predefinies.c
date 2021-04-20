/**
* \file predefinies.c
* \brief Fonction réalisant la page de sélection des matrices prédéfinies
* \version 1.0
* \date 18 Avril 2021
* \author Mohamed Lemrabott, Julien Mahouin, Gallup Mohamad Jamil, Alexis Nolière
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>
#include <unistd.h>

#include<../src/predefinies.h>

/**
* \fn int predefinie(SDL_Window * window, SDL_Renderer * renderer)
* \brief Fonction qui réalise la page de sélection des grilles prédéfinies
* @param window est une fenêtre générée avec SDL dans laquelle se déroulera l'affichage du jeu Picruise
* @param renderer est le moteur de rendu de la fenêtre, l'espace où nous allons pouvoir faire notre affichage
* \return 0 quand la fonction est terminée
*/
extern
int predefinie(SDL_Window * window, SDL_Renderer * renderer){
  int quit = 0;

  int xMouse;
  int yMouse;

  SDL_Event event;

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  int i, j, k;

  //Affichage du background
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

  for(i=0;i<5;i++){
    for(j=0;j<5;j++){
        dest.x = 0+j*(SCREEN_WIDTH/5);
        dest.y = (SCREEN_HEIGHT/9)+i*(SCREEN_HEIGHT/7);
        dest.w = SCREEN_WIDTH/5;
        dest.h = SCREEN_HEIGHT/7;
        k = (i*5)+j;
        switch(k){
            case 0 :
                background = SDL_LoadBMP("../sprites/aigle.bmp");
                break;
            case 1 :
                background = SDL_LoadBMP("../sprites/ancre.bmp");
                break;
            case 2 :
                background = SDL_LoadBMP("../sprites/canard.bmp");
                break;
            case 3 :
                background = SDL_LoadBMP("../sprites/coccinelle.bmp");
                break;
            case 4 :
                background = SDL_LoadBMP("../sprites/coupe.bmp");
                break;
            case 5 :
                background = SDL_LoadBMP("../sprites/couronne.bmp");
                break;
            case 6 :
                background = SDL_LoadBMP("../sprites/cygne.bmp");
                break;
            case 7 :
                background = SDL_LoadBMP("../sprites/dindon.bmp");
                break;
            case 8 :
                background = SDL_LoadBMP("../sprites/ecureuil.bmp");
                break;
            case 9 :
                background = SDL_LoadBMP("../sprites/flamand_rose.bmp");
                break;
            case 10 :
                background = SDL_LoadBMP("../sprites/footballer.bmp");
                break;
            case 11 :
                background = SDL_LoadBMP("../sprites/gameboy.bmp");
                break;
            case 12 :
                background = SDL_LoadBMP("../sprites/griffon.bmp");
                break;
            case 13 :
                background = SDL_LoadBMP("../sprites/hibou.bmp");
                break;
            case 14 :
                background = SDL_LoadBMP("../sprites/licorne.bmp");
                break;
            case 15 :
                background = SDL_LoadBMP("../sprites/meduse.bmp");
                break;
            case 16 :
                background = SDL_LoadBMP("../sprites/otarie.bmp");
                break;
            case 17 :
                background = SDL_LoadBMP("../sprites/pecheur.bmp");
                break;
            case 18 :
                background = SDL_LoadBMP("../sprites/perroquet.bmp");
                break;
            case 19 :
                background = SDL_LoadBMP("../sprites/petit_bateau.bmp");
                break;
            case 20 :
                background = SDL_LoadBMP("../sprites/petit_poisson.bmp");
                break;
            case 21 :
                background = SDL_LoadBMP("../sprites/pieuvre.bmp");
                break;
            case 22 :
                background = SDL_LoadBMP("../sprites/poisson.bmp");
                break;
            case 23 :
                background = SDL_LoadBMP("../sprites/robot.bmp");
                break;
            case 24 :
                background = SDL_LoadBMP("../sprites/tete_chien.bmp");
                break;
        }
        textBackground = SDL_CreateTextureFromSurface(renderer,background);
        SDL_RenderCopy(renderer, textBackground, NULL, &dest);
        SDL_RenderPresent(renderer);
    }
  }
    dest.x = (SCREEN_WIDTH/5);
    dest.y = (SCREEN_HEIGHT/9)+5*(SCREEN_HEIGHT/7);
    dest.w = SCREEN_WIDTH/5;
    dest.h = SCREEN_HEIGHT/7;
    background = SDL_LoadBMP("../sprites/toad.bmp");
    textBackground = SDL_CreateTextureFromSurface(renderer,background);
    SDL_RenderCopy(renderer, textBackground, NULL, &dest);
    SDL_RenderPresent(renderer);

    dest.x = 3*(SCREEN_WIDTH/5);
    dest.y = (SCREEN_HEIGHT/9)+5*(SCREEN_HEIGHT/7);
    dest.w = SCREEN_WIDTH/5;
    dest.h = SCREEN_HEIGHT/7;
    background = SDL_LoadBMP("../sprites/voilier.bmp");
    textBackground = SDL_CreateTextureFromSurface(renderer,background);
    SDL_RenderCopy(renderer, textBackground, NULL, &dest);
    SDL_RenderPresent(renderer);

  while (!quit)
  {
   SDL_WaitEvent(&event);

   switch (event.type)
   {
   case SDL_QUIT:
    quit = 1;
    break;
   case SDL_MOUSEBUTTONUP :
      xMouse=event.motion.x;
      yMouse=event.motion.y;
      //Retourne à la page précédente si on clique sur le bouton de retour
      if(event.button.button == SDL_BUTTON_LEFT && (xMouse>0 && xMouse<(0 + (SCREEN_WIDTH/20))) && (yMouse>0 && yMouse<(0 + (SCREEN_WIDTH/10)))){
        choix_type_grille(window, renderer);
        return 0;
      }
      //Renvoi vers la page de sélection de sélection du mode joueur ou solveur en prenant en compte la grille sélectionnée
      if(event.button.button == SDL_BUTTON_LEFT && (xMouse>0 && xMouse<((SCREEN_WIDTH/5))) && (yMouse>(SCREEN_HEIGHT/9) && yMouse<((SCREEN_HEIGHT/9) + (SCREEN_HEIGHT/7)))){
        choix_jeu(window, renderer, 20, "../grilles_predefinies/aigle.txt");
        return 0;
      }
      if(event.button.button == SDL_BUTTON_LEFT && (xMouse>(SCREEN_WIDTH/5) && xMouse<((SCREEN_WIDTH/5) + (SCREEN_WIDTH/5))) && (yMouse>((SCREEN_HEIGHT/9)) && yMouse<(((SCREEN_HEIGHT/9)) + (SCREEN_HEIGHT/7)))){
        choix_jeu(window, renderer, 15, "../grilles_predefinies/ancre.txt");
        return 0;
      }
      if(event.button.button == SDL_BUTTON_LEFT && (xMouse>(2*(SCREEN_WIDTH/5)) && xMouse<((2*(SCREEN_WIDTH/5)) + (SCREEN_WIDTH/5))) && (yMouse>((SCREEN_HEIGHT/9)) && yMouse<(((SCREEN_HEIGHT/9)) + (SCREEN_HEIGHT/7)))){
        choix_jeu(window, renderer, 10, "../grilles_predefinies/canard.txt");
        return 0;
      }
      if(event.button.button == SDL_BUTTON_LEFT && (xMouse>(3*(SCREEN_WIDTH/5)) && xMouse<((3*(SCREEN_WIDTH/5)) + (SCREEN_WIDTH/5))) && (yMouse>((SCREEN_HEIGHT/9)) && yMouse<(((SCREEN_HEIGHT/9)) + (SCREEN_HEIGHT/7)))){
        choix_jeu(window, renderer, 20, "../grilles_predefinies/coccinelle.txt");
        return 0;
      }
      if(event.button.button == SDL_BUTTON_LEFT && (xMouse>(4*(SCREEN_WIDTH/5)) && xMouse<((4*(SCREEN_WIDTH/5)) + (SCREEN_WIDTH/5))) && (yMouse>((SCREEN_HEIGHT/9)) && yMouse<(((SCREEN_HEIGHT/9)) + (SCREEN_HEIGHT/7)))){
        choix_jeu(window, renderer, 11, "../grilles_predefinies/coupe.txt");
        return 0;
      }

      if(event.button.button == SDL_BUTTON_LEFT && (xMouse>0 && xMouse<(SCREEN_WIDTH/5)) && (yMouse>((SCREEN_HEIGHT/9)+(SCREEN_HEIGHT/7)) && yMouse<(((SCREEN_HEIGHT/9)+(SCREEN_HEIGHT/7)) + (SCREEN_HEIGHT/7)))){
        choix_jeu(window, renderer, 20, "../grilles_predefinies/couronne.txt");
        return 0;
      }
      if(event.button.button == SDL_BUTTON_LEFT && (xMouse>(SCREEN_WIDTH/5) && xMouse<((SCREEN_WIDTH/5) + (SCREEN_WIDTH/5))) && (yMouse>((SCREEN_HEIGHT/9)+(SCREEN_HEIGHT/7)) && yMouse<(((SCREEN_HEIGHT/9)) + (SCREEN_HEIGHT/7) + (SCREEN_HEIGHT/7)))){
        choix_jeu(window, renderer, 20, "../grilles_predefinies/cygne.txt");
        return 0;
      }
      if(event.button.button == SDL_BUTTON_LEFT && (xMouse>(2*(SCREEN_WIDTH/5)) && xMouse<((2*(SCREEN_WIDTH/5)) + (SCREEN_WIDTH/5))) && (yMouse>((SCREEN_HEIGHT/9)+(SCREEN_HEIGHT/7)) && yMouse<(((SCREEN_HEIGHT/9)+(SCREEN_HEIGHT/7)) + (SCREEN_HEIGHT/7)))){
        choix_jeu(window, renderer, 15, "../grilles_predefinies/dindon.txt");
        return 0;
      }
      if(event.button.button == SDL_BUTTON_LEFT && (xMouse>(3*(SCREEN_WIDTH/5)) && xMouse<((3*(SCREEN_WIDTH/5)) + (SCREEN_WIDTH/5))) && (yMouse>((SCREEN_HEIGHT/9)+(SCREEN_HEIGHT/7)) && yMouse<(((SCREEN_HEIGHT/9)+(SCREEN_HEIGHT/7)) + (SCREEN_HEIGHT/7)))){
        choix_jeu(window, renderer, 10, "../grilles_predefinies/ecureuil.txt");
        return 0;
      }
      if(event.button.button == SDL_BUTTON_LEFT && (xMouse>(4*(SCREEN_WIDTH/5)) && xMouse<((4*(SCREEN_WIDTH/5)) + (SCREEN_WIDTH/5))) && (yMouse>((SCREEN_HEIGHT/9)+(SCREEN_HEIGHT/7)) && yMouse<(((SCREEN_HEIGHT/9)+(SCREEN_HEIGHT/7)) + (SCREEN_HEIGHT/7)))){
        choix_jeu(window, renderer, 15, "../grilles_predefinies/flamand_rose.txt");
        return 0;
      }

      if(event.button.button == SDL_BUTTON_LEFT && (xMouse>0 && xMouse<(SCREEN_WIDTH/5)) && (yMouse>((SCREEN_HEIGHT/9)+2*(SCREEN_HEIGHT/7)) && yMouse<(((SCREEN_HEIGHT/9)+2*(SCREEN_HEIGHT/7)) + (SCREEN_HEIGHT/7)))){
        choix_jeu(window, renderer, 20, "../grilles_predefinies/footballer.txt");
        return 0;
      }
      if(event.button.button == SDL_BUTTON_LEFT && (xMouse>(SCREEN_WIDTH/5) && xMouse<((SCREEN_WIDTH/5) + (SCREEN_WIDTH/5))) && (yMouse>((SCREEN_HEIGHT/9)+2*(SCREEN_HEIGHT/7)) && yMouse<(((SCREEN_HEIGHT/9)) + 2*(SCREEN_HEIGHT/7) + (SCREEN_HEIGHT/7)))){
        choix_jeu(window, renderer, 15, "../grilles_predefinies/gameboy.txt");
        return 0;
      }
      if(event.button.button == SDL_BUTTON_LEFT && (xMouse>(2*(SCREEN_WIDTH/5)) && xMouse<((2*(SCREEN_WIDTH/5)) + (SCREEN_WIDTH/5))) && (yMouse>((SCREEN_HEIGHT/9)+2*(SCREEN_HEIGHT/7)) && yMouse<(((SCREEN_HEIGHT/9)+2*(SCREEN_HEIGHT/7)) + (SCREEN_HEIGHT/7)))){
        choix_jeu(window, renderer, 20, "../grilles_predefinies/griffon.txt");
        return 0;
      }
      if(event.button.button == SDL_BUTTON_LEFT && (xMouse>(3*(SCREEN_WIDTH/5)) && xMouse<((3*(SCREEN_WIDTH/5)) + (SCREEN_WIDTH/5))) && (yMouse>((SCREEN_HEIGHT/9)+2*(SCREEN_HEIGHT/7)) && yMouse<(((SCREEN_HEIGHT/9)+2*(SCREEN_HEIGHT/7)) + (SCREEN_HEIGHT/7)))){
        choix_jeu(window, renderer, 15, "../grilles_predefinies/hibou.txt");
        return 0;
      }
      if(event.button.button == SDL_BUTTON_LEFT && (xMouse>(4*(SCREEN_WIDTH/5)) && xMouse<((4*(SCREEN_WIDTH/5)) + (SCREEN_WIDTH/5))) && (yMouse>((SCREEN_HEIGHT/9)+2*(SCREEN_HEIGHT/7)) && yMouse<(((SCREEN_HEIGHT/9)+2*(SCREEN_HEIGHT/7)) + (SCREEN_HEIGHT/7)))){
        choix_jeu(window, renderer, 15, "../grilles_predefinies/licorne.txt");
        return 0;
      }

      if(event.button.button == SDL_BUTTON_LEFT && (xMouse>0 && xMouse<(SCREEN_WIDTH/5)) && (yMouse>((SCREEN_HEIGHT/9)+3*(SCREEN_HEIGHT/7)) && yMouse<(((SCREEN_HEIGHT/9)+3*(SCREEN_HEIGHT/7)) + (SCREEN_HEIGHT/7)))){
        choix_jeu(window, renderer, 20, "../grilles_predefinies/meduse.txt");
        return 0;
      }
      if(event.button.button == SDL_BUTTON_LEFT && (xMouse>(SCREEN_WIDTH/5) && xMouse<((SCREEN_WIDTH/5) + (SCREEN_WIDTH/5))) && (yMouse>((SCREEN_HEIGHT/9)+3*(SCREEN_HEIGHT/7)) && yMouse<(((SCREEN_HEIGHT/9)) + 3*(SCREEN_HEIGHT/7) + (SCREEN_HEIGHT/7)))){
        choix_jeu(window, renderer, 20, "../grilles_predefinies/otarie.txt");
        return 0;
      }
      if(event.button.button == SDL_BUTTON_LEFT && (xMouse>(2*(SCREEN_WIDTH/5)) && xMouse<((2*(SCREEN_WIDTH/5)) + (SCREEN_WIDTH/5))) && (yMouse>((SCREEN_HEIGHT/9)+3*(SCREEN_HEIGHT/7)) && yMouse<(((SCREEN_HEIGHT/9)+3*(SCREEN_HEIGHT/7)) + (SCREEN_HEIGHT/7)))){
        choix_jeu(window, renderer, 15, "../grilles_predefinies/pecheur.txt");
        return 0;
      }
      if(event.button.button == SDL_BUTTON_LEFT && (xMouse>(3*(SCREEN_WIDTH/5)) && xMouse<((3*(SCREEN_WIDTH/5)) + (SCREEN_WIDTH/5))) && (yMouse>((SCREEN_HEIGHT/9)+3*(SCREEN_HEIGHT/7)) && yMouse<(((SCREEN_HEIGHT/9)+3*(SCREEN_HEIGHT/7)) + (SCREEN_HEIGHT/7)))){
        choix_jeu(window, renderer, 20, "../grilles_predefinies/perroquet.txt");
        return 0;
      }
      if(event.button.button == SDL_BUTTON_LEFT && (xMouse>(4*(SCREEN_WIDTH/5)) && xMouse<((4*(SCREEN_WIDTH/5)) + (SCREEN_WIDTH/5))) && (yMouse>((SCREEN_HEIGHT/9)+3*(SCREEN_HEIGHT/7)) && yMouse<(((SCREEN_HEIGHT/9)+3*(SCREEN_HEIGHT/7)) + (SCREEN_HEIGHT/7)))){
        choix_jeu(window, renderer, 10, "../grilles_predefinies/petit_bateau.txt");
        return 0;
      }

      if(event.button.button == SDL_BUTTON_LEFT && (xMouse>0 && xMouse<(SCREEN_WIDTH/5)) && (yMouse>((SCREEN_HEIGHT/9)+3*(SCREEN_HEIGHT/7)) && yMouse<(((SCREEN_HEIGHT/9)+4*(SCREEN_HEIGHT/7)) + (SCREEN_HEIGHT/7)))){
        choix_jeu(window, renderer, 10, "../grilles_predefinies/petit_poisson.txt");
        return 0;
      }
      if(event.button.button == SDL_BUTTON_LEFT && (xMouse>(SCREEN_WIDTH/5) && xMouse<((SCREEN_WIDTH/5) + (SCREEN_WIDTH/5))) && (yMouse>((SCREEN_HEIGHT/9)+4*(SCREEN_HEIGHT/7)) && yMouse<(((SCREEN_HEIGHT/9)) + 4*(SCREEN_HEIGHT/7) + (SCREEN_HEIGHT/7)))){
        choix_jeu(window, renderer, 20, "../grilles_predefinies/pieuvre.txt");
        return 0;
      }
      if(event.button.button == SDL_BUTTON_LEFT && (xMouse>(2*(SCREEN_WIDTH/5)) && xMouse<((2*(SCREEN_WIDTH/5)) + (SCREEN_WIDTH/5))) && (yMouse>((SCREEN_HEIGHT/9)+4*(SCREEN_HEIGHT/7)) && yMouse<(((SCREEN_HEIGHT/9)+4*(SCREEN_HEIGHT/7)) + (SCREEN_HEIGHT/7)))){
        choix_jeu(window, renderer, 20, "../grilles_predefinies/poisson.txt");
        return 0;
      }
      if(event.button.button == SDL_BUTTON_LEFT && (xMouse>(3*(SCREEN_WIDTH/5)) && xMouse<((3*(SCREEN_WIDTH/5)) + (SCREEN_WIDTH/5))) && (yMouse>((SCREEN_HEIGHT/9)+4*(SCREEN_HEIGHT/7)) && yMouse<(((SCREEN_HEIGHT/9)+4*(SCREEN_HEIGHT/7)) + (SCREEN_HEIGHT/7)))){
        choix_jeu(window, renderer, 11, "../grilles_predefinies/robot.txt");
        return 0;
      }
      if(event.button.button == SDL_BUTTON_LEFT && (xMouse>(4*(SCREEN_WIDTH/5)) && xMouse<((4*(SCREEN_WIDTH/5)) + (SCREEN_WIDTH/5))) && (yMouse>((SCREEN_HEIGHT/9)+4*(SCREEN_HEIGHT/7)) && yMouse<(((SCREEN_HEIGHT/9)+4*(SCREEN_HEIGHT/7)) + (SCREEN_WIDTH/7)))){
        choix_jeu(window, renderer, 10, "../grilles_predefinies/tete_chien.txt");
        return 0;
      }
			if(event.button.button == SDL_BUTTON_LEFT && (xMouse>(SCREEN_WIDTH/5) && xMouse<((SCREEN_WIDTH/5) + (SCREEN_WIDTH/5))) && (yMouse>((SCREEN_HEIGHT/9)+5*(SCREEN_HEIGHT/7)) && yMouse<(((SCREEN_HEIGHT/9)+5*(SCREEN_HEIGHT/7)) + (SCREEN_HEIGHT/7)))){
        choix_jeu(window, renderer, 20, "../grilles_predefinies/toad.txt");
        return 0;
      }
			if(event.button.button == SDL_BUTTON_LEFT && (xMouse>(3*(SCREEN_WIDTH/5)) && xMouse<((3*(SCREEN_WIDTH/5)) + (SCREEN_WIDTH/5))) && (yMouse>((SCREEN_HEIGHT/9)+5*(SCREEN_HEIGHT/7)) && yMouse<(((SCREEN_HEIGHT/9)+5*(SCREEN_HEIGHT/7)) + (SCREEN_HEIGHT/7)))){
        choix_jeu(window, renderer, 20, "../grilles_predefinies/voilier.txt");
        return 0;
      }
   }
  }

  return 0;
}
