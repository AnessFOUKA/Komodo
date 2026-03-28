#include "GameObject.h"
std::vector<std::string>* GameObject::getIdsList(){
    return &idsList;
}

void GameObject::setIdsList(std::vector<std::string> idsList){
    this->idsList=idsList;
}

std::vector<std::string>* GameObject::getScriptsIds(){
    return &scriptsIds;
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

ItemHandler* GameObject::getMother(){
    return mother;
}

void GameObject::setMother(ItemHandler* mother){
    this->mother=mother;
}

Game* GameObject::getGameInstance(){
    return gameInstance;
}

void GameObject::setGameInstance(Game* gameInstance){
    this->gameInstance=gameInstance;
}

bool GameObject::addScript(std::string scriptId,MemoryManager* memoryManager){
    Script* scriptPointer=memoryManager->getScript(scriptId);
    if(scriptPointer==nullptr){
        return false;
    }
    Script newScript=*(scriptPointer);
    newScript.setMother(this);
    this->scriptsList.push_back(newScript);
    return true;
}

std::vector<Camera*>* GameObject::getCameras(){
    return &cameras;
}
void GameObject::setCameras(std::vector<Camera*> cameras){
    this->cameras=cameras;
}

int GameObject::getArrayId(){
    return arrayId;
}

void GameObject::setArrayId(int arrayId){
    this->arrayId=arrayId;
}