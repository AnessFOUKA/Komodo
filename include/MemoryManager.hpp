#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#ifdef PLATFORM_3DS
    #include <3ds.h>
    #include <citro2d.h>
#endif

#ifdef PLATFORM_PSVITA
    #include <vita2d.h>
#endif

#include <vector>
#include <unordered_map>
#include <string>

enum DataType{
    TEXTURE,
    AUDIO
};

struct MemoryPipelineOrder{
    std::string path;
    DataType type;
};

class MemoryManager{
    private:
        #ifdef PLATFORM_3DS
            static std::unordered_map<std::string,C2D_SpriteSheet> texturesMap;
        #endif
        #ifdef PLATFORM_PSVITA
            static std::unordered_map<std::string,vita2d_texture*> texturesMap;
        #endif
        static std::vector<MemoryPipelineOrder> addPipeline;
        static std::vector<MemoryPipelineOrder> remPipeline;
    public:
        static void readPipelines();
        static void storeData(std::string path, DataType type);
        static void removeData(std::string path, DataType type);
        #ifdef PLATFORM_3DS
            static C2D_SpriteSheet getTexture(std::string path);
        #endif
        #ifdef PLATFORM_PSVITA
            static vita2d_texture* getTexture(std::string path);
        #endif
};

#endif