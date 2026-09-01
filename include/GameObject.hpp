#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <string>
#include <algorithm>
#include "Hyerarchy.hpp"
#include "Component.hpp"

class GameObject{
    protected:
        std::vector<std::string> ids;
        std::vector<std::unique_ptr<Component>> components;
        ObjectManagementPipeline<GameObject> objectsPipeline;
        ObjectManagementPipeline<Component> componentPipeline;
        Hyerarchy hyerarchy;
        size_t arrayId;

    public:
        GameObject():
            components(),
            objectsPipeline(),
            componentPipeline(),
            hyerarchy(),
            arrayId(0)

        {
        }

        virtual ~GameObject()=default;

        std::vector<std::string>* getIds();
        std::vector<std::unique_ptr<Component>>* getComponents();
        ObjectManagementPipeline<Component>* getComponentPipeline();
        ObjectManagementPipeline<GameObject>* getObjectsPipeline();
        
        size_t getArrayId();
        void setArrayId(size_t arrayId);
        Hyerarchy* getHyerarchy();

        virtual void onCreate();
        virtual void onLoop();
        virtual void onRemove();

        void manageComponentsPipeline();

        void updateComponentsArrayIds();

        void manageObjectsPipeline();

        void updateObjectsArrayIds();

        void loop();

};

#endif


