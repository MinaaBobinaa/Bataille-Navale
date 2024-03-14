#ifndef STATS_H
#define STATS_H

typedef struct {
   int nbr_total_tirs;     
   int nbr_lettres;       
   int coups_eau;      
   int deja_joue;         
   int coups_touche;            
   char dernier_navire[20]; 
   int premier_touche;   
} GameStats;

/**
 * Initialise les statistiques du jeu. Met à zéro tous les compteurs et initialise
 * le tableau du dernier navire coulé.
 * Cette fonction doit être appelée au début de chaque nouvelle partie pour réinitialiser
 * les statistiques.
 *
 * @param stats Pointeur vers la structure GameStats qui doit être initialisée
 */
void init_stats(GameStats *stats);

/**
 * Écrit les statistiques du jeu dans un fichier
 *
 * Sauvegarde les statistiques courantes du jeu, telles que le nombre total de tirs,
 * le nombre de lettres sans doublon du premier navire touché, les coups à l'eau, les coups
 * déjà joués, les coups touchés, et le nom du dernier navire coulé, dans le fichier spécifié.
 * Si le fichier ne peut pas être ouvert, un message d'erreur est affiché.
 *
 * @param stats Pointeur constant vers la structure GameStats contenant les statistiques à écrire
 * @param nom_fichier Chaîne de caractères représentant le nom du fichier où écrire les statistiques
 */
void write_stats_file(const GameStats *stats, const char *nom_fichier);

#endif
