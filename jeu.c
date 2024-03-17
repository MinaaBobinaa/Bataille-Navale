#include "include/jeu.h"
#include "include/stats.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <CUnit/Basic.h>


void commencer_jeu() {
   printf(MESSAGE_DEBUT_JEU);
}

void menu() {
   printf(MENU);
}

void terminer_jeu(int tirs) {
   printf(MESSAGE_FIN_JEU, tirs);
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
            plateau[x][y] = 'S';
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

void gerer_touche(Navire *navire, GameStats *stats) {
   navire->touche++;
   if (navire->touche == 1 && stats && !stats->premier_touche) {
      stats->nbr_lettres = navire->nbr_lettres;
      stats->premier_touche = 1;
   }
   if (stats) {
      stats->coups_touche++;
   }
}

void gerer_navire_coule(Navire *navire, char **plateau, char **action_plateau, int *navire_coule, GameStats *stats) {
   *navire_coule += 1;
   for (int j = 0; j < navire->taille; j++) {
      int posX = navire->positions[j].x;
      int posY = navire->positions[j].y;
      plateau[posX][posY] = 'C'; 
      action_plateau[posX][posY] = '+'; 
   }
   if (stats) {
      strcpy(stats->dernier_navire, navire->nom);
   }
   printf("Vous avez coulé un(e) %s!\n", navire->nom);
}

void touche_navire(Navire *navire, int x, int y, char **plateau, char **action_plateau, int *navire_coule, GameStats *stats) {
   for (int i = 0; i < navire->taille; i++) {
      if (navire->positions[i].x == x && navire->positions[i].y == y) {
         gerer_touche(navire, stats);
         if (navire->touche == navire->taille) {
            gerer_navire_coule(navire, plateau, action_plateau, navire_coule, stats);
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

void nettoyer_stdin(void) {
   int c;
   while ((c = getchar()) != '\n' && c != EOF) { }
}

int lire_coordonnees(char *input, int *x, int *y) {
   int resultat = 1;
   if (sscanf(input, "%d %d", x, y) != 2) {
      printf("Entrée non valide. Veuillez entrer des nombres.\n");
      nettoyer_stdin();
      resultat = 0;
   }
   return resultat;
}

int verifier_coordonnees(int x, int y, int taille) {
   int resultat = 1;
   if (x < 0 || y < 0 || x >= taille || y >= taille) {
      printf("Coordonnées hors du plateau. Veuillez entrer des coordonnées valides entre 0 et %d pour les deux axes.\n", taille - 1);
      resultat = 0;
   }
   return resultat;
}

int lire_entree_utilisateur(int *x, int *y, int taille) {
   char input[100];
   while (1) {
      nettoyer_stdin();
      printf("Entrez les coordonnées de tir (x y): ");
      if (!fgets(input, sizeof(input), stdin)) {
         printf("Erreur de lecture.\n");
         continue;
      }
      if (strlen(input) <= 1) {
         continue; 
      }
      if (!lire_coordonnees(input, x, y) || !verifier_coordonnees(*x, *y, taille)) {
         continue;
      }
      return 1; 
   }
}

int get_coordonnee_tir(int *x, int *y, int taille){
   int coordonneesValides = 0; 

   while (!coordonneesValides) {
      coordonneesValides = lire_entree_utilisateur(x, y, taille);
      if (!coordonneesValides) {
         printf("Coordonnées hors du plateau ou entrée invalide. Veuillez réessayer.\n");
         while (getchar() != '\n');
      }
   }

   return coordonneesValides;
}

void proceder_tir(char **plateau, char **action_plateau, Navire navires[], int x, int y, int *tirs, int *navire_coule, GameStats *stats){
   (*tirs)++;
   if (plateau[x][y] == 'S') {
      action_plateau[x][y] = 'x';
      for (int i = 0; i < 5; i++) {
         touche_navire(&navires[i], x, y, plateau, action_plateau, navire_coule, stats);
      }
   } else {
      action_plateau[x][y] = 'o';
      printf("À l'eau!\n");
      if (stats) stats->coups_eau++;
   }
   if (stats) stats->nbr_total_tirs++;
}

void jouer_jeu(char **plateau, char **action_plateau, Navire navires[], int taille, GameStats *stats){
   int x, y, tirs = 0, navire_coule = 0;
   while (navire_coule < 5) {
      if (!get_coordonnee_tir(&x, &y, taille)) continue;
      if (action_plateau[x][y] != '.') {
         if (stats) stats->deja_joue++;
         printf("Déjà joué.\n");
         continue;
      }
      proceder_tir(plateau, action_plateau, navires, x, y, &tirs, &navire_coule, stats);
      affichage_plateau(action_plateau, taille);
   }
   terminer_jeu(tirs);
}

void debut_jeu(GameStats *stats){
   srand(time(NULL));
   int taille = valider_taille_plateau();
   char **plateau = allouer_plateau(taille);
   char **action_plateau = allouer_plateau(taille);

   Navire navires[5] = {
      {{{0, 0}}, 5, "Porte-avions", 0, 10},
      {{{0, 0}}, 4, "Croiseur", 0, 7},
      {{{0, 0}}, 3, "Contre-torpilleur 1", 0, 10},
      {{{0, 0}}, 3, "Contre-torpilleur 2", 0, 10},
      {{{0, 0}}, 2, "Torpilleur", 0, 8}
   };

   initialiser_jeu(taille, &plateau, &action_plateau, navires);
   jouer_jeu(plateau, action_plateau, navires, taille, stats);
   free_plateau(plateau, taille);
   free_plateau(action_plateau, taille);
}
