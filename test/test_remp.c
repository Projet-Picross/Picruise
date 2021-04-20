#include<stdio.h>

#define N 10

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

//remplir la grille si les lignes/colonnes sont vides/pleines
void cas_basique_l(int mat_condition_l[N][N], int grille[N][N])
{
    int i, j;
    for(i=0;i<N;i++)
			//si une ligne n'a que des cases noires
			if(mat_condition_l[i][0] && !mat_condition_l[i][1] && mat_condition_l[i][0] == N)
        for(j=0;j<N;j++)
          grille[i][j]=1;
}

//remplir la grille si les lignes/colonnes sont vides/pleines
void cas_basique_c(int mat_condition_c[N][N], int grille[N][N])
{
    int i, j;
    for(i=0;i<N;i++)
			//si une ligne n'a que des cases noires
			if(mat_condition_c[i][0] && !mat_condition_c[i][1] && mat_condition_c[i][0] == N)
        for(j=0;j<N;j++)
          grille[j][i]=1;
}

void cas_mediane_l(int mat_condition_l[N][N], int grille[N][N])
{
    int i,j,k,l;
		int nb_noires; //
    //pour les lignes
    for(i=0;i<N;i++){
        //si la somme d'une condition d'une ligne est superieur à la moitié d'une taille d'une ligne
        for(k = 0; k < N && mat_condition_l[i][k]; k++){
					//Si N est paire
					if(!(N % 2))
						if(mat_condition_l[i][k] > (N / 2))
							for(j = N/2-1, l = N/2, nb_noires = 0; (j >= 0) && (l < N) && (nb_noires <= (mat_condition_l[i][k] - 2)); j--, l++){
								grille[i][j] = 1;
								grille[i][l] = 1;
								nb_noires += 2;
							}
					//Si N est paire
					if(N % 2)
						if(mat_condition_l[i][k] >= ((int)(N / 2)+1)){
							grille[i][(int)(N / 2)] = 1;
							for(j = (int)(N / 2)-1, l = (int)(N / 2)+1, nb_noires = 1; (j >= 0) && (l < N) && (nb_noires <= (mat_condition_l[i][k] - 2)); j--, l++){
								grille[i][j] = 1;
								grille[i][l] = 1;
								nb_noires += 2;
							}
						}
				}
		}
}

void cas_mediane_c(int mat_condition_c[N][N], int grille[N][N])
{
    int i,j,k,l;
		int nb_noires; //
    //pour les lignes
    for(i=0;i<N;i++){
        //si la somme d'une condition d'une ligne est superieur à la moitié d'une taille d'une ligne
        for(k = 0; k < N && mat_condition_c[i][k]; k++){
					//Si N est paire
					if(!(N % 2))
						if(mat_condition_c[i][k] > (N / 2))
							for(j = N/2-1, l = N/2, nb_noires = 0; (j >= 0) && (l < N) && (nb_noires <= (mat_condition_c[i][k] - 2)); j--, l++){
								grille[j][i] = 1;
								grille[l][i] = 1;
								nb_noires += 2;
							}
					//Si N est paire
					if(N % 2)
						if(mat_condition_c[i][k] >= ((int)(N / 2)+1)){
							grille[(int)(N / 2)][i] = 1;
							for(j = (int)(N / 2)-1, l = (int)(N / 2)+1, nb_noires = 1; (j >= 0) && (l < N) && (nb_noires <= (mat_condition_c[i][k] - 2)); j--, l++){
								grille[j][i] = 1;
								grille[l][i] = 1;
								nb_noires += 2;
							}
						}
				}
		}
}

int main(){
  //Matrices de test
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

  int mat_cond_1[N][N] =    { {3, 3, 0, 0, 0, 0, 0, 0, 0, 0},
                              {2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
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
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

  int grille_test_c2[N][N] = {{1, 0, 0, 1, 0, 0, 1, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
                              {1, 0, 1, 0, 1, 0, 1, 0, 0, 0},
                              {0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
                              {1, 0, 0, 1, 0, 0, 1, 0, 0, 0},
                              {0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
                              {1, 0, 1, 1, 1, 0, 1, 0, 0, 0},
                              {0, 1, 0, 1, 0, 0, 1, 0, 0, 0},
                              {0, 0, 1, 0, 1, 0, 1, 0, 0, 0},
                              {0, 1, 1, 0, 1, 0, 1, 0, 0, 0}};

  int mat_cond_2[N][N] =    { {3, 3, 0, 0, 0, 0, 0, 0, 0, 0},
                              {3, 3, 0, 0, 0, 0, 0, 0, 0, 0},
                              {2, 3, 1, 0, 0, 0, 0, 0, 0, 0},
                              {2, 3, 1, 0, 0, 0, 0, 0, 0, 0},
                              {2, 3, 2, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {10, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {7, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {2, 2, 1, 2, 0, 0, 0, 0, 0, 0},
                              {10, 0, 0, 0, 0, 0, 0, 0, 0, 0}};


  printf("Avant remplissage :\n");
  affiche_matrice(grille_test_c2);
  printf("\n\n");
  cas_mediane_c(mat_cond_2, grille_test_c2);
  printf("Après remplissage :\n");
  affiche_matrice(grille_test_c2);
}
