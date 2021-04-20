/**
* \file verif.c
* \brief Fonctions vérifiant les conditions d'une grille de picross
* \version 1.0
* \date 18 Avril 2021
* \author Mohamed Lemrabott, Julien Mahouin, Gallup Mohamad Jamil, Alexis Nolière
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>
#include <unistd.h>

#include <../src/verif.h>

/**
* \fn int verif_lignes(int * mat_cond, int * grille, int format)
* \brief Verifie les lignes de la matrice condition
* @param mat_cond est un pointeur d'entier qui pointe sur les conditions du picross
* @param grille est un pointeur d'entier qui pointe sur les cases de la grille du joueur
* @param format représente la taille de la matrice
* \return 1 si la grille est correct, 0 sinon
*/
extern
int verif_lignes(int * mat_cond, int * grille, int format){
  int i, j, k;
  int nb_cond, nb_bloc, nb_noires;
  for(i = 0; i < format; i++){
    //Calcul de la somme des conditions
    for(j = 0, nb_cond = 0; j < format && mat_cond[i*format + j]; j++);
    nb_cond += j;
    //Calcul du nombre de bloc
    for(j = 1, nb_bloc = 0; j < format; j++){
      //Un bloc est définie si la case actuelle est blanche et la case précedente est noire
      if((grille[i*format + j] != 1) && (grille[i*format + j-1] == 1))
        nb_bloc++;
    }
    //Cas où la dernière case est noire
    if((grille[i*format + format-1] == 1))
      nb_bloc++;

    if(nb_cond == nb_bloc){
    //Le nombre de cases noires de chaque bloc doît avoir un nombre de cases noires inférieur ou égale à la condition correspondante
      for(j = format-1, k = 0, nb_noires = 0; j >= 0 && k < format && mat_cond[i*format + k]; j--){
        if(grille[i*format + j] == 1)
          nb_noires++;
        //Cas ou le premier bloc est blanche
        else if(nb_noires){
          if(nb_noires != mat_cond[i*format + k])
            return 0;
          //Sinon, on passe au bloc suivant
          k++;
          nb_noires = 0;
        }
     }
     //Cas d'un bloc à l'extrémité
     if(grille[i*format] == 1)
        if(nb_noires != mat_cond[i*format + k])
            return 0;
    }
    else
        return 0;
  }
  return 1;
}


/**
* \fn int verif_colonnes(int * mat_cond, int * grille, int format)
* \brief Verifie les colonnes de la matrice condition
* @param mat_cond est un pointeur d'entier qui pointe sur les conditions du picross
* @param grille est un pointeur d'entier qui pointe sur les cases de la grille du joueur
* @param format représente la taille de la matrice
* \return 1 si la grille est correct, 0 sinon
*/
extern
int verif_colonnes(int * mat_cond, int * grille, int format){
  int i, j, k;
  int nb_cond, nb_bloc, nb_noires;
  for(i = 0; i < format; i++){
    //Calcul de la somme des conditions
    for(j = 0, nb_cond = 0; j < format && mat_cond[i*format + j]; j++);
    nb_cond += j;
    //Calcul du nombre de bloc
    for(j = 1, nb_bloc = 0; j < format; j++){
      //Un bloc est définie si la case actuelle est blanche et la case précedente est noire
      if((grille[j*format + i] != 1) && (grille[(j-1)*format + i] == 1))
        nb_bloc++;
    }
    //Cas où la dernière case est noire
    if(grille[(format-1)*format + i] == 1)
      nb_bloc++;

    if(nb_cond == nb_bloc){
    //Le nombre de cases noires de chaque bloc doît avoir un nombre de cases noires inférieur ou égale à la condition correspondante
      for(j = format-1, k = 0, nb_noires = 0; j >= 0 && k < format && mat_cond[i*format + k]; j--){
        if(grille[j*format + i] == 1)
          nb_noires++;
        //Cas ou le premier bloc est blanche
        else if(nb_noires){
          if(nb_noires != mat_cond[i*format + k])
            return 0;
          //Sinon, on passe au bloc suivant
          k++;
          nb_noires = 0;
        }
     }
     //Cas d'un bloc à l'extrémité
     if(grille[i] == 1)
        if(nb_noires != mat_cond[i*format + k])
            return 0;
    }
    else
        return 0;
  }
  return 1;
}
