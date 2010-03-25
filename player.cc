#include "player.h"
#include "weapon.h"
#include "error.h"
#include "data.h"


PLAYER::PLAYER()
{
 // load sprite bitmaps

 x = y = itofix(10);
 w = h = 0;

 speed = itofix(0);
 angle = 0;

 frame_count = 0;

 frames = NULL;
 win    = NULL;

 key_up    = NULL;
 key_down  = NULL;
 key_left  = NULL;
 key_right = NULL;
}



PLAYER::PLAYER(DATAFILE * playerdat)
{
 int i;

 x = y = itofix(10);

 speed = itofix(0);
 angle = 0;

 if (playerdat == NULL)
   error_quit("Unable to access player data file.", -1);

 // calculate frame_count
 frame_count = 0;
 while (playerdat[frame_count].type == DAT_ID('B', 'M', 'P', ' '))
   ++frame_count;

 // load frames of animation

 frames = new BITMAP *[frame_count];

 for (i = 0; i != frame_count; ++i)
   frames[i] = (BITMAP *)playerdat[i].dat;

 if (frame_count > 0)
   {
    w = MIN(frames[0]->w, frames[0]->h);
    h = w;
    valid = true;
   }
 else
   valid = false;
}



PLAYER::~PLAYER()
{
 if (win != NULL)
   delete win;

 if (frames != NULL)
   delete frames;
}



// update:
//   checks for keypresses, moves player
// returns:
//   non-zero if there is some error detected
//   zero otherwise
//
int PLAYER::update()
{
 // check for keys

 if (key[key_left])
   win->scroll(-1,  0);
 if (key[key_right])
   win->scroll( 1,  0);
 if (key[key_up])
   win->scroll( 0, -1);
 if (key[key_down])
   win->scroll( 0,  1);

 return 0;
}



// set_keys:
//   convenience function for setting all the player's keys at once
//
void PLAYER::set_keys(unsigned char newkey_up,   unsigned char newkey_down,
                      unsigned char newkey_left, unsigned char newkey_right)
{
 key_up    = newkey_up;
 key_down  = newkey_down;
 key_left  = newkey_left;
 key_right = newkey_right;
}



// draw:
//   draw the player on a window
//
void PLAYER::draw(WINDOW * win)
{
 if (win == NULL)
   return;

 if (frames == NULL)
   return;

 //rotate_sprite(win->buffer, frames[0], x - win->x - frames[0]->w/2,
 //                                      y - win->y - frames[0]->h/2, angle);
 draw_sprite(win->buffer, frames[1], x - win->x - frames[1]->w/2,
                                     y - win->y - frames[1]->h/2);
}



void PLAYER::set_window(WINDOW * newwin)
{
 win = newwin;
}
