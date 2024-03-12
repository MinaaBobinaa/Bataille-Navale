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

void init_stats(GameStats *stats);
void write_stats_file(const GameStats *stats, const char *nom_fichier);

#endif
