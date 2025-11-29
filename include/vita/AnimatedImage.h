#ifndef ANIMATEDIMAGE_H
#define ANIMATEDIMAGE_H
#include "Game.h"
class AnimatedImage : public GameObject{
    protected:
        std::string imgId;
        int x;
        int y;
        std::vector<std::vector<int>> imageCoords;
        float imageCoordsIndex;
        float animationSpeed;
    public:
        AnimatedImage(std::string imgId,int x,int y,std::vector<std::vector<int>> imageCoords,float imageCoordsIndex,float animationSpeed,std::vector<std::string> idsList,std::vector<std::string> scriptsIds):
            imgId(imgId),
            x(x),
            y(y),
            imageCoords(imageCoords),
            imageCoordsIndex(imageCoordsIndex),
            animationSpeed(animationSpeed),
            GameObject(idsList,scriptsIds)
        {}
        std::string getImgId();
        int getX();
        int getY();
        std::vector<std::vector<int>> getImageCoords();
        float getImageCoordsIndex();
        float getAnimationSpeed();


        void setImgId(std::string imgId);
        void setX(int x);
        void setY(int y);
        void setImageCoords(std::vector<std::vector<int>> imageCoords);
        void setImageCoordsIndex(float imageCoordsIndex);
        void setAnimationSpeed(float animationSpeed);


        void step();
    
};
#endif