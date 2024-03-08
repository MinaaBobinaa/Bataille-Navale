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
    Case positions[5];
    int taille;
    char *nom;
    int touche;
} Navire;


void commencer_jeu(void);
void terminer_jeu(int tirs);

char **allouer_plateau(int taille);
void free_plateau(char **plateau, int taille);
int verifier_placement(char **plateau, Case debut, int taille, int direction, int taille_plateau);
void placer_navire(char **plateau, Navire *navire, int taille_plateau);
void affichage_plateau(char **plateau, int taille);
void touche_navire(Navire *navire, int x, int y, int *navire_coule);

int valider_taille_plateau(void);
void initialiser_jeu(int taille, char ***plateau, char ***action_plateau, Navire navires[]);
int get_coordonnee_tir(int *x, int *y, int taille);
void proceder_tir(char **plateau, char **action_plateau, Navire navires[], int x, int y, int *tirs, int *navire_coule);


#endif 
