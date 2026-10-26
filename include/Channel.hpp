#ifndef CHANNEL_H
#define CHANNEL_H

//#define PLATFORM_PSVITA

#ifdef PLATFORM_3DS
#include <3ds.h>
#endif

#ifdef PLATFORM_PSVITA
#include <psp2/audioout.h>
#endif

#include "stb_vorbis.hpp"
#include <string>
#include <string.h>

struct AudioBuffer{
    int16_t* samples=NULL;
    int framesToPlay;
    #ifdef PLATFORM_3DS
    ndspWaveBuf ndspBuf;
    #endif
};

class Channel{
    #ifdef PLATFORM_3DS
    static bool ndspInitialized;
    static int maxChannelId;
    #endif
    int channelId;

    float volume;
    
    bool channelIdInitialized;

    AudioBuffer buffers[3];

    stb_vorbis* file;

    size_t bufferIndex;

    bool isPlaying;

    bool looping;

    int activeBuffers;
    
    int fillBuffer(stb_vorbis* vorbis, AudioBuffer* buffer);

    public:
    
        Channel():
            channelId(0),
            channelIdInitialized(false),
            bufferIndex(0),
            volume(1.0f),
            file(NULL),
            activeBuffers(3),
            looping(false)
        {}

        void init();
        void fini();

        int play(stb_vorbis* vorbis);
        void clearBuffers();
        int setTime(float second);
        void setVolume(float volumeLevel);
        void setIsPlaying(bool isPlaying);
        void loop();
        void setLooping(bool looping);
};

#endif