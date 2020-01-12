#ifndef _ETERNITY_H_
#define _ETERNITY_H_

#define PUZZLE_256 "./puzzles/eternityII_256.txt"
#define PUZZLE_72  "./puzzles/eternityII_72.txt"
#define PUZZLE_36  "./puzzles/eternityII_36.txt"

#define ANY 23

#define AFF 1

static int nx, ny;           /* nb de piece en x et y du puzzle */
static int currentx = 1;
static int currenty = 1;
static int nbpieceposees;

/* Structure des pièces
 * Chaque pièce est représentée par un identifiant, les 4 symboles qui composent
 * le tour. Chaque pièce est en mémoire telle qu'elles le seraient dans la boite
 * mais avec l'orientation actuelle
 * utilisée ou non et à quel endroit
 */

struct piece {
    int id;
    int used;      /* 1 pour used, 0 sinon */
    struct {
        int up;
        int right;
        int down;
        int left;
    } symbol;
};

typedef struct piece Piece;

/* Toutes les pieces du puzzle précédement dans un tableau
 * orientées, utilisée ou non et accessible uniquement ici
 * numéro de 0 à 255, dont l'id va de 1 à 256
 */
Piece Pieces[256];
Piece Rotations[1024];
Piece *Goodpieces[24][24][24][24][32];

/* Le Puzzle correspond à l'affichage et est une matrice 16x16 représentant
 * l'affichage en cours. Puzzle(1,1) pointe sur la pièce placée en haut à gauche
 */
Piece *Puzzle[17][17];

/* Une feuille représente un pavé du Puzzle sur lesquels peuvent etre posés
 * les différentes pieces possibles
 */
struct leaf_s {
    int loc; /* Endroit de la branche actuelle: 0 -> 99 du tab */
    int taille; /* Nombre max de branches totales pour le noeud */
    Piece tab[100];
};

typedef struct leaf_s Leaf;

/* Numéro de piece dans le tree sur la table en y et x */
enum directions { up = 0, right = 1, down = 2, left = 3};
Leaf Tree[17][17];

/* 42 = n'importe quel bord possible */
typedef unsigned char side[4];

void tourne_droite(Piece *p);
void tourne_gauche(Piece *p);
void avancer();
void reculer();
int searchgoodpiece();
void checkedges();
void loadfile(int argc, char *argv[]);

#endif
