#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

FILE * fichier;
FILE * fichier2;

//Le fichier contenant les matrices prédéfinies est de la forme :  #  nom_matrice - taille_matrice -     puis suite de coordonnées des points

void init_matrice_predef(int n, int matrice[n][n]){					//initialise la matrice avec des 0
	int i,j;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			matrice[i][j] = 0;
		}
		printf("\n");
	}
}

void affiche_matrice_predef(int n, int matrice[n][n]){		 			//affiche une matrice en convertissant les O en . et les 1 en X
	int i,j;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			if(matrice[i][j] == 1){
				printf("X ");									//cases remplies
			}else{
				printf(". ");									//cases vides
			}
		}
		printf("\n");
	}
}

void affecter_matrice_predef(int n, int matrice[n][n]){				//fonction qui lit un fichier et place des points dans la matrice
	int i,j;
	fichier = fopen("matrice_copie.txt","r");					
	while(!feof(fichier)){
		fscanf(fichier,"%d", &i);
		fscanf(fichier,"%d", &j);
		matrice[i][j] = 1;
	}
	fclose(fichier);
}

void transfert_mat(int marqueur){								//fonction qui récupère les points de la matrice prédéfinie choisit et les copies dans un autre
	int nb = 0;
	int find = 1;
	char lecture;
	fichier = fopen("mat_predef.txt","r");						//fichier de lecture
	fichier2 = fopen("matrice_copie.txt","w");					//fichier d'écriture
	fscanf(fichier,"%c",&lecture);
	while(nb != marqueur){
		if(lecture == '#'){										//on incremente nb jusqu'à atteindre le numéro de la matrice choisit
			nb++;
		}
		fscanf(fichier,"%c",&lecture);
	}
	while(!feof(fichier) && find == 1){				
		while(lecture != '-'){									//premier while pour "passer" la partie 'nom' de la matrice
			fscanf(fichier,"%c",&lecture);
		}
		while(lecture == '-' && find == 1){						//deuxième while pour "passer" la partie 'taille' de la matrice
			fscanf(fichier,"%c",&lecture);
			while(lecture != '-'){
				fscanf(fichier,"%c",&lecture);
				if(lecture == '-'){
					find = 0;
				}
			}
			fscanf(fichier,"%c",&lecture);
		}
		fscanf(fichier,"%c",&lecture);
		while(lecture != '#' && !feof(fichier)){									//troisième while pour la lecture des coordonnées jusqu'à la prochaine matrice
			fprintf(fichier2,"%c",lecture);
			fscanf(fichier,"%c",&lecture);
		}
	}
	fclose(fichier);
	fclose(fichier2);
}

int nb_matrice(){ 												//fonction qui compte le nombre de matrice prédéfinies
	int nb = 0;
	char lecture;
	fichier = fopen("mat_predef.txt","r");
	fscanf(fichier,"%c",&lecture);
	while(!feof(fichier)){
		if(lecture == '#'){										//chaque matrice commence par un # il suufit donc de les compter pour avoir le nombre de matrice
			nb++;
		}
		fscanf(fichier,"%c",&lecture);
	}
	fclose(fichier);
	return nb;
}

void liste_matrice(){												//fonction qui affiche le numéro et le nom de toute les matrices prédéfinies
	int nb = 0;
	char lecture;
	fichier = fopen("mat_predef.txt","r");
	printf("Vous avez le choix parmi les matrices suivantes : \n");
	fscanf(fichier,"%c",&lecture);
	while(!feof(fichier)){
		if(lecture == '#'){
			nb++;
			printf(" %i - ",nb);
			fscanf(fichier,"%c",&lecture);
			while(lecture != '-'){									//affichage de la partie nom de la matrice
				printf("%c",lecture);
				fscanf(fichier,"%c",&lecture);
			}
			printf("\n");
		}
		fscanf(fichier,"%c",&lecture);
	}
	fclose(fichier);
}

int taille_mat_choix(int choix){ 									// fonction qui retrouve la taille de la matrice choisit dans le fichier
	int nb = 0;
	int i = 0;
	char lecture;
	char taille[3];

	fichier = fopen("mat_predef.txt","r");
	fscanf(fichier,"%c",&lecture);
	while(nb !=  choix){
		if(lecture == '#'){
			nb++;
		}
		fscanf(fichier,"%c",&lecture);
	}
	while(!feof(fichier)){		
		if(lecture == '-'){
			fscanf(fichier,"%c",&lecture);							//comme la taille des matrices est entourée de - on lit ce qui l'y a entre les 2
			while(lecture != '-'){
				taille[i] = lecture;
				fscanf(fichier,"%c",&lecture);
				i++;
			}
			nb = atoi(taille);										// conversion de la taille qui est en format caractère en format entier
			fclose(fichier);
			return nb;
		}
		fscanf(fichier,"%c",&lecture);
	}
	fclose(fichier);
	return 1;
}


int choix_matrice(){				//fonction qui demande à l'utilisateur un numéro associé à une matrice prédéfinis
	int t;
	int choix;
	int max = nb_matrice();
	liste_matrice();
	printf("Entrez le numéro associez à la matrice de votre choix : ");
	scanf("%d", &choix);
	while(choix < 1 || choix > max){
		printf("Erreur dans la saisie du numéro de la matrice voulue, réessayer : ");
		scanf("%d", &choix);
	}
	t = taille_mat_choix(choix);
	transfert_mat(choix);
	return t;
}

int matrice_random(){				//fonction qui génère aléatoirement un numéro associé à une matrice prédéfinis
	int t;
	int max = nb_matrice();
	int n = rand() % max + 1;
	t = taille_mat_choix(n);
	transfert_mat(n);
	return t;
}


int main(){
	int nb;
	int choix;
	srand(time(NULL));
	printf("++ Matrices prédéfinies ++ \n");
	printf("Souhaitez-vous choisir une matrice ou bien laissez-vous le hasard le faire à votre place ? \n");		//on demande à l'utilisateur si il veut choisir la matrice ou la tirer au hasard
	printf("Tapez 0 pour tirer une matrice au hasard, 1 pour choisir \n");
	do{
		printf("Votre décision est : ");
		scanf("%d", &choix);
	}while(choix != 0 && choix != 1);
	if(choix == 1){
		nb = choix_matrice();						//appel de la fonction de choix de matrices prédéfinies
	}else{
		nb = matrice_random();						//appel de la fonction sélection aléatoire de matrices prédéfinies
	}
	int matrice[nb][nb];
	init_matrice(nb, matrice);
	affecter_matrice(nb, matrice);
	affiche_matrice(nb, matrice);
	return 1;
}









