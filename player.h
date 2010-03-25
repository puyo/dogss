#ifndef _PLAYER_H_
#define _PLAYER_H_


#include <allegro.h>
#include "object.h"
#include "dogtypes.h"
#include "weapon.h"
#include "colours.h"
#include "window.h"


class PLAYER : public OBJECT
{
public:
 unsigned char key_up;
 unsigned char key_down;
 unsigned char key_left;
 unsigned char key_right;

 PLAYER();
 PLAYER(DATAFILE * playerdat);
 ~PLAYER();

 int  update();
 //void draw(BITMAP * dest, int xoff, int yoff);
 void draw(WINDOW * win);

 void move();
 void attack();

 void set_colour(COLOUR newcolour)   { colour = newcolour; }
 void set_window(WINDOW * win);
 void set_keys(unsigned char newkey_up, unsigned char newkey_down, unsigned char newkey_left, unsigned char newkey_right);
 WINDOW * get_window() { return win; }

 bool is_player() { return true; }

protected:

 // velocity
 fixed speed;
 ANGLE angle;

 // weapon
// WEAPON weapon;

 // other
 //unsigned score;
 COLOUR colour;

 BITMAP ** frames;
 int frame_count;

 unsigned mapw, maph;

 // window
 WINDOW * win;
};


#endif
