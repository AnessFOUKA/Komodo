#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H
#include "Script.h"
class MemoryManager{
    protected:
        std::map<std::string,vita2d_texture*> imgMem;
        std::map<std::string,std::unique_ptr<Script>> scriptsMem;
        std::vector<std::function<void()>> pipeline;
    public:
        MemoryManager():
            imgMem(),
            scriptsMem(),
            pipeline()
        {}
        Script* getScript(std::string scriptId);
        vita2d_texture* getImg(std::string filename);
        std::map<std::string,vita2d_texture*> getImgMem();
        std::vector<std::function<void()>> getPipeline();
        void addImg(std::string filename);
        void removeImg(std::string filename);
        void addScript(std::string scriptId,std::unique_ptr<Script> newScript);
        void removeScript(std::string scriptId);
        void readPipeline();
        void clearMems();
        //on ajoute pas de setter pour img mem pipeline pour des raisons de sécurité
};
#endif