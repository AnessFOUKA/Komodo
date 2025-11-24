#include "Engine.h"
int main(){
    Game g1({},{},{
        {"cross",SCE_CTRL_CROSS}
    });
    Camera c1({{0,0,200,544}},0,0);
    g1.getMemoryManager()->addImg("app0:/assets/image.png");

    g1.getMemoryManager()->addScript("testb",new Script([&g1,&c1](Script* script){
        if(script->getIndex()==0.0f){
            script->getMother()->setCameras({&c1});
            g1.addItem(new AnimatedImage("app0:/assets/image.png",0,0,{{0,0,400,300},{0,0,200,300},{0,0,200,300}},0,1,2,2,{},{}),static_cast<ItemHandler*>(script->getMother()));
        }
    },0.0f,1.0f,1.0f,false));
    g1.addItem(new ItemHandler({},{"testb"}),&g1);
    g1.gameLoop();
    return 0;
}


//KOMODO !!!!!