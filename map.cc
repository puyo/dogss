#include "map.h"

#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>

#define TILE_MIN  1
#define TILE_MAX  5


MAP map;
char str[80] = "map";


MAP::MAP()
{
 init();
}



MAP::MAP(const char * mappath, const char * datapath)
{
 init();
 load(mappath, datapath);
}



// init:
//   inits all map values to NULL
//
void MAP::init()
{
 mybitmap = NULL;
 mydata = NULL;
 myw = myh = 0;
 myloaded = false;
}



MAP::~MAP()
{
 unload();
}



/*
void MAP::draw(BITMAP * dest, int xoff, int yoff)
{
 register int  i;
 register int  j;
 unsigned      starti, startj, maxi, maxj;
 RLE_SPRITE *  tile;
 unsigned char tileid;

 if (loaded)
   {
    starti = xoff>>3;
    startj = yoff>>3;
    maxi = ((xoff + dest->w)>>3) + 1;
    maxj = ((yoff + dest->h)>>3) + 1;

    for (j = startj; j < maxj; ++j)
      {
       for (i = starti; i < maxi; ++i)
         {
          tileid = getpixel(bitmap, i, j);

          if ((tileid < TILE_MIN) || (tileid > TILE_MAX))
            continue;

          tile = (RLE_SPRITE *)data[tileid].dat;
          draw_rle_sprite(dest, tile, (i<<3) - xoff, (j<<3) - yoff);
         }
      }
   }
}
*/



// draw:
//   draws the map to a window
//
void MAP::draw(WINDOW * win)
{
 register int  i, j;
 unsigned      starti, startj, maxi, maxj;
 RLE_SPRITE *  tile;
 unsigned char tileid;

 if (win == NULL)
   return;

 if (myloaded)
   {
    starti = win->x>>3;
    startj = win->y>>3;
    maxi = ((win->x + win->buffer->w)>>3) + 1;
    maxj = ((win->y + win->buffer->h)>>3) + 1;

    for (j = startj; j < maxj; ++j)
      {
       for (i = starti; i < maxi; ++i)
         {
          tileid = getpixel(mybitmap, i, j);

          if ((tileid < TILE_MIN) || (tileid > TILE_MAX))
            continue;

          tile = (RLE_SPRITE *)mydata[tileid].dat;
          draw_rle_sprite(win->buffer, tile, (i<<3) - win->x, (j<<3) - win->y);
         }
      }
   }
}



// load:
//   loads a map, given a map filename and a datafile name
// returns:
//   zero on success
//   non-zero on failure
//
int MAP::load(const char * mappath, const char * datapath)
{
 PALETTE pal;
 int i;

 mybitmap = load_pcx(mappath, pal);
 mydata = load_datafile(datapath);

 if ((mybitmap == NULL) || (mydata == NULL))
   {
    mybitmap = NULL;
    mydata   = NULL;
    myw      = 0;
    myh      = 0;
    myloaded = false;
    return -1;
   }

 myw      = mybitmap->w;
 myh      = mybitmap->h;
 myloaded = true;

 // find player starting positions
// for (i = 0; i != 4; i++)
//   find_player_start(i, &player_start_x[i], &player_start_y[i]);

 return 0;
}



// save:
//   saves the map to a file
// returns:
//   zero on success
//   non-zero on failure
//
int MAP::save(const char * path)
{
 PALETTE pal;

 get_palette(pal);
 if (save_pcx(path, mybitmap, pal) == 0)
   return 0;

 return -1;
}



// unload:
//   safely frees map memory and restores all map values to NULL
//
void MAP::unload()
{
 if (mybitmap != NULL)
   destroy_bitmap(mybitmap);

 if (mydata != NULL)
   unload_datafile(mydata);

 mybitmap = NULL;
 mydata   = NULL;
 myw      = 0;
 myh      = 0;
 myloaded = false;
}



// find_player_start:
//   search the map bitmap for a 'player pixel'
//   replaces that pixel with a 'runway pixel'
//   stores the starting position of that player3
//
// returns:
//   zero on success
//   non-zero if no player start can be found (failure)
//
int MAP::find_player_start(unsigned char player_colour, unsigned * x, unsigned * y)
{
 int i, j;
 int p;

 *x = *y = 0;

 if (myloaded == false)
   return 0;

 for (j = myh - 1; j >= 0; --j)
   {
    for (i = 0; i != myw; ++i)
      {
       if ((p = getpixel(mybitmap, i, j)) == (254 - player_colour))
         {
          putpixel(mybitmap, i, j, 5);
          *x = i*8;
          *y = j*8;
          return 0;
         }
      }
   }

 return -1;
}



// itomap:
//   converts a map id to a map filename string
// returns:
//   a pointer to the map filename string
//
char * itomap(unsigned id)
{
 sprintf(&str[3], "%03u", id);
 sprintf(&str[6], ".pcx");

 return str;
}



// maptoi:
//   converts a map filenam string to a map id
// returns:
//   the map id
//
unsigned maptoi(char * name)
{
 char str[80];

 sprintf(str, "%s", name);
 str[6] = NULL;

 return (unsigned)atoi(&str[3]);
}

