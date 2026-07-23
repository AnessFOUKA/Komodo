#include "MemoryManager.hpp"

std::vector<pipelineOrder> MemoryManager::addPipeline={};
std::vector<pipelineOrder> MemoryManager::remPipeline={};
std::unordered_map<std::string,vita2d_texture*> MemoryManager::textureMap={};

void MemoryManager::readPipelines(){
    for(auto& addOrder : addPipeline){
        if(addOrder.type==TEXTURE){
            textureMap[addOrder.filename]=vita2d_load_PNG_file(addOrder.filename.c_str());
        }
    }
    for(auto& remOrder : remPipeline){
        if(remOrder.type==TEXTURE){
            vita2d_free_texture(textureMap[remOrder.filename]);
            textureMap.erase(remOrder.filename);
        }
    }
    addPipeline={};
    remPipeline={};
}

void MemoryManager::storeData(std::string filename, contentType type){
    addPipeline.push_back({filename,type});
}

void MemoryManager::removeData(std::string filename, contentType type){
    remPipeline.push_back({filename,type});
}