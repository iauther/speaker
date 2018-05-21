#ifndef __SND_H__
#define __SND_H__

#include "portaudio.h"


enum {
    STAT_PLAY = 0,
    STAT_PAUSE,
    STAT_STOP,
};


typedef struct {
    int stat;
    PaStream *st;
    PaStreamParameters in;
    PaStreamParameters out;
}sound_t;


int snd_init();

int snd_open();

int snd_close();

int snd_read(void *data, int len);

int snd_write(void *data, int len);

int snd_set(int stat);

int snd_get(int *stat);

#endif

