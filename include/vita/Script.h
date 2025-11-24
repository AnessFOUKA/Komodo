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
    public:
        Script(std::function<void(Script*)> scriptFunction,float beginIndex,float endIndex,float scriptSpeed,bool loop) :
            scriptFunction(scriptFunction),
            beginIndex(beginIndex),
            index(beginIndex),
            endIndex(endIndex),
            scriptSpeed(scriptSpeed),
            loop(loop),
            mother(mother)
        {}

        std::function<void(Script*)> getScriptFunction();
        float getBeginIndex();
        float getIndex();
        float getEndIndex();
        bool getLoop();
        GameObject* getMother();
        float getScriptSpeed();

        void setScriptFunction(std::function<void(Script*)> scriptFunction);
        void setBeginIndex(float beginIndex);
        void setIndex(float index);
        void setEndIndex(float endIndex);
        void setLoop(bool loop);
        void setMother(GameObject* mother);
        void setScriptSpeed(float scriptSpeed);

        void loadScript();
};
#endif