#include "MemoryManager.hpp"

#ifdef PLATFORM_3DS
    std::unordered_map<std::string, C2D_SpriteSheet> MemoryManager::spritesheets={};
    std::unordered_map<std::string,C2D_Image> MemoryManager::texturesMap={};
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
            C2D_SpriteSheet newSpriteSheet=C2D_SpriteSheetLoad(fullPath.c_str());
            if(newSpriteSheet==NULL){
                ErrorHandler::sendError(0,"Texture load failed.");
                break;
            }
            spritesheets[addPipelineOrder.path]=newSpriteSheet;
            texturesMap[addPipelineOrder.path]=C2D_SpriteSheetGetImage(spritesheets[addPipelineOrder.path],0);
        #endif
        #ifdef PLATFORM_PSVITA
            std::string fullPath="app0:/gameFiles/gfx/"+addPipelineOrder.path+".png";
            vita2d_texture* newTexture=vita2d_load_PNG_file(fullPath.c_str());
            if(newTexture==NULL){
                ErrorHandler::sendError(0,"Texture load failed");
                break;
            }
            texturesMap[addPipelineOrder.path]=newTexture;
        #endif
    }
    for(auto& remPipelineOrder : remPipeline){
        if(texturesMap.find(remPipelineOrder.path)==texturesMap.end()){
            ErrorHandler::sendError(1,"Texture not found");
            break;
        }
        #ifdef PLATFORM_3DS
            C2D_SpriteSheetFree(spritesheets[remPipelineOrder.path]);
            spritesheets.erase(remPipelineOrder.path);
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
    C2D_Image* MemoryManager::getTexture(std::string path){
        if(texturesMap.find(path)==texturesMap.end()){
            ErrorHandler::sendError(1,"Texture not found");
            return nullptr;
        }
        return &texturesMap[path];
    }
#endif

#ifdef PLATFORM_PSVITA
    vita2d_texture* MemoryManager::getTexture(std::string path){
        if(texturesMap.find(path)==texturesMap.end()){
            ErrorHandler::sendError(1,"Texture not found");
            return nullptr;
        }
        return texturesMap[path];
    }
#endif