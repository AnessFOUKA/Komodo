#ifndef CAMERA_H
#define CAMERA_H
#include "GameObject.h"
class Camera{
    private:
        std::vector<std::vector<int>> renderers;
        int cameraX;
        int cameraY;
    public:
        Camera(std::vector<std::vector<int>> renderers,int cameraX,int cameraY) :
            renderers(renderers),
            cameraX(cameraX),
            cameraY(cameraY)
        {}
        std::vector<std::vector<int>> getRenderers();
        int getCameraX();
        int getCameraY();

        void setRenderers(std::vector<std::vector<int>> renderers);
        void setCameraX(int cameraX);
        void setCameraY(int cameraY);

        void pushCameraGraphicOrder(std::string imgId,int x,int y,int imageX,int imageY,int imageWidth,int imageHeigth,float scaleX,float scaleY,GameObject* gameInstance);
};
#endif