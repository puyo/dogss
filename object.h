#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <allegro.h>


class OBJECT
{
public:

 bool valid;

 OBJECT();
 virtual int  update();
 virtual void draw(BITMAP * bitmap);

 virtual bool is_player();

protected:

 // position and size
 fixed x;
 fixed y;

 unsigned w;
 unsigned h;
};


#endif
