#ifndef APPLE_H
#define APPLE_H
#include "AnimatedImage.h"
class Apple : public AnimatedImage{
    private:
        Collider collider;
    public:
        Apple(std::string imgId,int x,int y,std::vector<ImageCoord> imageCoords,float imageCoordsIndex,float animationSpeed,float scaleX,float scaleY,std::vector<std::string> idsList,std::vector<std::string> scriptsIds):
            AnimatedImage(imgId,x,y,imageCoords,imageCoordsIndex,animationSpeed,scaleX,scaleY,idsList,scriptsIds),
            collider(x,y,width,height)
        {}
        Collider* getCollider();
        void setCollider(Collider collider);
};
#endif