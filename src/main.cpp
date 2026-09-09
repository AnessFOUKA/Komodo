#include "AnimationComponent.hpp"
#include "GameObject.hpp"
#include "GraphicsManager.hpp"
#include "GameObjectsManager.hpp"
#include "Collider.hpp"

class Test : public Component{
    public:
        Test()
        {}

        void onLink(){}
        void onUnlink(){}
        void onLoop(){
            //auto stick=ControllersManager::getKeyState("std_controller","stick");
            auto dpad=ControllersManager::getKeyDown("std_controller","3ds_a");

            Collider collider(0,0,60,60);
            Collider collider2(60,60,60,60);
            if(collider.checkCollision(&collider2).collisionType==NULL_COLLISION){
                GraphicsManager::drawText({"aaaaaaa"},-1000,0,3,1.0f,255,{"test"},0);
            }
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
            GameObjectsManager::addComponent(std::make_unique<Test>(),this);
            
            GameObjectsManager::addComponent(std::make_unique<AnimationComponent>("test2",std::vector<AnimationFrame>{(AnimationFrame){
                .imageX=0,
                .imageY=0,
                .imageWidth=32,
                .imageHeight=32,
                .endFrameTime=1
            },
            (AnimationFrame){
                .imageX=0,
                .imageY=0,
                .imageWidth=20,
                .imageHeight=20,
                .endFrameTime=1
            }
        },1,-1000,50,1.0f,1.0f,255,0,ANCHOR_LEFT,std::vector<std::string>{"test"}),this);
        }
        void onLoop(){
            //GraphicsManager::drawTexturePart("test2",-1000,50,0,0,32,32,1.0f,1.0f,255,0,ANCHOR_LEFT,{"test"},0);
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