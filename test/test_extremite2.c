#include <stdio.h>
#define N 10

int nb_condi(int mat[N][N], int i){					// fonction qui compte le nombre de condition d'une matrice condition
	int j;
	int compt = 0;
	for(j = 0; j < N; j++){
		if(mat[i][j] > 0){
			compt++;
		}
	}
	return compt;
}

void extremite_ligne(int matrice[N][N], int mat_condi_ligne[N][N]){	// fonction qui remplie les lignes et colonnes dont une des extremites est une case noires
	int ind;
	int nb = 0;
	int i = 0, j = 0, k = 0;
	for(ind = 0; ind < N; ind++){
		i = ind;
		nb = nb_condi(mat_condi_ligne,i);
		if(matrice[i][0] >= 1){					// cas où on possède une case noire en début de ligne
			j = 0;
			while(k < mat_condi_ligne[i][nb-1]){
				matrice[i][j] = 1;
				k++;
				j++;
			}
		}
		k = 0;
		if(matrice[i][N-1] >= 1){					// cas où on possède une case noire en fin de ligne
			j = N-1;
			while(k < mat_condi_ligne[i][0]){
				matrice[i][j] = 1;
				k++;
				j--;
			}
		}
		k = 0;
	}
}

void extremite_colonne(int matrice[N][N], int mat_condi_colonne[N][N]){	// fonction qui remplie les lignes et colonnes dont une des extremites est une case noires
	int ind;
	int nb = 0;
	int i = 0, j = 0, k = 0;
	for(ind = 0; ind < N; ind++){
		j = ind;
		nb = nb_condi(mat_condi_colonne,i);
		if(matrice[0][j] >= 1 && mat_condi_colonne[j][nb-1] > 1){					// cas où on possède une case noire en début de ligne
			i = 0;
			while(k < mat_condi_colonne[j][nb-1]){
				matrice[i][j] = 1;
				k++;
				i++;
			}
		}
		k = 0;
		if(matrice[N-1][j] >= 1){					// cas où on possède une case noire en fin de ligne
			i = N-1;
			while(k < mat_condi_colonne[j][0] && mat_condi_colonne[j][0] > 1){
				matrice[i][j] = 1;
				k++;
				i--;
			}
		}
		k = 0;
	}
}

void affiche_matrice(int matrice[N][N]){
	int i,j;
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			if(matrice[i][j] == 1){
				printf("X ");					//cases remplies
			}else{
				printf(". ");					//cases vides
			}
		}
		printf("\n");
	}
}

int main(){
	int grille_test_l1[N][N] = {{1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                              {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
                              {1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
                              {0, 1, 0, 0, 1, 0, 1, 0, 1, 1},
                              {1, 0, 1, 0, 1, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
                              {0, 0, 1, 0, 1, 0, 1, 0, 1, 0},};

  int grille_test_c1[N][N] = {{1, 0, 1, 0, 1, 0, 0, 1, 0, 0},
                              {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
                              {0, 0, 0, 1, 1, 0, 0, 1, 0, 1},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 1, 0, 0, 1, 1, 0, 1},
                              {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                              {0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                              {0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
                              {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                              {1, 1, 0, 0, 0, 1, 1, 0, 1, 0},};

  int mat_cond_1[N][N] =    { {2, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                              {6, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {5, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {2, 3, 1, 0, 0, 0, 0, 0, 0, 0},
                              {1, 3, 0, 0, 0, 0, 0, 0, 0, 0},
                              {3, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                              {3, 3, 0, 0, 0, 0, 0, 0, 0, 0}};

  int grille_test_l2[N][N] = {{1, 0, 1, 0, 1, 0, 1, 0, 0, 0},
                              {0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
                              {0, 0, 1, 0, 0, 0, 1, 0, 1, 1},
                              {1, 0, 0, 0, 1, 0, 1, 1, 0, 0},
                              {0, 0, 1, 0, 0, 0, 1, 0, 1, 1},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                              {1, 0, 0, 0, 1, 0, 1, 1, 0, 0}};

  int grille_test_c2[N][N] = {{1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
                              {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
                              {1, 0, 1, 0, 1, 0, 1, 0, 0, 0},
                              {0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
                              {1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
                              {0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
                              {1, 0, 1, 1, 1, 0, 1, 0, 0, 1},
                              {0, 1, 0, 1, 0, 0, 1, 0, 0, 1},
                              {0, 0, 1, 0, 1, 0, 1, 0, 0, 0},
                              {0, 1, 1, 0, 1, 0, 1, 0, 0, 0}};

  int mat_cond_2[N][N] =    {{3, 3, 0, 0, 0, 0, 0, 0, 0, 0},
                              {3, 3, 0, 0, 0, 0, 0, 0, 0, 0},
                              {2, 3, 1, 0, 0, 0, 0, 0, 0, 0},
                              {2, 3, 1, 0, 0, 0, 0, 0, 0, 0},
                              {2, 3, 2, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {10, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {7, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {2, 2, 1, 2, 0, 0, 0, 0, 0, 0},
                              {2, 3, 1, 0, 0, 0, 0, 0, 0, 0}};

    /*printf("Avant remplissage :\n");
 	affiche_matrice(grille_test_l1);
  	printf("\n\n");
 	extremite_ligne(grille_test_l1,mat_cond_1);
  	printf("Après remplissage :\n");
  	affiche_matrice(grille_test_l1);*/

  	printf("Avant remplissage :\n");
 	affiche_matrice(grille_test_l1);
  	printf("\n\n");
 	extremite_ligne(grille_test_l1,mat_cond_1);
  	printf("Après remplissage :\n");
  	affiche_matrice(grille_test_l1);
	return 1;
}
