#include "ItemHandler.h"
std::vector<std::unique_ptr<GameObject>>* ItemHandler::getElements(){
    return &elements;
}

//

std::vector<std::unique_ptr<GameObject>>* ItemHandler::getAddPipeline(){
    return &addPipeline;
}

std::vector<int>* ItemHandler::getRemPipeline(){
    return &remPipeline;
}

void ItemHandler::readPipelines(){
    while(addPipeline.size()>0){
        elements.push_back(std::move(addPipeline[0]));
        addPipeline.erase(addPipeline.begin());
    }
    std::sort(remPipeline.begin(),remPipeline.end());
    for(int i=remPipeline.size()-1;i>=0;i--){
        elements.erase(elements.begin()+remPipeline[i]);
    }
    remPipeline={};
}

std::vector<GameObject*> ItemHandler::getElementById(std::string id){
    std::vector<GameObject*> gameObjectsList={};
    for(auto& i : elements){
        std::vector<std::string> list=*(i->getIdsList());
        if(std::find(list.begin(),list.end(),id)!=list.end()){
            gameObjectsList.push_back(i.get());
        }
    }
    return gameObjectsList;
}

float ItemHandler::getX(){
    return x;
}
float ItemHandler::getY(){
    return y;
}
        
void ItemHandler::setX(float x){
    this->x=x;
}
void ItemHandler::setY(float y){
    this->y=y;
}

float ItemHandler::getGlobalX(){
    return globalX;
}
float ItemHandler::getGlobalY(){
    return globalY;
}

void ItemHandler::setScaleX(float scaleX){
    this->scaleX=scaleX;
}

void ItemHandler::setScaleY(float scaleY){
    this->scaleY=scaleY;
}

float ItemHandler::getScaleX(){
    return scaleX;
}

float ItemHandler::getScaleY(){
    return scaleY;
}

float ItemHandler::getGlobalScaleX(){
    return globalScaleX;
}

float ItemHandler::getGlobalScaleY(){
    return globalScaleY;
}

void ItemHandler::step(){
    readPipelines();
    ItemHandler* motherConverted=dynamic_cast<ItemHandler*>(mother);
    globalX=x;
    globalY=y;
    globalScaleX=scaleX;
    globalScaleY=scaleY;
    if(motherConverted!=nullptr){
        globalX*=motherConverted->getGlobalScaleY();
        globalY*=motherConverted->getGlobalScaleY();
        globalX+=motherConverted->getGlobalX();
        globalY+=motherConverted->getGlobalY();
        globalScaleX*=motherConverted->getGlobalScaleX();
        globalScaleY*=motherConverted->getGlobalScaleY();
    }
   GameObject::step();
   for(int i=0;i<elements.size();i++){
    GameObject* element=elements[i].get();
    element->setArrayId(i);
    if(element->getIsJustCreated()){
        element->create();
        element->setIsJustCreated(false);
    }
    element->step();
   }
}