#include "Game.h"

MemoryManager* Game::getMemoryManager(){
    return &mainMemoryManager;
}

vita2d_pvf* Game::getPvf(){
    return pvf;
}

ErrorHandler* Game::getMainErrorHandler(){
    return &mainErrorHandler;
}

void Game::gameLoop(){
    vita2d_init();
    pvf=vita2d_load_default_pvf();
    while(1){
        mainMemoryManager.readPipeline();
        mainInputManager.fetchInputs();
        vita2d_start_drawing();
        vita2d_clear_screen();
        if(!mainErrorHandler.getShowErrorScreen()){
            step();
            readGraphicPipeline();
        }
        mainErrorHandler.manageErrors();
        vita2d_end_drawing();
        sceDisplayWaitVblankStart();
        vita2d_swap_buffers();
        high_resolution_clock::time_point currentTime=high_resolution_clock::now();
        dt=std::chrono::duration<float>(currentTime-previousTime).count();
        previousTime=currentTime;
    }
    vita2d_free_pvf(pvf);
    mainMemoryManager.clearMems();
    mainMemoryManager.readPipeline();
    vita2d_fini();
    sceKernelExitProcess(0);
}

bool Game::addItem(std::unique_ptr<GameObject> newObject,ItemHandler* itemHandler){
    newObject->setGameInstance(this);
    newObject->setMother(itemHandler);
    newObject->setArrayId(itemHandler->getElements()->size());
    std::vector<Camera*> newObjectCameras=*(newObject->getCameras());
    std::vector<Camera*> itemHandlerCameras=*(itemHandler->getCameras());
    itemHandlerCameras.insert(itemHandlerCameras.end(),newObjectCameras.begin(),newObjectCameras.end());
    newObject->setCameras(itemHandlerCameras);
    for(std::string i : *(newObject->getScriptsIds())){
        if(!newObject->addScript(i,&mainMemoryManager)){
            return false;
        }
    }
    itemHandler->getAddPipeline()->push_back(std::move(newObject));
    return true;
}
bool Game::removeItem(int index,ItemHandler* itemHandler){
    if(!(index>=0&&index<itemHandler->getElements()->size())){
        this->mainErrorHandler.sendError(5,"index out of itemHandler index plage",true,false);
        return false;
    }
    itemHandler->getRemPipeline()->push_back(index);
    return true;
    //NETTOYER LA DONNÉE EN INDEX S'IL S'AGIT D'UN ITEMHANDLER
}

InputManager* Game::getMainInputManager(){
    return &mainInputManager;
}

std::map<int,std::unordered_map<std::string,std::vector<GraphicOrder>>>* Game::getGraphicPipeline(){
    return &graphicPipeline;
}

void Game::addGraphicOrder(std::string imgId,float x,float y,float imageX,float imageY,float imageWidth,float imageHeight,float scaleX,float scaleY,float alpha,int layer){
    GraphicOrder graphicOrder={x,y,imageX,imageY,imageWidth,imageHeight,scaleX,scaleY,alpha,layer};
    if(graphicPipeline.find(layer)==graphicPipeline.end()){
        //graphicPipeline[imgId].push_back(graphicOrder);
        graphicPipeline[layer]={};
    }
    if(graphicPipeline[layer].find(imgId)==graphicPipeline[layer].end()){
        graphicPipeline[layer][imgId]={};
    }
    graphicPipeline[layer][imgId].push_back(graphicOrder);

        //graphicPipeline[imgId]={graphicOrder};
}

void Game::readGraphicPipeline(){
    for(auto& [layer,layerPipeline] : graphicPipeline){
        for(auto& [imgId,pipeGraphicOrders]: layerPipeline){
            for(auto& order : pipeGraphicOrders){
                vita2d_texture* tex=mainMemoryManager.getImg(imgId);
                if(tex!=nullptr){
                    vita2d_draw_texture_tint_part_scale(tex,order.x,order.y,order.imageX,order.imageY,order.imageWidth,order.imageHeight,order.scaleX,order.scaleY,RGBA8(255,255,255,static_cast<int>(order.alpha*255)));
                }
            }
        }
    }
    graphicPipeline.clear();
    /*for(auto& [imgId, pipeGraphicOrders] : graphicPipeline){
        for(auto& order : pipeGraphicOrders){
            vita2d_texture* tex=mainMemoryManager.getImg(imgId);
            if(tex!=nullptr){
                vita2d_draw_texture_tint_part_scale(tex,order.x,order.y,order.imageX,order.imageY,order.imageWidth,order.imageHeight,order.scaleX,order.scaleY,RGBA8(255,255,255,static_cast<int>(order.alpha*255)));
            }
        }
    }
    graphicPipeline.clear();*/
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

void Camera::pushCameraGraphicOrder(std::string imgId,float x,float y,float imageX,float imageY,float imageWidth,float imageHeight,float scaleX,float scaleY,float alpha,int layer,Game* gameInstance){
    for(auto renderer : renderers){
        float rendererX=renderer[0];
        float rendererY=renderer[1];
        float rendererWidth=renderer[2];
        float rendererHeight=renderer[3];
        if(detectInbound(x,y,imageWidth*scaleX,imageHeight*scaleY,cameraX,cameraY,rendererWidth,rendererHeight)){
            float worldX=x-(cameraX-rendererX);
            float worldY=y-(cameraY-rendererY);
            float imageXTemp=imageX;
            float imageYTemp=imageY;
            float imageWidthTemp=imageWidth;
            float imageHeightTemp=imageHeight;

            if(worldX<rendererX){
                float overflow=rendererX-worldX;
                float downscaledOverflow=overflow/scaleX;
                imageXTemp+=downscaledOverflow;
                imageWidthTemp-=downscaledOverflow;
                worldX=rendererX;
            }

            if(worldY<rendererY){
                float overflow=rendererY-worldY;
                float downscaledOverflow=overflow/scaleY;
                imageYTemp+=downscaledOverflow;
                imageHeightTemp-=downscaledOverflow;
                worldY=rendererY;
            }

            if(worldX+imageWidthTemp*scaleX>rendererX+rendererWidth){
                float overflow=(worldX+imageWidthTemp*scaleX)-(rendererX+rendererWidth);
                imageWidthTemp-=(overflow/scaleX);
            }

            if(worldY+imageHeightTemp*scaleY>rendererY+rendererHeight){
                float overflow=(worldY+imageHeightTemp*scaleY)-(rendererY+rendererHeight);
                imageHeightTemp-=(overflow/scaleY);
            }

            gameInstance->addGraphicOrder(imgId,worldX,worldY,imageXTemp,imageYTemp,imageWidthTemp,imageHeightTemp,scaleX,scaleY,alpha,layer);
        }
    }
}

bool Script::checkCondition(float conditionIndex){
    if(conditionMap.find((int)conditionIndex)==conditionMap.end()){
        mother->getGameInstance()->getMainErrorHandler()->sendError(3,"condition hasn't been added to condition table",true,false);
        return false;
    }
    bool conditionState=conditionMap[(int)conditionIndex];
    conditionMap[(int)conditionIndex]=false;
    return conditionState;
}

getFileJSONReturn ItemHandler::getFileJSON(std::string filename){
    getFileTextReturn fileText=getFileText(filename);
    if(fileText.error.size()>0){
        gameInstance->getMainErrorHandler()->sendError(6,fileText.error,true,false);
        return {json::object(),true};
    }
    try{
        json fileJson=json::parse(fileText.text);
        return {fileJson,false};
    }catch(json::parse_error& e){
        gameInstance->getMainErrorHandler()->sendError(6,"json parse error :"+std::string(e.what()),true,false);
        return {json::object(),true};
    }catch(json::type_error& e){
        gameInstance->getMainErrorHandler()->sendError(7,"json type error :"+std::string(e.what()),true,false);
        return {json::object(),true};
    }
}
//ajouter un return type capable de stocker des erreurs pour getFileJSON
void ItemHandler::injectJson(
    std::string filename,
    std::map<std::string,std::function<std::unique_ptr<GameObject>(json*)>> callbackMap,
    ItemHandler* itemHandler,
    json* jsonToInject
){
    try{
        itemHandler=(itemHandler!=nullptr?itemHandler:this);
        json workJson=json::object();
        if(jsonToInject!=nullptr){
            workJson=*jsonToInject;
        }else{
            getFileJSONReturn parsedJsonFile=getFileJSON(filename);
            if(!parsedJsonFile.error){
                workJson=parsedJsonFile.success;
            }
        }
        //json workJson=(jsonToInject!=nullptr?*jsonToInject:getFileJSON(filename));
        if(workJson.is_object()){
            for(auto it=workJson.begin();it!=workJson.end();it++){
                if(callbackMap.find(it.key())!=callbackMap.end()){
                    json objGroup=it.value();
                    std::unique_ptr<GameObject> objToAdd=nullptr;
                    if(objGroup.contains("coords")&&objGroup.at("coords").is_object()){
                        for(auto coordGroup=objGroup.at("coords").begin();coordGroup!=objGroup.at("coords").end();coordGroup++){
                            json xCoords=json::parse(coordGroup.key());
                            json yCoords=coordGroup.value();
                            //faire gaffe à ce qu'il s'agisse de nombres
                            for(auto& xCoord : xCoords){
                                for(auto& yCoord : yCoords){
                                    if(xCoord.is_number()&&yCoord.is_number()){
                                        json objToPass=objGroup;
                                        objToPass["x"]=xCoord;
                                        objToPass["y"]=yCoord;
                                        objToAdd=callbackMap[it.key()](&objToPass);
                                        ItemHandler* target=dynamic_cast<ItemHandler*>(objToAdd.get());
                                        if(objToPass.contains("elements")&&target!=nullptr){
                                            injectJson(filename,callbackMap,target,&objToPass["elements"]);
                                        }else if(target!=nullptr){
                                            gameInstance->getMainErrorHandler()->sendError(11,"'elements' hasn't been defined",true,false);
                                        }
                                        gameInstance->addItem(std::move(objToAdd),itemHandler);
                                    }else{
                                        gameInstance->getMainErrorHandler()->sendError(12,"coordinates must be numbers",true,false);
                                    }
                                }
                            }
                        }
                    }else if(objGroup.contains("coords")){
                        gameInstance->getMainErrorHandler()->sendError(10,"coords must be an object with arrays as keys and values(those as keys must be writted as stringified jsons)",true,false);
                    }else{
                        objToAdd=callbackMap[it.key()](&objGroup);
                        ItemHandler* target=dynamic_cast<ItemHandler*>(objToAdd.get());
                        if(objGroup.contains("elements")&&target!=nullptr){
                            injectJson(filename,callbackMap,target,&objGroup["elements"]);
                        }else if(target!=nullptr){
                            gameInstance->getMainErrorHandler()->sendError(11,"'elements' hasn't been defined",true,false);
                        }
                        gameInstance->addItem(std::move(objToAdd),itemHandler);
                    }
                }else{
                    gameInstance->getMainErrorHandler()->sendError(9,"itemId does not exist in callbackMap",true,false);
                }
            }
        }else{
            gameInstance->getMainErrorHandler()->sendError(8,"a map json must be an object with callbackMapIds as keys and object attributes as values",true,false);
        }
    }catch(json::parse_error& e){
        gameInstance->getMainErrorHandler()->sendError(6,"json parse error :"+std::string(e.what()),true,false);
    }catch(json::type_error& e){
        gameInstance->getMainErrorHandler()->sendError(7,"json type error :"+std::string(e.what()),true,false);
    }
}