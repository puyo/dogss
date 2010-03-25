
#include <allegro.h>
#include <cstdio>
#include <vector>
#include <iostream>

#include "object.h"
#include "player.h"
#include "map.h"
#include "error.h"
#include "data.h"
#include "colours.h"


#define SCR_W      320
#define SCR_H      240
#define FPS_DELAY   50


//  FUNCTION PROTOTYPES  ////////////////////////////////////////////////////

void draw_fps(BITMAP * buffer, FONT * font, int x, int y);
void draw_backgrounds(WINDOW * win, DATAFILE * backdat, unsigned mapw, unsigned maph);


//  MAIN FUNCTION  //////////////////////////////////////////////////////////

int main(void)
{
 std::vector<OBJECT *> objects;
 std::vector<OBJECT *>::iterator i;

 PLAYER * p       = NULL;
 BITMAP * buffer  = NULL;
 BITMAP * subbmp  = NULL;
 OBJECT * obj     = NULL;
 WINDOW * win     = NULL;
 MAP      map;
 int      err     = 0;

 printf("Loading...");

 printf("\nInitialising Allegro...");
 allegro_init();
 printf("\nInstalling timer...");
 install_timer();
 printf("\nInstalling keyboard...");
 install_keyboard();


 printf("\nSetting graphics mode...");
 set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCR_W, SCR_H, 0, 0);


 printf("\nLoading datafiles...");
 datafiles_init();


 // load the map
 printf("\nLoading map...");
 err = map.load("maps/map000.pcx", "data/mpstyl00.dat");
 if (err == -1)
   error_quit("Unable to load map \"maps\\map000.pcx\" and \"data\\mpstyle00.dat\".", -1);


 // main screen buffer
 printf("\nCreating main screen buffer...");
 buffer = create_bitmap(SCR_W, SCR_H);


 printf("\nCreating players...");
 // player 1
 p = new PLAYER(playerdat);

  win = new WINDOW;

   subbmp = create_sub_bitmap(buffer, 0, 0, SCREEN_W, SCREEN_H/2 - 4);
   win->set(subbmp, (map.get_w()<<3) - subbmp->w, (map.get_h()<<3) - subbmp->h);

  p->set_window(win);
  p->set_keys(KEY_Y, KEY_H, KEY_G, KEY_J);
  p->set_colour(COLOUR_RED);

 objects.push_back(p);


 // player 2
 p = new PLAYER(playerdat);

  win = new WINDOW;

   subbmp = create_sub_bitmap(buffer, 0, SCREEN_H/2 + 2, SCREEN_W, SCREEN_H/2 - 4);
   win->set(subbmp, (map.get_w()<<3) - subbmp->w, (map.get_h()<<3) - subbmp->h);

  p->set_window(win);
  p->set_keys(KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT);
  p->set_colour(COLOUR_BLUE);

 objects.push_back(p);


 // load the palette
 printf("\nSetting palette...");
 if (paldat != NULL)
   set_palette((RGB *)paldat[0].dat);


 do
   {
    // DRAW EVERYTHING //////////////////////////////////////////////////////
    // clear the buffer
    clear(buffer);

    // update the objects
    for (i = objects.begin(); i != objects.end(); ++i)
      {
       obj = *i;

       if (obj->is_player())
         {
          p = (PLAYER *)obj;

          // draw everything on the player's window
          win = p->get_window();

          // backgrounds
          draw_backgrounds(win, backdat, map.get_w()<<3, map.get_h()<<3);

          // map
          map.draw(win);

          // objects

          // player
          ((PLAYER *)obj)->draw(win);

          // info
          textprintf_ex(win->buffer, (FONT *)fontdat[0].dat, 0, 8, -1, -1, "(%d,%d)", win->x, win->y);
         }
      }

    // debug info
    draw_fps(buffer, (FONT *)fontdat[0].dat, 0, 0);

    // copy the buffer to the screen
    vsync();
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);


    // MOVE EVERYTHING //////////////////////////////////////////////////////

    // update the objects
    for (i = objects.begin(); i != objects.end(); ++i)
      {
       obj = *i;

       if ((obj != NULL) && (obj->valid))
         {
          err = obj->update();
          if (err != 0)
            error_quit("Object returned error.", err);
         }
      }



   }
 while (!key[KEY_ESC]);

 datafiles_exit();
 return 0;
}

END_OF_MAIN();


// draw_fps:
//   draws a frames-per-second counter on the given bitmap
//
void draw_fps(BITMAP * bitmap, FONT * f, int x, int y)
{
 static unsigned fps_count;
 static unsigned fps;

 if (fps_count > FPS_DELAY)
   {
    if (retrace_count)
      fps = (unsigned)(FPS_DELAY*(70/(float)retrace_count));
    fps_count = 0;
    retrace_count = 0;
   }
 else
   ++fps_count;
 textprintf_ex(bitmap, f, x, y, -1, -1, "FPS: %u", fps);
}



// draw_backgrounds:
//   draws the game's parallax backgrounds on a window
//
void draw_backgrounds(WINDOW * win, DATAFILE * backdat, unsigned mapw, unsigned maph)
{
 #define BACKGROUND_COUNT  5  // calculate this later?

 RLE_SPRITE * paramap;
 BITMAP *     dest;
 int   i;
 int   c, startc, maxc;
 int   x, y;
 int   maxy, miny;
 float distance;
 int   h;
 int   start_pixel;

 if (win == NULL)
   return;

 dest = win->buffer;

 // draw the sky background
 draw_rle_sprite(dest, (RLE_SPRITE *)backdat[0].dat, 0, 0);

 // draw the other backgrounds (with parallax scrolling)
 i = 1;
 while (backdat[i].type == DAT_ID('R', 'L', 'E', ' '))
   {
    paramap = (RLE_SPRITE *)backdat[i].dat;

    distance = (float)(BACKGROUND_COUNT - i + 1);

    /*
    h = maph - i*5;
    y = (int)((win->buffer->h - h) * (1.0 - win->y/(float)(maph - win->buffer->h)));
    y = y + h - paramap->h;
    y = maph - paramap->h - 50 - (int)(win->y/distance);

    miny = win->buffer->h/2;
    maxy = maph - paramap->h;
    y = (int)((win->y/(float)win->buffer->h) * (maxy - miny) + miny);
    */

    y = maph - paramap->h - win->y - 40;

    // tile across x range
    start_pixel = (int)(win->x/distance);

    startc = (int)((start_pixel          ) / paramap->w);
    maxc =   (int)((start_pixel + dest->w) / paramap->w) + 1;

    for (c = startc; c != maxc; ++c)
      draw_rle_sprite(dest, paramap, (c*paramap->w) - start_pixel, y);

    ++i;
   }
}

