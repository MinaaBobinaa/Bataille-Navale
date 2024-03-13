#include "include/jeu.h"
#include "include/stats.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>


int main(int argc, char** argv) {
	
   int choix;
   char buffer[100];
   char *fichier_stats = NULL;

   if (argc > 1) {
      if (argc == 3 && strcmp(argv[1], "-S") == 0) {
         fichier_stats = argv[2];
      } else {
         fprintf(stderr, "Usage: %s [-S stats.txt]\n", argv[0]);
         return 1;
      }
   }

   GameStats stats;
   if (fichier_stats) {
      init_stats(&stats);
   }   

   commencer_jeu();    

   while (1) {
      printf("Choisissez une option :\n\n");
      printf("1. Nouvelle partie\n");
      printf("2. Quitter\n\n");
      if (!fgets(buffer, sizeof(buffer), stdin)) {
         continue;
      }

      if (sscanf(buffer, "%d", &choix) != 1) {
         printf("Entrée non valide. Veuillez entrer un nombre.\n");
         continue;
      }

      switch (choix) {
         case 1:
            if (fichier_stats) {
               debut_jeu(&stats);
               write_stats_file(&stats, fichier_stats);
            } else {
               debut_jeu(NULL);
            }
               break;
         case 2:
            printf("Merci d'avoir joué. À bientôt!\n\n");
            return 0;
         default:
            printf("Choix non valide. Veuillez réessayer.\n");
      }
   }
   return 0;
}