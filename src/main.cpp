#include "Engine.h"
#include "Commander.h"
#include "Apple.h"
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
    g1.getMemoryManager()->addScript("Follower",std::make_unique<Script>([](Script* script){
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

    g1.getMemoryManager()->addScript("MapScript",std::make_unique<Script>([&g1,&randX,&randY,&gen](Script* script){
        if(script->checkCondition(0)){
            g1.addItem(std::make_unique<Apple>("app0:/assets/spritesheet.png",randX(gen),randY(gen),std::vector<std::vector<float>>{{10,47,18,18}},0,0,1,1,std::vector<std::string>{"Enemy"},std::vector<std::string>{"Apple"}),static_cast<ItemHandler*>(script->getMother()));
            std::unique_ptr<Commander> commander=std::make_unique<Commander>("app0:/assets/spritesheet.png",0,0,std::vector<std::vector<float>>{{10,5,18,18}},0,0,1,1,std::vector<std::string>{},std::vector<std::string>{"Commander","Follower"});
            std::unique_ptr<Node> Follower=std::make_unique<Node>("app0:/assets/spritesheet.png",0,0,std::vector<std::vector<float>>{{10,26,18,18}},0,0,1,1,std::vector<std::string>{"Follower","Node"},std::vector<std::string>{"Follower"});
            commander->getLastNode()->setFollower(Follower.get());
            commander->setLastNode(Follower.get());
            g1.addItem(std::move(commander),static_cast<Map*>(script->getMother()));
            g1.addItem(std::move(Follower),static_cast<Map*>(script->getMother()));
        }
        vita2d_draw_rectangle(0,0,960,544,RGBA8(255,255,255,255)); 
        vita2d_pvf_draw_text(g1.getPvf(),800,50,RGBA8(0,0,0,255),1.0f,std::to_string(static_cast<Map*>(script->getMother())->getScore()).c_str());
        vita2d_pvf_draw_text(g1.getPvf(),800,200,RGBA8(0,0,0,255),1.0f,std::to_string(static_cast<Map*>(script->getMother())->getHeight()).c_str());
    },0,1,0,false));
    g1.getMemoryManager()->getScript("MapScript")->createCondition(0);

    g1.getMemoryManager()->addScript("gameOverScreenScript",std::make_unique<Script>([&g1,&randX,&randY,&gen](Script* script){
        vita2d_draw_rectangle(0,0,960,544,RGBA8(255,255,255,255));
        vita2d_pvf_draw_text(g1.getPvf(),420,200,RGBA8(0,0,0,255),1.0f,"Game over !");
        if(g1.getMainInputManager()->checkClicked("cross")){
            g1.removeItem(0,&g1);
            g1.addItem(std::make_unique<Map>(0,0,std::vector<std::string>{"map"},std::vector<std::string>{"MapScript"}),&g1);
        }
    },0,1,0,false));

    g1.getMemoryManager()->addScript("Apple",std::make_unique<Script>([&g1,&randX,&randY,&gen](Script* script){
        Apple* target=static_cast<Apple*>(script->getMother());
        target->getCollider()->setX(target->getX());
        target->getCollider()->setY(target->getY());
        target->getCollider()->setWidth(target->getWidth());
        target->getCollider()->setHeight(target->getHeight());
    },0,1,0,false));

    g1.getMemoryManager()->addScript("Commander",std::make_unique<Script>([&g1,&randX,&randY,&gen](Script* script){
        Commander* target=static_cast<Commander*>(script->getMother());
        target->getCollider()->setX(target->getX());
        target->getCollider()->setY(target->getY());
        target->getCollider()->setWidth(target->getWidth());
        target->getCollider()->setHeight(target->getHeight());
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
                g1.addItem(std::make_unique<ItemHandler>(0,0,std::vector<std::string>{"gameOverScreen"},std::vector<std::string>{"gameOverScreenScript"}),&g1);
                target->setGameOver(true);
            }
        }

        std::vector<GameObject*> Apples=playerItemHandler->getElementById("Enemy");
        if(Apples.size()>0){
            Apple* apple=static_cast<Apple*>(Apples[0]);
            if(target->getCollider()->checkCollision(apple->getCollider()).collideTrue){
                g1.addItem(std::make_unique<Apple>("app0:/assets/spritesheet.png",randX(gen),randY(gen),std::vector<std::vector<float>>{{10,47,18,18}},0,0,1,1,std::vector<std::string>{"Enemy"},std::vector<std::string>{"Apple"}),playerItemHandler);
                g1.removeItem(apple->getArrayId(),static_cast<Map*>(apple->getMother()));
                std::unique_ptr<Node> Follower=std::make_unique<Node>("app0:/assets/spritesheet.png",target->getLastNode()->getX(),target->getLastNode()->getY(),std::vector<std::vector<float>>{{10,26,18,18}},0,0,1,1,std::vector<std::string>{"Follower","Node"},std::vector<std::string>{"Follower"});
                target->getLastNode()->setFollower(Follower.get());
                target->setLastNode(Follower.get());
                g1.addItem(std::move(Follower),playerItemHandler);
                playerItemHandler->setScore(playerItemHandler->getScore()+1);
            }
        }

    },0,1,0,false));

    g1.getMemoryManager()->addScript("MenuScript",std::make_unique<Script>([&g1](Script* script){
        if(g1.getMainInputManager()->checkClicked("cross")){
            g1.removeItem(0,&g1);
            g1.addItem(std::make_unique<Map>(0,0,std::vector<std::string>{"map"},std::vector<std::string>{"MapScript"}),&g1);
        }
        vita2d_draw_rectangle(0,0,960,544,RGBA8(255,255,255,255));
        vita2d_pvf_draw_text(g1.getPvf(),420,200,RGBA8(0,0,0,255),1.0f,"Snake !");
    },0,1,0,false));

    Camera c1({{0,0,960,544}},0,0);
    g1.getMemoryManager()->addImg("app0:/assets/spritesheet.png");
    g1.setCameras({&c1});
    g1.addItem(std::make_unique<ItemHandler>(0,0,std::vector<std::string>{"Menu"},std::vector<std::string>{"MenuScript"}),&g1);
    g1.gameLoop();
    return 0;
}

/*
organisation :

classe Collider:
	-x
	-y 
	-width
	-heigth
	-checkCollision(Collider* collider) -> struct{up:bool,down:bool,left:bool,right:bool,contact:bool}
chaque instance de collider est stockée dans une liste de colliders dans un gameObject
*/