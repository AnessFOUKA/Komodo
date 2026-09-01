#ifndef HYERARCHY_H
#define HYERARCHY_H

#include <vector>
#include <memory>

template<typename Type>
struct ObjectManagementPipeline{
    std::vector<std::unique_ptr<Type>> add;
    std::vector<Type*> rem;
};

class GameObject;
class Hyerarchy{
    std::vector<std::unique_ptr<GameObject>> childs;
    GameObject* parent;
    public:
        Hyerarchy();

        std::vector<std::unique_ptr<GameObject>>* getChilds();

        GameObject* getParent();
        void setParent(GameObject* parent);

        void manageChilds();

};

#endif