#include "include/jeu.h"
#include "include/stats.h"
#include "jeu.c"
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
	Grille grille;
	int taillePlateau;

	taillePlateau = demanderTaillePlateau();

	printf("Taille du plateau choisie : %d\n", taillePlateau);

	initialiserGrille(&grille, taillePlateau);
	afficherGrille(&grille);
	libererGrille(&grille);que

	return 0;

}