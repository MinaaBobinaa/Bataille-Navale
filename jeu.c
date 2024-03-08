#include "include/jeu.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


char **allouer_plateau(int taille) {
    char **plateau = (char **)malloc(taille * sizeof(char *));
    for (int i = 0; i < taille; i++) {
        plateau[i] = (char *)malloc(taille * sizeof(char));
        for (int j = 0; j < taille; j++) {
            plateau[i][j] = '.';
        }
    }
    return plateau;
}

void free_plateau(char **plateau, int taille) {
    for (int i = 0; i < taille; i++) {
        free(plateau[i]);
    }
    free(plateau);
}




