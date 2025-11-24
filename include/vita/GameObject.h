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
        std::vector<Camera*> cameras;
    public:
        GameObject(std::vector<std::string> idsList,std::vector<std::string> scriptsIds) : 
            idsList(idsList),
            scriptsIds(scriptsIds),
            scriptsList(),
            isJustCreated(false),
            mother(nullptr),
            gameInstance(nullptr),
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
        
        virtual std::vector<GameObject*>* getElements();
        virtual void setElements(std::vector<GameObject*> elements);

        virtual std::vector<std::function<void()>>* getAddPipeline();
        virtual std::vector<int>* getRemPipeline();

        virtual void readPipelines();

        virtual MemoryManager* getMemoryManager();

        virtual void gameLoop();

        virtual void addItem(GameObject* newObject,ItemHandler* itemHandler);
        virtual void removeItem(int index,ItemHandler* itemHandler);
        virtual std::map<std::string,std::vector<std::function<void()>>> getGraphicPipeline();
        virtual void addGraphicOrder(std::string imgId,int x,int y,int imageX,int imageY,int imageWidth,int imageHeigth,float scaleX,float scaleY);
        virtual void readGraphicPipeline();

        virtual std::string getImgId();
        virtual int getX();
        virtual int getY();
        virtual std::vector<std::vector<int>> getImageCoords();
        virtual float getImageCoordsIndex();
        virtual float getAnimationSpeed();
        virtual float getScaleX();
        virtual float getScaleY();

        virtual void setImgId(std::string imgId);
        virtual void setX(int x);
        virtual void setY(int y);
        virtual void setImageCoords(std::vector<std::vector<int>> imageCoords);
        virtual void setImageCoordsIndex(float imageCoordsIndex);
        virtual void setAnimationSpeed(float animationSpeed);
        virtual void setScaleX(float scaleX);
        virtual void setScaleY(float scaleY);
        virtual std::vector<Camera*> getCameras();
        virtual void setCameras(std::vector<Camera*> cameras);
        virtual float getDt();
        //on inclura pas de setters pour scriptsIds et scriptsList et on inclura pas de getter pour scriptsList pour des raisons de sécurité.
};
#endif