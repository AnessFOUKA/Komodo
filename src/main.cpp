#include "Engine.h"
#include "Commander.h"
#include "Map.h"
#include <fstream>
#include <random>
int main(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution randX(0,800);
    std::uniform_int_distribution randY(0,400);
    Game g1({},{},{
        {"up",SCE_CTRL_UP},
        {"down",SCE_CTRL_DOWN},
        {"left",SCE_CTRL_LEFT},
        {"right",SCE_CTRL_RIGHT},
        {"cross",SCE_CTRL_CROSS},
        {"square",SCE_CTRL_SQUARE},
        {"circle",SCE_CTRL_CIRCLE},
        {"triangle",SCE_CTRL_TRIANGLE}
    });
    
    g1.getMemoryManager()->addScript("Follower",new Script([](Script* script){
        Node* target=static_cast<Node*>(script->getMother());
        if(target->getFollower()!=nullptr){
            target->getFollower()->setRecordPositions(target->getRecordPositions());
            if(target->getRecordPositions()){
                target->getFollower()->getPositions()->push_back(*(target->getSpeedVector()));
            }
        }
        std::vector<SpeedVector>* positions=target->getPositions();
        int positionsSize=positions->size();
        if(positionsSize>=8){
            target->setSpeedVector((*positions)[positionsSize-7]);
        }
        if(positionsSize>=16){
            positions->assign(positions->begin()+8,positions->begin()+16);
        }
        target->setX(target->getX()+target->getSpeedVector()->x);
        target->setY(target->getY()+target->getSpeedVector()->y);
    },0,1,0,false));

    g1.getMemoryManager()->addScript("MapScript",new Script([&g1,&randX,&randY,&gen](Script* script){
        if(script->checkCondition(0)){
            g1.addItem(new AnimatedImage("app0:/assets/spritesheet.png",randX(gen),randY(gen),{{10,47,18,18}},0,0,{"Enemy"},{}),static_cast<ItemHandler*>(script->getMother()));
            Commander* commander=new Commander("app0:/assets/spritesheet.png",0,0,{{10,5,18,18}},0,0,{},{"Commander","Follower"});
            g1.addItem(commander,static_cast<Map*>(script->getMother()));
            
            Node* Follower=new Node("app0:/assets/spritesheet.png",0,0,{{10,26,18,18}},0,0,{"Follower","Node"},{"Follower"});
            commander->getLastNode()->setFollower(Follower);
            commander->setLastNode(Follower);
            g1.addItem(Follower,static_cast<Map*>(script->getMother()));
        }
        vita2d_draw_rectangle(0,0,960,544,RGBA8(255,255,255,255)); 
        vita2d_pvf_draw_text(g1.getPvf(),800,50,RGBA8(0,0,0,255),1.0f,std::to_string(static_cast<Map*>(script->getMother())->getScore()).c_str());
    },0,1,0,false));
    g1.getMemoryManager()->getScript("MapScript")->createCondition(0);

    g1.getMemoryManager()->addScript("gameOverScreenScript",new Script([&g1,&randX,&randY,&gen](Script* script){
        vita2d_draw_rectangle(0,0,960,544,RGBA8(255,255,255,255));
        vita2d_pvf_draw_text(g1.getPvf(),420,200,RGBA8(0,0,0,255),1.0f,"Game over !");
        if(g1.getMainInputManager()->checkClicked("cross")){
            g1.removeItem(0,&g1);
            g1.addItem(new Map({"map"},{"MapScript"}),&g1);
        }
    },0,1,0,false));

    g1.getMemoryManager()->addScript("Commander",new Script([&g1,&randX,&randY,&gen](Script* script){
        Commander* target=static_cast<Commander*>(script->getMother());
        Game* gameInstance=static_cast<Game*>(target->getGameInstance());
        std::unordered_map<std::string,SpeedVector> directions={
            {"left",{-300.0f*gameInstance->getDt(),0}},
            {"right",{+300.0f*gameInstance->getDt(),0}},
            {"up",{0,-300.0f*gameInstance->getDt()}},
            {"down",{0,+300.0f*gameInstance->getDt()}}
        };
        for(auto& [key,speedVector] : directions){
            if(g1.getMainInputManager()->checkPressed(key)){
                target->setSpeedVector(speedVector);
            }
        }
        Map* playerItemHandler=static_cast<Map*>(target->getMother());

        std::vector<GameObject*> Followers=playerItemHandler->getElementById("Node");
        for(GameObject* i:Followers){
            Node* follower=static_cast<Node*>(i); 
            if(detectInbound(target->getX()+5,target->getY()+5,target->getWidth()-5,target->getHeight()-5,follower->getX()+5,follower->getY()+5,follower->getWidth()-5,follower->getHeight()-5)&&playerItemHandler->getScore()>0&&!target->getGameOver()){
                g1.removeItem(0,&g1);
                g1.addItem(new ItemHandler({"gameOverScreen"},{"gameOverScreenScript"}),&g1);
                target->setGameOver(true);
            }
        }

        std::vector<GameObject*> Apples=playerItemHandler->getElementById("Enemy");
        if(Apples.size()>0){
            AnimatedImage* Apple=static_cast<AnimatedImage*>(Apples[0]);
            if(detectInbound(target->getX(),target->getY(),target->getWidth(),target->getHeight(),Apple->getX(),Apple->getY(),Apple->getWidth(),Apple->getHeight())){
                g1.addItem(new AnimatedImage("app0:/assets/spritesheet.png",randX(gen),randY(gen),{{10,47,18,18}},0,0,{"Enemy"},{}),playerItemHandler);
                g1.removeItem(Apple->getArrayId(),static_cast<Map*>(Apple->getMother()));
                Node* Follower=new Node("app0:/assets/spritesheet.png",target->getLastNode()->getX(),target->getLastNode()->getY(),{{10,26,18,18}},0,0,{"Follower","Node"},{"Follower"});
                target->getLastNode()->setFollower(Follower);
                target->setLastNode(Follower);
                g1.addItem(Follower,playerItemHandler);
                playerItemHandler->setScore(playerItemHandler->getScore()+1);
            }
        }

    },0,1,0,false));

    g1.getMemoryManager()->addScript("MenuScript",new Script([&g1](Script* script){
        if(g1.getMainInputManager()->checkClicked("cross")){
            g1.removeItem(0,&g1);
            g1.addItem(new Map({"map"},{"MapScript"}),&g1);
        }
        vita2d_draw_rectangle(0,0,960,544,RGBA8(255,255,255,255));
        vita2d_pvf_draw_text(g1.getPvf(),420,200,RGBA8(0,0,0,255),1.0f,"Snake !");
    },0,1,0,false));

    Camera c1({{0,0,960,544}},0,0);
    g1.getMemoryManager()->addImg("app0:/assets/spritesheet.png");
    g1.setCameras({&c1});
    g1.addItem(new ItemHandler({"Menu"},{"MenuScript"}),&g1);
    g1.gameLoop();
    return 0;
}