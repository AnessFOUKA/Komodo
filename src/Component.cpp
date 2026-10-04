#include "Component.hpp"

size_t Component::getArrayId(){
    return arrayId;
}
void Component::setArrayId(size_t arrayId){
    this->arrayId=arrayId;
}

GameObject* Component::getParent(){
    return parent;
}
void Component::setParent(GameObject* parent){
        this->parent=parent;
}