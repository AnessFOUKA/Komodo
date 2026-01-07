#ifndef GAME_H
#define GAME_H
#include "ItemHandler.h"
using high_resolution_clock=std::chrono::high_resolution_clock;

struct GraphicOrder{
    float x;
    float y;
    float imageX;
    float imageY;
    float imageWidth;
    float imageHeight;
    float scaleX;
    float scaleY;
};

class Game : public ItemHandler{
    protected:
        MemoryManager mainMemoryManager;
        InputManager mainInputManager;
        std::unordered_map<std::string,std::vector<GraphicOrder>> graphicPipeline;
        std::vector<std::string> imgIds;
        high_resolution_clock::time_point previousTime;
        float dt;
        vita2d_pvf* pvf;
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
        vita2d_pvf* getPvf();
        MemoryManager* getMemoryManager();
        InputManager* getMainInputManager();
        std::unordered_map<std::string,std::vector<GraphicOrder>>* getGraphicPipeline();
        void addGraphicOrder(std::string imgId,float x,float y,float imageX,float imageY,float imageWidth,float imageHeight,float scaleX,float scaleY);
        void readGraphicPipeline();
        void gameLoop();
        void addItem(std::unique_ptr<GameObject> newObject,ItemHandler* itemHandler);
        void removeItem(int index,ItemHandler* itemHandler);
        float getDt();
};
#endif