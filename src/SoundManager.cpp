#include "SoundManager.hpp"

Channel SoundManager::channels[10];
std::vector<AudioPipelineOrder> SoundManager::audioPipeline={};

void SoundManager::init(){
    for(size_t channelId=0; channelId<10; channelId++){
        channels[channelId].init();
    }
}

void SoundManager::fini(){
    for(size_t channelId=0; channelId<10; channelId++){
        channels[channelId].fini();
    }
}

void SoundManager::play(size_t channelId, std::string filePath){
    AudioPipelineOrder order={
        .orderType=0,
        .channelId=channelId,
        .filePath=filePath,
        .second=0
    };
    audioPipeline.push_back(order);
}

void SoundManager::executePipeline(){
    for(auto& audioPipelineOrder : audioPipeline){
        if(audioPipelineOrder.orderType==0){
            if(audioPipelineOrder.channelId>=0 && audioPipelineOrder.channelId<10){
                stb_vorbis* vorbis=MemoryManager::getAudio(audioPipelineOrder.filePath);
                if(vorbis!=nullptr){
                    int error=channels[audioPipelineOrder.channelId].play(vorbis);
                    if(error!=0){
                        std::string errorsStrings[2]={"audio buffers allocation failed","uncompatible amount of channels"};
                        int errorsCodes[2]={10,11};
                        ErrorHandler::sendError(errorsCodes[(error*(-1))-1],errorsStrings[(error*(-1))-1]);
                    }
                }else{
                    ErrorHandler::sendError(3,"Audio not found");
                }
            }else{
                ErrorHandler::sendError(7,"out of range channelId"); 
            }   
        }else{
            if(audioPipelineOrder.channelId>=0 && audioPipelineOrder.channelId<10){
                int error=channels[audioPipelineOrder.channelId].setTime(audioPipelineOrder.second);
                if(error!=0){
                    std::string errorsStrings[2]={"out of range time data","Audio not found"};
                    int errorsCodes[2]={8,3};
                    ErrorHandler::sendError(errorsCodes[(error*(-1))-1],errorsStrings[(error*(-1))-1]);
                }
            }else{
                ErrorHandler::sendError(7,"out of range channelId"); 
            }
        }
    }
    audioPipeline={};
}

void SoundManager::loop(){
    for(size_t channelId=0; channelId<10; channelId++){
        channels[channelId].loop();
    }
}
void SoundManager::setTime(size_t channelId, float second){
    AudioPipelineOrder order={
        .orderType=1,
        .channelId=channelId,
        .filePath="",
        .second=second
    };
    audioPipeline.push_back(order);
}
void SoundManager::setVolume(size_t channelId, float volumeLevel){
    if(channelId>=0 && channelId<10){
        channels[channelId].setVolume(volumeLevel);
    }else{
       ErrorHandler::sendError(7,"out of range channelId"); 
    }
}
void SoundManager::setIsPlaying(size_t channelId, bool isPlaying){
    if(channelId>=0 && channelId<10){
        channels[channelId].setIsPlaying(isPlaying);
    }else{
       ErrorHandler::sendError(7,"out of range channelId"); 
    }
}
void SoundManager::setLooping(size_t channelId, bool looping){
    if(channelId>=0 && channelId<10){
        channels[channelId].setLooping(looping);
    }else{
       ErrorHandler::sendError(7,"out of range channelId"); 
    }
}