#include "window.h"



WINDOW::WINDOW()
{
 buffer = NULL;
 maxx = maxy = 0;
 x = y = 0;
}



void WINDOW::set(BITMAP * newbuffer, int newmaxx, int newmaxy)
{
 buffer = newbuffer;
 maxx = newmaxx;
 maxy = newmaxy;
 x = y = 0;
}



// scroll:
//   scroll the window on the map
//
void WINDOW::scroll(int dx, int dy)
{
 x += dx;
 y += dy;

      if (x < 0)     x = 0;
 else if (x > maxx)  x = maxx;

      if (y < 0)     y = 0;
 else if (y > maxy)  y = maxy;
}

