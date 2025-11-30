#include "Game.h"

MemoryManager* Game::getMemoryManager(){
    return &mainMemoryManager;
}

void Game::gameLoop(){
    vita2d_init();
    while(1){
        mainMemoryManager.readPipeline();
        mainInputManager.fetchInputs();
        vita2d_start_drawing();
        vita2d_clear_screen();
        step();
        readGraphicPipeline();
        vita2d_end_drawing();
        sceDisplayWaitVblankStart();
        vita2d_swap_buffers();
        high_resolution_clock::time_point currentTime=high_resolution_clock::now();
        dt=std::chrono::duration<float>(currentTime-previousTime).count();
        previousTime=currentTime;
    }
    vita2d_fini();
    sceKernelExitProcess(0);
}

void Game::addItem(GameObject* newObject,ItemHandler* itemHandler){
    newObject->setGameInstance(this);
    newObject->setMother(itemHandler);
    std::vector<Camera*> newObjectCameras=newObject->getCameras();
    std::vector<Camera*> itemHandlerCameras=itemHandler->getCameras();
    itemHandlerCameras.insert(itemHandlerCameras.end(),newObjectCameras.begin(),newObjectCameras.end());
    newObject->setCameras(itemHandlerCameras);
    for(std::string i : newObject->getScriptsIds()){
        newObject->addScript(i,&mainMemoryManager);
    }
    itemHandler->getAddPipeline()->push_back([itemHandler,newObject](){
        itemHandler->getElements()->push_back(newObject);
    });
}
void Game::removeItem(int index,ItemHandler* itemHandler){
    itemHandler->getRemPipeline()->push_back(index);
    //NETTOYER LA DONNÉE EN INDEX S'IL S'AGIT D'UN ITEMHANDLER
}

InputManager* Game::getMainInputManager(){
    return &mainInputManager;
}

std::unordered_map<std::string,std::vector<GraphicOrder>> Game::getGraphicPipeline(){
    return graphicPipeline;
}

void Game::addGraphicOrder(std::string imgId,int x,int y,int imageX,int imageY,int imageWidth,int imageHeigth){
    GraphicOrder graphicOrder={x,y,imageX,imageY,imageWidth,imageHeigth};
    if(graphicPipeline.find(imgId)!=graphicPipeline.end()){
        graphicPipeline[imgId].push_back(graphicOrder);
    }else{
        graphicPipeline[imgId]={graphicOrder};
        imgIds.push_back(imgId);
    }
}

void Game::readGraphicPipeline(){
    for(auto& [imgId, pipeGraphicOrders] : graphicPipeline){
        for(auto& order : pipeGraphicOrders){
            vita2d_draw_texture_part_scale(mainMemoryManager.getImg(imgId),order.x,order.y,order.imageX,order.imageY,order.imageWidth,order.imageHeigth,1,1);
        }
    }
    graphicPipeline.clear();
    imgIds.clear(); // si imgIds n'est utilisé que pour stocker les clés
}


float Game::getDt(){
    return dt;
}

void Script::loadScript(){
    if(index<=endIndex){
        scriptFunction(this);
        index+=scriptSpeed*static_cast<Game*>(mother->getGameInstance())->getDt();
    }else if(loop){
        index=beginIndex;
    }
};

void Camera::pushCameraGraphicOrder(std::string imgId,int x,int y,int imageX,int imageY,int imageWidth,int imageHeigth,Game* gameInstance){
    for(auto renderer : renderers){
        int rendererX=renderer[0];
        int rendererY=renderer[1];
        int rendererWidth=renderer[2];
        int rendererHeigth=renderer[3];
        if(detectInbound(x,y,imageWidth,imageHeigth,rendererX,rendererY,rendererWidth,rendererHeigth)){
            int worldXTemp=x-(cameraX-rendererX);
            int worldYTemp=y-(cameraY-rendererY);
            int imageXTemp=imageX;
            int imageYTemp=imageY;
            int imageWidthTemp=imageWidth;
            int imageHeigthTemp=imageHeigth;

            if(worldXTemp<rendererX){
                int overflow=rendererX-worldXTemp;
                imageXTemp+=overflow;
                imageWidthTemp-=overflow;
                worldXTemp=rendererX;
            }

            if(worldYTemp<rendererY){
                int overflow=rendererY-worldYTemp;
                imageYTemp+=overflow;
                imageHeigthTemp-=overflow;
                worldYTemp=rendererY;
            }

            if(worldXTemp+imageWidthTemp>rendererX+rendererWidth){
                int overflow=(worldXTemp+imageWidthTemp)-(rendererX+rendererWidth);
                imageWidthTemp-=overflow;
            }

            if(worldYTemp+imageHeigthTemp>rendererY+rendererHeigth){
                int overflow=(worldYTemp+imageHeigthTemp)-(rendererY+rendererHeigth);
                imageHeigthTemp-=overflow;
            }

            gameInstance->addGraphicOrder(imgId,worldXTemp,worldYTemp,imageXTemp,imageYTemp,imageWidthTemp,imageHeigthTemp);

        }
    }
}