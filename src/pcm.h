#ifndef __PCM_H__
#define __PCM_H__


typedef struct {
    int     sr;         //samplerate
    int     chs         //channels
    int     bits;       //bits persample
    int     fmt;        //format
}fmt_t;



int pcm_conv();





#endif

