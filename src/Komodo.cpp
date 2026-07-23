#include "Komodo.hpp"

bool Komodo::isRunning=true;

void Komodo::graphicPipeline(){
    #ifdef _PSVITA
        vita2d_start_drawing();
        vita2d_clear_screen();

        vita2d_end_drawing();
        sceDisplayWaitVblankStart();
        vita2d_swap_buffers();
    #endif
}

void Komodo::gameloop(){
    #ifdef _PSVITA
        vita2d_init();
        while (isRunning)
        {
            MemoryManager::readPipelines();
            graphicPipeline();   
        }
        vita2d_fini();
        sceKernelExitProcess(0);    
    #endif
}