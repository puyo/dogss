#include "object.h"
#include "error.h"


OBJECT::OBJECT()
{
 x = itofix(0);
 y = itofix(0);
 w = 0;
 h = 0;

 valid = false;
}



// update:
//   updates a game object (this is a deferred function)
//
int OBJECT::update()
{
 error_cont("Object of type OBJECT updated.");
 return 0;
}



// draw:
//   draws a game object (this is a deferred function)
void OBJECT::draw(BITMAP * bitmap)
{

}



// is_player:
//   returns whether or not this object is a player
bool OBJECT::is_player()
{
 return false;
}
