#ifndef _HEAD4MAD_TS_SIMPLEST_PLAYER_H
#define _HEAD4MAD_TS_SIMPLEST_PLAYER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <sys/soundcard.h> 
# include <sys/ioctl.h>     
# include <sys/fcntl.h>     
# include <sys/types.h>     
# include <mad.h>  
#include <stdbool.h>
#include <pthread.h> 

#include "SDL.h"

# define WIDTH  800
# define HEIGHT 480
# define BPP    32

struct buffer
{     
    unsigned char const *start;     
    unsigned long length;     
};     


int decode(unsigned char const *start, unsigned long length);
int getsfd();

#endif