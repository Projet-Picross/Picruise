#ifndef _PICRUISE_GENERATION_H_
#define _PICRUISE_GENERATION_H_

#include "commun.h"

//initialise la matrice avec des 0
extern
void init_matrice(int * matrice, int format);

extern
int nombre_bloc(int * condi_ligne, int ligne, int format);

extern
void somme_cond_l(int * mat_cond, int * somme_cond, int format);

extern
void remplissage_inter(int * mat, int * mat2, int format);

extern
int genera_aleatoire(int * grille, int format);

extern
void affecter_matrice_predef(int * matrice, int format, char * fich);

extern
void generat_condi_lignes(int * matrice, int * mat_condi_lignes, int format);

extern
void generat_condi_colonnes(int * matrice, int * mat_condi_colonnes, int format);

#endif
