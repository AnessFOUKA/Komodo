#include "Channel.hpp"

int Channel::fillBuffer(stb_vorbis* vorbis, AudioBuffer* buffer){
    stb_vorbis_info vorbisInfo=stb_vorbis_get_info(vorbis);
    int samplesNum=48000*vorbisInfo.channels;

    int frames=stb_vorbis_get_samples_short_interleaved(
        vorbis,
        vorbisInfo.channels,
        buffer->samples,
        samplesNum
    );

    if(frames<0){
        return 0;
    }

    #ifdef PLATFORM_3DS
    buffer->ndspBuf.nsamples=frames;
    buffer->ndspBuf.data_vaddr=buffer->samples;
    buffer->ndspBuf.looping=false;
    #endif

    return frames;
}

#ifdef PLATFORM_3DS
bool Channel::ndspInitialized=false;
int Channel::maxChannelId=0;
#endif

void Channel::init(){
    #ifdef PLATFORM_3DS
    if(!ndspInitialized){
        ndspInit();
        ndspSetOutputMode(NDSP_OUTPUT_STEREO);
        ndspInitialized=true;
    }
    #endif
    if(!channelIdInitialized){
        #ifdef PLATFORM_3DS
        channelId=maxChannelId;
        maxChannelId++;
        #endif
        #ifdef PLATFORM_PSVITA
        channelId=sceAudioOutOpenPort(
            SCE_AUDIO_OUT_PORT_TYPE_MAIN,
            48000,
            48000,
            SCE_AUDIO_OUT_MODE_STEREO
        );
        #endif
        channelIdInitialized=true;
    }
}

void Channel::fini(){
    #ifdef PLATFORM_3DS
    if(ndspInitialized){
        ndspExit();
        ndspInitialized=false;
    }
    #endif
    #ifdef PLATFORM_PSVITA
    if(channelIdInitialized){
        sceAudioOutReleasePort(channelId);
        channelIdInitialized=false;
    }
    #endif
    clearBuffers();
}

int Channel::play(stb_vorbis* vorbis){
    clearBuffers();
    #ifdef PLATFORM_3DS
    ndspChnWaveBufClear(channelId);
    #endif
    file=nullptr;
    bufferIndex=0;
    activeBuffers=3;
    if(vorbis!=NULL){
        stb_vorbis_info vorbisInfo=stb_vorbis_get_info(vorbis);
        if(vorbisInfo.channels==1 || vorbisInfo.channels==2){
            bool allocationError=false;
            memset(buffers,0,sizeof(buffers));
            for(size_t bufferId=0; bufferId<3; bufferId++){
                #ifdef PLATFORM_3DS
                buffers[bufferId].samples=static_cast<int16_t*>(
                    linearAlloc(48000*vorbisInfo.channels*sizeof(int16_t))
                );
                #endif
                #ifdef PLATFORM_PSVITA
                buffers[bufferId].samples=static_cast<int16_t*>(
                    calloc(48000*vorbisInfo.channels,sizeof(int16_t))
                );
                #endif

                if(buffers[bufferId].samples==NULL){
                    allocationError=true;
                    break;
                }

                #ifdef PLATFORM_3DS
                memset(&buffers[bufferId].ndspBuf,0,sizeof(ndspWaveBuf));
                buffers[bufferId].ndspBuf.status=NDSP_WBUF_DONE;
                #endif
            }
            if(!allocationError){
                stb_vorbis_seek_start(vorbis);
                #ifdef PLATFORM_3DS
                ndspChnReset(channelId);
                ndspChnSetRate(channelId,48000);
                ndspChnSetFormat(
                    channelId,
                    vorbisInfo.channels==1?NDSP_FORMAT_MONO_PCM16:NDSP_FORMAT_STEREO_PCM16
                );
                #endif
                #ifdef PLATFORM_PSVITA
                sceAudioOutSetConfig(
                    channelId,
                    48000,
                    48000,
                    vorbisInfo.channels==1?SCE_AUDIO_OUT_MODE_MONO:SCE_AUDIO_OUT_MODE_STEREO
                );
                #endif
                for(size_t bufferId=0; bufferId<2; bufferId++){
                    buffers[bufferId].framesToPlay=fillBuffer(vorbis,&buffers[bufferId]);
                }
                file=vorbis;
                isPlaying=true;
            }else{
                return -1;
            }
        }else{
            return -2;
        }
    }else{
        return -3;
    }
    return 0;
}

void Channel::clearBuffers(){
    for(size_t bufferId=0; bufferId<3; bufferId++){
        if(buffers[bufferId].samples!=NULL){
            #ifdef PLATFORM_3DS
            linearFree(buffers[bufferId].samples);
            #endif
            #ifdef PLATFORM_PSVITA
            free(buffers[bufferId].samples);
            #endif
            buffers[bufferId].samples=NULL;
        }
    }
}

void Channel::loop(){
    if(file!=NULL && isPlaying){
        stb_vorbis_info vorbisInfo=stb_vorbis_get_info(file);
        bool bufferPlaying;
        #ifdef PLATFORM_3DS
        bufferPlaying=buffers[0].ndspBuf.status!=NDSP_WBUF_DONE;
        for(size_t bufferId=1; bufferId<3; bufferId++){
            bufferPlaying=bufferPlaying || buffers[bufferId].ndspBuf.status!=NDSP_WBUF_DONE;
        }
        #endif
        #ifdef PLATFORM_PSVITA
        bufferPlaying=sceAudioOutGetRestSample(channelId)!=0;
        #endif

        if(!bufferPlaying && activeBuffers>0){
            activeBuffers-=buffers[bufferIndex].framesToPlay==0;
            #ifdef PLATFORM_3DS
            ndspChnWaveBufAdd(channelId,&buffers[bufferIndex].ndspBuf);
            #endif
            #ifdef PLATFORM_PSVITA
            sceAudioOutOutput(channelId,buffers[bufferIndex].samples);
            #endif
            if(bufferIndex==0){
                buffers[2].framesToPlay=fillBuffer(file,&buffers[2]);
            }else{
                buffers[bufferIndex-1].framesToPlay=fillBuffer(file,&buffers[bufferIndex-1]);
            }

            bufferIndex++;

            if(bufferIndex>2){
                bufferIndex=0;
            }
        }else if(!bufferPlaying){
            if(looping){
                setTime(0);
                activeBuffers=3;
            }else{
                isPlaying=false;
            }
        }
    }
}

void Channel::setIsPlaying(bool isPlaying){
    this->isPlaying=isPlaying;
}

int Channel::setTime(float second){
    if(file!=NULL){
        if(second>=0 && second<=stb_vorbis_stream_length_in_seconds(file)){
            #ifdef PLATFORM_3DS
            ndspChnWaveBufClear(channelId);
            #endif
            stb_vorbis_seek_frame(file,48000*second);
            bufferIndex=0;
            for(size_t bufferId=0; bufferId<2; bufferId++){
                buffers[bufferId].framesToPlay=fillBuffer(file,&buffers[bufferId]);
            }
        }else{
            return -1;
        }
    }else{
        return -2;
    }
    return 0;
}

void Channel::setVolume(float volumeLevel){
    if(volumeLevel<0.0f){
        volumeLevel=0.0f;
    }else if(volumeLevel>1.0f){
        volumeLevel=1.0f;
    }
    volume=volumeLevel;
    #ifdef PLATFORM_3DS
    float mix[12]={volume,volume};
    ndspChnSetMix(channelId,mix);
    #endif
    #ifdef PLATFORM_PSVITA
    int volumes[2]={
        static_cast<int>(volume*SCE_AUDIO_OUT_MAX_VOL),
        static_cast<int>(volume*SCE_AUDIO_OUT_MAX_VOL)
    };
    sceAudioOutSetVolume(
        channelId,
        static_cast<SceAudioOutChannelFlag>(SCE_AUDIO_VOLUME_FLAG_L_CH|SCE_AUDIO_VOLUME_FLAG_R_CH),
        volumes
    );
    #endif
}

void Channel::setLooping(bool looping){
    this->looping=looping;
}