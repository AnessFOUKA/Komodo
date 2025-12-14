#ifndef ITEMHANDLER_H
#define ITEMHANDLER_H
#include "Camera.h"
class ItemHandler : public GameObject{
    protected:
        std::vector<GameObject*> elements;
        std::vector<std::function<void()>> addPipeline;
        std::vector<int> remPipeline;
        void itemRemover(int itemId);
    public: 
        ItemHandler(std::vector<std::string> idsList,std::vector<std::string> scriptsIds):
            GameObject(idsList,scriptsIds),
            elements({})
        {}
        std::vector<GameObject*>* getElements();
        void setElements(std::vector<GameObject*> elements);

        std::vector<std::function<void()>>* getAddPipeline();
        std::vector<int>* getRemPipeline();
        void readPipelines();
        void step();
        std::vector<GameObject*> getElementById(std::string id);
};  
#endif