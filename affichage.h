#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <SDL/SDL.h>

#define PIECE_HEIGHT 20
#define PIECE_WIDTH  20

void drawpiece(SDL_Surface *ecran, Piece p, int x, int y);
void erasepiece(SDL_Surface *ecran, int x, int y);
void endpause();

#endif /* _DISPLAY_H_ */
