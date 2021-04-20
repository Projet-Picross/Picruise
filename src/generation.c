/**
* \file generation.c
* \brief Fonctions réalisant la génération des matrices
* \version 1.0
* \date 18 Avril 2021
* \author Mohamed Lemrabott, Julien Mahouin, Gallup Mohamad Jamil, Alexis Nolière
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>
#include <unistd.h>

#include <../src/generation.h>

/**
* \fn void init_matrice(int * matrice, int format)
* \brief Initialise une matrice avec des 0
* @param matrice est un pointeur d'entier qui pointe sur les cases de la grille du joueur
* @param format représente la taille de la matrice
*/
extern
void init_matrice(int * matrice, int format){
	int i,j;
	for(i = 0; i < format; i++){
		for(j = 0; j < format; j++){
			matrice[i*format + j] = 0;
		}
	}
}



/**
* \fn int genera_aleatoire(int * grille, int format)
* \brief Remplie une matrice aléatoirement avec des 0 et des 1
* @param grille est un pointeur d'entier qui pointe sur les cases de la grille du joueur
* @param format représente la taille de la matrice
* \return cpt un compteur de cases noires
*/
extern
int genera_aleatoire(int * grille, int format){
  srand(time(NULL));
  //Compteur de cases noires;
  int cpt = (int)(0.25*format*format) + rand()%(int)((0.75*format*format)-(0.25*format*format));
  int i, j, k;
  for(k = 0; k < cpt; k++){
      //Tirage aléatoire des coordonnées d'une case vide
      do{
        i = rand()%format;
        j = rand()%format;
      }while(grille[i*format + j]);
      grille[i*format + j] = 1;
  }
  return cpt;
}

/**
* \fn void affecter_matrice_predef(int * matrice, int format, char * fich)
* \brief Fonction qui remplie la matrice passée en paramètre via une seconde située dans un fichier
* @param matrice est un pointeur d'entier qui pointe sur les cases de la grille du joueur
* @param format représente la taille de la matrice
* @param fich est une chaine de caractère comportant le nom de la matrice prédéfinie
*/
extern
void affecter_matrice_predef(int * matrice, int format, char * fich){
	//fonction qui lit un fichier et place des points dans la matrice
	int i,j;
	FILE * fichier = fopen(fich,"r");
	while(!feof(fichier)){
		fscanf(fichier,"%d", &i);
		fscanf(fichier,"%d", &j);
		matrice[i*format + j] = 1;
	}
	fclose(fichier);
}


/**
* \fn void generat_condi_lignes(int * matrice, int * mat_condi_lignes, int format)
* \brief Génération de la matrice des conditions des lignes
* @param matrice est un pointeur d'entier qui pointe sur les cases de la grille du joueur
* @param mat_condi_lignes est un pointeur d'entier qui pointe sur les conditions des lignes du picross
* @param format représente la taille de la matrice
*/
extern
void generat_condi_lignes(int * matrice, int * mat_condi_lignes, int format){
  int i, j, k;
  int somme;
  //Parcours des lignes de la grille
  for(i = 0; i < format; i++){
    for(j = format-1, k = 0, somme = 0; j >= 0; j--){
      if(matrice[i*format + j])
        somme++;
      //Dès qu'on rencontre une case blanche, on enregistre le nombre de cases noires formant une chaîne
      else if(somme){
        mat_condi_lignes[i*format + k] = somme;
				k++;
        somme = 0;
      }
      else
        somme = 0;
    }
    //Ajoute la dernière somme en cas de parcours complet de la ligne
    if(somme)
      mat_condi_lignes[i*format + k] = somme;
  }
}

/**
* \fn void generat_condi_colonnes(int * matrice, int * mat_condi_colonnes, int format)
* \brief Génération de la matrice des conditions des colonnes
* @param matrice est un pointeur d'entier qui pointe sur les cases de la grille du joueur
* @param mat_condi_colonnes est un pointeur d'entier qui pointe sur les conditions des lignes du picross
* @param format représente la taille de la matrice
*/
extern
void generat_condi_colonnes(int * matrice, int * mat_condi_colonnes, int format){
  int i, j, k;
  int somme;
  //Parcours des lignes de la grille
  for(i = 0; i < format; i++){
    for(j = format-1, k = 0, somme = 0; j >= 0; j--){
      if(matrice[j*format + i])
        somme++;
      //Dès qu'on rencontre une case blanche, on enregistre le nombre de cases noires formant une chaîne
      else if(somme){
        mat_condi_colonnes[i*format + k] = somme;
				k++;
        somme = 0;
      }
      else
        somme = 0;
    }
    //Ajoute la dernière somme en cas de parcours complet de la colonne
    if(somme)
      mat_condi_colonnes[i*format + k] = somme;
  }
}
