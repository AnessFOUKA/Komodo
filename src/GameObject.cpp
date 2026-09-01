#include "GameObject.hpp"
#include "GraphicsManager.hpp"

size_t GameObject::getArrayId(){
    return arrayId;
}

Hyerarchy::Hyerarchy():
    childs(),
    parent(nullptr)
{}

ObjectManagementPipeline<GameObject>* GameObject::getObjectsPipeline(){
    return &objectsPipeline;
}

std::vector<std::unique_ptr<GameObject>>* Hyerarchy::getChilds(){
    return &childs;
}

GameObject* Hyerarchy::getParent(){
    return parent;
}

void Hyerarchy::manageChilds(){
    for(auto& child : childs){
        child->loop();
    }
}

void GameObject::loop(){
    if(!ErrorHandler::getInterrupt()){
        onLoop();
        manageObjectsPipeline();
        updateObjectsArrayIds();
        manageComponentsPipeline();
        updateComponentsArrayIds();
        for(auto& component : components){
            component->onLoop();
        }
        hyerarchy.manageChilds();
    }
}

void Hyerarchy::setParent(GameObject* parent){
    this->parent=parent;
}

void GameObject::setArrayId(size_t arrayId){
    this->arrayId=arrayId;
}

std::vector<std::string>* GameObject::getIds(){
    return &ids;
}

Hyerarchy* GameObject::getHyerarchy(){
    return &hyerarchy;
}

void GameObject::onCreate(){}

void GameObject::onLoop(){
}

Component::Component(GameObject* parent):
    parent(parent),
    arrayId(0)
{}

void GameObject::onRemove(){}

std::vector<std::unique_ptr<Component>>* GameObject::getComponents(){
    return &components;
}

ObjectManagementPipeline<Component>* GameObject::getComponentPipeline(){
    return &componentPipeline;
}

void GameObject::manageComponentsPipeline(){
    for(auto& linkOrder : componentPipeline.add){
        linkOrder->setArrayId(components.size());
        linkOrder->setParent(this);
        components.push_back(std::move(linkOrder));
        components[components.size()-1]->onLink();
    }

    std::sort(componentPipeline.rem.begin(),componentPipeline.rem.end(),[](Component* component1,Component* component2){
        return component2->getArrayId()<component1->getArrayId();
    });

    for(auto& unlinkOrder : componentPipeline.rem){
        size_t arrayId=unlinkOrder->getArrayId();
        if(arrayId>=0 && arrayId<components.size()){
            unlinkOrder->onUnlink();
            components.erase(components.begin()+unlinkOrder->getArrayId());
        }else{
            ErrorHandler::sendError(4, "index out of bounds");
        }
    }
    componentPipeline.add.clear();
    componentPipeline.rem.clear();
}

void GameObject::updateComponentsArrayIds(){
    for(size_t componentIndex=0; componentIndex<components.size();componentIndex++){
        components[componentIndex]->setArrayId(componentIndex);
    }
}

void GameObject::manageObjectsPipeline(){
    for(auto& addOrder : objectsPipeline.add){
        addOrder->setArrayId(hyerarchy.getChilds()->size());
        addOrder->getHyerarchy()->setParent(this);
        hyerarchy.getChilds()->push_back(std::move(addOrder));
        (*hyerarchy.getChilds())[hyerarchy.getChilds()->size()-1]->onCreate();
    }

    std::sort(objectsPipeline.rem.begin(),objectsPipeline.rem.end(),[](const GameObject* order1,const GameObject* order2){
        return order2->arrayId<order1->arrayId;
    });

    for(auto& remOrder : objectsPipeline.rem){
        size_t arrayId=remOrder->getArrayId();
        if(arrayId>=0 && arrayId<hyerarchy.getChilds()->size()){
            remOrder->onRemove();
            hyerarchy.getChilds()->erase(hyerarchy.getChilds()->begin()+remOrder->getArrayId());
        }else{
            ErrorHandler::sendError(4, "index out of bounds");
        }
    }
    objectsPipeline.add.clear();
    objectsPipeline.rem.clear();
}