#include "include/jeu.h"
#include <stdio.h>
#include <stdlib.h>


// Vérifie si l'entrée est un nombre
int verifierEntreeNombre(int resultat) {
    if (resultat != 1) {
        fprintf(stderr, "Erreur: La valeur entrée n'est pas un nombre.\n");
        exit(1); 
    }
    return 1; 
}

// Vérifie si la taille est dans la plage autorisée
int verifierPlageTaille(int taille) {
    if (taille < TAILLE_MIN_PLATEAU || taille > TAILLE_MAX_PLATEAU) {
        fprintf(stderr, "Erreur: La taille du plateau (%d) est hors des limites autorisées (%d à %d).\n", taille, TAILLE_MIN_PLATEAU, TAILLE_MAX_PLATEAU);
        exit(1);
    }
    return 1; 
}

// Demande à l'utilisateur d'entrer la taille du plateau et vérifie cette entrée
int demanderTaillePlateau() {
    int taille, resultat;
    printf("Entrez la taille du plateau (%d à %d) : ", TAILLE_MIN_PLATEAU, TAILLE_MAX_PLATEAU);
    resultat = scanf("%d", &taille);

    verifierEntreeNombre(resultat);
    verifierPlageTaille(taille);
    

    return taille;
}

void initialiserGrille(Grille* grille, int taillePlateau) {
    grille->taille = taillePlateau;
    grille->cases = malloc(taillePlateau * sizeof(char*));
    for (int i = 0; i < taillePlateau; i++) {
        grille->cases[i] = malloc(taillePlateau * sizeof(char));
        for (int j = 0; j < taillePlateau; j++) {
            grille->cases[i][j] = '.';
        }
    }
}

void afficherGrille(Grille* grille) {
    for (int i = 0; i < grille->taille; i++) {
        for (int j = 0; j < grille->taille; j++) {
            printf(" %c ", grille->cases[i][j]);
        }
        printf("\n");
    }
}

void libererGrille(Grille* grille) {
    for (int i = 0; i < grille->taille; i++) {
        free(grille->cases[i]);
    }
    free(grille->cases);
}
