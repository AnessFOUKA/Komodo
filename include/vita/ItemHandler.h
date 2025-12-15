#ifndef ITEMHANDLER_H
#define ITEMHANDLER_H
#include "Camera.h"

class ItemHandler : public GameObject{
    protected:
        std::vector<std::unique_ptr<GameObject>> elements;
        std::vector<std::unique_ptr<GameObject>> addPipeline;
        std::vector<int> remPipeline;
        void itemRemover(int itemId);
    public: 
        ItemHandler(std::vector<std::string> idsList,std::vector<std::string> scriptsIds):
            GameObject(idsList,scriptsIds)
        {}
        std::vector<std::unique_ptr<GameObject>>* getElements();

        std::vector<std::unique_ptr<GameObject>>* getAddPipeline();
        std::vector<int>* getRemPipeline();
        void readPipelines();
        void step();
        std::vector<GameObject*> getElementById(std::string id);
};  
#endif