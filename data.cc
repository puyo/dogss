#include "data.h"

#include <stdio.h>
#include "error.h"


DATAFILE * paldat    = NULL;
DATAFILE * backdat   = NULL;
DATAFILE * fontdat   = NULL;
DATAFILE * playerdat = NULL;


// datafiles_init:
//   loads all the game datafiles, quitting with an error if one can't be
//   loaded
//
void datafiles_init()
{
 paldat = load_datafile("data/palette.dat");
 if (paldat == NULL)
   error_quit("Unable to load palette datafile \"data\\palette.dat\".", -1);

 backdat = load_datafile("data/bckgrnds.dat");
 if (backdat == NULL)
   error_quit("Unable to load background datafile \"data\\backgrnds.dat\".", -1);

 fontdat = load_datafile("data/fonts.dat");
 if (backdat == NULL)
   error_quit("Unable to load font datafile \"data\\fonts.dat\".", -1);

 playerdat = load_datafile("data/plane.dat");
 if (playerdat == NULL)
   error_quit("Unable to load player datafile \"data\\plane.dat\".", -1);
}



// datafiles_exit:
//   unloads all the game datafiles
//
void datafiles_exit()
{
 if (paldat != NULL)
   unload_datafile(paldat);

 if (backdat != NULL)
   unload_datafile(backdat);

 if (fontdat != NULL)
   unload_datafile(fontdat);

 if (playerdat != NULL)
   unload_datafile(playerdat);
}


