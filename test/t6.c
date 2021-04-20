#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#include<time.h>

#define N 30

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

void init_matrice(int matrice[N][N]){			//initialise la matrice avec des 0
	int i,j;
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			matrice[i][j] = 0;
		}
		printf("\n");
	}
}

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

//Génération aléatoire de la grille
int genera_aleatoire(int grille[N][N]){
  srand(time(NULL));
  //Compteur de cases noires;
  int cpt = (int)(0.25*N*N) + rand()%(int)((0.75*N*N)-(0.25*N*N));
  int i, j, k;
  for(k = 0; k < cpt; k++){
      //Tirage aléatoire des coordonnées d'une case vide
      do{
        i = rand()%N;
        j = rand()%N;
      }while(grille[i][j]);
      grille[i][j] = 1;
  }
  return cpt;
}

void somme_cond_l(int mat_cond[N][N], int somme_cond[N]){
  int i, j;
  for(i = 0; i < N; i++){
    //Calcul de la somme des conditions
    for(j = 0; j < N && mat_cond[i][j]; j++){
      somme_cond[i] += mat_cond[i][j];
    }
  }
}

void remplissage_inter(int mat[N][N], int mat2[N][N]){    // on complete la matrice condition avec des 0 (pour faire des comparaison) dans une matrice intermédiaire
  int i,j;
  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){
      if(mat[i][j] < 0 || mat[i][j] > N){
        mat2[i][j] = 0;
      }else{
        mat2[i][j] = mat[i][j];
      }
    }
  }
}

int nombre_bloc(int condi_ligne[N][N],int ligne){
  int j;
  int nb_bloc_grille = 0;
  int inter_ligne[N][N];
  remplissage_inter(condi_ligne,inter_ligne);

  for(j = 0; j < N; j++){
    if(inter_ligne[ligne][j] >= 1){
      nb_bloc_grille++;
    }
  }
  return nb_bloc_grille;
}

int main(){
  //Matrices de test
  /*int grille_test_l1[N][N] = {{1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
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
                              {10, 0, 0, 0, 0, 0, 0, 0, 0, 0}};*/

  int mat_cond_1[N][N] =    { {4, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {2, 2, 0, 0, 0, 0, 0, 0, 0, 0},
                              {1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
                              {2, 1, 1, 0, 0, 0, 0, 0, 0, 0},
                              {4, 2, 0, 0, 0, 0, 0, 0, 0, 0},
                              {1, 2, 1, 0, 0, 0, 0, 0, 0, 0},
                              {1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
                              {2, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                              {1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
                              {7, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

  int grille[N][N];
  init_matrice(grille);
  genera_aleatoire(grille);
  int mat_cond_l[N][N];
  init_matrice(mat_cond_l);
  generat_condi_lignes(grille, mat_cond_l);
  affiche_matrice(grille);
  printf("\n");


  int s[N];             // tableau qui contiendra les sommes des cases noires de chaque ligne
  int i, b, z, k;         // plusieurs indices
  int somme_b;            // nombre de cases blanches à avoir sur une ligne
  int compt_b = 0;          // compteur de case blanches sur une ligne
  int faux = 0;           // vaut 1 si la combinaison n'est pas possible

  for(i = 0; i < N; i++){
    s[i] = 0;
  }
  somme_cond_l(mat_cond_l,s);   // ce tableau comporte les sommes des cases noires de chaque ligne

  for(i = 0; i < N; i++){     // a chaque ligne de la matrice,

    b = nombre_bloc(mat_cond_l,i);  // on met a jour le nombre de bloc noir sur la ligne
    somme_b = N - s[i];       // on déduit le nombre de cases blanches à trouver
    int combi[b+1];         // on créer un tableau ayant comme taille le nombre de blocs noirs + 1 (contiendra uniquement les cases blanches)
    int c[b*2 +1];          // on créer un tableau ayant comme taille le nombre de blocs noirs et blanc + 1 (contiendra cases blanches et noires)
    for(z = 0; z < b + 1; z++){   // on met à 0 le tableau qui testera les combinaisons possibles
      combi[z] = 0;
    }
      while(combi[0] <= (N - s[i] - b + 1)){
        for(z = 0; z < b + 1; z++){
          compt_b = compt_b + combi[z];
          if(z != 0 && z != b){
            if(combi[z] == 0){        // chaque case situées entre deux cases noires vaut au moins 1
              faux = 1;         // donc si ce n'est pas le cas on sort des if et de la boucle for
              compt_b = N+1;
              z = b+2;
            }
          }
        }

        k = 0;
        if(faux != 1 && (compt_b == somme_b)){  // si la combinaison est possible, on l'affiche
          for(z = 0; z < b*2 + 1; z++){   // on remplie le tableau c avec le tableau des cases blanches et des conditions (un après l'autres)
            if(z % 2 == 0){
              c[z] = combi[k];
            }else{
              c[z] = mat_cond_l[i][k];
              k++;
            }
            printf("| %d ",c[z]);
          }
          printf("| \n");
        }
        faux = 0;
        compt_b = 0;
        for(z = b; z > 0; z--){       // incrémentation du tableaux des combinaisons en partant de la fin
          if(combi[b] >= (N - s[i] - b + 1)){ // si la dernière case du tableaux est au max, on met à 0 et on incrémente la case d'avant
            combi[b] = 0;
            z--;
            combi[z]++;
            while(combi[z] >= (N - s[i] - (b - 2)) && z != 0){  // si la case actuelle du tableaux est au max, on met à 0 et on incrémente la case d'avant
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
