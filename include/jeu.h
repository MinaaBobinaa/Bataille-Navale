#ifndef JEU_H
#define JEU_H

#include "stats.h"

#define TAILLE_MIN_PLATEAU 6
#define TAILLE_MAX_PLATEAU 100
#define MESSAGE_DEBUT_JEU \
   "================================================\n" \
   "Bienvenue dans le jeu de bataille navale !\n" \
   "================================================\n"
#define MENU \
   "Choisissez une option :\n\n" \
   "1. Nouvelle partie\n" \
   "2. Quitter\n\n"
#define MESSAGE_FIN_JEU \
   "================================================\n" \
   "Bravo !! Vous avez gagné en %d coups.\n" \
   "================================================\n"

// Définition de la structure Case
typedef struct {
   int x; /* position de la case en x*/
   int y; /* position de la case en y*/
} Case;

// Définition de la structure Navire
typedef struct {
   Case positions[5];
   int taille;
   char *nom;    
   int touche;
   int nbr_lettres;
} Navire;

/**
 * Démarre le jeu en affichant un message de bienvenue
 */
void commencer_jeu(void);

/**
 * Affiche menu du jeu
 */
void menu(void);

/**
 * Termine le jeu en affichant un message de fin
 *
 * @param tirs Le nombre total de tirs effectués par le joueur
 */
void terminer_jeu(int tirs);

/**
 * Alloue dynamiquement un plateau de jeu carré
 *
 * @param taille La dimension du plateau de jeu
 * @return Un pointeur vers le plateau de jeu alloué dynamiquement
 */
char **allouer_plateau(int taille);

/**
 * Libère la mémoire allouée pour le plateau de jeu
 *
 * @param plateau Un pointeur vers le plateau de jeu à libérer
 * @param taille La dimension du plateau de jeu
 */
void free_plateau(char **plateau, int taille);

/**
 * Vérifie si un objet peut être placé sur le plateau à partir
 * de la position de départ spécifiée, dans la direction donnée, sans dépasser
 * les limites du plateau et en s'assurant que toutes les cases occupées sont vides
 *
 * @param plateau Le plateau de jeu actuel
 * @param debut La position de départ pour le placement de l'objet
 * @param taille La taille de l'objet à placer
 * @param direction La direction du placement (0: droite, 1: bas, 2: gauche, 3: haut)
 * @param taille_plateau La dimension du plateau de jeu
 * @return 1 si le placement est valide, 0 sinon
 */
int verifier_placement(char **plateau, Case debut, int taille, int direction, int taille_plateau);

/**
 * Sélectionne une position aléatoire de départ sur le plateau et une direction
 * pour tenter de placer le navire. Si le placement est possible (toutes les cases nécessaires sont
 * libres et dans les limites du plateau), le navire est placé et le plateau est mis à jour
 *
 * @param plateau Le plateau de jeu actuel
 * @param navire Pointeur vers la structure Navire à placer
 * @param taille_plateau La dimension du plateau de jeu
 */
void placer_navire(char **plateau, Navire *navire, int taille_plateau);

/**
 * Affiche le plateau de jeu actuel dans la console
 *
 * @param plateau Le plateau de jeu actuel
 * @param taille La dimension du plateau de jeu
 */
void affichage_plateau(char **plateau, int taille);

/**
 * Gère une touche sur un navire en incrémentant le nombre de touches reçues par ce navire
 * Si c'est la première touche reçue par le navire, met à jour les statistiques
 *
 * @param navire Un pointeur vers le Navire touché
 * @param stats Un pointeur vers les statistiques globales du jeu pour la mise à jour
 */
void gerer_touche(Navire *navire, GameStats *stats);

/**
 * Marque un navire comme étant coulé en changeant les symboles sur les plateaux 
 * de jeu et d'action et met à jour les statistiques
 *
 * @param navire Un pointeur vers le Navire coulé
 * @param plateau Un pointeur vers le plateau de jeu principal
 * @param action_plateau Un pointeur vers le plateau d'action
 * @param navire_coule Un pointeur vers le compteur du nombre total de navires coulés
 * @param stats Un pointeur vers les statistiques du jeu
 */
void gerer_navire_coule(Navire *navire, char **plateau, char **action_plateau, int *navire_coule, GameStats *stats);

/**
 * Détecte si un tir touche une partie d'un navire sur le plateau. Parcourt les positions
 * d'un navire donné pour vérifier si le tir (x, y) le touche
 *
 * @param navire Pointeur vers le navire à vérifier
 * @param x Coordonnée X du tir
 * @param y Coordonnée Y du tir
 * @param plateau Pointeur vers le plateau de jeu principal
 * @param action_plateau Pointeur vers le plateau d'action utilisé pour marquer les tirs
 * @param navire_coule Pointeur vers le compteur des navires coulés
 * @param stats Pointeur vers les statistiques du jeu
 */
void touche_navire(Navire *navire, int x, int y, char **plateau, char **action_plateau, int *navire_coule, GameStats *stats);

int valider_taille(int taille);

/**
 * Demande à l'utilisateur d'entrer la taille du plateau de jeu et valide l'entrée
 *
 * @return La taille validée du plateau de jeu.
 */
int valider_taille_plateau(void);

/**
 * Initialise le jeu en allouant les plateaux de jeu et en plaçant les navires
 *
 * Crée deux plateaux de jeu de taille spécifiée: un pour le jeu réel et un autre
 * pour enregistrer les actions du joueur. Puis, place les navires de manière aléatoire
 * sur le plateau de jeu
 *
 * @param taille La dimension des plateaux de jeu
 * @param plateau Un pointeur double vers le plateau de jeu principal, alloué dynamiquement
 * @param action_plateau Un pointeur double vers le plateau d'action, alloué dynamiquement
 * @param navires Un tableau de structures Navire à placer sur le plateau
 */
void initialiser_jeu(int taille, char ***plateau, char ***action_plateau, Navire navires[]);

/**
 * Nettoie le buffer d'entrée standard pour éliminer tout caractère résiduel
 */
void nettoyer_stdin(void);

/**
 * Lit et valide les coordonnées entrées par l'utilisateur. Si la lecture échoue ou 
 * si moins de deux nombres sont fournis, affiche un message d'erreur et 
 * nettoie l'entrée standard.
 *
 * @param input La chaîne de caractères contenant l'entrée
 * @param x Un pointeur vers l'entier où stocker la coordonnée x
 * @param y Un pointeur vers l'entier où stocker la coordonnée y
 * @return 1 si la lecture réussit et que deux nombres sont fournis, 0 sinon
 */
int lire_coordonnees(char *input, int *x, int *y);

/**
 * Vérifie si les coordonnées fournies sont dans les limites du plateau de jeu
 *
 * @param x La coordonnée x à vérifier
 * @param y La coordonnée y à vérifier
 * @param taille La dimension du plateau de jeu
 * @return 1 si les coordonnées sont valides, 0 sinon
 */
int verifier_coordonnees(int x, int y, int taille);

/**
 * Invite l'utilisateur à entrer des coordonnées de tir et les valide.
 *
 * @param x Un pointeur pour stocker la coordonnée x 
 * @param y Un pointeur pour stocker la coordonnée y
 * @param taille La taille du plateau
 * @return 1 si les coordonnées sont valides et dans les limites du plateau, 0 sinon
 */
int lire_entree_utilisateur(int *x, int *y, int taille);

/**
 * Obtient des coordonnées de tir valides de l'utilisateur
 *
 * @param x Un pointeur vers un entier où stocker la coordonnée x du tir
 * @param y Un pointeur vers un entier où stocker la coordonnée y du tir
 * @param taille La taille du plateau
 * @return 1 si les coordonnées entrées sont valides, sinon ne retourne pas
 */
int get_coordonnee_tir(int *x, int *y, int taille);

/**
 * Gère le processus de tir, y compris la vérification des coups et la mise à jour des plateaux
 *
 * @param plateau Le plateau principal du jeu
 * @param action_plateau Le plateau indiquant les tirs précédents
 * @param navires Le tableau des navires présents sur le plateau
 * @param x La coordonnée x du tir
 * @param y La coordonnée y du tir
 * @param tirs Un pointeur vers le nombre total de tirs effectués
 * @param navire_coule Un pointeur vers le nombre de navires coulés
 * @param stats Les statistiques du jeu en cours
 */
void proceder_tir(char **plateau, char **action_plateau, Navire navires[], int x, int y, int *tirs, int *navire_coule, GameStats *stats);

/**
 * Boucle principale du jeu où les utilisateurs entrent des tirs jusqu'à ce que tous les navires soient coulés
 *
 * @param plateau Le plateau principal du jeu
 * @param action_plateau Le plateau indiquant les tirs précédents
 * @param navires Le tableau des navires présents sur le plateau
 * @param taille La taille du plateau
 * @param stats Les statistiques du jeu en cours
 */
void jouer_jeu(char **plateau, char **action_plateau, Navire navires[], int taille, GameStats *stats);

/**
 * Lance une nouvelle partie du jeu
 *
 * Cette fonction initialise l'environnement de jeu, y compris la génération du plateau de jeu et du plateau d'action,
 * le placement des navires, et la gestion du jeu jusqu'à ce que tous les navires soient coulés ou que l'utilisateur
 * décide de quitter. Les statistiques du jeu sont mises à jour tout au long de la partie.
 *
 * @param stats Pointeur vers une structure GameStats qui contiendra les statistiques de la partie jouée
 */
void debut_jeu(GameStats *stats);


#endif 
