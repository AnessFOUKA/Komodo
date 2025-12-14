#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "MemoryManager.h"
class ItemHandler;
class GameObject{
    protected:
        std::vector<std::string> idsList;
        std::vector<std::string> scriptsIds; 
        std::vector<Script> scriptsList;
        //les scripts est ajouté à create
        bool isJustCreated;
        GameObject* mother;
        GameObject* gameInstance;
        int arrayId;
        std::vector<Camera*> cameras;
    public:
        GameObject(std::vector<std::string> idsList,std::vector<std::string> scriptsIds) : 
            idsList(idsList),
            scriptsIds(scriptsIds),
            scriptsList(),
            isJustCreated(false),
            mother(nullptr),
            gameInstance(nullptr),
            arrayId(0),
            cameras({})
        {}
        virtual ~GameObject()=default;
        virtual std::vector<std::string> getIdsList();
        virtual void setIdsList(std::vector<std::string> idsList);
        virtual std::vector<std::string> getScriptsIds();
        virtual bool getIsJustCreated();
        virtual void setIsJustCreated(bool isJustCreated);

        virtual GameObject* getMother();
        virtual void setMother(GameObject* mother);
        virtual GameObject* getGameInstance();
        virtual void setGameInstance(GameObject* gameInstance);
        virtual void addScript(std::string scriptId,MemoryManager* memoryManager);
        virtual void create();
        virtual void step();

        virtual std::vector<Camera*> getCameras();
        virtual void setCameras(std::vector<Camera*> cameras);
        virtual int getArrayId();
        virtual void setArrayId(int arrayId);
        //on inclura pas de setters pour scriptsIds et scriptsList et on inclura pas de getter pour scriptsList pour des raisons de sécurité.
};
#endif