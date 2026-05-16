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
        float alpha;
        int layer;
        std::string anchorInfos;
        float globalX;
        float globalY;
        float globalScaleX;
        float globalScaleY;
    public:
        AnimatedImage(
            std::string imgId,
            float x,
            float y,
            std::vector<ImageCoord> imageCoords,
            float imageCoordsIndex,
            float animationSpeed,
            float scaleX,
            float scaleY,
            float alpha,
            int layer,
            std::string anchorInfos,
            std::vector<std::string> idsList,
            std::vector<std::string> scriptsIds
        );
        std::string getImgId();
        float getX();
        float getY();
        float getGlobalX();
        float getGlobalY();
        std::vector<ImageCoord>* getImageCoords();
        float getImageCoordsIndex();
        float getAnimationSpeed();
        float getWidth();
        float getHeight();
        float getScaleX();
        float getScaleY();
        float getAlpha();
        std::string getAnchorInfos();

        void setAlpha(float alpha);

        void setScaleX(float scaleX);
        void setScaleY(float scaleY);
        void setImgId(std::string imgId);
        void setX(float x);
        void setY(float y);
        void setImageCoords(std::vector<ImageCoord> imageCoords);
        void setImageCoordsIndex(float imageCoordsIndex);
        void setAnimationSpeed(float animationSpeed);
        void setAnchorInfos(std::string anchorInfos);
        float getGlobalScaleX();
        float getGlobalScaleY();
        void step();
        void init();
    
};
#endif