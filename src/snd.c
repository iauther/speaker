#include "snd.h"


#define SAMPLE_RATE         (44100)
#define FRAMES_PER_BUFFER   (512)



static sound_t *psnd=NULL;

static double standardSampleRates[] = {
    8000.0, 9600.0, 11025.0, 12000.0, 16000.0, 22050.0, 24000.0, 32000.0,
    44100.0, 48000.0, 88200.0, 96000.0, 192000.0, -1 /* negative terminated  list */
};



static void print_samplerates(const PaStreamParameters *in, const PaStreamParameters *out)
{
    int i,cnt;
    PaError err;

    for(i=0; standardSampleRates[i]>0; i++) {
        err = Pa_IsFormatSupported(in, put, standardSampleRates[i]);
        if(err == paFormatIsSupported) {
            printf("%8.2f\n", standardSampleRates[i]);
        }
    }
}



static void print_devinfo(PaDeviceInfo *p)
{
    printf("Name                        = %s\n",       p->name);
    printf("Host API                    = %s\n",       Pa_GetHostApiInfo(p->hostApi)->name);
    printf("Max inputs                  = %d",         p->maxInputChannels);
    printf("Max outputs                 = %d\n",       p->maxOutputChannels);
    printf("Default sample rate         = %8.2f\n",   p->defaultSampleRate);

    printf("Default low input latency   = %8.4f\n",    p->defaultLowInputLatency);
    printf("Default low output latency  = %8.4f\n",    p->defaultLowOutputLatency);
    printf("Default high input latency  = %8.4f\n",    p->defaultHighInputLatency);
    printf("Default high output latency = %8.4f\n",    p->defaultHighOutputLatency);
    
}


static void print_devinfo(PaStreamParameters *p)
{
    
}


static int print_device()
{
    PaError err;
    int     i, numDevices, defaultDisplayed;
    const   PaDeviceInfo *deviceInfo;
    PaStreamParameters inputParameters, outputParameters;
    
    numDevices = Pa_GetDeviceCount();
    if(numDevices < 0)
    {
        printf("ERROR: Pa_GetDeviceCount returned 0x%x\n", numDevices);
        err = numDevices;
        goto error;
    }
    
    printf("Number of devices = %d\n", numDevices);
    for(i=0; i<numDevices; i++)
    {
        deviceInfo = Pa_GetDeviceInfo(i);
        printf("--------------------------------------- device #%d\n", i);
                
   
        

}



static int print_all()
{
    PaError err;
    int     i, numDevices, defaultDisplayed;
    const   PaDeviceInfo *deviceInfo;
    PaStreamParameters inputParameters, outputParameters;
    
    numDevices = Pa_GetDeviceCount();
    if(numDevices < 0)
    {
        printf("ERROR: Pa_GetDeviceCount returned 0x%x\n", numDevices);
        err = numDevices;
        goto error;
    }
    
    printf("Number of devices = %d\n", numDevices);
    for(i=0; i<numDevices; i++)
    {
        deviceInfo = Pa_GetDeviceInfo(i);
        printf("--------------------------------------- device #%d\n", i);
                
   
        

}


/*
typedef int PaStreamCallback(
    const void *input, void *output,
    unsigned long frameCount,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *userData );
    
typedef void PaStreamFinishedCallback( void *userData );
    
    
*/

static int stream_allback(const void *inputBuffer, void *outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo* timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void *userData)
{
        
    return paContinue;  //paComplete, paAbort
}





static int snd_start()
{
    PaError err;
    
    if (!psnd) {
        return -1;
    }
    
    err = Pa_StartStream(psnd->st);
    if(err != paNoError) {
        return -1;
    }
    
    return 0;
}

static int snd_stop()
{
    PaError err;
    
    if (!psnd) {
        return -1;
    }
    
    Pa_AbortStream(psnd->st);
    
    return 0;
}




////////////////////////////////////////////////////////////

int snd_init()
{
    int i;
    PaError err;
    int numBytes;
    int numChannels;
    char *sampleBlock = NULL;
    PaDeviceInfo *pi,*po;
    PaStreamParameters *in,*out;
    
    psnd = calloc(1, sizeof(snd_t));
    if (!psnd) {
        return -1;
    }
    
    err = Pa_Initialize();
    if(err != paNoError)
    {
        printf("ERROR: Pa_Initialize returned 0x%x\n", err);
        free(psnd);
        return -1;
    }
    
    printf("PortAudio version: 0x%08X\n", Pa_GetVersion());
    printf("Version text: '%s'\n", Pa_GetVersionInfo()->versionText);
    
    psnd->in.paras.device = Pa_GetDefaultInputDevice(); /* default input device */
    pi = Pa_GetDeviceInfo(psnd->in.device);

    outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
    po = Pa_GetDeviceInfo(outputParameters.device);

    numChannels = pi->maxInputChannels < po->maxOutputChannels
            ? pi->maxInputChannels : po->maxOutputChannels;
    printf("Num channels = %d.\n", numChannels);
    
    in = &psnd->in;
    in->channelCount = numChannels;
    in->sampleFormat = PA_SAMPLE_TYPE;
    in->suggestedLatency = in->defaultHighInputLatency ;
    in->hostApiSpecificStreamInfo = NULL;

    out = &psnd->out;
    out->channelCount = numChannels;
    out->sampleFormat = PA_SAMPLE_TYPE;
    out->suggestedLatency = out->defaultHighOutputLatency;
    out->hostApiSpecificStreamInfo = NULL;
    
    return 0;
}



int snd_open()
{
    int i;
    PaError err;
    int numBytes;
    int numChannels;
    char *sampleBlock = NULL;
    
    if (!psnd) {
        return -1;
    }
    
    
    err = Pa_OpenStream(
              &psnd->st,
              &psnd->in,
              NULL,
              SAMPLE_RATE,
              FRAMES_PER_BUFFER,
              paClipOff,      /* we won't output out of range samples so don't bother clipping them */
              NULL, /* no callback, use blocking API */
              NULL); /* no callback, so no callback userData */
    if(err != paNoError)
        goto error2;
    
    //err = Pa_SetStreamFinishedCallback( PaStream *stream, PaStreamFinishedCallback* streamFinishedCallback ); 
    
    
    err = Pa_StartStream(stream);
    if(err != paNoError)
        goto error1;
    
    return 0;
    
}


int snd_close()
{
    if (!psnd) {
        return -1;
    }
    
    Pa_AbortStream(psnd->st);
    Pa_CloseStream(psnd->st);
    Pa_Terminate();
    return 0;
}


int snd_read(void *data, int len)
{
    PaError err;
    
    if (!psnd || !data || len<=0) {
        return -1;
    }
    
    err = Pa_ReadStream(psnd->st, data, 4);
    return err;
}


int snd_write(void *data, int len)
{
    PaError err;
    
    if (!psnd || !data || len<=0) {
        return -1;
    }
    
    err = Pa_WriteStream(psnd->st, data, 4);
    
    return err;
}



int snd_set(int stat)
{
    PaError err;
    
    if (!psnd) {
        return -1;
    }
    
    switch(stat) {
        
        case STAT_PLAY:
        snd_play();
        break;
        
        case STAT_PAUSE:
        //snd_pa();
        break;
        
        case STAT_STOP:
        snd_stop();
        break;
        
        default:
        return -1;
        
    }
    psnd->stat = stat;
    
    return 0;
}


int snd_get(int *stat)
{
    if (!psnd) {
        return -1;
    }
    
    if (stat) {
        *stat = psnd->stat;
    }
    
    return 0;
}
