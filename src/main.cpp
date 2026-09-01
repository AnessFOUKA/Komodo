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

class Test : public Component{
    public:
        Test(GameObject* parent):
            Component(parent)
        {}

        void onLink(){}
        void onUnlink(){}
        void onLoop(){
            GraphicsManager::drawText({"eee"}, -800, 0, 0, 1.0f, 255, {"test"}, 0);
        }
};

class GameObjectTest : public GameObject{
    public:
        GameObjectTest():
            GameObject()
        {}

        void onCreate(){
            GameObjectsManager::addComponent(std::make_unique<Test>(this),this);
        }
        void onLoop(){
            GraphicsManager::drawTexturePart("test2",-1000,50,0,0,32,32,1.0f,1.0f,255,0,{"test"},0);
            GraphicsManager::drawText({std::to_string(components.size())},-1000,0,0,1.0f,255,{"test"},0);
            GameObject::onLoop();
        }
};

int main(){
    #ifdef PLATFORM_PSVITA
        vita2d_init();
        MemoryManager::storeData("test2",TEXTURE);
        std::unique_ptr<GameObject> test = std::make_unique<GameObjectTest>();
        GameObjectsManager::addChild(std::move(test),GameObjectsManager::getMothernode());
        GraphicsManager::addCamera("test",-1200,0,-200,0,400,240);
        while(true){
            MemoryManager::readPipelines();
            GameObjectsManager::getMothernode()->loop();
            GraphicsManager::executeGraphicPipeline();
            ErrorHandler::manageErrors();  
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

        MemoryManager::storeData("test2",TEXTURE);
        std::unique_ptr<GameObject> test = std::make_unique<GameObjectTest>();
        GameObjectsManager::addChild(std::move(test),GameObjectsManager::getMothernode());
        GraphicsManager::addCamera("test",-1200,0,-200,0,400,240);
        while (aptMainLoop())
        {
            MemoryManager::readPipelines();
            GameObjectsManager::getMothernode()->loop();
            GraphicsManager::executeGraphicPipeline();
            ErrorHandler::manageErrors();
        }
        romfsExit();
        C2D_Fini();
        C3D_Fini();
        gfxExit();
    #endif
    return 0;
}