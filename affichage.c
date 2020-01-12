#include <stdlib.h>
#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

#include "eternity.h"
#include "affichage.h"
#include "color.h"

SDL_Surface *rectangle = NULL;
SDL_Rect position;

void drawpiece(SDL_Surface *ecran, Piece p, int x, int y) {
	//up
	filledTrigonRGBA(ecran, (x-1)*PIECE_WIDTH, (y-1)*PIECE_HEIGHT, x*PIECE_WIDTH-2, (y-1)*PIECE_HEIGHT, x*PIECE_WIDTH-PIECE_WIDTH/2-1, (y-1)*PIECE_HEIGHT+PIECE_WIDTH/2-1, int2color(p.symbol.up).r, int2color(p.symbol.up).g, int2color(p.symbol.up).b, 255);
	//right
	filledTrigonRGBA(ecran, x*PIECE_WIDTH-2, (y-1)*PIECE_HEIGHT+1, x*PIECE_WIDTH-2, y*PIECE_HEIGHT-2, x*PIECE_WIDTH-PIECE_WIDTH/2, (y-1)*PIECE_HEIGHT+PIECE_WIDTH/2-1, int2color(p.symbol.right).r, int2color(p.symbol.right).g, int2color(p.symbol.right).b, 255);
	//down
	filledTrigonRGBA(ecran, (x-1)*PIECE_WIDTH, y*PIECE_HEIGHT-2, x*PIECE_WIDTH-2, y*PIECE_HEIGHT-2, x*PIECE_WIDTH-PIECE_WIDTH/2-2, (y-1)*PIECE_HEIGHT+PIECE_WIDTH/2-2, int2color(p.symbol.down).r, int2color(p.symbol.down).g, int2color(p.symbol.down).b, 255);
	//left
	filledTrigonRGBA(ecran, (x-1)*PIECE_WIDTH, (y-1)*PIECE_HEIGHT, (x-1)*PIECE_WIDTH, y*PIECE_HEIGHT-2, x*PIECE_WIDTH-PIECE_WIDTH/2-1, (y-1)*PIECE_HEIGHT+PIECE_WIDTH/2-1, int2color(p.symbol.left).r, int2color(p.symbol.left).g, int2color(p.symbol.left).b, 255);
	SDL_Flip(ecran);
}


void erasepiece(SDL_Surface *ecran, int x, int y) {

	rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, PIECE_WIDTH, PIECE_HEIGHT, 32, 0, 0, 0, 0);
	SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

	position.x = (x-1)*PIECE_WIDTH;
	position.y = (y-1)*PIECE_HEIGHT;

	SDL_BlitSurface(rectangle, NULL, ecran, &position);
	SDL_Flip(ecran); // Mise à jour de l'écran
	SDL_FreeSurface(rectangle); 
}

void endpause() {
    int continuer = 1;
    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}
