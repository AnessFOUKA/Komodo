#include "MemoryManager.hpp"

#ifdef PLATFORM_3DS
    std::unordered_map<std::string, C2D_SpriteSheet> MemoryManager::spritesheets={};
    std::unordered_map<std::string,C2D_Image> MemoryManager::texturesMap={};
#endif

#ifdef PLATFORM_PSVITA
    std::unordered_map<std::string, vita2d_texture*> MemoryManager::texturesMap={};
#endif
std::unordered_map<std::string,stb_vorbis*> MemoryManager::audioMap={};

std::vector<MemoryPipelineOrder> MemoryManager::addPipeline={};
std::vector<MemoryPipelineOrder> MemoryManager::remPipeline={};

void MemoryManager::clearMemory(){
    for(auto& [path,texture] : texturesMap){
        #ifdef PLATFORM_3DS
        C2D_SpriteSheetFree(spritesheets[path]);
        spritesheets.erase(path);
        #endif
        #ifdef PLATFORM_PSVITA
        vita2d_free_texture(texture);
        #endif
        texturesMap.erase(path);
    }
}

void MemoryManager::readPipelines(){
    for(auto& addPipelineOrder : addPipeline){
        if(addPipelineOrder.type==TEXTURE){
            #ifdef PLATFORM_3DS
                std::string fullPath="romfs:/gfx/"+addPipelineOrder.path+".t3x";
                C2D_SpriteSheet newSpriteSheet=C2D_SpriteSheetLoad(fullPath.c_str());
                if(newSpriteSheet==NULL){
                    ErrorHandler::sendError(0,"Texture load failed.");
                    break;
                }
                spritesheets[addPipelineOrder.path]=newSpriteSheet;
                texturesMap[addPipelineOrder.path]=C2D_SpriteSheetGetImage(spritesheets[addPipelineOrder.path],0);
            #endif
            #ifdef PLATFORM_PSVITA
                std::string fullPath="app0:/gameFiles/gfx/"+addPipelineOrder.path;
                vita2d_texture* newTexture=vita2d_load_PNG_file(fullPath.c_str());
                if(newTexture==NULL){
                    ErrorHandler::sendError(0,"Texture load failed");
                    break;
                }
                texturesMap[addPipelineOrder.path]=newTexture;
            #endif
        }else if(addPipelineOrder.type==AUDIO){
            std::string fullPath="";
            #ifdef PLATFORM_PSVITA
            fullPath="app0:/gameFiles/audio/";
            #endif
            #ifdef PLATFORM_3DS
            fullPath="romfs:/audio/";
            #endif
            fullPath+=addPipelineOrder.path;
            int error=0;
            stb_vorbis* vorbis=stb_vorbis_open_filename(
                fullPath.c_str(),
                &error,
                nullptr
            );
            if(vorbis==nullptr){
                ErrorHandler::sendError(1,"Audio load failed.");
                break;
            }
            audioMap[addPipelineOrder.path]=vorbis;
        }
    }
    for(auto& remPipelineOrder : remPipeline){
        if(remPipelineOrder.type==TEXTURE){
            if(texturesMap.find(remPipelineOrder.path)==texturesMap.end()){
                ErrorHandler::sendError(2,"Texture not found");
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
        }else if(remPipelineOrder.type==AUDIO){
            if(audioMap.find(remPipelineOrder.path)==audioMap.end()){
                ErrorHandler::sendError(3,"Audio not found");
                break;
            }
            stb_vorbis_close(audioMap[remPipelineOrder.path]);
            audioMap.erase(remPipelineOrder.path);

        }
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
            return nullptr;
        }
        return &texturesMap[path];
    }

#endif

#ifdef PLATFORM_PSVITA
    vita2d_texture* MemoryManager::getTexture(std::string path){
        if(texturesMap.find(path)==texturesMap.end()){
            return nullptr;
        }
        return texturesMap[path];
    }
#endif

stb_vorbis* MemoryManager::getAudio(std::string path){
    return (audioMap.find(path)!=audioMap.end()?audioMap[path]:nullptr);
}