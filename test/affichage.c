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
    for(j = N-1, k = 0, somme = 0; j >= 0; j--){
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
    for(j = N-1, k = 0, somme = 0; j >= 0; j--){
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







//Calcul du nombre maximum de conditions de la matrice
int nb_max_cond(int mat_cond[N][N]){
  int i, j;
  int nb_max_cond, cpt;
  for(i = 0, nb_max_cond = 0; i < N; i++){
    for(j = 0, cpt = 0; j < N && mat_cond[i][j]; j++)
      cpt++;
    if(nb_max_cond < cpt)
      nb_max_cond = cpt;
  }
  return nb_max_cond;
}

//Inversion d'une matrice
void inversion(int inverse[N], int mat[N][N], int ligne){
  int j, k;
  for(j = N-1, k = 0; j >= 0; j--){
    if(mat[ligne][j])
      inverse[k++] = mat[ligne][j];
  }
}

//Initialisation d'un tableau
void init_tab(int tab[N]){
  int i;
  for(i = 0; i < N; i++)
    tab[i] = 0;
}

void affichage_jeu(int mat_condi_colonnes[N][N], int mat_condi_lignes[N][N], int grille[N][N]){
  int i, j, k, l;

  //Calcul du nombre maximum de conditions pour les lignes et les colonnes
  int nb_max_cond_lignes = nb_max_cond(mat_condi_lignes);
  printf("Nb max cond lignes : %i\n", nb_max_cond_lignes);
  int nb_max_cond_colonnes = nb_max_cond(mat_condi_colonnes);
  printf("Nb max cond colonnes : %i\n", nb_max_cond_colonnes);

  //Tableaux à partir desquels on affichera une ligne condition/grille
  int tab_ligne[N+nb_max_cond_lignes];
  init_tab(tab_ligne);

  //Affichage de la matrice des conditions des colonnes
  for(j = nb_max_cond_colonnes; j >= 0; j--){
    //Allignement des affichages
    for(k = 0; k <= nb_max_cond_lignes; k++)
      printf("  ");
    for(i = 0; i < N; i++){
      if(mat_condi_colonnes[i][j])
        printf("%i ", mat_condi_colonnes[i][j]);
      else
        printf("  ");
    }
    printf("\n");
  }
  printf("\n");

  //Affichage côte à côte des conditions de ligne et de la grille
  for(i = 0; i < N; i++){
    //Affectation du tableau représentant la ligne
    for(j = nb_max_cond_lignes, k = 0; j >= 0; j--, k++)
      tab_ligne[k] = mat_condi_lignes[i][j];
    for(j = 0; j < N; j++, k++)
      tab_ligne[k] = grille[i][j];
    //Affichage des lignes avec leurs conditions
    for(l = 0; l <= (N+nb_max_cond_lignes); l++)
      if(l < nb_max_cond_lignes+1){
        if(tab_ligne[l])
          printf("%i ", tab_ligne[l]);
        else
          printf("  ");
      }
      else{
        if(tab_ligne[l])
          printf("x ");
        else
          printf("  ");
      }
    printf("\n");
  }
}

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

  int tab_inverse[N];
  init_tab(tab_inverse);
  inversion(tab_inverse, mat_condi_colonnes, 3);
  int i;
  printf("\n");
  for(i = 0; i < N; i++)
    printf("%i ", tab_inverse[i]);

  //Vérification des conditions
  printf("\nValidation des conditions des lignes : %i\n", verif_somme_cond(mat_condi_lignes));
  printf("Validation des conditions des colonnes : %i\n", verif_somme_cond(mat_condi_colonnes));

  printf("Affichage pour le jeu :\n");
  affichage_jeu(mat_condi_colonnes, mat_condi_lignes, grille);
}
