#include "include/jeu.h"
#include "include/stats.h"
#include "jeu.c"
#include <stdio.h>
#include <string.h>
#include<time.h>


int main(int argc, char** argv) {
	int choixUtilisateur;
	int taille_plateau;
    int **plateau, **prop;
    int nb_touche_nav[5] = {0};
    int nb_touche = 0, nb_joue = 0;
    
    printf("================================================\n");
    printf("Bienvenue dans le jeu de bataille navale !\n");
    printf("================================================\n");

    do {
    	
        printf("Choisissez une option :\n\n");

        printf("1. Nouvelle partie\n");
        printf("2. Quitter\n\n");
        int valide = 0;
		do {
   			printf("Votre choix : ");
    		if (scanf("%d", &choixUtilisateur) == 1) {
        		valide = 1;
        		while (getchar() != '\n');
    		} else {
       			printf("Entrée invalide. Veuillez entrer un nombre.\n");
        		while (getchar() != '\n'); 
    		}
		} while (!valide);

        switch (choixUtilisateur) {
            case 1:
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
    			printf("================================================\n");
    			printf("Félicitations! Vous avez coulé tous les navires en %d coups.\n", nb_joue);
    			printf("================================================\n");

   				 // Libération de la mémoire
    			for (int i = 0; i < taille_plateau; i++) {
        			free(plateau[i]);
        			free(prop[i]);
   				}
    			free(plateau);
    			free(prop);
    			break;
    		case 2:
                printf("Merci d'avoir joué. À bientôt!\n");
                break;
            default:
                printf("Choix non valide. Veuillez réessayer.\n");
        }
    } while (choixUtilisateur != 2);

    return 0;

	

}