#include "Komodo.hpp"
#include "GameObject.hpp"
#include "GraphicsManager.hpp"
#include "GameObjectsManager.hpp"

class Test : public Component{
    public:
        Test(GameObject* parent):
            Component(parent)
        {}

        void onLink(){}
        void onUnlink(){}
        void onLoop(){
            //auto stick=ControllersManager::getKeyState("std_controller","stick");
            auto dpad=ControllersManager::getKeyDown("std_controller","3ds_a");
            //auto touch=ControllersManager::getKeyState("std_controller","touchScreen");
            if(dpad!=nullptr){
                GraphicsManager::drawText({
                    std::to_string((*dpad)[0])+" "+std::to_string((*dpad)[1])
                }, -800, 0, 30, 1.0f, 255, {"test"}, 0);  
            }
            
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

    Komodo::init();
    GraphicsManager::addCamera("test",-1000,0,0,0,400,400);
    MemoryManager::storeData("test2",TEXTURE);
    GameObjectsManager::addChild(std::make_unique<GameObjectTest>(),GameObjectsManager::getMothernode());
    Komodo::gameloop();
    Komodo::fini();

    return 0;
}