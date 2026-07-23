#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H
#include <unordered_map>
#include <vita2d.h>
#include <string>
#include <vector>
#include <psp2/io/fcntl.h>
#include <psp2/io/stat.h>

enum contentType{
    TEXTURE,
    AUDIO
};

struct pipelineOrder{
    std::string filename;
    contentType type;
};

class MemoryManager{
    private:
        static std::vector<pipelineOrder> addPipeline;
        static std::vector<pipelineOrder> remPipeline;
        static std::unordered_map<std::string,vita2d_texture*> textureMap;
    public:
        static void readPipelines();
        static void storeData(std::string filename, contentType type);
        static void removeData(std::string filename, contentType type);

};

#endif