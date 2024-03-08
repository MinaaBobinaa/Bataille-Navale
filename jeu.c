#include "include/jeu.h"
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

/* Initialiser le générateur au début du main par la fonction suivante*/
void init_nb_aleatoire() {
srandom(time(NULL));
}
/* Renvoie un nombre, tiré au hasard, compris entre 1 et max*/
int nb_aleatoire(int max) {
return (random()%max);
}

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


Navire creer_navire(int taille, int taille_plateau) {
    Navire navire;
    navire.taille = taille;
    navire.sens = nb_aleatoire(4);
switch(navire.sens) {
    case 0: // haut 
        navire.premiere_case.x = nb_aleatoire(taille_plateau-1);
        navire.premiere_case.y = nb_aleatoire(taille_plateau - taille); 
        break;
    case 1: // droite
        navire.premiere_case.x = nb_aleatoire(taille_plateau - taille);
        navire.premiere_case.y = nb_aleatoire(taille_plateau-1);
        break;
    case 2: // bas 
        navire.premiere_case.x = nb_aleatoire(taille_plateau-1);
        navire.premiere_case.y = nb_aleatoire(taille_plateau - taille);
        break;
    case 3: // gauche
        navire.premiere_case.x = nb_aleatoire(taille_plateau - taille);
        navire.premiere_case.y = nb_aleatoire(taille_plateau-1);
        break;
}

    return navire;
}


int est_valide(int **plateau, int taille_plateau, Navire *nav) {
    int dx[] = {0, 1, 0, -1};
    int dy[] = {-1, 0, 1, 0};
    int x = nav->premiere_case.x;
    int y = nav->premiere_case.y;

    for (int i = 0; i < nav->taille; i++) {
        if (x < 0 || x >= taille_plateau || y < 0 || y >= taille_plateau) {
            return 0; 
        }
        if (plateau[x][y] == 1) {
            return 0; 
        }

        x += dx[nav->sens];
        y += dy[nav->sens];
    }
    return 1; 
}


void initialisation_plateau(int **plateau, int taille_plateau) {
    int tailles_navires[] = {5, 4, 3, 3, 2}; 
    for (int i = 0; i < 5; i++) {
        int place = 0;
        while (!place) {
            Navire nav = creer_navire(tailles_navires[i], taille_plateau);
            if (est_valide(plateau, taille_plateau, &nav)) {
                place = 1; // Navire peut être placé
                int x = nav.premiere_case.x;
                int y = nav.premiere_case.y;
                int dx[] = {0, 1, 0, -1}; 
                int dy[] = {-1, 0, 1, 0}; 
                for (int j = 0; j < nav.taille; j++) {
                    plateau[x][y] = 1; 
                    x += dx[nav.sens];
                    y += dy[nav.sens];
                }
            }
        }
    }
}



void proposition_joueur(int **plateau, int **prop, int *nb_touche, int *nb_joue, int *nb_touche_nav, int taille_plateau) {
    int x, y;
    printf("Entrez les coordonnées (y x) : ");
    scanf("%d %d", &x, &y);
    x -= 1;
    y -= 1;

    if (x < 0 || x >= taille_plateau || y < 0 || y >= taille_plateau) {
        printf("Case invalide.\n");
        return;
    }
    
    if (prop[x][y] != 0) {
        printf("Case déjà jouée.\n");
        return;
    }

    (*nb_joue)++;
    if (plateau[x][y] == 1) {
        printf("Touche!\n");
        prop[x][y] = 1; 
        (*nb_touche)++;

    } else {
        printf("Manqué!\n");
        prop[x][y] = -1; 
    }
}


void affichage_plateau(int **plateau, int taille_plateau) {
    for (int i = 0; i < taille_plateau; i++) {
        for (int j = 0; j < taille_plateau; j++) {
            printf(". ");    
        }
        printf("\n");
    }
}

void affichage_choix_joueur(int **plateau, int **prop, int taille_plateau) {
    for (int i = 0; i < taille_plateau; i++) {
        for (int j = 0; j < taille_plateau; j++) {
            if (prop[i][j] == 1) { // Si un tir a touché un navire
                printf("x ");
            } else if (prop[i][j] == -1) { // Si un tir a manqué
                printf("o ");
            } else { // Si la case n'a pas encore été tentée
                printf(". ");
            }
        }
        printf("\n");
    }
}



