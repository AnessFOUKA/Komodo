#include "GameObject.h"
std::vector<std::string> GameObject::getIdsList(){
    return idsList;
}

void GameObject::setIdsList(std::vector<std::string> idsList){
    this->idsList=idsList;
}

std::vector<std::string> GameObject::getScriptsIds(){
    return scriptsIds;
}

void GameObject::create(){

}

void GameObject::step(){
    for(auto& i:scriptsList){
        i.loadScript();
    }
}

bool GameObject::getIsJustCreated(){
    return isJustCreated;
}

void GameObject::setIsJustCreated(bool isJustCreated){
    this->isJustCreated=isJustCreated;
}

GameObject* GameObject::getMother(){
    return mother;
}

void GameObject::setMother(GameObject* mother){
    this->mother=mother;
}

GameObject* GameObject::getGameInstance(){
    return gameInstance;
}

void GameObject::setGameInstance(GameObject* gameInstance){
    this->gameInstance=gameInstance;
}

void GameObject::addScript(std::string scriptId,MemoryManager* memoryManager){
    Script newScript=*(memoryManager->getScript(scriptId));
    newScript.setMother(this);
    this->scriptsList.push_back(newScript);
}

std::vector<GameObject*>* GameObject::getElements(){
    return nullptr;
}

void GameObject::setElements(std::vector<GameObject*> elements){

}

MemoryManager* GameObject::getMemoryManager(){
    return nullptr;
}

void GameObject::gameLoop(){
    
}

std::vector<std::function<void()>>* GameObject::getAddPipeline(){
    return nullptr;
}

std::vector<int>* GameObject::getRemPipeline(){
    return nullptr;
}

void GameObject::readPipelines(){

}

void GameObject::addItem(GameObject* newObject,ItemHandler* itemHandler){

}

void GameObject::removeItem(int index,ItemHandler* itemHandler){

}

std::map<std::string,std::vector<std::function<void()>>> GameObject::getGraphicPipeline(){
    return {};
}

void GameObject::addGraphicOrder(std::string imgId,int x,int y,int imageX,int imageY,int imageWidth,int imageHeigth,float scaleX,float scaleY){

}

void GameObject::readGraphicPipeline(){

}


std::string GameObject::getImgId(){
    return "";
}
int GameObject::getX(){
    return 0;
}
int GameObject::getY(){
    return 0;
}
std::vector<std::vector<int>> GameObject::getImageCoords(){
    return {};
}
float GameObject::getImageCoordsIndex(){
    return 0.0f;
}
float GameObject::getAnimationSpeed(){
    return 0.0f;
}

void GameObject::setImgId(std::string imgId){}
void GameObject::setX(int x){}
void GameObject::setY(int y){}
void GameObject::setImageCoords(std::vector<std::vector<int>> imageCoords){}
void GameObject::setImageCoordsIndex(float imageCoordsIndex){}
void GameObject::setAnimationSpeed(float animationSpeed){}

float GameObject::getScaleX(){
    return 0.0f;
}
float GameObject::getScaleY(){
    return 0.0f;
}

void GameObject::setScaleX(float scaleX){
}
void GameObject::setScaleY(float scaleY){
}

std::vector<Camera*> GameObject::getCameras(){
    return cameras;
}
void GameObject::setCameras(std::vector<Camera*> cameras){
    this->cameras=cameras;
}

void Script::loadScript(){
    if(index<=endIndex){
        scriptFunction(this);
        index+=scriptSpeed*mother->getGameInstance()->getDt();
    }else if(loop){
        index=beginIndex;
    }
};

float GameObject::getDt(){
    return 0.0f;
}