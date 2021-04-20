#include <stdio.h>
#define N 11

int nb_condi(int mat[N][N], int i){           // fonction qui compte le nombre de condition d'une matrice condition
  int j;
  int compt = 0;
  for(j = 0; j < N; j++){
    if(mat[i][j] != 0){
      compt++;
    }
  }
  return compt;
}

void cas_uniques_ligne(int matrice[N][N], int mat_condi_ligne[N][N]){ // fonction qui rempli la grille en fonction des cas simples hormis les lignes/ colonnes pleines ou vides qui seront résolus par d'autres fonctions
  int somme;
  int i,j,k;
  int nb;
  // Pour les lignes
  for(i = 0; i < N; i++){
    k = 0;
    somme = 0;
    nb = nb_condi(mat_condi_ligne,i);       // on compte le nombre de condition
    while(k < nb){                  // brieve somme des conditions
      somme = somme + mat_condi_ligne[i][k];
      k++;
    }
    k = 0;
    if(somme == N-1){               // cas de deux blocs de cases noires
      for(j = 0; j < N; j++){
        if(j != mat_condi_ligne[i][0]){
          matrice[i][j] = 1;
        }else{
          matrice[i][j] = 0;
        }
      }
    }

    if(N % 2 == 1){                 // cas d'une matrice impair
      if(nb == N / 2 + 1){            // cas d'une case noir sur 2 avec N/2 + 1 cases noires
        for(j = 0; j < N; j++){
          if(j % 2 == 0){
            matrice[i][j] = 1;
          }else{
            matrice[i][j] = 0;
          }
        }
      }else{
        if(nb == N / 2){            // cas d'une case noir sur 2 avec N/2 cases noires
          for(j = 0; j < N; j++){
            if(j % 2 == 1){
              matrice[i][j] = 1;
            }else{
              matrice[i][j] = 0;
            }
          }
        }
      }
    }else{
      if(matrice[i][0] >= 1){            // cas d'une ligne commencant par une case noire
        for(j = 0; j < N; j++){
          if(j % 2 == 0){
            matrice[i][j] = 1;
          }else{
            matrice[i][j] = 0;
          }
        }
      }else{
        for(j = 0; j < N; j++){
          if(j % 2 == 1){
            matrice[i][j] = 1;
          }else{
            matrice[i][j] = 0;
          }
        }
      }
    }
  }
}

void cas_uniques_colonne(int matrice[N][N], int mat_condi_colonne[N][N]){ // fonction qui rempli la grille en fonction des cas simples hormis les lignes/ colonnes pleines ou vides qui seront résolus par d'autres fonctions
  int somme;
  int i,j,k;
  int nb;
  // Pour les colonnes
  for(j = 0; j < N; j++){
    k = 0;
    somme = 0;
    nb = nb_condi(mat_condi_colonne,j);       // on compte le nombre de condition
    while(k < nb){                  // brieve somme des conditions
      somme = somme + mat_condi_colonne[j][k];
      k++;
    }
    k = 0;
    if(somme == N-1){               // cas de deux blocs de cases noires
      for(i = 0; i < N; i++){
        if(i != mat_condi_colonne[j][0]){
          matrice[i][j] = 1;
        }else{
          matrice[i][j] = 0;
        }
      }
    }

    if(N % 2 == 1){                 // cas d'une matrice impair
      if(nb == N / 2 + 1){            // cas d'une case noir sur 2 avec N/2 + 1 cases noires
        for(i = 0; i < N; i++){
          if(i % 2 == 0){
            matrice[i][j] = 1;
          }else{
            matrice[i][j] = 0;
          }
        }
      }else{
        if(nb == N / 2){            // cas d'une case noir sur 2 avec N/2 cases noires
          for(i = 0; i < N; i++){
            if(i % 2 == 1){
              matrice[i][j] = 1;
            }else{
              matrice[i][j] = 0;
            }
          }
        }
      }
    }else{
      if(matrice[0][j] >= 1){            // cas d'une colonne commencant par une case noire
        for(i = 0; i < N; i++){
          if(i % 2 == 0){
            matrice[i][j] = 1;
          }else{
            matrice[i][j] = 0;
          }
        }
      }else{
        for(i = 0; i < N; j++){
          if(i % 2 == 1){
            matrice[i][j] = 1;
          }else{
            matrice[i][j] = 0;
          }
        }
      }
    }
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
                              {0, 0, 1, 0, 1, 0, 1, 0, 1, 0}};

  int grille_test_c1[N][N] = {{1, 0, 1, 0, 1, 0, 0, 1, 0, 0},
                              {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
                              {0, 0, 0, 1, 1, 0, 0, 1, 0, 1},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 1, 0, 0, 1, 1, 0, 1},
                              {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                              {0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                              {0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
                              {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                              {1, 1, 0, 0, 0, 1, 1, 0, 1, 0}};

  int mat_cond_1[N][N] =    { {3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {4, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {2, 3, 1, 0, 0, 0, 0, 0, 0, 0},
                              {1, 3, 0, 0, 0, 0, 0, 0, 0, 0},
                              {3, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                              {3, 3, 0, 0, 0, 0, 0, 0, 0, 0}};

  int grille_test_l2[N][N] = {{1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
                              {0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                              {0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0},
                              {1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0},
                              {0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
                              {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}};

  int grille_test_c2[N][N] = {{1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                              {1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
                              {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                              {1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
                              {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                              {1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0},
                              {0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0},
                              {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                              {0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
                              {0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0}};

  int mat_cond_2[N][N] =    {{5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {2, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                              {2, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                              {2, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {2, 2, 1, 2, 0, 0, 0, 0, 0, 0, 0},
                              {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
                              {2, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

  printf("Avant remplissage :\n");
 	affiche_matrice(grille_test_l2);
  printf("\n\n");
 	cas_uniques_ligne(grille_test_l2,mat_cond_2);
  printf("Après remplissage :\n");
  affiche_matrice(grille_test_l2);

  printf("\n Autre remplissage :\n");

  printf("Avant remplissage :\n");
 	affiche_matrice(grille_test_c2);
  printf("\n\n");
 	cas_uniques_colonne(grille_test_c2,mat_cond_2);
  printf("Après remplissage :\n");
  affiche_matrice(grille_test_c2);
	return 1;
}







