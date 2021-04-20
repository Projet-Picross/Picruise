/**
* \file affichage.c
* \brief Fonction produisant le rendu du jeu Picruise
* \version 1.0
* \date 18 Avril 2021
* \author Mohamed Lemrabott, Julien Mahouin, Gallup Mohamad Jamil, Alexis Nolière
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>
#include <unistd.h>

#include <../src/affichage.h>

/**
* \fn void affiche_jeu(SDL_Window * window, SDL_Renderer * renderer, SDL_Rect * r, int * grille, int * mat_cond_l, int * mat_cond_c, int format, int nb_max_cond_lignes, int nb_max_cond_colonnes)
* \brief Fonction qui produit le rendu final du jeu Picruise
* @param window est une fenêtre générée avec SDL dans laquelle se déroulera l'affichage du jeu Picruise
* @param renderer est le moteur de rendu de la fenêtre, l'espace où nous allons pouvoir faire notre affichage
* @param r représente un ensemble de cases, formant une grille, avec lesquelles le joueur peut intéragir
* @param grille est un pointeur d'entier qui pointe sur les cases de la grille du joueur
* @param mat_cond_l est un pointeur d'entier qui pointe sur les conditions des lignes du picross
* @param mat_cond_c est un pointeur d'entier qui pointe sur les conditions des colonnes du picross
* @param format représente la taille de la matrice
* @param nb_max_cond_lignes est le nombre maximale de condition qu'une ligne du picross puisse obtenir
* @param nb_max_cond_colonnes est le nombre maximale de condition qu'une colonne du picross puisse obtenir
* \return une variable utilisée pour perpétuer la boucle d'intéraction, sa valeur sera 0 quand on arretera le jeu
*/
extern
void affiche_jeu(SDL_Window * window, SDL_Renderer * renderer, SDL_Rect * r, int * grille, int * mat_cond_l, int * mat_cond_c, int format, int nb_max_cond_lignes, int nb_max_cond_colonnes){
    int i,j;
		SDL_RenderClear(renderer);
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

//Affichage du bouton pour quitter
SDL_Rect dest = { (SCREEN_WIDTH/2)+(SCREEN_WIDTH/4)+(SCREEN_WIDTH/5)+(SCREEN_WIDTH/190), 0, SCREEN_WIDTH/22, SCREEN_HEIGHT/12};
background = SDL_LoadBMP("../sprites/bouton_quit.bmp");
textBackground = SDL_CreateTextureFromSurface(renderer,background);
SDL_RenderCopy(renderer, textBackground, NULL, &dest);
SDL_RenderPresent(renderer);


//Affichage du timer
dest.x = SCREEN_WIDTH/36;
dest.y = SCREEN_HEIGHT/17;
dest.w = SCREEN_WIDTH/6;
dest.h = SCREEN_HEIGHT/9;
background = SDL_LoadBMP("../sprites/timer.bmp");
textBackground = SDL_CreateTextureFromSurface(renderer,background);
SDL_RenderCopy(renderer, textBackground, NULL, &dest);
SDL_RenderPresent(renderer);


TTF_Font * font = TTF_OpenFont("arial.ttf", 25);
const char * error = TTF_GetError();
SDL_Color color = { 0, 0, 0 };
SDL_Surface * surface = NULL;
SDL_Texture * texture = NULL;
int texW = 0;
int texH = 0;
SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
SDL_Rect dstrect = { 0, 0, texW, texH };


int nb_max_condi = (nb_max_cond_lignes > nb_max_cond_colonnes) ? nb_max_cond_lignes : nb_max_cond_colonnes;
int d_c_l = (SCREEN_WIDTH/(format+nb_max_condi))*(nb_max_cond_lignes-1);
int d_c_c = (SCREEN_HEIGHT/(format+nb_max_condi))*nb_max_cond_colonnes;

char valeur[2];

//Affichage de la matrice des conditions des colonnes

 for(i = 0; i < format; i++){
   for(j = nb_max_cond_colonnes; j >= 0; j--){
     if(mat_cond_c[i*format + j]){
       dest.x = (SCREEN_WIDTH/36 + SCREEN_WIDTH/6) + (i+1+nb_max_condi/2)*((SCREEN_HEIGHT- SCREEN_HEIGHT/9)/(format+nb_max_condi+1));
       dest.y = ((SCREEN_HEIGHT/17 + SCREEN_HEIGHT/9) + (nb_max_condi/2+1)*((SCREEN_HEIGHT- SCREEN_HEIGHT/9)/(format+nb_max_condi+1))) - ((j+1)*((SCREEN_HEIGHT- SCREEN_HEIGHT/9)/(format+nb_max_condi+1)));
       dest.w = (SCREEN_HEIGHT- SCREEN_HEIGHT/9)/(format+nb_max_condi+1);
       dest.h = (SCREEN_HEIGHT- SCREEN_HEIGHT/9)/(format+nb_max_condi+1);
       if(j%2){
         switch(mat_cond_c[i*format + j]){
           case 1 :
               background = SDL_LoadBMP("../sprites/1.bmp");
               break;
           case 2 :
               background = SDL_LoadBMP("../sprites/2.bmp");
               break;
           case 3 :
               background = SDL_LoadBMP("../sprites/3.bmp");
               break;
           case 4 :
               background = SDL_LoadBMP("../sprites/4.bmp");
               break;
           case 5 :
               background = SDL_LoadBMP("../sprites/5.bmp");
               break;
          case 6 :
              background = SDL_LoadBMP("../sprites/6.bmp");
              break;
           case 7 :
               background = SDL_LoadBMP("../sprites/7.bmp");
               break;
          case 8 :
               background = SDL_LoadBMP("../sprites/8.bmp");
               break;
          case 9 :
               background = SDL_LoadBMP("../sprites/9.bmp");
               break;
          case 10 :
               background = SDL_LoadBMP("../sprites/10.bmp");
               break;
          case 11 :
               background = SDL_LoadBMP("../sprites/11.bmp");
               break;
          case 12 :
               background = SDL_LoadBMP("../sprites/12_1.bmp");
               break;
          case 13 :
               background = SDL_LoadBMP("../sprites/13.bmp");
               break;
          case 14 :
              background = SDL_LoadBMP("../sprites/14.bmp");
              break;
          case 15 :
              background = SDL_LoadBMP("../sprites/15.bmp");
              break;
          case 16 :
              background = SDL_LoadBMP("../sprites/16.bmp");
              break;
          case 17 :
              background = SDL_LoadBMP("../sprites/17.bmp");
              break;
          case 18 :
              background = SDL_LoadBMP("../sprites/18.bmp");
              break;
          case 19 :
              background = SDL_LoadBMP("../sprites/19.bmp");
              break;
          case 20 :
              background = SDL_LoadBMP("../sprites/20.bmp");
              break;
           default :
               break;
        }
       }
       else{
         switch(mat_cond_c[i*format + j]){
          case 1 :
              background = SDL_LoadBMP("../sprites/12.bmp");
              break;
          case 2 :
              background = SDL_LoadBMP("../sprites/22.bmp");
              break;
          case 3 :
              background = SDL_LoadBMP("../sprites/32.bmp");
              break;
          case 4 :
              background = SDL_LoadBMP("../sprites/42.bmp");
              break;
          case 5 :
              background = SDL_LoadBMP("../sprites/52.bmp");
              break;
          case 6 :
              background = SDL_LoadBMP("../sprites/62.bmp");
              break;
          case 7 :
              background = SDL_LoadBMP("../sprites/72.bmp");
              break;
          case 8 :
               background = SDL_LoadBMP("../sprites/82.bmp");
               break;
          case 9 :
               background = SDL_LoadBMP("../sprites/92.bmp");
               break;
          case 10 :
               background = SDL_LoadBMP("../sprites/102.bmp");
               break;
          case 11 :
               background = SDL_LoadBMP("../sprites/112.bmp");
               break;
          case 12 :
               background = SDL_LoadBMP("../sprites/122.bmp");
               break;
          case 13 :
               background = SDL_LoadBMP("../sprites/132.bmp");
               break;
          case 14 :
              background = SDL_LoadBMP("../sprites/142.bmp");
              break;
          case 15 :
              background = SDL_LoadBMP("../sprites/152.bmp");
              break;
          case 16 :
              background = SDL_LoadBMP("../sprites/162.bmp");
              break;
          case 17 :
              background = SDL_LoadBMP("../sprites/172.bmp");
              break;
          case 18 :
              background = SDL_LoadBMP("../sprites/182.bmp");
              break;
          case 19 :
              background = SDL_LoadBMP("../sprites/192.bmp");
              break;
          case 20 :
              background = SDL_LoadBMP("../sprites/202.bmp");
              break;
          default :
              break;
         }
       }
       textBackground = SDL_CreateTextureFromSurface(renderer,background);
       SDL_RenderCopy(renderer, textBackground, NULL, &dest);
       SDL_RenderPresent(renderer);
     }
     /*if(mat_cond_c[i][j]){

       dstrect = { (SCREEN_WIDTH/N)*(nb_max_cond_lignes-1)+i*(500 / (N+nb_max_condi)), d_c_c - (j+1)*(500/(N+nb_max_condi)), 500/(N+nb_max_condi), 500/(N+nb_max_condi) };
       if(j%2)
           SDL_SetRenderDrawColor( renderer, 200, 200, 200, 200 );
       else
           SDL_SetRenderDrawColor( renderer, 100, 100, 100, 100 );

       SDL_RenderFillRect( renderer, &dstrect);
       SDL_RenderPresent(renderer);
       sprintf(valeur, "%d", mat_cond_c[i][j]);
       surface = TTF_RenderText_Solid(font, valeur, color);
       texture = SDL_CreateTextureFromSurface(renderer, surface);
       SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
       dstrect.x += (dstrect.w / 3);
       dstrect.y += (dstrect.h / 5);
       dstrect.w = texW;
       dstrect.h = texH;
       SDL_RenderCopy(renderer, texture, NULL, &dstrect);
       SDL_RenderPresent(renderer);

     }*/
   }
 }

 //Affichage de la matrice des conditions des lignes
   for(i = 0; i < format; i++){
    for(j = nb_max_cond_lignes; j >= 0; j--){
     if(mat_cond_l[i*format + j]){
       dest.x = ((SCREEN_WIDTH/36 + SCREEN_WIDTH/6) + (nb_max_condi/2+1)*((SCREEN_HEIGHT- SCREEN_HEIGHT/9)/(format+nb_max_condi+1))) - ((j+1)*((SCREEN_HEIGHT- SCREEN_HEIGHT/9)/(format+nb_max_condi+1)));
       dest.y = (SCREEN_HEIGHT/17 + SCREEN_HEIGHT/9) +  (i+1+nb_max_condi/2)*((SCREEN_HEIGHT- SCREEN_HEIGHT/9)/(format+nb_max_condi+1));
       dest.w = (SCREEN_HEIGHT- SCREEN_HEIGHT/9)/(format+nb_max_condi+1);
       dest.h = (SCREEN_HEIGHT- SCREEN_HEIGHT/9)/(format+nb_max_condi+1);
       if(j%2){
         switch(mat_cond_l[i*format + j]){
           case 1 : background = SDL_LoadBMP("../sprites/1.bmp");
               break;
           case 2 : background = SDL_LoadBMP("../sprites/2.bmp");
               break;
           case 3 :
               background = SDL_LoadBMP("../sprites/3.bmp");
               break;
           case 4 :
               background = SDL_LoadBMP("../sprites/4.bmp");
               break;
           case 5 :
               background = SDL_LoadBMP("../sprites/5.bmp");
               break;
            case 6 :
               background = SDL_LoadBMP("../sprites/6.bmp");
               break;
           case 7 :
               background = SDL_LoadBMP("../sprites/7.bmp");
               break;
           case 8 :
               background = SDL_LoadBMP("../sprites/8.bmp");
               break;
          case 9 :
               background = SDL_LoadBMP("../sprites/9.bmp");
               break;
          case 10 :
               background = SDL_LoadBMP("../sprites/10.bmp");
               break;
          case 11 :
               background = SDL_LoadBMP("../sprites/11.bmp");
               break;
          case 12 :
               background = SDL_LoadBMP("../sprites/12_1.bmp");
               break;
          case 13 :
               background = SDL_LoadBMP("../sprites/13.bmp");
               break;
          case 14 :
              background = SDL_LoadBMP("../sprites/14.bmp");
              break;
          case 15 :
              background = SDL_LoadBMP("../sprites/15.bmp");
              break;
          case 16 :
              background = SDL_LoadBMP("../sprites/16.bmp");
              break;
          case 17 :
              background = SDL_LoadBMP("../sprites/17.bmp");
              break;
          case 18 :
              background = SDL_LoadBMP("../sprites/18.bmp");
              break;
          case 19 :
              background = SDL_LoadBMP("../sprites/19.bmp");
              break;
          case 20 :
              background = SDL_LoadBMP("../sprites/20.bmp");
              break;
           default :
               break;
        }
       }
       else{
         switch(mat_cond_l[i*format + j]){
           case 1 :
               background = SDL_LoadBMP("../sprites/12.bmp");
           case 2 :
               background = SDL_LoadBMP("../sprites/22.bmp");
           case 3 :
               background = SDL_LoadBMP("../sprites/32.bmp");
               break;
           case 4 :
               background = SDL_LoadBMP("../sprites/42.bmp");
               break;
           case 5 :
               background = SDL_LoadBMP("../sprites/52.bmp");
               break;
            case 6 :
               background = SDL_LoadBMP("../sprites/62.bmp");
               break;
           case 7 :
               background = SDL_LoadBMP("../sprites/72.bmp");
               break;
        case 8 :
               background = SDL_LoadBMP("../sprites/82.bmp");
               break;
          case 9 :
               background = SDL_LoadBMP("../sprites/92.bmp");
               break;
          case 10 :
               background = SDL_LoadBMP("../sprites/102.bmp");
               break;
          case 11 :
               background = SDL_LoadBMP("../sprites/112.bmp");
               break;
          case 12 :
               background = SDL_LoadBMP("../sprites/122.bmp");
               break;
          case 13 :
               background = SDL_LoadBMP("../sprites/132.bmp");
               break;
          case 14 :
              background = SDL_LoadBMP("../sprites/142.bmp");
              break;
          case 15 :
              background = SDL_LoadBMP("../sprites/152.bmp");
              break;
          case 16 :
              background = SDL_LoadBMP("../sprites/162.bmp");
              break;
          case 17 :
              background = SDL_LoadBMP("../sprites/172.bmp");
              break;
          case 18 :
              background = SDL_LoadBMP("../sprites/182.bmp");
              break;
          case 19 :
              background = SDL_LoadBMP("../sprites/192.bmp");
              break;
          case 20 :
              background = SDL_LoadBMP("../sprites/202.bmp");
              break;
           default :
               break;
         }
       }
       textBackground = SDL_CreateTextureFromSurface(renderer,background);
       SDL_RenderCopy(renderer, textBackground, NULL, &dest);
       SDL_RenderPresent(renderer);
     }
       /*
       if(j%2)
           SDL_SetRenderDrawColor( renderer, 200, 200, 200, 200 );
       else
           SDL_SetRenderDrawColor( renderer, 100, 100, 100, 100 );
       SDL_RenderFillRect( renderer, &dstrect);
       SDL_RenderPresent(renderer);
       sprintf(valeur, "%d", mat_cond_l[i][j]);
       surface = TTF_RenderText_Solid(font, valeur, color);
       texture = SDL_CreateTextureFromSurface(renderer, surface);
       SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
       dstrect.x += (dstrect.w / 3);
       dstrect.y += (dstrect.h / 5);
       dstrect.w = texW;
       dstrect.h = texH;
       SDL_RenderCopy(renderer, texture, NULL, &dstrect);
       SDL_RenderPresent(renderer);*/
     }
   }


//sdl affiche grille
int compteur=0;
for(i=0;i<format;i++){
for(j=0;j<format;j++){
       r[i*format + j].w = (SCREEN_HEIGHT- SCREEN_HEIGHT/9)/(format+nb_max_condi+1);
       r[i*format + j].h = (SCREEN_HEIGHT- SCREEN_HEIGHT/9)/(format+nb_max_condi+1);
       r[i*format + j].x = (SCREEN_WIDTH/36 + SCREEN_WIDTH/6) + (j+1+nb_max_condi/2)*r[i*format + j].w;
       r[i*format + j].y  = (SCREEN_HEIGHT/17 + SCREEN_HEIGHT/9) +  (i+1+nb_max_condi/2)*r[i*format + j].h;

      dest.x = r[i*format + j].x;
      dest.y = r[i*format + j].y;
      dest.w = r[i*format + j].w;
      dest.h = r[i*format + j].h;
			 if(grille[i*format + j])
			 	background = SDL_LoadBMP("../sprites/case_noire.bmp");
			 else
       	background = SDL_LoadBMP("../sprites/case_vide.bmp");
       textBackground = SDL_CreateTextureFromSurface(renderer,background);
       SDL_RenderCopy(renderer, textBackground, NULL, &dest);
       SDL_RenderPresent(renderer);
       // Up until now everything was drawn behind the scenes.
       // This will show the new, red contents of the window.
       SDL_RenderPresent(renderer);
       compteur++;
        printf("%d\n",compteur);
}
}
}
