#include "error.h"

#include <allegro.h>
#include <stdio.h>


// error_cont:
//   prints an error message to stderr
void error_cont(const char * message)
{
 fprintf(stderr, "\nError: %s\n", message);
}



// error_quit:
//   prints an error message to stderr then quits with the given return value
//
void error_quit(const char * message, int code)
{
 error_cont(message);
 set_gfx_mode(GFX_TEXT, 80, 25, 0, 0);
 exit(code);
}
