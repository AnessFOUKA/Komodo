#include "MemoryManager.h"

std::map<std::string,vita2d_texture*> MemoryManager::getImgMem(){
    return imgMem;
}

void MemoryManager::addImg(std::string filename){
    pipeline.push_back([this,filename](){
        imgMem[filename]=vita2d_load_PNG_file(filename.c_str());
    });
}

void MemoryManager::removeImg(std::string filename){
    pipeline.push_back([this,filename](){
        vita2d_free_texture(imgMem[filename]);
        imgMem.erase(filename);
    });
}

std::vector<std::function<void()>> MemoryManager::getPipeline(){
    return pipeline;
}

void MemoryManager::readPipeline(){
    while(pipeline.size()>0){
        pipeline[0]();
        pipeline.erase(pipeline.begin()+0);
    }
}

vita2d_texture* MemoryManager::getImg(std::string filename){
    return imgMem[filename];
}

Script* MemoryManager::getScript(std::string scriptId){
    return scriptsMem[scriptId];
}

void MemoryManager::addScript(std::string scriptId,Script* newScript){
    scriptsMem[scriptId]=newScript;
}
void MemoryManager::removeScript(std::string scriptId){
    Script* script=scriptsMem[scriptId];
    scriptsMem.erase(scriptId);
    delete script;
}

void MemoryManager::clearMems(){
    for(auto& [imgId,texture] : imgMem){
        removeImg(imgId);
    }
    for(auto& [scriptId,script] : scriptsMem){
        removeScript(scriptId);
    }
}