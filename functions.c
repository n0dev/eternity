#include <stdio.h>

#include "eternity.h"

void displayLeaf(int x, int y) {
	int b=0;
	printf("Position: x=%d, y=%d, %d pieces peuvent etre placees: ", x, y, Tree[y][x].taille-Tree[y][x].loc);
	for(b=0; b < Tree[y][x].taille; b++) {
		if(b==Tree[y][x].loc) {
			printf("%c[1m",27); /*- turn on bold */
		}
		printf("%d ", Tree[y][x].tab[b].id); /* (*Tree[y][x].tab[b]).id */
		if(b==Tree[y][x].loc) {
			printf("%c[0m",27); /*- turn off bold */
		}
	}
	printf(" max: %d.\n", Tree[y][x].taille);
}

void displayPieces() {
	int b=0;
	printf("Pieces: ");
	for(b=0; b < nx*ny; b++) {
		if(Pieces[b].used == 1) {
			printf("%c[1m",27); /*- turn on bold */
		}
		printf("%d ", Pieces[b].id);
		if(Pieces[b].used == 1) {
			printf("%c[0m",27); /*- turn off bold */
		}
	}
	printf("\n");
}
