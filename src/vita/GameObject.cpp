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

std::vector<Camera*> GameObject::getCameras(){
    return cameras;
}
void GameObject::setCameras(std::vector<Camera*> cameras){
    this->cameras=cameras;
}