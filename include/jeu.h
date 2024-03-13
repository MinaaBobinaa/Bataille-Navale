#ifndef JEU_H
#define JEU_H

#include "stats.h"

#define TAILLE_MIN_PLATEAU 6
#define TAILLE_MAX_PLATEAU 100
#define MESSAGE_DEBUT_JEU \
    "================================================\n" \
    "Bienvenue dans le jeu de bataille navale !\n" \
    "================================================\n"
#define MESSAGE_FIN_JEU \
    "================================================\n" \
    "Bravo !! Vous avez gagné en %d coups.\n" \
    "================================================\n"

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
    int nbr_lettres;
} Navire;


// Prototypes de fonctions publiques
void commencer_jeu(void);
void terminer_jeu(int tirs);

char **allouer_plateau(int taille);
void free_plateau(char **plateau, int taille);
int verifier_placement(char **plateau, Case debut, int taille, int direction, int taille_plateau);
void placer_navire(char **plateau, Navire *navire, int taille_plateau);
void affichage_plateau(char **plateau, int taille);
void enregstr_prem_touch(GameStats *stats, Navire *navire);
void marquer_navire_coule(char **plateau, char **action_plateau, Navire *navire, GameStats *stats);
void gerer_touche_navire(Navire *navire, int x, int y, char **plateau, char **action_plateau, int *navire_coule, GameStats *stats);
void touche_navire(Navire *navire, int x, int y, char **plateau, char **action_plateau, int *navire_coule, GameStats *stats);

int valider_taille_plateau(void);
void initialiser_jeu(int taille, char ***plateau, char ***action_plateau, Navire navires[]);
void nettoyer_stdin(void);
int lire_coordonnees(char *input, int *x, int *y);
int verifier_coordonnees(int x, int y, int taille);
int lire_entree_utilisateur(int *x, int *y, int taille);
int get_coordonnee_tir(int *x, int *y, int taille);
void proceder_tir(char **plateau, char **action_plateau, Navire navires[], int x, int y, int *tirs, int *navire_coule, GameStats *stats);

void jouer_jeu(char **plateau, char **action_plateau, Navire navires[], int taille, GameStats *stats);
void debut_jeu(GameStats *stats);


#endif 
