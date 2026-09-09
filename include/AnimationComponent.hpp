#ifndef ANIMATIONCOMPONENT_H

#include "Component.hpp"
#include "Komodo.hpp"

struct AnimationFrame{
    float imageX;
    float imageY;
    float imageWidth;
    float imageHeight;
    float endFrameTime;
    float frameTimer=0;
};

class AnimationComponent : public Component{
    private:
        std::string texturePath;
        std::vector<std::string> cam_ids;
        std::vector<AnimationFrame> frames;
        float frameIndex;
        float animationSpeed;
        float x;
        float y;
        float scaleX;
        float scaleY;
        float alpha;
        int layer;
        size_t screenIndex;
        Anchor anchor;
    public:
        AnimationComponent(std::string texturePath, std::vector<AnimationFrame> frames, float animationSpeed, float x, float y, float scaleX, float scaleY, float alpha, int layer, Anchor anchor, std::vector<std::string> cam_ids, size_t screenIndex=0):
            texturePath(texturePath),
            cam_ids(cam_ids),
            frames(frames),
            frameIndex(0),
            animationSpeed(animationSpeed),
            x(x),
            y(y),
            scaleX(scaleX),
            scaleY(scaleY),
            alpha(alpha),
            layer(layer),
            screenIndex(screenIndex),
            anchor(anchor)
        {}

        std::vector<AnimationFrame>* getFrames();
        std::string getTexturePath();
        std::vector<std::string>* getCamIds();
        float getFrameIndex();
        float getAnimationSpeed();
        float getX();
        float getY();
        float getScaleX();
        float getScaleY();
        float getAlpha();
        int getLayer();
        size_t getScreenIndex();
        Anchor getAnchor();

        void setTexturePath(std::string texturePath);
        void setFrameIndex(float frameIndex);
        void setAnimationSpeed(float animationSpeed);
        void setX(float x);
        void setY(float y);
        void setScaleX(float scaleX);
        void setScaleY(float scaleY);
        void setAlpha(float alpha);
        void setLayer(int layer);
        void setScreenIndex(size_t screenIndex);
        void setAnchor(Anchor anchor);

        void onLoop();
};

#endif