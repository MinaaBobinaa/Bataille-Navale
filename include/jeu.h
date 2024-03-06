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
    char* nom;
    int sens; // 0 haut, 1 droite, 2 bas, 3 gauche
    Case premiere_case;
    int taille;
    int touche; // Nombre de cases touchées pour ce navire
    int coule;
} Navire;

typedef struct TypeInfoNavire {
    char *nom;
    int taille;
} TypeInfoNavire;

TypeInfoNavire typesNavires[] = {
    {"Porte-avions", 5},
    {"Croiseur", 4},
    {"Contre-torpilleur", 3},
    {"Contre-torpilleur", 3},
    {"Torpilleur", 2},
};



#define TAILLE_MIN_PLATEAU 6
#define TAILLE_MAX_PLATEAU 100

int demanderTaillePlateau();
int verifierPlageTaille(int taille);
int verifierEntreeNombre(int resultat);


#endif 
