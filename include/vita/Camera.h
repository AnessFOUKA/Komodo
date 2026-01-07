#ifndef CAMERA_H
#define CAMERA_H
#include "GameObject.h"
class Camera{
    private:
        std::vector<std::vector<float>> renderers;
        float cameraX;
        float cameraY;
    public:
        Camera(std::vector<std::vector<float>> renderers,float cameraX,float cameraY) :
            renderers(renderers),
            cameraX(cameraX),
            cameraY(cameraY)
        {}
        std::vector<std::vector<float>>* getRenderers();
        float getCameraX();
        float getCameraY();

        void setRenderers(std::vector<std::vector<float>> renderers);
        void setCameraX(float cameraX);
        void setCameraY(float cameraY);

        void pushCameraGraphicOrder(std::string imgId,float x,float y,float imageX,float imageY,float imageWidth,float imageHeight,float scaleX,float scaleY,Game* gameInstance);
};
#endif