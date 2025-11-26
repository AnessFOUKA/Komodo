#ifndef SCRIPT_H
#define SCRIPT_H
#include "InputManager.h"
class Script{
    protected:
        std::function<void(Script*)> scriptFunction;
        float beginIndex;
        float index;
        float endIndex;
        float scriptSpeed;
        bool loop;
        GameObject* mother;
        std::map<int,bool> conditionMap;
    public:
        Script(std::function<void(Script*)> scriptFunction,float beginIndex,float endIndex,float scriptSpeed,bool loop) :
            scriptFunction(scriptFunction),
            beginIndex(beginIndex),
            index(beginIndex),
            endIndex(endIndex),
            scriptSpeed(scriptSpeed),
            loop(loop),
            mother(nullptr),
            conditionMap({})
        {}

        std::function<void(Script*)> getScriptFunction();
        float getBeginIndex();
        float getIndex();
        float getEndIndex();
        bool getLoop();
        GameObject* getMother();
        float getScriptSpeed();
        std::map<int,bool> getConditionMap();

        void setScriptFunction(std::function<void(Script*)> scriptFunction);
        void setBeginIndex(float beginIndex);
        void setIndex(float index);
        void setEndIndex(float endIndex);
        void setLoop(bool loop);
        void setMother(GameObject* mother);
        void setScriptSpeed(float scriptSpeed);
        void setConditionMap(std::map<int,bool> conditionMap);
        
        void createCondition(int conditionIndex);
        bool checkCondition(float conditionIndex);
        void loadScript();
};
#endif