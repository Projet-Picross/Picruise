/*
```C

``` */

#include<stdio.h>

#define N 10

void init_matrice(int matrice[N][N]){			//initialise la matrice avec des 0
	int i,j;
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			matrice[i][j] = 0;
		}
		printf("\n");
	}
}

void affecter_matrice(int matrice[N][N]){		// cette fonction lit un fichier
	int i,j;
	FILE * fichier;
	fichier = fopen("test_unitaire.txt","r");
	while(!feof(fichier)){
		fscanf(fichier,"%d", &i);
		fscanf(fichier,"%d", &j);
		matrice[i][j] = 1;
	}
	fclose(fichier);
}

//Début partie conditions

//Génération de la matrice des conditions des lignes
void generat_condi_lignes(int matrice[N][N], int mat_condi_lignes[N][N]){
  int i, j, k;
  int somme;
  //Parcours des lignes de la grille
  for(i = 0; i < N; i++){
    for(j = 0, k = 0, somme = 0; j < N; j++){
      if(matrice[i][j])
        somme++;
      //Dès qu'on rencontre une case blanche, on enregistre le nombre de cases noires formant une chaîne
      else if(somme){
        mat_condi_lignes[i][k++] = somme;
        somme = 0;
      }
      else
        somme = 0;
    }
    //Ajoute la dernière somme en cas de parcours complet de la ligne
    if(somme)
      mat_condi_lignes[i][k] = somme;
  }
}

//Génération de la matrice des conditions des colonnes
void generat_condi_colonnes(int matrice[N][N], int mat_condi_colonnes[N][N]){
  int i, j, k;
  int somme;
  //Parcours des lignes de la grille
  for(i = 0; i < N; i++){
    for(j = 0, k = 0, somme = 0; j < N; j++){
      if(matrice[j][i])
        somme++;
      //Dès qu'on rencontre une case blanche, on enregistre le nombre de cases noires formant une chaîne
      else if(somme){
        mat_condi_colonnes[i][k++] = somme;
        somme = 0;
      }
      else
        somme = 0;
    }
    //Ajoute la dernière somme en cas de parcours complet de la colonne
    if(somme)
      mat_condi_colonnes[i][k] = somme;
  }
}

//Vérifie que la somme des conditions, d'une ligne / colonne, ne dépasse pas sa taille et qu'il y a une case blanche entre chaque chaîne de cases noires
int verif_somme_cond(int mat_cond[N][N]){
  int i, j;
  int somme;
  for(i = 0; i < N; i++){
    //Parcours des conditions de la ligne / colonne
    for(j = 0, somme = 0; j < N && mat_cond[i][j]; j++)
      somme += mat_cond[i][j];
    if(somme+j-1 > N) //+j-1 : nombre de cases blanches nécessaires
      return 0;
  }
  return 1;
}

//Affichage des conditions
void affichage_condi(int mat_cond[N][N]){
  int i, j;
  for(i = 0; i < N; i++){
    //Parcours des conditions de la ligne / colonne
    for(j = 0; j < N && mat_cond[i][j]; j++)
      printf("%i ", mat_cond[i][j]);
    printf("\n");
  }
}


//Résultats attendus à partir de la matrice tête de chien
/*conditions_ligne[N][N]={{4}, {8}, {10}, {1, 1, 2, 1, 1}, {1, 6, 1}, {6}, {2, 2}, {4}, {2}}
4
8
10
1 1 2 1 1
1 1 2 1 1
1 6 1
6
2 2
4
2
*/

/*conditions_colonnes[N][N]={{4}, {2}, {7}, {3, 4}, {7, 2}, {7, 2}, {3, 4}, {7}, {2}, {4}}
4
2
7
3 4
7 2
7 2
3 4
7
2
4
*/


//Résultats attendus à partir de la matrice canard
/*conditions_ligne[N][N]={{4}, {2, 2}, {1, 1, 1}, {2, 1, 1}, {4, 2}, {1, 2, 1}, {1, 1, 1}, {2, 1}, {1, 1, 1}, {7}}
4
2 2
1 1 1
2 1 1
4 2
1 2 1
1 1 1
2 1
1 1 1
7
*/

/*conditions_colonnes[N][N]={{1, 1}, {4, 3}, {1, 3, 1}, {1, 1, 1}, {1, 2, 1}, {1, 1, 2}, {2, 1, 1}, {5, 1}, {1, 1}, {4}}
1 1
4 3
1 3 1
1 1 1
1 2 1
1 1 2
2 1 1
5 1
1 1
4
*/


//Test de les fonctions avec la matrice de la tête de chien
int main(){
  //Initialisation de la matrice tête de chien
  int grille[N][N];
  init_matrice(grille);
  affecter_matrice(grille);
  //Initialisation des matrices des conditions
  int mat_condi_lignes[N][N];
  int mat_condi_colonnes[N][N];
  init_matrice(mat_condi_lignes);
  init_matrice(mat_condi_colonnes);

  //Génération des conditions à partir des matrices
  generat_condi_lignes(grille, mat_condi_lignes);
  generat_condi_colonnes(grille, mat_condi_colonnes);

  //Affichage des conditions
  printf("Matrice conditions des lignes : \n");
  affichage_condi(mat_condi_lignes);
  printf("\nMatrice conditions des colonnes\n");
  affichage_condi(mat_condi_colonnes);

  //Vérification des conditions
  printf("\nValidation des conditions des lignes : %i\n", verif_somme_cond(mat_condi_lignes));
  printf("Validation des conditions des colonnes : %i\n", verif_somme_cond(mat_condi_colonnes));
}
