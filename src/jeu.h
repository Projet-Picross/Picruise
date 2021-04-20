#ifndef _PICRUISE_JEU_H_
#define _PICRUISE_JEU_H_

#include "affichage.h"
#include "verif.h"
#include "generation.h"
#include "solveur.h"
#include "accueil.h"
#include "commun.h"

int jouer(SDL_Window * window, SDL_Renderer* renderer ,SDL_Rect * r, int * grille, int * mat_cond_l, int * mat_cond_c, int nb_max_cond_lignes, int nb_max_cond_colonnes, int format);

int jeu (SDL_Window * window, SDL_Renderer * renderer, int format, char * grille_predef, int joueur);

#endif
