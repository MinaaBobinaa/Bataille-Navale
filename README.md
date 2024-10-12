# Jeu de bataille navale


## Description du programme:
Le programme est un jeu de bataille navale interactif, où le joueur commence 
par choisir la taille du plateau de jeu, avec une limite minimale de 6x6 et 
maximale de 100x100 cases. Sur ce plateau, le programme dispose aléatoirement
cinq navires de tailles variées : un Porte-avions de 5 cases, un Croiseur de 4
cases, deux Contre-torpilleurs de 3 cases chacun, et un Torpilleur de 2 cases.

Le joueur engage le jeu en sélectionnant des cases pour lancer des torpilles,
dans le but de toucher et couler ces navires. L'objectif pour le joueur est de
couler tous les navires adverses. 
Le jeu se poursuit jusqu'à ce que tous les navires soient
coulés.

Ce jeu combine stratégie, anticipation et un élément de chance, offrant
une expérience ludique enrichissante tout en restant fidèle à l'esprit
classique de la bataille navale.

Vous devez également installer les sous-modules Git permettant d'utiliser Bats.
Pour cela, il suffit d'entrer la commande:

```bash
$ git submodule update --init
```

Pour excecuter les tests unitaires (CUnits) vous devez entrer cette commande:

```bash
$ sudo apt install libcunit1 libcunit1-doc libcunit1-dev
```

## Compilation et Exécution:

Pour compiler le programme, utilisez la commande suivante dans le terminal :

```bash
$ gcc -Wall -Wextra -std=c99 -o bataille_navale main.c jeu.c stats.c
```
Après compilation, exécutez 'bataille_navale' sans ou avec les arguments qui suivent:

```bash
$ ./bataille_navale
```
La commande ci-dessous enregistrera les statistiques du jeu dans un fichier stats.txt:
```bash
$ ./bataille_navale -S stats.txt
```
## Comportement du jeu:


A l'excecution du jeu, vous aurez un menu qui se representera sous cette forme:

```bash
================================================
Bienvenue dans le jeu de bataille navale !
================================================
Choisissez une option :

1. Nouvelle partie
2. Quitter
```
Si vous entrez '2' au clavier, cela terminera l'execution du programme. 

A la saisie de '1', vous commencerez une nouvelle partie.
Pour débuter le jeu, vous serez invité à entrer la taille du plateau de jeu.
Voici ce à quoi s'attendre :

```bash
$ Entrez la taille du plateau de jeu (min 6, max 100):
0
$ Taille invalide. La taille doit être entre 6 et 100.
$ Entrez la taille du plateau de jeu (min 6, max 100): 
101
$ Taille invalide. La taille doit être entre 6 et 100.
$ Entrez la taille du plateau de jeu (min 6, max 100): 
6
$ Entrez les coordonnées de tir (x y): 
```
Apres la validation de la taille du plateau, le jeu demandera au joeur d'entrer les 
coordonnees de tir.
Voici ce à quoi s'attendre pour un plateau de taille 6:

```bash 
$ Entrez les coordonnées de tir (x y): a b
$ Entrée non valide. Veuillez entrer des nombres.


$ Entrez les coordonnées de tir (x y): 1 10
Coordonnées hors du plateau. Veuillez entrer des coordonnées valides entre 0 et 5 pour les deux axes.

$ Entrez les coordonnées de tir (x y): 0 0
Touché!
x . . . . . 
. . . . . . 
. . . . . . 
. . . . . . 
. . . . . . 
. . . . . . 
```
Veuillez noter que les symboles et messages vont variez après chaque tir.

Le plateau de jeu est affiché à l'écran avec les symboles suivants pour représenter
l'état actuel :
- `x` : Une case jouée qui touche un navire.
- `o` : Une case jouée ne contenant aucun navire.
- `.` : Une case qui n'a pas encore été jouée.
- `+` : Les cases qui coule un navire.

**Résultat du Tir** :
- **Touché** : Si un navire se trouve sur la case visée, le jeu affiche `Touché!`
- **À l'eau** : Si aucune partie d'un navire n'occupe la case, le jeu affiche `À l'eau`
- **Déjà joué** : Si la case a déjà été ciblée auparavant, le jeu vous invite à choisir une nouvelle case
- **Vous avez coulé (navire)** : Si un navire a été coulé

```bash
$ Entrez les coordonnées de tir (x y): 0 1
Vous avez coulé un(e) Torpilleur de taille 2!
+ + . . . . 
. . . . . . 
. . . . . . 
. . . . . . 
. . . . . . 
. . . . . . 

$ Entrez les coordonnées de tir (x y): 0 2
À l\'eau!
+ + o . . . 
. . . . . . 
. . . . . . 
. . . . . . 
. . . . . . 
. . . . . . 

$ Entrez les coordonnées de tir (x y): 0 2
Déjà joué.

$ Entrez les coordonnées de tir (x y): 
```

A la fin du jeu, le programme affichera un message qui indiquera en combien de coups
vous avez gagné la partie:

```bash
$ Entrez les coordonnées de tir (x y): 3 5
Vous avez coulé un(e) Contre-torpilleur 1 de taille 3!
+ + o o o o 
+ + + + + . 
o o o o o o 
o + + + . + 
o + + + + + 
. o o . o + 
================================================
Bravo !! Vous avez gagné en 32 coups.
================================================
```
Si vous avez executé le programme avec `-S stats.txt`, vous pouvez consulter le fichier 
de statistiques en ecrivant la commande suivante:

```bash
$ cat stats.txt
```
Votre fichier affichera différentes statistiques en fonction du déroulement du jeu.
```text
Nombre total de coups: 32
Nombre de lettres sans doublon du premier navire touché: 8
Nombre total de coups à l’eau: 15
Nombre total de coups déjà joué: 2
Nombre total de coups touché: 17
Nom du dernier navire coulé: Contre-torpilleur 1
```

---
## Makefile:
Le Makefile fourni est conçu pour faciliter la compilation, les tests et le nettoyage du
jeu de bataille navale. Voici un aperçu de son fonctionnement et de ses commandes
principales:

### Commande Principale
- `make build`: Compile le projet en créant l'exécutable du jeu `bataille_navale`

#### Plus de détails
- `$(TARGET)`: Cette cible compile tous les fichiers objets (`$(OBJECTS)`) en
utilisant les flags de compilation spécifiés (`$(CFLAGS)`) pour créer l'exécutable du projet.
- `%.o`: Compile chaque fichier source `.c` en un fichier objet `.o`, permettant une 
compilation séparée des différentes parties du projet.


### Commande de test Bats
- `make test`: Exécute les tests **Bats** du projet

#### Plus de détails
- `test-bataille_navale`: Cette cible utilise Bats pour exécuter les tests définis dans
`bataille_navale.bats`, permettant de tester le fonctionnement du jeu.

### Commande de test CUnit
- `make cunits`: Compile et exécute les tests CUnit pour le projet,
puis génère des rapports de couverture de code avec `gcov`.

#### Plus de détails
- Compile le fichier de test CUnit avec le fichier source `jeu.c`,
crée l'exécutable de test, exécute les tests, puis utilise `gcov` pour 
analyser la couverture de code des fichiers testés.

### Commande HTML
- `make html` est utilisée pour convertir le fichier `README.md` en une version HTML, facilitant ainsi sa lecture dans un navigateur web. Cette opération est effectuée à l'aide de `pandoc`.

#### Plus de détails
- Cette commande prend le contenu du fichier spécifié dans la variable `README` et génère un fichier HTML dans l'emplacement spécifié par la variable `README_HTML`.
- Il est nécessaire que `pandoc` soit installé sur votre système pour que cette commande fonctionne correctement.

### Commande de Nettoyage
- `make clean`: Supprime tous les fichiers générés par le processus de build et
de test, y compris les fichiers objets, l'exécutable, les fichiers de couverture 
de code et les fichiers de statistiques.

### Commande Phony
- `.PHONY`: Déclare les cibles qui ne correspondent pas à des fichiers réels comme étant 'phony', évitant ainsi des conflits avec des fichiers de même nom et garantissant que les commandes sont toujours exécutées.

