#ifndef JEU_H
#define JEU_H

#include <stdlib.h> 

// Définition de la structure Case
typedef struct {
    int x; // position en x
    int y; // position en y
} Case;

// Définition de la structure Navire
typedef struct {
    int sens; // 0 haut, 1 droite, 2 bas, 3 gauche
    Case premiere_case;
    int taille;
} Navire;

// Définition de la structure Grille
typedef struct {
    char** cases;
    int taille;
} Grille;

#define TAILLE_MIN_PLATEAU 6
#define TAILLE_MAX_PLATEAU 100

int demanderTaillePlateau();
int verifierPlageTaille(int taille);
int verifierEntreeNombre(int resultat);

void initialiserGrille(Grille* grille, int taillePlateau);
void afficherGrille(Grille* grille);
void libererGrille(Grille* grille);

void init_jeu(int taille_plateau);
void jouer(int taille_plateau);
void liberer_ressources();


#endif 
