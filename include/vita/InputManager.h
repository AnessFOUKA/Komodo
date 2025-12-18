#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include "Collider.h"
class InputManager{
    private:
        std::map<std::string,uint32_t> keys;
        std::map<std::string,bool> keysStates;
        SceCtrlData pad;
    public:
        //PAS DE GETTER NI DE SETTER RISQUE DE SÉCURITÉ
        InputManager(std::map<std::string,uint32_t> keys);  
        void fetchInputs();
        bool checkPressed(std::string keyId);
        bool checkClicked(std::string keyId);
};
#endif