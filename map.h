#ifndef _MAP_H_
#define _MAP_H_


#include <allegro.h>
#include "window.h"


char *   itomap(unsigned id);
unsigned maptoi(char * name);


class MAP
{
public:
 MAP();
 MAP(const char * mappath, const char * datapath);
 ~MAP();

 void draw(WINDOW * win);

 int  load(const char * mappath, const char * datapath);
 int  save(const char * path);
 void unload();

 unsigned get_w() { return myw; }
 unsigned get_h() { return myh; }

 bool is_loaded() { return myloaded; }

protected:
 void init();
 int  find_player_start(unsigned char player_colour, unsigned * x, unsigned * y);

 BITMAP *   mybitmap;
 unsigned   myw;
 unsigned   myh;
 bool       myloaded;
 DATAFILE * mydata;

 //unsigned myplayer_start_x[4];
 //unsigned myplayer_start_y[4];
};


extern MAP map;

#endif

