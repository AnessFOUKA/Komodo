#include "Game.h"

MemoryManager* Game::getMemoryManager(){
    return &mainMemoryManager;
}

void Game::gameLoop(){
    vita2d_init();
    vita2d_pgf* pgf=vita2d_load_default_pgf();
    while(1){
        mainMemoryManager.readPipeline();
        mainInputManager.fetchInputs();
        vita2d_start_drawing();
        vita2d_clear_screen();
        if(mainInputManager.checkClicked("cross")){
            vita2d_pgf_draw_text(pgf,50,50,RGBA8(255,255,255,255),1.0f,std::to_string(elements.size()).c_str());
        }
        step();
        readGraphicPipeline();
        vita2d_end_drawing();
        sceDisplayWaitVblankStart();
        vita2d_swap_buffers();
        high_resolution_clock::time_point currentTime=high_resolution_clock::now();
        dt=std::chrono::duration<float>(currentTime-previousTime).count();
        previousTime=currentTime;
    }
    vita2d_free_pgf(pgf);
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

std::map<std::string,std::vector<std::function<void()>>> Game::getGraphicPipeline(){
    return graphicPipeline;
}

void Game::addGraphicOrder(std::string imgId,int x,int y,int imageX,int imageY,int imageWidth,int imageHeigth,float scaleX,float scaleY){
    std::function<void()> graphicOrder=[this,imgId,x,y,imageX,imageY,imageWidth,imageHeigth,scaleX,scaleY](){
        vita2d_draw_texture_part_scale(mainMemoryManager.getImg(imgId),x,y,imageX,imageY,imageWidth,imageHeigth,scaleX,scaleY);
    };
    if(graphicPipeline.find(imgId)!=graphicPipeline.end()){
        graphicPipeline[imgId].push_back(graphicOrder);
    }else{
        graphicPipeline[imgId]={graphicOrder};
        imgIds.push_back(imgId);
    }
}

void Game::readGraphicPipeline(){
    while(graphicPipeline.size()!=0){
        std::vector<std::function<void()>> pipeGraphicOrders=graphicPipeline[imgIds[0]];
        while(pipeGraphicOrders.size()!=0){
            pipeGraphicOrders[0]();
            pipeGraphicOrders.erase(pipeGraphicOrders.begin());
        }
        graphicPipeline.erase(imgIds[0]);
        imgIds.erase(imgIds.begin());
    }
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

void Camera::pushCameraGraphicOrder(std::string imgId,int x,int y,int imageX,int imageY,int imageWidth,int imageHeigth,float scaleX,float scaleY,Game* gameInstance){
    for(auto renderer : renderers){
        int rendererX=renderer[0];
        int rendererY=renderer[1];
        int rendererWidth=renderer[2];
        int rendererHeigth=renderer[3];
        if(detectInbound(x,y,imageWidth*scaleX,imageHeigth*scaleY,rendererX,rendererY,rendererWidth,rendererHeigth)){
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

            if(worldXTemp+imageWidthTemp*scaleX>rendererX+rendererWidth){
                int overflow=(worldXTemp+imageWidthTemp*scaleX)-(rendererX+rendererWidth);
                imageWidthTemp-=(overflow/scaleX);
            }

            if(worldYTemp+imageHeigthTemp*scaleY>rendererY+rendererHeigth){
                int overflow=(worldYTemp+imageHeigthTemp*scaleY)-(rendererY+rendererHeigth);
                imageHeigthTemp-=(overflow/scaleY);
            }

            gameInstance->addGraphicOrder(imgId,worldXTemp,worldYTemp,imageXTemp,imageYTemp,imageWidthTemp,imageHeigthTemp,scaleX,scaleY);

        }
    }
}