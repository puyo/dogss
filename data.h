#ifndef _DATA_H_
#define _DATA_H_


#include <allegro.h>

extern DATAFILE * paldat;
extern DATAFILE * backdat;
extern DATAFILE * fontdat;
extern DATAFILE * playerdat;


void datafiles_init();
void datafiles_exit();


#endif
