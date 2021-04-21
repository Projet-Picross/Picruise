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

int extremite_ligne(int matrice[N][N], int mat_condi_ligne[N][N]){	// fonction qui remplie les lignes et colonnes dont une des extremites est une case noires
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
	return 1;
}

int extremite_colonne(int matrice[N][N], int mat_condi_colonne[N][N]){	// fonction qui remplie les lignes et colonnes dont une des extremites est une case noires
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
		if(matrice[N-1][j] >= 1  && mat_condi_colonne[j][0] > 1){					// cas où on possède une case noire en fin de ligne
			i = N-1;
			while(k < mat_condi_colonne[j][0]){
				matrice[i][j] = 1;
				k++;
				i--;
			}
		}
		k = 0;
	}
	return 1;
}

int cas_basique_l(int mat_condition_l[N][N], int grille[N][N]){
    int i, j;
    for(i = 0; i < N; i++){
		//si une ligne n'a que des cases noires
		if(mat_condition_l[i][0] && !mat_condition_l[i][1] && mat_condition_l[i][0] == N){
        	for(j = 0; j < N; j++){
         		grille[i][j]=1;
        	}
    	}
    }
    return 1;
}

//remplir la grille si les lignes/colonnes sont vides/pleines
int cas_basique_c(int mat_condition_c[N][N], int grille[N][N]){
    int i, j;
    for(i=0;i<N;i++){
		//si une ligne n'a que des cases noires
		if(mat_condition_c[i][0] && !mat_condition_c[i][1] && mat_condition_c[i][0] == N){
        	for(j=0;j<N;j++){
          		grille[j][i]=1;
        	}
        }
    }
    return 1;
}

int cas_mediane_l(int mat_condition_l[N][N], int grille[N][N]){
    int i,j,k,l;
	int nb_noires;
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
    return 1;
}

int cas_mediane_c(int mat_condition_c[N][N], int grille[N][N]){
    int i,j,k,l;
	int nb_noires;
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
    return 1;
}

int cas_uniques_ligne(int matrice[N][N], int mat_condi_ligne[N][N]){ // fonction qui rempli la grille en fonction des cas simples hormis les lignes/ colonnes pleines ou vides qui seront résolus par d'autres fonctions
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
  return 1;
}

int cas_uniques_colonne(int matrice[N][N], int mat_condi_colonne[N][N]){ // fonction qui rempli la grille en fonction des cas simples hormis les lignes/ colonnes pleines ou vides qui seront résolus par d'autres fonctions
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
        for(i = 0; i < N; i++){
          if(i % 2 == 1){
            matrice[i][j] = 1;
          }else{
            matrice[i][j] = 0;
          }
        }
      }
    }
  }
  return 1;
}

//Si il n'y a qu'une seule condition et deux cases noircies non voisines l'une de l'autre, remplir les cases intermédiaires. Pour les lignes.
int remp_intermediaires_l(int mat_cond[N][N], int grille[N][N]){
  int i, j, k;
  //Il n'y a qu'une seule condition
  for(i = 0; i < N; i++){
    if(mat_cond[i][0] && !mat_cond[i][1]){
      //On parcours la ligne jusqu'à la première case noire
      for(j = N - 1; j >= 0 && !grille[i][j]; j--);
      //Si la case à la limite de la condition est noire et la case suivante est blanche, on noirçit les cases intermédiaires
      if((j-mat_cond[i][0]+1) >= 0 && grille[i][j-mat_cond[i][0]+1])
        for(k = j; k >= (j-mat_cond[i][0]+1); k--)
          grille[i][k] = 1;
    }
  }
  return 1;
}

//Si il n'y a qu'une seule condition et deux cases noircies non voisines l'une de l'autre, remplir les cases intermédiaires. Pour les colonnes.
int remp_intermediaires_c(int mat_cond[N][N], int grille[N][N]){
  int i, j, k;
  //Il n'y a qu'une seule condition
  for(i = 0; i < N; i++){
    if(mat_cond[i][0] && !mat_cond[i][1]){
      //On parcours la ligne jusqu'à la première case noire
      for(j = N-1; j >= 0 && !grille[j][i]; j--);
      //Si la case à la limite de la condition est noire et la case suivante est blanche, on noirçit les cases intermédiaires
      if((j-mat_cond[i][0]+1) < N && grille[j-mat_cond[i][0]+1][i])
        for(k = j; k >= (j-mat_cond[i][0]+1); k--)
          grille[k][i] = 1;
    }
  }
  return 1;
}

//Faire la même chose en cas d'une condition non validée restante. Pour les lignes
int remp_derniere_cond_l(int mat_cond[N][N], int grille[N][N]){
  int i, j, k;
  int cpt_cond_f; //Compteur de conditions fausses
  int nb_noires; //Compteur de cases noires
  int i_cond_f; //Indice de la condition fausse
  int i_deb_f; //Indice de début du bloc faux
  for(i = 0; i < N; i++){
    for(j = N-1, k = 0, cpt_cond_f = 0, nb_noires = 0; j >= 0 && k < N && mat_cond[i][k] && cpt_cond_f <= 1; j--){
      if(grille[i][j] == 1)
        nb_noires++;
      //Cas ou le premier bloc est blanc
      else if(nb_noires){
        if(nb_noires != mat_cond[i][k]){
          i_cond_f = k;
          cpt_cond_f++;
          i_deb_f = (j+nb_noires);
          j -= (mat_cond[i][k] - nb_noires - 1);
        }
        k++;
        nb_noires = 0;
      }
    }
      //Cas d'un bloc à l'extrémité
      if(grille[i][0] == 1)
        if(nb_noires != mat_cond[i][k]){
          i_cond_f = k;
          cpt_cond_f++;
          i_deb_f = (j+nb_noires);
        }
      //Si il reste une condition invalide et qu'il y a deux cases noires correspondantes aux extrémités de la condition, on remplit
      if(cpt_cond_f == 1)
        if(((i_deb_f - mat_cond[i][i_cond_f]+1) >= 0) && (grille[i][i_deb_f - mat_cond[i][i_cond_f]+1]))
          for(j = i_deb_f; j >= (i_deb_f - (mat_cond[i][i_cond_f]-1)); j--)
            grille[i][j] = 1;
  }
  return 1;
}


//Faire la même chose en cas d'une condition non validée restante. Pour les colonnes
int remp_derniere_cond_c(int mat_cond[N][N], int grille[N][N]){
  int i, j, k;
  int cpt_cond_f; //Compteur de conditions fausses
  int nb_noires; //Compteur de cases noires
  int i_cond_f; //Indice de la condition fausse
  int i_deb_f; //Indice de début du bloc faux
  for(i = 0; i < N; i++){
    for(j = N-1, k = 0, cpt_cond_f = 0, nb_noires = 0; j >= 0 && k < N && mat_cond[i][k] && cpt_cond_f <= 1; j--){
      if(grille[j][i] == 1)
        nb_noires++;
      //Cas ou le premier bloc est blanc
      else if(nb_noires){
        if(nb_noires != mat_cond[i][k]){
          i_cond_f = k;
          cpt_cond_f++;
          i_deb_f = (j+nb_noires);
          j -= (mat_cond[i][k] - nb_noires - 1);
        }
        k++;
        nb_noires = 0;
      }
    }
      //Cas d'un bloc à l'extrémité
      if(grille[0][i] == 1)
        if(nb_noires != mat_cond[i][k])
          cpt_cond_f++;
      //Si il reste une condition invalide et qu'il y a deux cases noires correspondantes aux extrémités de la condition, on remplit
      if(cpt_cond_f == 1)
        if(((i_deb_f - mat_cond[i][i_cond_f]+1) >= 0) && (grille[i_deb_f - mat_cond[i][i_cond_f]+1][i]))
          for(j = i_deb_f; j >= (i_deb_f - (mat_cond[i][i_cond_f]-1)); j--)
            grille[j][i] = 1;
  }
  return 1;
}

//Si la case est noire, que les deux cases précédentes existent et sont respectivement blanche et noire et que la condition précedante est rempli, alors les cases suivantes sont forcément noires.
int remp_blanc_noire_l(int mat_cond[N][N], int grille[N][N]){
  int i, j, k;
  int cond_pred_remp; //Vaut 1 si la condition précédente est remplie, 0 sinon
  int nb_noires; //Compteur de cases noires
  int j_deb; //Indice de début de bloc
	for(i = 0; i < N; i++){
  	for(j = N-1, k = 0, cond_pred_remp = 0, nb_noires = 0; j >= 0 && k < N && mat_cond[i][k]; j--){
    	if(grille[i][j] == 1)
      	nb_noires++;
    	//Cas ou le premier bloc est blanc
    	else if(nb_noires){
      	if(nb_noires != mat_cond[i][k]){
        	//Cas décrit plus haut
        	if(cond_pred_remp){
          	j_deb = (j+nb_noires);
          	if(grille[i][j_deb] && !grille[i][j_deb+1] && grille[i][j_deb+2]){
            	for(; j_deb >= (j - (mat_cond[i][k] - nb_noires - 1)); j_deb--)
              	grille[i][j_deb] = 1;
            	j -= (mat_cond[i][k] - nb_noires - 1);
          	}
					}
        	cond_pred_remp = 0;
      	}
      	else
        	cond_pred_remp = 1;
      	k++;
      	nb_noires = 0;
  		}
 		}
	}
	return 1;
}

//Si la case est noire, que les deux cases précédentes existent et sont respectivement blanche et noire et que la condition précedante est rempli, alors les cases suivantes sont forcément noires.
int remp_blanc_noire_c(int mat_cond[N][N], int grille[N][N]){
  int i, j, k;
  int cond_pred_remp; //Vaut 1 si la condition précédente est remplie, 0 sinon
  int nb_noires; //Compteur de cases noires
  int j_deb; //Indice de début de bloc
	for(i = 0; i < N; i++){
  	for(j = N-1, k = 0, cond_pred_remp = 0, nb_noires = 0; j >= 0 && k < N && mat_cond[i][k]; j--){
    	if(grille[j][i] == 1)
      	nb_noires++;
    	//Cas ou le premier bloc est blanc
    	else if(nb_noires){
      	if(nb_noires != mat_cond[i][k]){
        	//Cas décrit plus haut
        	if(cond_pred_remp){
          	j_deb = (j+nb_noires);
          	if(grille[j_deb][i] && !grille[j_deb+1][i] && grille[j_deb+2][i]){
            	for(; j_deb >= (j - (mat_cond[i][k] - nb_noires - 1)); j_deb--)
              	grille[j_deb][i] = 1;
            	j -= (mat_cond[i][k] - nb_noires - 1);
          	}
					}
        	cond_pred_remp = 0;
      	}
      	else
        	cond_pred_remp = 1;
      	k++;
      	nb_noires = 0;
  		}
 		}
	}
  return 1;
}

void remp_ext_l(int grille[N][N], int mat_cond[N][N]){
	int i, j, k, l;
	for(i = 0; i < N; i++){
		//Si il n'y a qu'une seule condition
			if(mat_cond[i][0] && !mat_cond[i][1]){
				//Et que la première case est noircie
				if(grille[i][0]){
					for(j = 1; j < (mat_cond[i][0]-1); j++)
						grille[i][j] = 1;
				}
				else if (grille[i][N-1]){
					for(j = N-2; j > (N-2-(mat_cond[i][0]-1)); j--)
						grille[i][j] = 1;
				}
			}
	}
}

void remp_ext_c(int grille[N][N], int mat_cond[N][N]){
	int i, j, k, l;
	for(i = 0; i < N; i++){
		//Si il n'y a qu'une seule condition
			if(mat_cond[i][0] && !mat_cond[i][1]){
				//Et que la première case est noircie
				if(grille[0][i]){
					for(j = 1; j < (mat_cond[i][0]-1); j++)
						grille[j][i] = 1;
				}
				else if (grille[i][N-1]){
					for(j = N-2; j > (N-2-(mat_cond[i][0]-1)); j--)
						grille[j][i] = 1;
				}
			}
	}
}
