#include "ControllersManager.hpp"

std::unordered_map<std::string,std::unique_ptr<Controller>> ControllersManager::controllers={};

void ControllersManager::addController(std::string controller_id, std::unique_ptr<Controller> controller){
    controllers[controller_id]=std::move(controller);
}

void ControllersManager::removeController(std::string controller_id){
    controllers.erase(controller_id);
}

std::vector<float>* ControllersManager::getKeyState(std::string controller_id, std::string key_id){
    auto controller=controllers.find(controller_id);
    if(controller!=controllers.end()){
        auto keys=(*controller->second->getKeysState()).find(key_id);
        if(keys!=controller->second->getKeysState()->end()){
            return &keys->second;
        }else{
            return nullptr;
        }
    }else{
        return nullptr;
    }
}

void ControllersManager::updateControllersState(){
    for(auto& [controller_id, controller] : controllers){
        controller->updateKeysState();
    }
}

std::vector<float>* ControllersManager::getKeyDown(std::string controller_id, std::string key_id){
    auto controller=controllers.find(controller_id);
    if(controller!=controllers.end()){
        auto keys=(*controller->second->getDownKeys()).find(key_id);
        if(keys!=controller->second->getDownKeys()->end()){
            return &keys->second;
        }else{
            return nullptr;
        }
    }else{
        return nullptr;
    }
}