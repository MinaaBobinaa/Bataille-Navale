#include "include/stats.h"
#include <stdio.h>
#include <string.h>

void init_stats(GameStats *stats) {
   stats->nbr_total_tirs = 0;
   stats->nbr_lettres = 0;
   stats->coups_eau = 0;
   stats->deja_joue = 0;
   stats->coups_touche = 0;
   memset(stats->dernier_navire, 0, sizeof(stats->dernier_navire));
   stats->premier_touche = 0;     
}


void write_stats_file(const GameStats *stats, const char *nom_fichier) {
   FILE *file = fopen(nom_fichier, "w");
   if (file) {
      fprintf(file, "Nombre total de coups: %d\n", stats->nbr_total_tirs);
      fprintf(file, "Nombre de lettres sans doublon du premier navire touché: %d\n", stats->nbr_lettres);
      fprintf(file, "Nombre total de coups à l’eau: %d\n", stats->coups_eau);
      fprintf(file, "Nombre total de coups déjà joué: %d\n", stats->deja_joue);
      fprintf(file, "Nombre total de coups touché: %d\n", stats->coups_touche);
      fprintf(file, "Nom du dernier navire coulé: %s\n", stats->dernier_navire);
      fclose(file);
   } else {
      printf("Erreur lors de l'ouverture du fichier '%s'\n", nom_fichier);
   }
}
