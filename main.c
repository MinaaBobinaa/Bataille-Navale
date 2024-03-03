#include "include/jeu.h"
#include "include/stats.h"
#include "jeu.c"
#include <stdio.h>
#include <string.h>
#include<time.h>


int main(int argc, char** argv) {
	int taille_plateau;
    int **plateau;
    int **prop; // Pour suivre les propositions des joueurs
    int nb_touche = 0, nb_joue = 0;
    int nb_touche_nav[5] = {0}; // Adapté selon le nombre de navires
    init_nb_aleatoire();


	taille_plateau = demanderTaillePlateau();

	printf("Taille du plateau choisie : %d\n", taille_plateau);

	plateau = (int**)malloc(taille_plateau * sizeof(int*));
    prop = (int**)malloc(taille_plateau * sizeof(int*));
    for (int i = 0; i < taille_plateau; i++) {
        plateau[i] = (int*)calloc(taille_plateau, sizeof(int));
        prop[i] = (int*)calloc(taille_plateau, sizeof(int));
    }

    initialisation_plateau(plateau, taille_plateau);
    affichage_plateau(plateau, taille_plateau);

    printf("================================================\n");
    
    while (nb_touche < 17) {
        
        affichage_choix_joueur(plateau, prop, taille_plateau);
        proposition_joueur(plateau, prop, &nb_touche, &nb_joue, nb_touche_nav, taille_plateau);
    }

    affichage_choix_joueur(plateau, prop, taille_plateau);

    printf("Félicitations! Vous avez coulé tous les navires en %d coups.\n", nb_joue);

    // Libération de la mémoire
    for (int i = 0; i < taille_plateau; i++) {
        free(plateau[i]);
        free(prop[i]);
    }
    free(plateau);
    free(prop);

    return 0;

	

}