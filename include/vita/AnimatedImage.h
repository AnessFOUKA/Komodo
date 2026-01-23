#ifndef ANIMATEDIMAGE_H
#define ANIMATEDIMAGE_H
#include "Game.h"
struct ImageCoord{
    float x;
    float y;
    float width;
    float height;
    float frameTimeIndex;
    float frameTimeMax;
};
class AnimatedImage : public GameObject{
    protected:
        std::string imgId;
        float x;
        float y;
        std::vector<ImageCoord> imageCoords;
        float imageCoordsIndex;
        float animationSpeed;
        float width;
        float height;
        float scaleX;
        float scaleY;
    public:
        AnimatedImage(std::string imgId,float x,float y,std::vector<ImageCoord> imageCoords,float imageCoordsIndex,float animationSpeed,float scaleX,float scaleY,std::vector<std::string> idsList,std::vector<std::string> scriptsIds):
            imgId(imgId),
            x(x),
            y(y),
            imageCoords(imageCoords),
            imageCoordsIndex(imageCoordsIndex),
            animationSpeed(animationSpeed),
            width(imageCoords[imageCoordsIndex].width),
            height(imageCoords[imageCoordsIndex].height),
            scaleX(scaleX),
            scaleY(scaleY),
            GameObject(idsList,scriptsIds)
        {}
        std::string getImgId();
        float getX();
        float getY();
        float getWorldX();
        float getWorldY();
        std::vector<ImageCoord>* getImageCoords();
        float getImageCoordsIndex();
        float getAnimationSpeed();
        float getWidth();
        float getHeight();
        float getScaleX();
        float getScaleY();

        void setScaleX(float scaleX);
        void setScaleY(float scaleY);
        void setImgId(std::string imgId);
        void setX(float x);
        void setY(float y);
        void setImageCoords(std::vector<ImageCoord> imageCoords);
        void setImageCoordsIndex(float imageCoordsIndex);
        void setAnimationSpeed(float animationSpeed);


        void step();
    
};
#endif