#ifndef KOMODO_H
#define KOMODO_H

#include <chrono>

#ifdef PLATFORM_3DS
#include <3ds.h>
#include <citro2d.h>
#endif

#ifdef PLATFORM_PSVITA
#include <vita2d.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/display.h>
#endif

#include "MemoryManager.hpp"
#include "ErrorHandler.hpp"
#include "GraphicsManager.hpp"
#include "GameObject.hpp"
#include "GameObjectsManager.hpp"
#include "ControllersManager.hpp"
#include "StdController.hpp"

class Komodo{
    static bool run;
    static std::chrono::high_resolution_clock::time_point oldTime;
    static std::chrono::high_resolution_clock::time_point currentTime;
    static float dt;
    public:
        static bool getRun();
        static void setRun(bool run);

        static void init();
        static void gameloop();
        static void fini();
        static float getDt();
};

#endif