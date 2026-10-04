#include "Controller.hpp"

std::unordered_map<std::string, std::vector<float>>* Controller::getKeysState(){
    return &keysState;
}

std::unordered_map<std::string, std::vector<float>>* Controller::getKeysFormerState(){
    return &keysFormerState;
}

std::unordered_map<std::string, std::vector<float>>* Controller::getDownKeys(){
    return &downKeys;
}