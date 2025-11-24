#ifndef GAME_H
#define GAME_H
#include "ItemHandler.h"
using high_resolution_clock=std::chrono::high_resolution_clock;
class Game : public ItemHandler{
    protected:
        MemoryManager mainMemoryManager;
        InputManager mainInputManager;
        std::map<std::string,std::vector<std::function<void()>>> graphicPipeline;
        std::vector<std::string> imgIds;
        high_resolution_clock::time_point previousTime;
        float dt;
    public:
        Game(std::vector<std::string> idsList,std::vector<std::string> scriptsIds,std::map<std::string,uint32_t> keys):
            ItemHandler(idsList,scriptsIds),
            mainMemoryManager(),
            mainInputManager(keys),
            graphicPipeline({}),
            imgIds({}),
            previousTime(high_resolution_clock::now()),
            dt(0.0f)
        {}
        MemoryManager* getMemoryManager();
        InputManager* getMainInputManager();
        std::map<std::string,std::vector<std::function<void()>>> getGraphicPipeline();
        void addGraphicOrder(std::string imgId,int x,int y,int imageX,int imageY,int imageWidth,int imageHeigth,float scaleX,float scaleY);
        void readGraphicPipeline();
        void gameLoop();
        void addItem(GameObject* newObject,ItemHandler* itemHandler);
        void removeItem(int index,ItemHandler* itemHandler);
        float getDt();
};
#endif