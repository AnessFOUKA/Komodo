#include <Komodo.hpp>
#include "AnimationComponent.hpp"

class Test : public GameObject{
    public:
        Test():
            GameObject()
        {
            MemoryManager::storeData("test2",TEXTURE);
            GameObjectsManager::addComponent(std::make_unique<AnimationComponent>("test2",std::vector<AnimationFrame>{{0,0,32,32,1}},0.0f,0,0,1.0f,1.0f,255,0,ANCHOR_CENTER,ANCHOR_CENTER,std::vector<std::string>{"std_cam"},1),this);
        }

        void onLoop(){
            GraphicsManager::drawTexturePart("test2",0,0,0,0,32,32,1.0f,1.0f,255,0,ANCHOR_CENTER,ANCHOR_CENTER,{"std_cam"},0);
        }
};

int main(){
    Komodo::init();
    GameObjectsManager::addChild(std::make_unique<Test>(),GameObjectsManager::getMothernode());
    Komodo::gameloop();
    Komodo::fini();
    return 0;
}