#include "include/jeu.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void commencer_jeu() {
    printf("================================================\n");
    printf("Bienvenue dans le jeu de bataille navale !\n");
    printf("================================================\n");
}

void terminer_jeu(int shots) {
    printf("================================================\n");
    printf("Bravo !! Vous avez gagné en %d coups.\n", shots);
    printf("================================================\n");
}


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

int verifier_placement(char **plateau, Case debut, int taille, int direction, int taille_plateau){
    for (int i = 0; i < taille; i++) {
        int x = debut.x + (direction < 2 ? i : 0);
        int y = debut.y + (direction == 2 ? i : (direction == 3 ? -i : 0));
        if (x < 0 || y < 0 || x >= taille_plateau || y >= taille_plateau || plateau[x][y] != '.') return 0;
    }
    return 1;
}

void placer_navire(char **plateau, Navire *navire, int taille_plateau){
    int place = 0;
    while (!place) {
        Case debut = { rand() % taille_plateau, rand() % taille_plateau };
        int direction = rand() % 4; // 0: droite, 1: bas, 2: gauche, 3: haut
        if (verifier_placement(plateau, debut, navire->taille, direction, taille_plateau)) {
            for (int i = 0; i < navire->taille; i++) {
                int x = debut.x + (direction < 2 ? i : 0);
                int y = debut.y + (direction == 2 ? i : (direction == 3 ? -i : 0));
                plateau[x][y] = 'S'; // 'S' pour navire
                navire->positions[i].x = x;
                navire->positions[i].y = y;
            }
            place = 1;
        }
    }
}

void affichage_plateau(char **plateau, int taille){
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            printf("%c ", plateau[i][j]);
        }
        printf("\n");
    }
}

void touche_navire(Navire *navire, int x, int y, int *navire_coule){
    for (int i = 0; i < navire->taille; i++) {
        if (navire->positions[i].x == x && navire->positions[i].y == y) {
            navire->touche++;
            if (navire->touche == navire->taille) {
                (*navire_coule)++;
                printf("Vous avez coulé un(e) %s!\n", navire->nom);
            } else {
                printf("Touché!\n");
            }
            return;
        }
    }
}



