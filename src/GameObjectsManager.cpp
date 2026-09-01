
#include "GameObjectsManager.hpp"

GameObject GameObjectsManager::mothernode({});

GameObject* GameObjectsManager::getMothernode(){
    return &mothernode;
}

void GameObjectsManager::addChild(std::unique_ptr<GameObject> child, GameObject* parent){
    parent->getObjectsPipeline()->add.push_back(std::move(child));
}

void GameObjectsManager::remChild(GameObject* child, GameObject* parent){
    parent->getObjectsPipeline()->rem.push_back(child);
}

void GameObjectsManager::addComponent(std::unique_ptr<Component> component, GameObject* child){
    child->getComponentPipeline()->add.push_back(std::move(component));
}

void GameObjectsManager::remComponent(Component* component, GameObject* child){
    child->getComponentPipeline()->rem.push_back(component);
}

void GameObject::updateObjectsArrayIds(){
    for(size_t childIndex=0; childIndex<hyerarchy.getChilds()->size();childIndex++){
        GameObject* child=(*hyerarchy.getChilds())[childIndex].get();
        child->setArrayId(arrayId);
    }
}