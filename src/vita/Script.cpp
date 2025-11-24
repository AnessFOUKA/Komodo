#include "Script.h"

std::function<void(Script*)> Script::getScriptFunction(){
    return scriptFunction;
}
float Script::getBeginIndex(){
    return beginIndex;
}
float Script::getIndex(){
    return index;
}
float Script::getEndIndex(){
    return endIndex;
}
bool Script::getLoop(){
    return loop;
}

void Script::setScriptFunction(std::function<void(Script*)> scriptFunction){
    this->scriptFunction=scriptFunction;
};
void Script::setBeginIndex(float beginIndex){
    this->beginIndex=beginIndex;
};
void Script::setIndex(float index){
    this->index=index;
};
void Script::setEndIndex(float endIndex){
    this->endIndex=endIndex;
};
void Script::setLoop(bool loop){
    this->loop=loop;
};

GameObject* Script::getMother(){
    return mother;
}

void Script::setMother(GameObject* mother){
    this->mother=mother;
}

float Script::getScriptSpeed(){
    return scriptSpeed;
}

void Script::setScriptSpeed(float scriptSpeed){
    this->scriptSpeed=scriptSpeed;
}