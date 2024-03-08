#include "include/jeu.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void commencer_jeu() {
    printf("================================================\n");
    printf("Bienvenue dans le jeu de bataille navale !\n");
    printf("================================================\n");
}

void terminer_jeu(int tirs) {
    printf("================================================\n");
    printf("Bravo !! Vous avez gagné en %d coups.\n", tirs);
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

int valider_taille_plateau(void){
    int taille;
    do {
        printf("Entrez la taille du plateau de jeu (min %d, max %d): ", TAILLE_MIN_PLATEAU, TAILLE_MAX_PLATEAU);
        scanf("%d", &taille);
        if (taille < TAILLE_MIN_PLATEAU || taille > TAILLE_MAX_PLATEAU) {
            printf("Taille invalide. La taille doit être entre %d et %d.\n", TAILLE_MIN_PLATEAU, TAILLE_MAX_PLATEAU);
        }
    } while (taille < TAILLE_MIN_PLATEAU || taille > TAILLE_MAX_PLATEAU);
    return taille;
}

void initialiser_jeu(int taille, char ***plateau, char ***action_plateau, Navire navires[]){
    *plateau = allouer_plateau(taille);
    *action_plateau = allouer_plateau(taille);
    for (int i = 0; i < 5; i++) {
        placer_navire(*plateau, &navires[i], taille);
    }
}

int get_coordonnee_tir(int *x, int *y, int taille){
    printf("Entrez les coordonnées de tir (x y): ");
    scanf("%d %d", x, y);
    if (*x < 0 || *y < 0 || *x >= taille || *y >= taille) {
        printf("Coordonnées hors du plateau.\n");
        return 0;
    }
    return 1;
}

void proceder_tir(char **plateau, char **action_plateau, Navire navires[], int x, int y, int *tirs, int *navire_coule){
    (*tirs)++;
    if (plateau[x][y] == 'S') {
        action_plateau[x][y] = 'x';
        for (int i = 0; i < 5; i++) {
            touche_navire(&navires[i], x, y, navire_coule);
        }
    } else {
        action_plateau[x][y] = 'o';
        printf("À l'eau!\n");
    }
}

void jouer_jeu(char **plateau, char **action_plateau, Navire navires[], int taille){
    int x, y, tirs = 0, navire_coule = 0;
    while (navire_coule < 5) {
        if (!get_coordonnee_tir(&x, &y, taille)) continue;
        if (action_plateau[x][y] != '.') {
            printf("Déjà joué.\n");
            continue;
        }
        proceder_tir(plateau, action_plateau, navires, x, y, &tirs, &navire_coule);
        affichage_plateau(action_plateau, taille);
    }
    terminer_jeu(tirs);
}
void debut_jeu(void){
    srand(time(NULL));
    int taille = valider_taille_plateau();
    char **plateau = allouer_plateau(taille);
    char **action_plateau = allouer_plateau(taille);

    Navire navires[5] = {
        {{0}, 5, "Porte-avions", 0},
        {{0}, 4, "Croiseur", 0},
        {{0}, 3, "Contre-torpilleur 1", 0},
        {{0}, 3, "Contre-torpilleur 2", 0},
        {{0}, 2, "Torpilleur", 0}
    };

    initialiser_jeu(taille, &plateau, &action_plateau, navires);
    jouer_jeu(plateau, action_plateau, navires, taille);
    free_plateau(plateau, taille);
    free_plateau(action_plateau, taille);
}
