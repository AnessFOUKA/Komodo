#include "MemoryManager.hpp"

#ifdef PLATFORM_3DS
    std::unordered_map<std::string, C2D_SpriteSheet> MemoryManager::texturesMap={};
#endif

#ifdef PLATFORM_PSVITA
    std::unordered_map<std::string, vita2d_texture*> MemoryManager::texturesMap={};
#endif

std::vector<MemoryPipelineOrder> MemoryManager::addPipeline={};
std::vector<MemoryPipelineOrder> MemoryManager::remPipeline={};

void MemoryManager::readPipelines(){
    for(auto& addPipelineOrder : addPipeline){
        #ifdef PLATFORM_3DS
            std::string fullPath="romfs:/gfx/"+addPipelineOrder.path+".png.t3x";
            texturesMap[addPipelineOrder.path]=C2D_SpriteSheetLoad(fullPath.c_str());
        #endif
        #ifdef PLATFORM_PSVITA
            std::string fullPath="app0:/gameFiles/gfx/"+addPipelineOrder.path+".png";
            texturesMap[addPipelineOrder.path]=vita2d_load_PNG_file(fullPath.c_str());
        #endif
    }
    for(auto& remPipelineOrder : remPipeline){
        #ifdef PLATFORM_3DS
            C2D_SpriteSheetFree(texturesMap[remPipelineOrder.path]);
            texturesMap.erase(remPipelineOrder.path);
        #endif
        #ifdef PLATFORM_PSVITA
            vita2d_free_texture(texturesMap[remPipelineOrder.path]);
            texturesMap.erase(remPipelineOrder.path);
        #endif
    }
    addPipeline={};
    remPipeline={};
}

void MemoryManager::storeData(std::string path, DataType type){
    addPipeline.push_back({path,type});
}

void MemoryManager::removeData(std::string path, DataType type){
    remPipeline.push_back({path,type});
}

#ifdef PLATFORM_3DS
    C2D_SpriteSheet MemoryManager::getTexture(std::string path){
        return texturesMap[path];
    }
#endif

#ifdef PLATFORM_PSVITA
    vita2d_texture* MemoryManager::getTexture(std::string path){
        return texturesMap[path];
    }
#endif