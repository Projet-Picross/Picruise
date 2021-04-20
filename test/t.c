#include<stdio.h>
#include <math.h>

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

//Génère toutes les combinaisons possibles pour une ligne
int main(){
  int n = 20;
  int k = 1;
  int row, col;
  int cell;
  int rdiv;
  int nbr_comb = pow(k+1, n);

  int combinaisons[100000][n];
  int i, j;
	for(i = 0; i < 100000; i++)
		for(j = 0; j < n; j++)
			combinaisons[i][j] = 0;
	int somme;

  for (row=0, i = 0; row < nbr_comb; row++)
  {
      for (col=n-1; col>=0; col--)
      {
          rdiv = pow(k+1, col);
          cell = (row/rdiv) % (k+1);
          combinaisons[i][col] = cell;
      }
			for(j = 0, somme = 0; j < n; j++)
				if(combinaisons[i][j] == 1)
					somme++;
			if(somme == 6)
				i++;
  }

  for(i = 0; i < 100000; i++){
    for(j = 0; j < n; j++){
      printf(" %d", combinaisons[i][j]);
    }
    printf("\n");
  }
}
