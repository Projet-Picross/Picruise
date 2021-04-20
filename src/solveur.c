/**
* \file solveur.c
* \brief Fonctions permettant la résolution d'une grille de picross
* \version 1.0
* \date 18 Avril 2021
* \author Mohamed Lemrabott, Julien Mahouin, Gallup Mohamad Jamil, Alexis Nolière
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>
#include <unistd.h>

#include <../src/solveur.h>

/**
* \fn int nombre_bloc(int * condi_ligne,int ligne, int format)
* \brief Fonction qui compte le nombre de bloc present sur une ligne précise de la matrice condition
* @param condi_ligne est un pointeur d'entier qui pointe sur les conditions  des lignes du picross
* @param ligne est un indice indiquant la ligne à utiliser
* @param format représente la taille de la matrice
* \return un entier représentant le nombre de bloc sur la ligne concernée
*/
extern
int nombre_bloc(int * condi_ligne, int ligne, int format){
  int j;
  int nb_bloc_grille = 0;
  int inter_ligne[format][format];
  remplissage_inter(condi_ligne,&(inter_ligne[0][0]), format);

  for(j = 0; j < format; j++){
    if(inter_ligne[ligne][j] >= 1){
      nb_bloc_grille++;
    }
  }
  return nb_bloc_grille;
}

/**
* \fn void somme_cond_l(int * mat_cond, int * somme_cond, int format)
* \brief Remplie un tableau avec la somme de chaque lignes de la matrice condition
* @param mat_cond est un pointeur d'entier qui pointe sur les conditions du picross
* @param somme_cond est un pointeur d'entier qui pointe sur les sommes des conditions des lignes
* @param format représente la taille de la matrice
*/
extern
void somme_cond_l(int * mat_cond, int * somme_cond, int format){
  int i, j;
  for(i = 0; i < format; i++){
    //Calcul de la somme des conditions
    for(j = 0; j < format && mat_cond[i*format + j]; j++){
      somme_cond[i] += mat_cond[i*format + j];
    }
  }
}

/**
* \fn void remplissage_inter(int * mat, int * mat2, int format)
* \brief Copie la première matrice dans la deuxième et complète les vides avec des 0
* @param mat est un pointeur d'entier qui pointe sur les conditions du picross
* @param mat2 est un pointeur d'entier et sera la copie de mat mais pointant sur des 0 quand il y a des vides (elle complete mat)
* @param format représente la taille de la matrice
*/
extern
void remplissage_inter(int * mat, int * mat2, int format){
// on complete la matrice condition avec des 0 (pour faire des comparaison) dans une matrice intermédiaire
  int i,j;
  for(i = 0; i < format; i++){
    for(j = 0; j < format; j++){
      if(mat[i*format + j] < 0 || mat[i*format + j] > format){
        mat2[i*format + j] = 0;
      }else{
        mat2[i*format + j] = mat[i*format + j];
      }
    }
  }
}

/**
* \fn int solve(int * grille, int * mat_cond_l, int * mat_cond_c, int * combinaisons, int format)
* \brief Génère des solutions possibles pour la résolution du picross
* @param grille est un pointeur d'entier qui pointe sur les cases de la grille du joueur
* @param mat_cond_l est un pointeur d'entier qui pointe sur les conditions des lignes du picross
* @param mat_cond_c est un pointeur d'entier qui pointe sur les conditions des colonnes du picross
* @param combinaisons est un pointeur d'entier qui pointe sur les cases de la matrice cubique
* @param format représente la taille de la matrice
* \return 1 quand la fonction est terminée
*/
extern
int solve(int * grille, int * mat_cond_l, int * mat_cond_c, int * combinaisons, int format){
  int s[format];             // tableau qui contiendra les sommes des cases noires de chaque ligne
  int i, j, b, z, k;         // plusieurs indices
  int somme_b;            // nombre de cases blanches à avoir sur une ligne
  int compt_b = 0;          // compteur de case blanches sur une ligne
  int faux = 0;           // vaut 1 si la combinaison n'est pas possible

  for(i = 0; i < format; i++){
    s[i] = 0;
  }
  somme_cond_l(mat_cond_l,s, format);   // ce tableau comporte les sommes des cases noires de chaque ligne

  for(i = 0; i < format; i++){     // a chaque ligne de la matrice,
		j = 0;
    b = nombre_bloc(mat_cond_l,i, format);  // on met a jour le nombre de bloc noir sur la ligne
    somme_b = format - s[i];       // on déduit le nombre de cases blanches à trouver
    int combi[b+1];         // on créer un tableau ayant comme taille le nombre de blocs noirs + 1 (contiendra uniquement les cases blanches)
    int c[b*2 +1];          // on créer un tableau ayant comme taille le nombre de blocs noirs et blanc + 1 (contiendra cases blanches et noires)
    for(z = 0; z < b + 1; z++){   // on met à 0 le tableau qui testera les combinaisons possibles
      combi[z] = 0;
    }
      while(combi[0] <= (format - s[i] - b + 1)){
        for(z = 0; z < b + 1; z++){
          compt_b = compt_b + combi[z];
          if(z != 0 && z != b){
            if(combi[z] == 0){        // chaque case situées entre deux cases noires vaut au moins 1
              faux = 1;         // donc si ce n'est pas le cas on sort des if et de la boucle for
              compt_b = format+1;
              z = b+2;
            }
          }
        }

        k = 0;
        if(faux != 1 && (compt_b == somme_b)){  // si la combinaison est possible, on l'affiche
          for(z = 0; z < b*2 + 1; z++){   // on remplie le tableau c avec le tableau des cases blanches et des conditions (un après l'autres)
            if(z % 2 == 0){
              combinaisons[i*300*10 + j*10 + z] = combi[k];
            }else{
              combinaisons[i*300*10 + j*10 + z] = mat_cond_l[i* format + k];
              k++;
            }
          }
					j++;
        }
        faux = 0;
        compt_b = 0;
        for(z = b; z > 0; z--){       // incrémentation du tableaux des combinaisons en partant de la fin
          if(combi[b] >= (format - s[i] - b + 1)){ // si la dernière case du tableaux est au max, on met à 0 et on incrémente la case d'avant
            combi[b] = 0;
            z--;
            combi[z]++;
            while(combi[z] >= (format - s[i] - (b - 2)) && z != 0){  // si la case actuelle du tableaux est au max, on met à 0 et on incrémente la case d'avant
              combi[z] = 0;
              z--;
              combi[z]++;
            }
            z = 0;
          }else{              // si la dernière case du tableaux n'est pas au max, on l'incrémente
            combi[b]++;
            z = 0;
          }
        }
      }
			printf("\n");
   }
  return 1;
}

/**
* \fn int resoudre_grille(int * grille, int * mat_cond_l, int * mat_cond_c, int * combinaisons, int i, int format)
* \brief Combine les différentes lignes, générées précédamment et stockées dans la matrice cubique, et teste celles-ci afin de trouver la combinaison gagnante
* @param grille est un pointeur d'entier qui pointe sur les cases de la grille du joueur
* @param mat_cond_l est un pointeur d'entier qui pointe sur les conditions des lignes du picross
* @param mat_cond_c est un pointeur d'entier qui pointe sur les conditions des colonnes du picross
* @param combinaisons est un pointeur d'entier qui pointe sur les cases de la matrice cubique
* @param i est un entier indique la ligne de la matrice à traiter
* @param format représente la taille de la matrice
*/
extern
int resoudre_grille(int * grille, int * mat_cond_l, int * mat_cond_c, int * combinaisons/*[N][300][10]*/, int i, int format){
	int j, k, l, m, n, o, p;
	//Pour chaque ligne de la grille
			//On parcours toutes les combinaisons possibles
      for (j = 0; j < 300 && combinaisons[i*300*10 + j*10] != -1; j++){
					//On remplie la grille selon les blocs blancs et blocs noires
          for(k = 0, l = format-1; k < 10 && combinaisons[i*300*10 + j*10 + k] != -1; k++){
							for(p = l; l > (p - combinaisons[i*300*10 + j*10 + k]);){
								if(((k % 2) == 0) && (combinaisons[i*300*10 + j*10 + k] != 0)){
									grille[i*format + l] = 0;
									l--;
								}
								else{
									grille[i*format + l] = 1;
									l--;
								}
							}
      		}
				//Si on a terminé la grille, on l'affiche et on arrête la partie
				if(verif_lignes(mat_cond_l, grille, format) == 1 && verif_colonnes(mat_cond_c, grille, format) == 1){
					for(m = 0; m < format; m++){
						for(o = 0; o < format; o++){
							printf(" %d", grille[m*format + o]);
						}
						printf("\n");
					}
					printf("\n\nOK\n");
                    return 1;
				}

                    //Sinon, on continue de tester les autres possibilités et lignes sinon
				for(n = i+1; n < format; n++){
					resoudre_grille(grille, mat_cond_l, mat_cond_c, combinaisons, n, format);
					//Si on a terminé la grille, on l'affiche et on arrête la partie
				if(verif_lignes(mat_cond_l, grille, format) == 1 && verif_colonnes(mat_cond_c, grille, format) == 1){
					for(m = 0; m < format; m++){
						for(o = 0; o < format; o++){
							printf(" %d", grille[m*format + o]);
						}
						printf("\n");
					}
					printf("\n\nOK\n");
                    return 1;
				}
				}

  	}
}

/**
* \fn void init_mat_cub(int * combinaisons, int format)
* \brief Initialise la matrice cubique avec des -1
* @param combinaisons est un pointeur d'entier qui pointe sur les cases de la matrice cubique
* @param format représente la taille de la matrice
*/
extern
void init_mat_cub(int * combinaisons, int format){
	int i, j, k;
	for(i = 0; i < format; i++)
		for(j = 0; j < 300; j++)
			for(k = 0; k < 10; k++)
				combinaisons[i*300*10 + j*10 +k] = -1;
}

/**
* \fn int solveur(int * grille, int * jeu, int * mat_cond_l, int * mat_cond_c, int format)
* \brief Fonction qui appelle résoud une grille de picross à partir de plusieurs autres fonctions
* @param grille est un pointeur d'entier qui pointe sur les cases de la grille du joueur
* @param jeu est un pointeur d'entier qui pointe sur les cases d'une grille dont on effectuera des modifications
* @param mat_cond_l est un pointeur d'entier qui pointe sur les conditions des lignes du picross
* @param mat_cond_c est un pointeur d'entier qui pointe sur les conditions des colonnes du picross
* @param format représente la taille de la matrice
* \return 1 si la grille est résolue, 0 sinon
*/
extern
int solveur(int * grille, int * jeu, int * mat_cond_l, int * mat_cond_c, int format){
  int combinaisons[format][300][10];
  init_mat_cub(&(combinaisons[0][0][0]), format);
  solve(grille, mat_cond_l, mat_cond_c, &(combinaisons[0][0][0]), format);
  resoudre_grille(jeu, mat_cond_l, mat_cond_c, &(combinaisons[0][0][0]), 0, format);
}
