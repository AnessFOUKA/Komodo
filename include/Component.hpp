#ifndef COMPONENT_H
#define COMPONENT_H
#include <stdlib.h>
class GameObject;
class Component{
    protected:
        GameObject* parent;
        size_t arrayId;
    public:
        Component();
        virtual ~Component()=default;

        virtual void onLink(){};
        virtual void onLoop(){};
        virtual void onUnlink(){};
        size_t getArrayId();
        void setArrayId(size_t arrayId);
        GameObject* getParent();
        void setParent(GameObject* parent);
    
};

#endif