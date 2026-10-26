#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include "Channel.hpp"
#include "ErrorHandler.hpp"
#include <vector>

struct AudioPipelineOrder{
    int8_t orderType;
    size_t channelId=0;
    std::string filePath="";
    float second=0;

};

class SoundManager{
    static Channel channels[10];
    static std::vector<AudioPipelineOrder> audioPipeline;
    public:
        static void init();
        static void fini();
        static void play(size_t channelId, std::string filePath);
        static void executePipeline();
        static void loop();
        static void setTime(size_t channelId, float second);
        static void setVolume(size_t channelId, float volumeLevel);
        static void setIsPlaying(size_t channelId, bool isPlaying);
        static void setLooping(size_t channelId, bool looping);
};

#endif