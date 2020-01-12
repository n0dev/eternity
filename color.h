#ifndef _COLOR_H_
#define _COLOR_H_

struct RGB_s {
    unsigned char r;
    unsigned char g;
    unsigned char b;
};
typedef struct RGB_s RGB;

RGB int2color(int c);

#endif