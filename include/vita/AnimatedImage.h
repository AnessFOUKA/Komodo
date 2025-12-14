#ifndef ANIMATEDIMAGE_H
#define ANIMATEDIMAGE_H
#include "Game.h"
class AnimatedImage : public GameObject{
    protected:
        std::string imgId;
        float x;
        float y;
        std::vector<std::vector<int>> imageCoords;
        float imageCoordsIndex;
        float animationSpeed;
        float width;
        float height;
    public:
        AnimatedImage(std::string imgId,int x,int y,std::vector<std::vector<int>> imageCoords,float imageCoordsIndex,float animationSpeed,std::vector<std::string> idsList,std::vector<std::string> scriptsIds):
            imgId(imgId),
            x(x),
            y(y),
            imageCoords(imageCoords),
            imageCoordsIndex(imageCoordsIndex),
            animationSpeed(animationSpeed),
            width(imageCoords[imageCoordsIndex][2]),
            height(imageCoords[imageCoordsIndex][3]),
            GameObject(idsList,scriptsIds)
        {}
        std::string getImgId();
        float getX();
        float getY();
        std::vector<std::vector<int>> getImageCoords();
        float getImageCoordsIndex();
        float getAnimationSpeed();
        float getWidth();
        float getHeight();


        void setImgId(std::string imgId);
        void setX(float x);
        void setY(float y);
        void setImageCoords(std::vector<std::vector<int>> imageCoords);
        void setImageCoordsIndex(float imageCoordsIndex);
        void setAnimationSpeed(float animationSpeed);


        void step();
    
};
#endif