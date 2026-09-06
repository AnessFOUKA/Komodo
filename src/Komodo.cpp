#include "Komodo.hpp"

bool Komodo::run=true;

std::chrono::high_resolution_clock::time_point Komodo::oldTime=std::chrono::high_resolution_clock::now();
std::chrono::high_resolution_clock::time_point Komodo::currentTime=std::chrono::high_resolution_clock::now();
float Komodo::dt = 0;

float Komodo::getDt(){
    return dt;
}

void Komodo::init(){
    ControllersManager::addController("std_controller",std::make_unique<StdController>());
    #ifdef PLATFORM_3DS
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();
    romfsInit();

    #endif
    #ifdef PLATFORM_PSVITA
    vita2d_init();
    #endif
}

void Komodo::gameloop(){
    while(run
        #ifdef PLATFORM_3DS
            && aptMainLoop()
        #endif
    ){
        
        oldTime=currentTime;
        currentTime=std::chrono::high_resolution_clock::now();
        dt=std::chrono::duration<float>(currentTime-oldTime).count();

        ControllersManager::updateControllersState();
        MemoryManager::readPipelines();
        GameObjectsManager::getMothernode()->loop();
        GraphicsManager::executeGraphicPipeline();
        ErrorHandler::manageErrors();  
    }
}

void Komodo::fini(){
    #ifdef PLATFORM_3DS
    romfsExit();
    C2D_Fini();
    C3D_Fini();
    gfxExit();
    #endif
    #ifdef PLATFORM_PSVITA
    vita2d_fini();
    sceKernelExitProcess(0);
    #endif
}

bool Komodo::getRun(){
    return run;
}

void Komodo::setRun(bool run){
    Komodo::run=run;
}