#ifndef _WINDOW_H_
#define _WINDOW_H_


#include <allegro.h>

class WINDOW
{
public:
 BITMAP * buffer;
 int x, y;
 int maxx, maxy;

 WINDOW();
 void set(BITMAP * buffer, int maxx, int maxy);
 void scroll(int dx, int dy);
};


#endif
