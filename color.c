#include "color.h"

RGB int2color(int c) {
	RGB color;
	switch(c) {
		case 0:  /* Noir */
			color.r = 0;
			color.g = 0;	
			color.b = 0;
			break;
		case 1: /* Rouge */
			color.r = 255;
			color.g = 0;	
			color.b = 0;
			break;
		case 2: /* Vert */
			color.r = 0;
			color.g = 255;	
			color.b = 0;
			break;
		case 3: /* Bleu */
			color.r = 0;
			color.g = 0;	
			color.b = 255;
			break;
		case 4: /* Blanc */
			color.r = 255;
			color.g = 255;	
			color.b = 255;
			break;
		case 5: /* Rose */
			color.r = 255;
			color.g = 192;	
			color.b = 203;
			break;
		case 6: /* Orange */
			color.r = 255;
			color.g = 128;	
			color.b = 0;
			break;
		case 7: /* Marron */
			color.r = 255;
			color.g = 255;	
			color.b = 90;
			break;
		case 8: /* Gris */
			color.r = 100;
			color.g = 100;	
			color.b = 100;
			break;
		case 9: /* Gold */
			color.r = 255;
			color.g = 215;	
			color.b = 0;
			break;
		case 10: /* Magenta */
			color.r = 255;
			color.g = 0;	
			color.b = 255;
			break;
		case 11: /* Cyan */
			color.r = 0;
			color.g = 255;	
			color.b = 255;
			break;
		case 12: /* Saumon */
			color.r = 248;
			color.g = 142;	
			color.b = 85;
			break;
		case 13: /* Rouge_Fonce */
			color.r = 90;
			color.g = 0;	
			color.b = 0;
			break;
		case 14: /* Vert_Fonce */
			color.r = 0;
			color.g = 90;	
			color.b = 0;
			break;
		case 15: /* Bleu_Fonce */
			color.r = 0;
			color.g = 0;	
			color.b = 90;
			break;
		case 16: /* Bleu_Vert */
			color.r = 0;
			color.g = 90;	
			color.b = 90;
			break;
		case 17: /* Indigo */
			color.r = 54;
			color.g = 0;	
			color.b = 94;
			break;
		case 18: /* Anthracite */
			color.r = 48;
			color.g = 48;	
			color.b = 48;
			break;
		case 19: /* Aurore */
			color.r = 255;
			color.g = 203;	
			color.b = 96;
			break;
		case 20: /* Rouge_Cardinal */
			color.r = 184;
			color.g = 32;	
			color.b = 16;
			break;
		case 21: /* Puce */
			color.r = 78;
			color.g = 22;	
			color.b = 9;
			break;
		case 22: /* Jaune_De_Naples */
			color.r = 250;
			color.g = 218;	
			color.b = 94;
			break;
		default:
			color.r = 0;
			color.g = 0;	
			color.b = 0;
			break;
	}
	return color;
}
