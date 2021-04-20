#ifndef _PICRUISE_SOLVEUR_H_
#define _PICRUISE_SOLVEUR_H_

#include "verif.h"
#include "commun.h"

void somme_cond_l(int * mat_cond, int * somme_cond, int format);

// on complete la matrice condition avec des 0 (pour faire des comparaison) dans une matrice intermédiaire
void remplissage_inter(int * mat, int * mat2, int format);

int nombre_bloc(int * condi_ligne,int ligne, int format);

extern
int solve(int * grille, int * mat_cond_l, int * mat_cond_c, int * combinaisons, int format);

extern
int resoudre_grille(int * grille, int * mat_cond_l, int * mat_cond_c, int * combinaisons, int i, int format);

extern
void init_mat_cub(int * combinaisons, int format);

extern
int solveur(int * grille, int * jeu, int * mat_cond_l, int * mat_cond_c, int format);

#endif
