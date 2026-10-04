#ifndef CONTROLLERSMANAGER_H
#define CONTROLLERSMANAGER_H

#include "Controller.hpp"
#include <memory>

#ifdef PLATFORM_3DS
#include <3ds.h>
#endif

class ControllersManager{
    
    static std::unordered_map<std::string,std::unique_ptr<Controller>> controllers;

    public:

        static void addController(std::string controller_id, std::unique_ptr<Controller> controller);
        static void removeController(std::string controller_id);
        static std::vector<float>* getKeyState(std::string controller_id, std::string key_id);
        static std::vector<float>* getKeyDown(std::string controller_id, std::string key_id);
        static void updateControllersState();
};

#endif