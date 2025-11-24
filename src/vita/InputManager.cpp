#include <InputManager.h>

InputManager::InputManager(std::map<std::string,uint32_t> keys):
    keys(keys),
    keysStates()
{
    memset(&pad,0,sizeof(pad));
    for(auto& key : keys){
        keysStates[key.first]=true;
    }
}

bool InputManager::checkPressed(std::string keyId){
    return (pad.buttons & keys[keyId]);
}

bool InputManager::checkClicked(std::string keyId){
    bool isPressed=checkPressed(keyId);
    if(isPressed&&keysStates[keyId]){
        keysStates[keyId]=false;
        return true;
    }
    keysStates[keyId]=!isPressed;
    return false;
}

void InputManager::fetchInputs(){
    sceCtrlReadBufferPositive(0,&pad,1);
}