#ifdef PLATFORM_3DS
#include <3ds.h>
#include <citro2d.h>
#include <pthread.h>
#endif

#ifdef PLATFORM_PSVITA
#include <vita2d.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/display.h>
#endif

#include "MemoryManager.hpp"
#include "ErrorHandler.hpp"

int main(){
    #ifdef PLATFORM_PSVITA
        vita2d_init();
        MemoryManager::readPipelines();
        while(true){
            ErrorHandler::sendError(0,"test",false,50,50);
            vita2d_start_drawing();
            vita2d_clear_screen();

            ErrorHandler::manageErrors();

            vita2d_end_drawing();
            sceDisplayWaitVblankStart();
            vita2d_swap_buffers();
        }
        vita2d_fini();
        sceKernelExitProcess(0);
    #endif

    #ifdef PLATFORM_3DS
        gfxInitDefault();
        C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
        C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
        C2D_Prepare();
        romfsInit();
        C3D_RenderTarget* up=C2D_CreateScreenTarget(GFX_TOP,GFX_LEFT);
        C3D_RenderTarget* bottom=C2D_CreateScreenTarget(GFX_BOTTOM,GFX_LEFT);
        MemoryManager::storeData("test",TEXTURE);
        MemoryManager::readPipelines();
        consoleInit(GFX_BOTTOM,NULL);
        printf("aaa");

        C2D_Font font=C2D_FontLoadSystem(CFG_REGION_EUR);
        C2D_TextBuf buff=C2D_TextBufNew(4096);
        C2D_Text text;

        C2D_TextFontParse(&text,font,buff,"test");
        C2D_TextOptimize(&text);
        while (aptMainLoop())
        {
            C2D_Image img=C2D_SpriteSheetGetImage(MemoryManager::getTexture("test"),0);
            ErrorHandler::sendError(0,"test",false,0,0);
            C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
            C2D_TargetClear(up,C2D_Color32(0,0,0,255));
            C2D_SceneBegin(up);
            
            ErrorHandler::manageErrors();
            //C2D_DrawImageAt(img,0,0,0,NULL,1.0f,1.0f);

            C3D_FrameEnd(0);
        }
        romfsExit();
        C2D_Fini();
        C3D_Fini();
        gfxExit();
    #endif
    return 0;
}