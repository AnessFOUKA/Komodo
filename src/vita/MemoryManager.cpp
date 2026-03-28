#include "MemoryManager.h"

std::map<std::string,vita2d_texture*> MemoryManager::getImgMem(){
    return imgMem;
}

void MemoryManager::addImg(std::string filename){
    SceIoStat stat;
    if(sceIoGetstat(filename.c_str(),&stat)<0){
        errorHandler->sendError(0,"file does not exist",true,false);
    }else{
        pipeline.push_back([this,filename](){
            imgMem[filename]=vita2d_load_PNG_file(filename.c_str());
        });
    }
}

void MemoryManager::removeImg(std::string filename){
    if(this->imgMem.find(filename)!=this->imgMem.end()){
        pipeline.push_back([this,filename](){
            vita2d_free_texture(imgMem[filename]);
            imgMem.erase(filename);
        });
    }else{
        errorHandler->sendError(1,"image hasn't been saved to vram",true,false);
    }
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
    if(this->imgMem.find(filename)!=this->imgMem.end()){
        return imgMem[filename];
    }else{
        errorHandler->sendError(1,"image hasn't been saved to vram",true,false);
        return nullptr;
    }
}

Script* MemoryManager::getScript(std::string scriptId){
    if(this->scriptsMem.find(scriptId)!=this->scriptsMem.end()){
        return scriptsMem[scriptId].get();
    }else{
        errorHandler->sendError(2,"script hasn't been added to ram",true,false);
        return nullptr;
    }
}

void MemoryManager::addScript(std::string scriptId,std::unique_ptr<Script> newScript){
    scriptsMem[scriptId]=std::move(newScript);
}
void MemoryManager::removeScript(std::string scriptId){
    if(this->scriptsMem.find(scriptId)!=this->scriptsMem.end()){
        scriptsMem.erase(scriptId);
    }else{
        errorHandler->sendError(2,"script hasn't been added to ram",true,false);
    }
}

void MemoryManager::clearMems(){
    for(auto& [imgId,texture] : imgMem){
        removeImg(imgId);
    }
    for(auto& [scriptId,script] : scriptsMem){
        removeScript(scriptId);
    }
}