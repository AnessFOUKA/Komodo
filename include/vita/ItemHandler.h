#ifndef ITEMHANDLER_H
#define ITEMHANDLER_H
#include "Camera.h"

struct getFileJSONReturn{
    json success;
    bool error;
};

class ItemHandler : public GameObject{
    protected:
        std::vector<std::unique_ptr<GameObject>> elements;
        std::vector<std::unique_ptr<GameObject>> addPipeline;
        std::vector<int> remPipeline;
        float x;
        float y;
    public: 
        ItemHandler(float x,float y,std::vector<std::string> idsList,std::vector<std::string> scriptsIds):
            GameObject(idsList,scriptsIds),
            x(x),
            y(y)
        {}
        std::vector<std::unique_ptr<GameObject>>* getElements();

        std::vector<std::unique_ptr<GameObject>>* getAddPipeline();
        std::vector<int>* getRemPipeline();
        void readPipelines();
        void step();
        std::vector<GameObject*> getElementById(std::string id);
        float getX();
        float getY();
        void setX(float x);
        void setY(float y);
        float getWidth();
        float getHeight();
        getFileJSONReturn getFileJSON(std::string filename);
        void injectJson(
            std::string filename,
            std::map<std::string,std::function<std::unique_ptr<GameObject>(json*)>> callbackMap,
            ItemHandler* itemHandler,
            json* jsonToInject
        );
};  
#endif