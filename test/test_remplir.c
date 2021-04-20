#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int int_to_char(int nb)
{
  if(nb==0)
    return 48;
  else if(nb==1)
    return 49;
}



int main()
{
  int N;
  int alea;
  int i,j;
  srand(time(NULL));
  int case_noire=0;


  printf("Veuillez inserer la taille du tableau: ");
  scanf("%i",&N);
  N = N+5;
  char tableau[N][N];

  for(i = 0; i < N; i++)
    for (j = 0; j < N; j++) {
      tableau[i][j] = '-';
    }

    for(i = 0; i < N; i++)
      for (j = 0; j < N; j++) {
        if (i==3 && j>=3) {
           tableau[i][j] = '#';
        }
        if (i>=3 && j==3) {
           tableau[i][j] = '#';
        }
        if (i>=3 && j==N-1) {
           tableau[i][j] = '#';
        }
        if (i==N-1 && j>=3) {
           tableau[i][j] = '#';
        }

      }

      for(i=4;i<N;i++)
        for(j=4;j<N;j++){
          alea = (rand() % (1 + 1 - 0)) + 0;
          if (alea==1) {
            tableau[i][j]=int_to_char(1);
            case_noire++;
          }
          else if (alea==0) {
            tableau[i][j]=int_to_char(0);
          }
        }


    for(i = 0; i < N; i++){

      for (j = 0; j < N; j++) {

        printf(" %c ",tableau[i][j]);

      }
      printf("\n");

    }

  return 0;
}
