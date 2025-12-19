#ifndef APPLE_H
#define APPLE_H
#include "AnimatedImage.h"
class Apple : public AnimatedImage{
    private:
        Collider collider;
    public:
        Apple(std::string imgId,int x,int y,std::vector<std::vector<float>> imageCoords,float imageCoordsIndex,float animationSpeed,std::vector<std::string> idsList,std::vector<std::string> scriptsIds):
            AnimatedImage(imgId,x,y,imageCoords,imageCoordsIndex,animationSpeed,idsList,scriptsIds),
            collider(x,y,width,height)
        {}
        Collider* getCollider();
        void setCollider(Collider collider);
};
#endif