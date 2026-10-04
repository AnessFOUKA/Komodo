#ifndef GAMEOBJECTSMANAGER_H
#define GAMEOBJECTSMANAGER_H

#include "GameObject.hpp"
#include <unordered_map>

class GameObjectsManager{
    
    private:
        static GameObject mothernode;

    public:

        static GameObject* getMothernode();
        static std::unordered_map<std::string, std::vector<GameObject*>>* getIdsMap();
        static void addChild(std::unique_ptr<GameObject> child, GameObject* parent);
        static void remChild(GameObject* child, GameObject* parent);

        static void addComponent(std::unique_ptr<Component> component, GameObject* child);
        static void remComponent(Component* component, GameObject* child);
};

#endif