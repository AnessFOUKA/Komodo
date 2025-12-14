#include "ItemHandler.h"
std::vector<GameObject*>* ItemHandler::getElements(){
    return &elements;
}

void ItemHandler::setElements(std::vector<GameObject*> elements){
    this->elements=elements;
}

void ItemHandler::step(){
    readPipelines();
    for(auto& i:scriptsList){
        i.loadScript();
    }
    /*for(GameObject* i : elements){
        if(i->getIsJustCreated()){
            i->create();
            i->setIsJustCreated(false);
        }
        i->step();
    }*/
   for(int i=0;i<elements.size();i++){
    GameObject* element=elements[i];
    element->setArrayId(i);
    if(element->getIsJustCreated()){
        element->create();
        element->setIsJustCreated(false);
    }
    element->step();
   }
}

std::vector<std::function<void()>>* ItemHandler::getAddPipeline(){
    return &addPipeline;
}

std::vector<int>* ItemHandler::getRemPipeline(){
    return &remPipeline;
}

void ItemHandler::itemRemover(int itemId){
    GameObject* obj=elements[itemId];
    ItemHandler* trueTypeObj=dynamic_cast<ItemHandler*>(obj);
    if(trueTypeObj){
        for(int i=trueTypeObj->getElements()->size()-1;i>=0;i--){
            trueTypeObj->itemRemover(i);
        }
    }
    elements.erase(elements.begin()+itemId);
    delete obj;
}

void ItemHandler::readPipelines(){
    while(addPipeline.size()>0){
        addPipeline[0]();
        addPipeline.erase(addPipeline.begin());
    }
    std::sort(remPipeline.begin(),remPipeline.end());
    for(int i=remPipeline.size()-1;i>=0;i--){
        itemRemover(remPipeline[i]);
    }
    remPipeline={};
}

std::vector<GameObject*> ItemHandler::getElementById(std::string id){
    std::vector<GameObject*> gameObjectsList={};
    for(auto* i : elements){
        std::vector<std::string> list=i->getIdsList();
        if(std::find(list.begin(),list.end(),id)!=list.end()){
            gameObjectsList.push_back(i);
        }
    }
    return gameObjectsList;
}