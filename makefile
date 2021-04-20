CFLAGS=-Wall -lSDL2main -lSDL2 -lSDL2_ttf

all: main

main: main.o verif.o solveur.o predefinies.o options.o jeu.o generation.o choix_type_grille.o choix_jeux.o choix_format.o affichage.o accueil.o
	gcc  main.o verif.o solveur.o predefinies.o options.o jeu.o generation.o choix_type_grille.o choix_jeux.o choix_format.o affichage.o accueil.o -o bin/Picruise -I include -L lib $(CFLAGS)


main.o: src/main.c src/commun.h
	gcc -c src/main.c -I include -L lib $(CFLAGS)

verif.o : src/verif.c src/verif.h
	gcc -c src/verif.c  -I include -L lib $(CFLAGS)

solveur.o : src/solveur.c src/solveur.h
	gcc -c src/solveur.c  -I include -L lib $(CFLAGS)

predefinies.o : src/predefinies.c src/predefinies.h
	gcc -c src/predefinies.c  -I include -L lib $(CFLAGS)

options.o : src/options.c src/options.h
	gcc -c src/options.c  -I include -L lib $(CFLAGS)

jeu.o : src/jeu.c src/jeu.h
	gcc -c src/jeu.c  -I include -L lib $(CFLAGS)

generation.o: src/generation.c src/generation.h
	gcc -c src/generation.c -I include -L lib $(CFLAGS)

choix_type_grille.o : src/choix_type_grille.c src/choix_type_grille.h
	gcc -c src/choix_type_grille.c  -I include -L lib $(CFLAGS)

choix_jeux.o : src/choix_jeux.c src/choix_jeux.h
	gcc -c src/choix_jeux.c  -I include -L lib $(CFLAGS)

choix_format.o: src/choix_format.c src/choix_format.h
	gcc -c src/choix_format.c -I include -L lib $(CFLAGS)

affichage.o: src/affichage.c src/affichage.h
	gcc -c src/affichage.c -I include -L lib $(CFLAGS)

accueil.o: src/accueil.c src/accueil.h
	gcc -c src/accueil.c -I include -L lib $(CFLAGS)


clean:
	del *.o

cleanall: clean
	del .\bin\*.exe
