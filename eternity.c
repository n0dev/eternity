#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#ifdef AFF
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#endif // AFF

#include "eternity.h"

#ifdef AFF
#include "affichage.h"
#endif // AFF

int maxpieceposees;
int test;
int verbose=1;
side sides;


void quit()
{
#ifdef AFF
	SDL_Quit();
#endif // AFF
	exit(0);
}

int main(int argc, char *argv[])
{
	int goodpieces=0;
	int loc=0;
	int max=0;
	int i=0, j=0;
	#ifdef AFF
		SDL_Surface *ecran = NULL;
		SDL_Event event;
	#endif

	/* Chargement des pieces dans Pieces */
	loadfile(argc, argv);

	/* Creation de la fenetre SDL */
	#ifdef AFF
		SDL_Init(SDL_INIT_VIDEO);
		ecran = SDL_SetVideoMode(nx*PIECE_WIDTH, ny*PIECE_HEIGHT, 32, SDL_HWSURFACE);
		SDL_WM_SetCaption("Eternity II", NULL);
	#endif

	signal(SIGINT, quit);
	signal(SIGTERM, quit);

	/* Pose de la premiere piece au coin superieur gauche
	 *	Il en trouve une piece qu'il met dans la tab en 0 */
	tourne_gauche(&Pieces[0]);
	Pieces[0].used = 1;
	Puzzle[1][1] = &Pieces[0];

	Tree[1][1].loc = 0;
	Tree[1][1].taille = 1;
	Tree[1][1].tab[0] = Pieces[0];

	#ifdef AFF
		drawpiece(ecran, *Puzzle[1][1], 1, 1);
	#endif
	nbpieceposees = 1;

	/* Debut de l'algorithme */
	avancer();
	bzero(&Tree[currenty][currentx], sizeof(Leaf)); /* Vide la feuille */
	Puzzle[currenty][currentx] = NULL;
	checkedges();
	goodpieces = searchgoodpiece();      /* Rempli la feuille */

	while(nbpieceposees < nx*ny) {

		loc = Tree[currenty][currentx].loc;    /* 0 - (max-1) */
		max = Tree[currenty][currentx].taille; /* Nb max de piece pouvant etre posees */
		goodpieces = max - loc;

		/*displayLeaf(currentx, currenty);
		displayPieces();*/

		#ifdef AFF
			SDL_PollEvent(&event);
		#endif

		if(nbpieceposees > maxpieceposees) {
			maxpieceposees = nbpieceposees;
			printf("Max pieces: %d\n", maxpieceposees);
			/*printf("\a");*/
		}

		/* S'il existe des pieces valable dans le Tree on les met sur le puzzle et on avance
		 * Sinon on recule
		 */
		if(goodpieces >= 1) {

			/*printf("Pose de la piece %d\n", Tree[currenty][currentx].tab[loc].id);*/
			nbpieceposees++;
			Puzzle[currenty][currentx] = &Tree[currenty][currentx].tab[loc]; /* Pointe sur la bonne piece */
			Pieces[Tree[currenty][currentx].tab[loc].id-1].used = 1;

			#ifdef AFF
				drawpiece(ecran, *Puzzle[currenty][currentx], currentx, currenty);
			#endif

			/* La pièce a été posée, on peut donc avancer */
			avancer();

			bzero(&Tree[currenty][currentx], sizeof(Leaf)); /* Vide la feuille */
			Puzzle[currenty][currentx] = NULL;
			loc = Tree[currenty][currentx].loc;
			Pieces[Tree[currenty][currentx].tab[loc].id-1].used = 0;
			checkedges();
			goodpieces = searchgoodpiece();      /* Rempli la feuille */

		} else {

			loc = Tree[currenty][currentx].loc;
			Pieces[Tree[currenty][currentx].tab[loc].id-1].used = 0;
			Puzzle[currenty][currentx] = NULL;

			#ifdef AFF
				erasepiece(ecran, currentx, currenty);
			#endif

			reculer();

			loc = Tree[currenty][currentx].loc;
			Pieces[Tree[currenty][currentx].tab[loc].id-1].used = 0;
			Tree[currenty][currentx].loc++;
			nbpieceposees--;

			#ifdef AFF
				erasepiece(ecran, currentx, currenty);
			#endif

		}
		if(test % 1000000 == 0)
			printf("%d\n", test);
		test++;
	}

	printf("-----------------------------------------\n");
	printf("Le Puzzle est terminé: voici le résultat:\n");
	printf("-----------------------------------------\n\n");

	for(i=1; i<=nx; i++) {
		for(j=1; j<=ny; j++) {
			if(Puzzle[j][i] != NULL) {
				printf("Position x=%d y=%d: piece: %d\n", i, j, (*Puzzle[j][i]).id);
			}
		}
	}

	#ifdef AFF
		SDL_Flip(ecran);
		endpause();
		SDL_Quit();
	#endif
	return EXIT_SUCCESS;
}

int searchgoodpiece() {
	int i=0;
	int k=0;

	for(i=0; i<32; i++) {
		if(Goodpieces[sides[up]][sides[right]][sides[down]][sides[left]][i] != NULL) {
			if(Pieces[Goodpieces[sides[up]][sides[right]][sides[down]][sides[left]][i]->id-1].used == 0) {
				Tree[currenty][currentx].tab[k] = *Goodpieces[sides[up]][sides[right]][sides[down]][sides[left]][i];
				k++;
			}
		}
		else {
			break;
		}
	}

	Tree[currenty][currentx].loc = 0;
	Tree[currenty][currentx].taille = k;
	return k;
}


void checkedges() {
	sides[left] = (currentx == 1) ? 0 : ((Puzzle[currenty][currentx-1] != NULL) ? (*Puzzle[currenty][currentx-1]).symbol.right : ANY);
	sides[right] = (currentx == nx) ? 0 : ((Puzzle[currenty][currentx+1] != NULL) ? (*Puzzle[currenty][currentx+1]).symbol.left : ANY);
	sides[up] = (currenty == 1) ? 0 : ((Puzzle[currenty-1][currentx] != NULL) ? (*Puzzle[currenty-1][currentx]).symbol.down : ANY);
	sides[down] = (currenty == ny) ? 0 : ((Puzzle[currenty+1][currentx] != NULL) ? (*Puzzle[currenty+1][currentx]).symbol.up : ANY);
}

void tourne_droite(Piece *p) {
	int swap = (*p).symbol.up;
	p->symbol.up = p->symbol.left;
	p->symbol.left = p->symbol.down;
	p->symbol.down = p->symbol.right;
	p->symbol.right = swap;
}

void tourne_gauche(Piece *p) {
	int swap = (*p).symbol.up;
	p->symbol.up = p->symbol.right;
	p->symbol.right = p->symbol.down;
	p->symbol.down = p->symbol.left;
	p->symbol.left = swap;
}

void avancer() {
	if(currenty <= nx/2 ) {
		if(currenty < 3 ) {
			if(currentx<= nx-currenty ) {
				currentx= currentx+1;
			} else {
				if(currenty>currentx ) {
					currenty = currenty-1;
				} else {
					currenty= currenty +1;
				}
			}
		} else {
			if(currenty-1<=currentx && currentx<= nx-currenty ) {
				currentx = currentx+1;
			} else {
				if(currenty>currentx ) {
					currenty = currenty-1;
				} else {
					currenty= currenty +1;
				}
			}
		}
	} else {
		if(nx-currenty+2 <= currentx && currentx<= currenty ) {
			currentx = currentx-1;
		} else {
			if(currenty>currentx ) {
				currenty = currenty-1;
			} else {
				currenty = currenty+1;
			}
		}
	}
}

void reculer()
{
	if(currentx >= currenty && currentx <= nx-currenty+1) {
		currentx = currentx - 1;
	}
	else if(currentx >= currenty && currentx > nx-currenty+1) {
		currenty = currenty - 1;
	}
	else if(currentx < currenty && currentx < nx-currenty+1) {
		currenty = currenty + 1;
	}
	else if(currentx < currenty && currentx >= nx-currenty+1) {
		currentx = currentx + 1;
	}
}

void loadfile(int argc, char *argv[]) {
	FILE *file;
	int i=0, j=0;
	int a=0, b=0, c=0, d=0, k=0;

	if (argc == 1) {
		printf("Ouverture du fichier 256\n");
		file = fopen(PUZZLE_256, "r");
	}
	else {
		switch (atoi(argv[1])) {
			case 36:
				printf("Ouverture du fichier 36\n");
				file = fopen(PUZZLE_36, "r");
				break;
			case 72 :
				printf("Ouverture du fichier 72\n");
				file = fopen(PUZZLE_72, "r");
				break;
			default:
				printf("Usage: ./eternity [36] [72] [256]\n");
				exit(0);
		}
	}

	fscanf(file,"%d %d\n", &nx, &ny);
	printf("Le puzzle est de %d x %d\n", nx, ny);

	for(i = 0; i < nx*ny; i++ ) {
		fscanf(file,"%d %d %d %d %d", &Pieces[i].id, &Pieces[i].symbol.up, &Pieces[i].symbol.right, &Pieces[i].symbol.down, &Pieces[i].symbol.left);

		/* Pre-compute les rotations */
		for(j=0; j<4; j++) {
			Rotations[i*4+j] = Pieces[i];
			Rotations[i*4+j].used = 0;
			tourne_droite(&Pieces[i]);
		}

		Pieces[i].used = 0;
		if(verbose) {
			printf("Piece %d: %d %d %d %d\n", Pieces[i].id, Pieces[i].symbol.up, Pieces[i].symbol.right, Pieces[i].symbol.down, Pieces[i].symbol.left);
		}
	}

	/* Pre-compute Goodpieces
	 * Renvoie un tableau de bonnes pieces suivant les contraintes up, right, down, left (entre 0 et 23)
     * Faire attention pour les coins -> Pas a ranger quand 0 ANY ANY ANY
     */
	for(a=0; a <= ANY; a++ ) {
		for(b=0; b <= ANY; b++ ) {
			for(c=0; c <= ANY; c++ ) {
				for(d=0; d <= ANY; d++ ) {

					if(a == b && b== c && c== d && d == ANY) {
						break;
					}

					k=0;

					for(i = 0; i < 16; i++ ) {
						if((a == 0 && b == 0) || (a == 0 && c == 0) || (a == 0 && d == 0) ||
						   (b == 0 && c == 0) || (b == 0 && d == 0) || (c == 0 && d == 0)) {
							if(a == ANY || Rotations[i].symbol.up == a) {
								if(b == ANY || Rotations[i].symbol.right == b) {
									if(c == ANY || Rotations[i].symbol.down == c) {
										if(d == ANY || Rotations[i].symbol.left == d) {
											Goodpieces[a][b][c][d][k] = &(Rotations[i]);
											/*printf("Ajoute la piece %d au tableau: %d %d %d %d\n", Rotations[i].id, a, b, c, d);*/
											k++;
										}
									}
								}
							}
						}
					}

					/* Pour up=a, right=b, down=c et left=d, calcule les pieces qui vont bien sauf les coins */
					for(i = 16; i < nx*ny*4; i++ ) {
						if(a == ANY || Rotations[i].symbol.up == a) {
							if(b == ANY || Rotations[i].symbol.right == b) {
								if(c == ANY || Rotations[i].symbol.down == c) {
									if(d == ANY || Rotations[i].symbol.left == d) {
										Goodpieces[a][b][c][d][k] = &(Rotations[i]);
										/*printf("Ajoute la piece %d au tableau: %d %d %d %d\n", Rotations[i].id, a, b, c, d);*/
										k++;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	printf("\n");
}

