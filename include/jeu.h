#ifndef JEU_H
#define JEU_H

#define TAILLE_MIN_PLATEAU 6
#define TAILLE_MAX_PLATEAU 100

// Définition de la structure Case
typedef struct {
    int x;
    int y; 
} Case;

// Définition de la structure Navire
typedef struct {
    Position positions[5];
    int taille;
    char *nom;
    int touche;
} Navire;


char **allouer_plateau(int taille);
void free_plateau(char **plateau, int taille);


#endif 
